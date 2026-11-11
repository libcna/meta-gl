#include <metagl/metagl.hpp>
#include <GLES3/gl32.h>

#include <array>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <span>
#include <string>
#include <string_view>

#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#endif

// =============================================================================
// R10 - Release-contract (death) tests
//
// meta-gl terminates on contract violations (Functions.hpp, "Invalid Input
// Contract"). Every wrapper also terminates when meta-gl is not initialized or
// the entry point was not loaded. A death test therefore proves nothing unless
// the child process is *initialized* when it makes the violating call:
// otherwise the call dies for the wrong reason, whatever its arguments.
//
// So every case here runs in a child process that first calls Initialize()
// with a headless mock loader (an "OpenGL ES 3.2" context made of stubs) and
// exits with kInitFailedExitCode if that does not succeed. Each violation has
// a positive control: the same wrapper with valid arguments, which must
// return normally and must reach the mock driver with the expected arguments.
// The pair shows that the violation, and only the violation, terminates.
// =============================================================================

using namespace metagl;

namespace
{
    // ---------------------------------------------------------------------
    // Mock driver
    // ---------------------------------------------------------------------

    // What the last stub received; reset before each case body runs.
    struct Recorded
    {
        const char* function = nullptr;
        GLsizei count = -1;
        GLsizeiptr size = -1;
        GLboolean transpose = 0xFF;
        GLuint program = 0;
        GLint location = -2;
        GLint length = -1;
        GLenum cap = GL_NONE;
    };

    Recorded g_rec;

    const char* g_mock_version = "OpenGL ES 3.2 Mock";
    const char* g_omitted_function = nullptr;

    const GLubyte* GL_APIENTRY stub_GetString(GLenum name)
    {
        static const GLubyte vendor[] = "MockVendor";
        static const GLubyte renderer[] = "MockRenderer";
        static const GLubyte glsl[] = "OpenGL ES GLSL ES 3.20";
        static const GLubyte empty[] = "";
        if (name == GL_VERSION)
            return reinterpret_cast<const GLubyte*>(g_mock_version);
        if (name == GL_VENDOR) return vendor;
        if (name == GL_RENDERER) return renderer;
        if (name == GL_SHADING_LANGUAGE_VERSION) return glsl;
        return empty;
    }

    void GL_APIENTRY stub_GetIntegerv(GLenum pname, GLint* params)
    {
        if (!params) return;
        *params = 0;
        if (pname == GL_MAJOR_VERSION) *params = 3;
        if (pname == GL_MINOR_VERSION) *params = 2;
        if (pname == GL_NUM_EXTENSIONS) *params = 0;
    }

    const GLubyte* GL_APIENTRY stub_GetStringi(GLenum, GLuint)
    {
        static const GLubyte empty[] = "";
        return empty;
    }

    GLenum GL_APIENTRY stub_GetError()
    {
        return GL_NO_ERROR;
    }

    void GL_APIENTRY stub_Enable(GLenum cap)
    {
        g_rec.function = "glEnable";
        g_rec.cap = cap;
    }

    void GL_APIENTRY stub_BlendBarrier()
    {
        g_rec.function = "glBlendBarrier";
    }

    void GL_APIENTRY stub_GenBuffers(GLsizei n, GLuint* buffers)
    {
        g_rec.function = "glGenBuffers";
        g_rec.count = n;
        // Never touch the array for the huge boundary control below.
        if (buffers != nullptr && n > 0 && n <= 16)
            for (GLsizei i = 0; i < n; ++i)
                buffers[i] = static_cast<GLuint>(i + 1);
    }

    void GL_APIENTRY stub_BufferData(
        GLenum, GLsizeiptr size, const void*, GLenum)
    {
        g_rec.function = "glBufferData";
        g_rec.size = size;
    }

    void GL_APIENTRY stub_ShaderSource(
        GLuint, GLsizei count, const GLchar* const*, const GLint* length)
    {
        g_rec.function = "glShaderSource";
        g_rec.count = count;
        g_rec.length = length ? *length : -1;
    }

    void GL_APIENTRY stub_Uniform2fv(GLint location, GLsizei count, const GLfloat*)
    {
        g_rec.function = "glUniform2fv";
        g_rec.location = location;
        g_rec.count = count;
    }

