#include <metagl/metagl.hpp>
#include <iostream>
#include <csignal>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

using namespace metagl;

// Access the internal global table to simulate initialization
namespace metagl::detail {
    struct GlTable;
    extern thread_local struct GlTable g_gl;
}

// Since GlTable is private to Functions.cpp, we can't easily reach it.
// Let's use Initialize with a dummy loader that always returns a non-null no-op function.
void* dummy_loader(const char*) {
    static auto noop = []() { };
    return (void*)+noop; // Convert lambda to function pointer
}

#ifdef _WIN32
// MSVC's std::terminate() ends in abort(), whose exit code depends on the CRT
// build and on WER (3, or 0xC0000409 via __fastfail). The child turns SIGABRT
// into one fixed exit code so the parent can tell "terminated" from "returned".
constexpr int kTerminatedExitCode = 134;

extern "C" void exit_on_abort(int) {
    std::_Exit(kTerminatedExitCode);
}
#endif

// Runs func in a child process and reports whether the child was terminated.
// POSIX forks; Windows has no fork, so it re-runs this executable with
// "--child <name>" and main() dispatches to func there.
bool expect_terminate(const char* name, void (*func)()) {
#ifdef _WIN32
    (void)func;
    char* self = nullptr;
    if (_get_pgmptr(&self) != 0 || self == nullptr) {
        return false;
    }
    // _spawnv does not quote arguments; quote argv[0] so a path with spaces
    // does not shift the child's argv.
    const std::string quoted_self = std::string("\"") + self + "\"";
    const char* args[] = {quoted_self.c_str(), "--child", name, nullptr};
    const std::intptr_t status = _spawnv(_P_WAIT, self, args);
    std::cout << " (exit code " << status << ") ";
    return status == kTerminatedExitCode;
#else
    (void)name;
    pid_t pid = fork();
    if (pid == 0) {
        // Ensure initialized for Debug builds to avoid assert(initialized) failing first
        Initialize(dummy_loader);
        func();
        std::exit(0);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
            int sig = WTERMSIG(status);
            std::cout << " (signal " << sig << ") ";
            // SIGABRT is 6, SIGSEGV is 11
            return sig == SIGABRT || sig == SIGSEGV;
        }
        return false;
    } else {
        return false;
    }
#endif
}

void test_overflow_glsizei() {
    std::size_t huge = static_cast<std::size_t>(2147483647) + 1;
    glGenBuffers(huge, nullptr);
}

void test_invalid_transpose() {
    float matrix[16] = {0};
    glUniformMatrix4fv(UniformLocation{0}, 1, GL_TRUE, matrix);
}

void test_invalid_element_count() {
    float data[3] = {1, 2, 3};
    // glUniform<4> expects multiple of 4 elements
    glUniform<4>(UniformLocation{0}, std::span<const float>{data, 3});
}

struct ContractCase {
    const char* name;
    void (*func)();
};

constexpr ContractCase kCases[] = {
    {"test_overflow_glsizei", test_overflow_glsizei},
    {"test_invalid_transpose", test_invalid_transpose},
    {"test_invalid_element_count", test_invalid_element_count},
};

int main(int argc, char** argv) {
#ifdef _WIN32
    if (argc == 3 && std::strcmp(argv[1], "--child") == 0) {
#ifdef _MSC_VER
        // Keep abort() from popping a dialog or fast-failing past the handler.
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif
        std::signal(SIGABRT, exit_on_abort);
        for (const ContractCase& c : kCases) {
            if (std::strcmp(argv[2], c.name) == 0) {
                Initialize(dummy_loader);
                c.func();
                return 0;
            }
        }
        return 2;
    }
#else
    (void)argc;
    (void)argv;
#endif

    int failed = 0;

    std::cout << "Running Release-contract tests (R10)..." << std::endl;

    for (const ContractCase& c : kCases) {
        if (expect_terminate(c.name, c.func)) {
            std::cout << "PASS: " << c.name << " terminated as expected." << std::endl;
        } else {
            std::cerr << "FAIL: " << c.name << " did NOT terminate." << std::endl;
            failed++;
        }
    }

    if (failed == 0) {
        std::cout << "All Release-contract tests passed!" << std::endl;
    } else {
        std::cerr << failed << " Release-contract test(s) failed." << std::endl;
    }

    return failed;
}
