#include <metagl/metagl.hpp>

#include <string_view>
#include <type_traits>

int main()
{
    // Compile-time checks (inline / header-only)
    static_assert(metagl::GlBitfield<metagl::ClearBufferBit>);
    static_assert(!std::is_convertible_v<metagl::TextureId, metagl::BufferId>);

    // The generated header is installed with the package and agrees with its CMake version
    // file. meta-gl_VERSION is numeric only, so compare it with the MAJOR.MINOR.PATCH prefix.
    static_assert(metagl::GetVersionString().starts_with(std::string_view{METAGL_PACKAGE_VERSION}));

    const auto mask =
        metagl::ClearBufferBit::Color | metagl::ClearBufferBit::Depth;
    if (static_cast<metagl::GLbitfield>(mask) == 0)
        return 1;

    // R12: call out-of-line symbols from the installed library to verify linking.
    // GetContextStatus() and GetContextGeneration() are non-inline functions
    // compiled into Context.cpp; they work without an active GL context.
    const auto status = metagl::GetContextStatus();
    if (status != metagl::ContextStatus::NotCreated)
        return 2;

    const auto generation = metagl::GetContextGeneration();
    if (generation != 0)
        return 3;

    const auto info = metagl::GetContextInfo();
    if (info.api != metagl::ApiKind::Unknown)
        return 4;

    return 0;
}