    void GL_APIENTRY stub_Uniform4fv(GLint location, GLsizei count, const GLfloat*)
    {
        g_rec.function = "glUniform4fv";
        g_rec.location = location;
        g_rec.count = count;
    }

    void GL_APIENTRY stub_UniformMatrix4fv(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat*)
    {
        g_rec.function = "glUniformMatrix4fv";
        g_rec.location = location;
        g_rec.count = count;
        g_rec.transpose = transpose;
    }

    void GL_APIENTRY stub_UniformMatrix3x2fv(
        GLint location, GLsizei count, GLboolean transpose, const GLfloat*)
    {
        g_rec.function = "glUniformMatrix3x2fv";
        g_rec.location = location;
        g_rec.count = count;
        g_rec.transpose = transpose;
    }

    void GL_APIENTRY stub_ProgramUniform4fv(
        GLuint program, GLint location, GLsizei count, const GLfloat*)
    {
        g_rec.function = "glProgramUniform4fv";
        g_rec.program = program;
        g_rec.location = location;
        g_rec.count = count;
    }

    void GL_APIENTRY stub_ProgramUniformMatrix2x3fv(
        GLuint program, GLint location, GLsizei count, GLboolean transpose,
        const GLfloat*)
    {
        g_rec.function = "glProgramUniformMatrix2x3fv";
        g_rec.program = program;
        g_rec.location = location;
        g_rec.count = count;
        g_rec.transpose = transpose;
    }

    // Every other entry point: present, so that the ES 3.2 mandatory-entry
    // check in Initialize() passes. The cases never call these.
    void GL_APIENTRY stub_noop() {}

    template <typename Fn>
    void* as_proc(Fn fn)
    {
        return reinterpret_cast<void*>(fn);
    }

    void* mock_es32_loader(const char* name)
    {
        if (g_omitted_function != nullptr
            && std::strcmp(name, g_omitted_function) == 0)
            return nullptr;

        struct Entry { const char* name; void* proc; };
        const Entry entries[] = {
            {"glGetString", as_proc(stub_GetString)},
            {"glGetIntegerv", as_proc(stub_GetIntegerv)},
            {"glGetStringi", as_proc(stub_GetStringi)},
            {"glGetError", as_proc(stub_GetError)},
            {"glEnable", as_proc(stub_Enable)},
            {"glBlendBarrier", as_proc(stub_BlendBarrier)},
            {"glGenBuffers", as_proc(stub_GenBuffers)},
            {"glBufferData", as_proc(stub_BufferData)},
            {"glShaderSource", as_proc(stub_ShaderSource)},
            {"glUniform2fv", as_proc(stub_Uniform2fv)},
            {"glUniform4fv", as_proc(stub_Uniform4fv)},
            {"glUniformMatrix4fv", as_proc(stub_UniformMatrix4fv)},
            {"glUniformMatrix3x2fv", as_proc(stub_UniformMatrix3x2fv)},
            {"glProgramUniform4fv", as_proc(stub_ProgramUniform4fv)},
            {"glProgramUniformMatrix2x3fv",
                as_proc(stub_ProgramUniformMatrix2x3fv)},
        };
        for (const Entry& e : entries)
            if (std::strcmp(name, e.name) == 0)
                return e.proc;
        return as_proc(stub_noop);
    }

    // An ES 3.1 context whose driver does not export glBlendBarrier (an
    // ES 3.2 entry point, so Initialize() still succeeds without it).
    void* mock_es31_without_blend_barrier(const char* name)
    {
        g_mock_version = "OpenGL ES 3.1 Mock";
        g_omitted_function = "glBlendBarrier";
        return mock_es32_loader(name);
    }

    // The same ES 3.1 context, with glBlendBarrier exported.
    void* mock_es31_with_blend_barrier(const char* name)
    {
        g_mock_version = "OpenGL ES 3.1 Mock";
        g_omitted_function = nullptr;
        return mock_es32_loader(name);
    }

    bool recorded(const char* function)
    {
        return g_rec.function != nullptr
            && std::strcmp(g_rec.function, function) == 0;
    }

    // A span/string_view whose size() exceeds a GL size type. Only size() is
    // read by the checked overloads before they terminate (and by the
    // boundary controls, whose stubs never dereference the data), so the
    // storage behind the pointer is never accessed beyond its first element.
    BufferId g_one_buffer{};
    std::byte g_one_byte{};
    const char g_one_char = 'x';

