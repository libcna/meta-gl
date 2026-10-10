// Release identity: the generated metagl/Version.hpp must agree with the CMake project that
// generated it. The checks are structural -- nothing here names a concrete release -- so a
// version bump never has to edit this file (docs/releasing.md).
#include <metagl/metagl.hpp>

#include <charconv>
#include <cstdio>
#include <string>
#include <string_view>
#include <system_error>

#ifndef METAGL_TEST_EXPECTED_VERSION
#error "METAGL_TEST_EXPECTED_VERSION must be defined by tests/CMakeLists.txt"
#endif

namespace {

int failures = 0;

void check(bool condition, const char* what)
{
    if (!condition) {
        std::fprintf(stderr, "FAILED: %s\n", what);
        ++failures;
    }
}

} // namespace

// The macros are usable by the preprocessor, which is why they exist beside the functions.
#if !(METAGL_VERSION_MAJOR >= 0 && METAGL_VERSION_MINOR >= 0 && METAGL_VERSION_PATCH >= 0)
#error "METAGL_VERSION_* must be preprocessor-testable integer literals"
#endif

static_assert(metagl::GetVersionMajor() == METAGL_VERSION_MAJOR);
static_assert(metagl::GetVersionMinor() == METAGL_VERSION_MINOR);
static_assert(metagl::GetVersionPatch() == METAGL_VERSION_PATCH);
static_assert(metagl::GetVersionString() == std::string_view{METAGL_VERSION_STRING});
static_assert(metagl::GetVersionPreRelease() == std::string_view{METAGL_VERSION_PRERELEASE});
static_assert(metagl::IsPreReleaseVersion() == !metagl::GetVersionPreRelease().empty());

int main()
{
    const std::string_view version = metagl::GetVersionString();

    check(version == METAGL_TEST_EXPECTED_VERSION,
          "GetVersionString() equals the METAGL_VERSION_STRING CMake configured");
    check(!version.empty() && version.front() != 'v',
          "the version string carries no leading 'v' (only the git tag does)");

    const std::string numeric = std::to_string(metagl::GetVersionMajor()) + "." +
                                std::to_string(metagl::GetVersionMinor()) + "." +
                                std::to_string(metagl::GetVersionPatch());
    check(version.starts_with(numeric),
          "the version string starts with MAJOR.MINOR.PATCH");

    if (metagl::IsPreReleaseVersion()) {
        check(version == numeric + "-" + std::string{metagl::GetVersionPreRelease()},
              "a pre-release is spelled MAJOR.MINOR.PATCH-PRERELEASE");
    } else {
        check(version == numeric, "a final release is exactly MAJOR.MINOR.PATCH");
    }

    // The numeric components parse back from the string, so no component is out of sync.
    int parsed_major = -1;
    const auto first = version.data();
    const auto last  = version.data() + version.size();
    const auto [end, error] = std::from_chars(first, last, parsed_major);
    check(error == std::errc{} && end != last && *end == '.' &&
              parsed_major == metagl::GetVersionMajor(),
          "the major component parses back from the version string");

    if (failures != 0)
        return 1;

    std::printf("meta-gl version %.*s: all version checks passed\n",
                static_cast<int>(version.size()), version.data());
    return 0;
}