    constexpr std::size_t kGlsizeiMax =
        static_cast<std::size_t>(std::numeric_limits<GLsizei>::max());
    constexpr std::size_t kGlsizeiptrMax =
        static_cast<std::size_t>(std::numeric_limits<GLsizeiptr>::max());

    std::span<BufferId> buffer_names(std::size_t count)
    {
        return {&g_one_buffer, count};
    }

    std::span<const std::byte> bytes(std::size_t count)
    {
        return {&g_one_byte, count};
    }

    // ---------------------------------------------------------------------
    // Cases. A body returns true if the mock driver saw what it expected.
    // For a violation the body must not return at all.
    // ---------------------------------------------------------------------

    // --- Meta: the harness itself ------------------------------------------

    // Initialize() succeeds in the child, the context is a usable ES 3.2
    // context, and a wrapper call reaches the mock driver.
    bool meta_initialized_child_reaches_driver()
    {
        const auto info = GetContextInfo();
        if (!IsInitialized() || !AllFunctionsLoaded()) return false;
        if (GetContextStatus() != ContextStatus::Current) return false;
        if (info.api != ApiKind::OpenGLES || info.major != 3 || info.minor != 2)
            return false;
        if (!SupportsGLES32()) return false;
        glEnable(Capability::DepthTest);
        return recorded("glEnable") && g_rec.cap == GL_DEPTH_TEST;
    }

    // Without Initialize() the very same valid call terminates. This is the
    // trap the old harness fell into (its loader made Initialize() fail).
    bool meta_uninitialized_valid_call()
    {
        glEnable(Capability::DepthTest);
        return true;
    }

    // --- Missing entry point -----------------------------------------------

    bool missing_entry_point()
    {
        if (IsFunctionAvailable("glBlendBarrier")) return false;
        glBlendBarrier();
        return true;
    }

    bool missing_entry_point_control()
    {
        if (!IsFunctionAvailable("glBlendBarrier")) return false;
        glBlendBarrier();
        return recorded("glBlendBarrier");
    }

    // --- checked_glsizei: span count > GLsizei max -------------------------

    bool gen_buffers_count_overflow()
    {
        glGenBuffers(buffer_names(kGlsizeiMax + 1));
        return true;
    }

    bool gen_buffers_count_control()
    {
        std::array<BufferId, 3> names{};
        glGenBuffers(std::span<BufferId>{names});
        return recorded("glGenBuffers") && g_rec.count == 3
            && names[0].value == 1 && names[2].value == 3;
    }

    bool gen_buffers_count_boundary_control()
    {
        glGenBuffers(buffer_names(kGlsizeiMax));
        return recorded("glGenBuffers")
            && g_rec.count == std::numeric_limits<GLsizei>::max();
    }

    // Not a contract: the raw GLsizei overload forwards n unchanged, and a
    // negative n is the driver's INVALID_VALUE (ES 3.2 6.1). Only the span
    // overloads check sizes. (The old death test passed a size_t of 2^31 to
    // this overload; it narrowed to INT_MIN and "terminated" only because
    // meta-gl was not initialized.)
    bool raw_gen_buffers_negative_count_forwarded()
    {
        glGenBuffers(GLsizei{-1}, nullptr);
        return recorded("glGenBuffers") && g_rec.count == -1;
    }

    // --- checked_glsizei: string_view length > GLsizei max -----------------

    bool shader_source_length_overflow()
    {
        glShaderSource(ShaderId{1}, std::string_view{&g_one_char, kGlsizeiMax + 1});
        return true;
    }

    bool shader_source_length_control()
    {
        glShaderSource(ShaderId{1}, std::string_view{"void main() {}"});
        return recorded("glShaderSource") && g_rec.count == 1
            && g_rec.length == 14;
    }

    // --- checked_glsizeiptr: span byte size > GLsizeiptr max ---------------

    bool buffer_data_size_overflow()
    {
        glBufferData(BufferTarget::Array, bytes(kGlsizeiptrMax + 1),
            BufferUsage::StaticDraw);
        return true;
    }

    bool buffer_data_size_control()
    {
        const std::array<float, 2> data{1.0f, 2.0f};
        glBufferData(BufferTarget::Array, std::span<const float>{data},
            BufferUsage::StaticDraw);
        return recorded("glBufferData") && g_rec.size == 8;
    }

    bool buffer_data_size_boundary_control()
    {
        glBufferData(BufferTarget::Array, bytes(kGlsizeiptrMax),
            BufferUsage::StaticDraw);
        return recorded("glBufferData")
            && g_rec.size == std::numeric_limits<GLsizeiptr>::max();
    }

    // --- checked_element_count: glUniform<N> -------------------------------

    bool uniform_vec4_partial()
    {
        const float data[3] = {1, 2, 3};
        glUniform<4>(UniformLocation{5}, std::span<const float>{data, 3});
        return true;
    }

    bool uniform_vec4_control()
    {
        const float data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        glUniform<4>(UniformLocation{5}, std::span<const float>{data, 8});
        return recorded("glUniform4fv") && g_rec.location == 5
            && g_rec.count == 2;
    }

    bool uniform_vec2_initializer_list_partial()
    {
        glUniform<2>(UniformLocation{6}, {1.0f, 2.0f, 3.0f});
        return true;
    }

    bool uniform_vec2_initializer_list_control()
    {
        glUniform<2>(UniformLocation{6}, {1.0f, 2.0f, 3.0f, 4.0f});
        return recorded("glUniform2fv") && g_rec.location == 6
            && g_rec.count == 2;
    }

    // --- checked_element_count: glProgramUniform<N> ------------------------

    bool program_uniform_vec4_partial()
    {
        const float data[5] = {1, 2, 3, 4, 5};
        glProgramUniform<4>(ProgramId{9}, UniformLocation{2},
            std::span<const float>{data, 5});
        return true;
    }

    bool program_uniform_vec4_control()
    {
        const float data[4] = {1, 2, 3, 4};
        glProgramUniform<4>(ProgramId{9}, UniformLocation{2},
            std::span<const float>{data, 4});
        return recorded("glProgramUniform4fv") && g_rec.program == 9
            && g_rec.location == 2 && g_rec.count == 1;
    }

    // --- checked_matrix_count: glUniformMatrix / glProgramUniformMatrix ----

    bool uniform_mat4_partial()
    {
        const float data[15] = {};
        glUniformMatrix<4>(UniformLocation{0}, std::span<const float>{data, 15});
        return true;
    }

    bool uniform_mat4_control()
    {
        const float data[16] = {};
        glUniformMatrix<4>(UniformLocation{0}, std::span<const float>{data, 16});
        return recorded("glUniformMatrix4fv") && g_rec.count == 1
            && g_rec.transpose == GL_FALSE;
    }

    // transpose == GL_TRUE is not a contract violation: ES 3.0+ accepts
    // row-major uploads (ES 3.0 2.12.6.1, ES 3.2 7.6.1). It must be forwarded
    // unchanged. An earlier death test "proved" the opposite.
    bool uniform_mat4_transpose_forwarded()
    {
        const float data[32] = {};
        glUniformMatrix<4>(UniformLocation{3}, std::span<const float>{data, 32},
            GL_TRUE);
        return recorded("glUniformMatrix4fv") && g_rec.location == 3
            && g_rec.count == 2 && g_rec.transpose == GL_TRUE;
    }

    bool uniform_mat3x2_partial()
    {
        const float data[7] = {};
        glUniformMatrix<3, 2>(UniformLocation{4}, std::span<const float>{data, 7});
        return true;
    }

    bool uniform_mat3x2_control()
    {
        const float data[12] = {};
        glUniformMatrix<3, 2>(UniformLocation{4}, std::span<const float>{data, 12});
        return recorded("glUniformMatrix3x2fv") && g_rec.location == 4
            && g_rec.count == 2;
    }

    bool program_uniform_mat2x3_partial()
    {
        const float data[5] = {};
        glProgramUniformMatrix<2, 3>(ProgramId{7}, UniformLocation{1},
            std::span<const float>{data, 5});
        return true;
    }

    bool program_uniform_mat2x3_control()
    {
        const float data[6] = {};
        glProgramUniformMatrix<2, 3>(ProgramId{7}, UniformLocation{1},
            std::span<const float>{data, 6});
        return recorded("glProgramUniformMatrix2x3fv") && g_rec.program == 7
            && g_rec.location == 1 && g_rec.count == 1
            && g_rec.transpose == GL_FALSE;
    }

    // ---------------------------------------------------------------------
    // Harness
    // ---------------------------------------------------------------------

    enum class Expect { Terminate, Return };

    struct ContractCase
    {
        const char* name;
        bool (*body)();
        Expect expect;
        // nullptr: the child does not call Initialize() at all.
        GlGetProcAddressFn loader = mock_es32_loader;
    };

    const ContractCase kCases[] = {
        {"meta_initialized_child_reaches_driver",
            meta_initialized_child_reaches_driver, Expect::Return},
        {"meta_uninitialized_valid_call",
            meta_uninitialized_valid_call, Expect::Terminate, nullptr},

        {"missing_entry_point_control", missing_entry_point_control,
            Expect::Return, mock_es31_with_blend_barrier},
        {"missing_entry_point", missing_entry_point,
            Expect::Terminate, mock_es31_without_blend_barrier},

        {"gen_buffers_count_control", gen_buffers_count_control, Expect::Return},
        {"gen_buffers_count_boundary_control",
            gen_buffers_count_boundary_control, Expect::Return},
        {"gen_buffers_count_overflow", gen_buffers_count_overflow,
            Expect::Terminate},
        {"raw_gen_buffers_negative_count_forwarded",
            raw_gen_buffers_negative_count_forwarded, Expect::Return},

        {"shader_source_length_control", shader_source_length_control,
            Expect::Return},
        {"shader_source_length_overflow", shader_source_length_overflow,
            Expect::Terminate},

        {"buffer_data_size_control", buffer_data_size_control, Expect::Return},
        {"buffer_data_size_boundary_control",
            buffer_data_size_boundary_control, Expect::Return},
        {"buffer_data_size_overflow", buffer_data_size_overflow,
            Expect::Terminate},

        {"uniform_vec4_control", uniform_vec4_control, Expect::Return},
        {"uniform_vec4_partial", uniform_vec4_partial, Expect::Terminate},
        {"uniform_vec2_initializer_list_control",
            uniform_vec2_initializer_list_control, Expect::Return},
        {"uniform_vec2_initializer_list_partial",
            uniform_vec2_initializer_list_partial, Expect::Terminate},

        {"program_uniform_vec4_control", program_uniform_vec4_control,
            Expect::Return},
        {"program_uniform_vec4_partial", program_uniform_vec4_partial,
            Expect::Terminate},

        {"uniform_mat4_control", uniform_mat4_control, Expect::Return},
        {"uniform_mat4_partial", uniform_mat4_partial, Expect::Terminate},
        {"uniform_mat4_transpose_forwarded", uniform_mat4_transpose_forwarded,
            Expect::Return},
        {"uniform_mat3x2_control", uniform_mat3x2_control, Expect::Return},
        {"uniform_mat3x2_partial", uniform_mat3x2_partial, Expect::Terminate},

        {"program_uniform_mat2x3_control", program_uniform_mat2x3_control,
            Expect::Return},
        {"program_uniform_mat2x3_partial", program_uniform_mat2x3_partial,
            Expect::Terminate},
    };

    // Child exit codes for "returned normally".
    constexpr int kBodyOkExitCode = 0;
    constexpr int kBodyMismatchExitCode = 1;
    // Initialize() failed: the case would prove nothing, so it never runs.
    constexpr int kInitFailedExitCode = 77;
    // The child's argument named no case (Windows re-exec only).
    constexpr int kUnknownCaseExitCode = 78;

#ifdef _WIN32
    // MSVC's std::terminate() ends in abort(), whose exit code depends on the
    // CRT build and on WER (3, or 0xC0000409 via __fastfail). The child turns
    // SIGABRT into one fixed exit code so the parent can tell "terminated"
    // from "returned".
    constexpr int kTerminatedExitCode = 134;

    extern "C" void exit_on_abort(int)
    {
        std::_Exit(kTerminatedExitCode);
    }
#endif

    // Runs in the child process.
    int run_case_in_child(const ContractCase& c)
    {
        if (c.loader != nullptr)
        {
            if (!Initialize(c.loader) || !IsInitialized()
                || GetContextStatus() != ContextStatus::Current)
                return kInitFailedExitCode;
        }
        g_rec = {};
        return c.body() ? kBodyOkExitCode : kBodyMismatchExitCode;
    }

    struct Outcome
    {
        bool terminated = false;  // std::terminate() / abort()
        bool exited = false;      // returned from main / exit()
        int code = -1;            // exit code, or signal number
    };

    // POSIX forks; Windows has no fork, so it re-runs this executable with
    // "--child <name>" and main() dispatches to the case there.
    Outcome run_case(const ContractCase& c)
    {
        Outcome outcome{};
#ifdef _WIN32
        char* self = nullptr;
        if (_get_pgmptr(&self) != 0 || self == nullptr)
            return outcome;
        // _spawnv does not quote arguments; quote argv[0] so a path with
        // spaces does not shift the child's argv.
        const std::string quoted_self = std::string("\"") + self + "\"";
        const char* args[] = {quoted_self.c_str(), "--child", c.name, nullptr};
        const std::intptr_t status = _spawnv(_P_WAIT, self, args);
        if (status == kTerminatedExitCode)
        {
            outcome.terminated = true;
            outcome.code = SIGABRT;
        }
        else if (status >= 0)
        {
            outcome.exited = true;
            outcome.code = static_cast<int>(status);
        }
#else
        std::cout.flush();
        std::cerr.flush();
        const pid_t pid = fork();
        if (pid == 0)
            std::_Exit(run_case_in_child(c));
        if (pid < 0)
            return outcome;
        int status = 0;
        if (waitpid(pid, &status, 0) != pid)
            return outcome;
        if (WIFSIGNALED(status))
        {
            outcome.code = WTERMSIG(status);
            // std::terminate() calls abort(); any other signal (e.g. a
            // SIGSEGV) is a different failure, not the contract.
            outcome.terminated = outcome.code == SIGABRT;
        }
        else if (WIFEXITED(status))
        {
            outcome.exited = true;
            outcome.code = WEXITSTATUS(status);
        }
#endif
        return outcome;
    }

    std::string describe(const Outcome& o)
    {
        if (o.terminated) return "terminated (SIGABRT)";
        if (!o.exited)
        {
            if (o.code >= 0)
                return "killed by signal " + std::to_string(o.code);
            return "could not run the child";
        }
        switch (o.code)
        {
        case kBodyOkExitCode: return "returned; driver saw the expected call";
        case kBodyMismatchExitCode:
            return "returned; driver did NOT see the expected call";
        case kInitFailedExitCode:
            return "Initialize() with the mock loader failed in the child";
        case kUnknownCaseExitCode: return "child did not know the case";
        default: return "exited with code " + std::to_string(o.code);
        }
    }
}

int main(int argc, char** argv)
{
#ifdef _WIN32
    if (argc == 3 && std::strcmp(argv[1], "--child") == 0)
    {
#ifdef _MSC_VER
        // Keep abort() from popping a dialog or fast-failing past the handler.
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif
        std::signal(SIGABRT, exit_on_abort);
        for (const ContractCase& c : kCases)
            if (std::strcmp(argv[2], c.name) == 0)
                return run_case_in_child(c);
        return kUnknownCaseExitCode;
    }
#else
    (void)argc;
    (void)argv;
#endif

    int failed = 0;
    std::cout << "Running Release-contract tests (R10) under a mock ES context..."
              << std::endl;

    for (const ContractCase& c : kCases)
    {
        const Outcome o = run_case(c);
        const bool pass = c.expect == Expect::Terminate
            ? o.terminated
            : (o.exited && o.code == kBodyOkExitCode);
        const char* expected = c.expect == Expect::Terminate
            ? "terminate" : "return";
        if (pass)
        {
            std::cout << "PASS: " << c.name << " (expected " << expected
                      << "): " << describe(o) << std::endl;
        }
        else
        {
            std::cerr << "FAIL: " << c.name << " (expected " << expected
                      << "): " << describe(o) << std::endl;
            ++failed;
        }
    }

    if (failed == 0)
        std::cout << "All Release-contract tests passed!" << std::endl;
    else
        std::cerr << failed << " Release-contract test(s) failed." << std::endl;
    return failed;
}
