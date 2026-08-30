#include "metagl/metagl.hpp"

#include <algorithm>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Module-level state
// ---------------------------------------------------------------------------
namespace metagl::detail
{
    static thread_local ContextInfo  g_context_info{};
    static thread_local Capabilities g_capabilities{};
    static thread_local std::vector<ContextListener*> g_listeners{};

    // Implemented in Functions.cpp. Context loss makes a previously successful
    // loader state unusable until all entry points have been loaded again.
    void InvalidateFunctionsAfterContextLoss() noexcept;

#ifndef __EMSCRIPTEN__
    static bool parse_version(const char* ptr, int& major, int& minor)
    {
        if (!ptr || !*ptr) return false;
        major = 0;
        minor = 0;
        while (*ptr >= '0' && *ptr <= '9')
            major = major * 10 + (*ptr++ - '0');
        if (*ptr == '.') ++ptr;
        while (*ptr >= '0' && *ptr <= '9')
            minor = minor * 10 + (*ptr++ - '0');
        return major > 0 || minor > 0;
    }
#endif

    // Called by Functions.cpp Initialize() after function pointers are loaded.
    // Uses the public metagl::gl* API which is valid at this point.
    void UpdateContextAfterLoad()
    {
        Capabilities caps{};
        ContextInfo  info{};

        auto to_str = [](const GLubyte* p) -> std::string
        {
            return p ? reinterpret_cast<const char*>(p) : "";
        };

        caps.version_string           = to_str(metagl::glGetString(metagl::StringName::Version));
        caps.vendor                   = to_str(metagl::glGetString(metagl::StringName::Vendor));
        caps.renderer                 = to_str(metagl::glGetString(metagl::StringName::Renderer));
        caps.shading_language_version = to_str(metagl::glGetString(metagl::StringName::ShadingLanguageVersion));

        const auto contains_angle = [](const std::string& value)
        {
            return value.find("ANGLE") != std::string::npos;
        };
        caps.angle = contains_angle(caps.version_string)
            || contains_angle(caps.vendor)
            || contains_angle(caps.renderer);

#ifdef __EMSCRIPTEN__
        info.api = ApiKind::WebGL;
        if (caps.version_string.find("WebGL 2") != std::string::npos ||
            caps.version_string.find("OpenGL ES 3") != std::string::npos)
        {
            caps.webgl2 = true;
            info.major  = 3;
            info.minor  = 0;
        }
        else
        {
            caps.webgl1 = true;
            info.major  = 2;
            info.minor  = 0;
        }
#else
        const bool is_es = caps.version_string.find("OpenGL ES") != std::string::npos;
        if (is_es)
        {
            info.api = ApiKind::OpenGLES;
            // Skip "OpenGL ES "
            const char* v = caps.version_string.c_str();
            if (caps.version_string.size() > 10) v += 10;
            parse_version(v, info.major, info.minor);
        }
        else
        {
            info.api = ApiKind::OpenGL;
            caps.desktop_gl = true;
            if (!parse_version(caps.version_string.c_str(), info.major, info.minor))
            {
                metagl::glGetIntegerv(metagl::GetParameter::MajorVersion, &info.major);
                metagl::glGetIntegerv(metagl::GetParameter::MinorVersion, &info.minor);
            }
        }
#endif

        // GLES version flags — single source of truth in Capabilities
        if (info.api == ApiKind::OpenGLES || info.api == ApiKind::WebGL)
        {
            if (info.major >= 2)                    { caps.gles20 = true; }
            if (info.major >= 3)                    { caps.gles30 = true; }
            if (info.major == 3 && info.minor >= 1) { caps.gles31 = true; }
            if (info.major == 3 && info.minor >= 2) { caps.gles32 = true; }
        }

        // Extensions
        if (info.major >= 3)
        {
            int num = 0;
            metagl::glGetIntegerv(metagl::GetParameter::NumExtensions, &num);
            for (int i = 0; i < num; ++i)
            {
                const GLubyte* ext = metagl::glGetStringi(
                    metagl::StringName::Extensions, static_cast<GLuint>(i));
                if (ext) caps.extensions.push_back(reinterpret_cast<const char*>(ext));
            }
        }
        else
        {
            const GLubyte* raw = metagl::glGetString(metagl::StringName::Extensions);
            if (raw)
            {
                std::string s(reinterpret_cast<const char*>(raw));
                std::string::size_type pos = 0;
                while ((pos = s.find(' ')) != std::string::npos)
                {
                    std::string tok = s.substr(0, pos);
                    if (!tok.empty()) caps.extensions.push_back(std::move(tok));
                    s.erase(0, pos + 1);
                }
                if (!s.empty()) caps.extensions.push_back(std::move(s));
            }
        }

        info.generation = g_context_info.generation + 1;
        info.status     = ContextStatus::Current;

        g_capabilities = std::move(caps);
        g_context_info = std::move(info);
    }

    static void ClearCurrentContextState(ContextStatus status) noexcept
    {
        const auto generation = g_context_info.generation;

        g_capabilities = {};
        g_context_info = {};
        g_context_info.generation = generation;
        g_context_info.status = status;
    }

    // Called while a new load attempt is hidden, or after it failed version or
    // mandatory-entry validation. Do not expose the previous capabilities.
    void ResetContextAfterLoadFailure() noexcept
    {
        const auto status = g_context_info.status == ContextStatus::NotCreated
            ? ContextStatus::NotCreated
            : ContextStatus::Lost;
        ClearCurrentContextState(status);
    }
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
namespace metagl
{
    ContextInfo GetContextInfo() noexcept
    {
        return detail::g_context_info;
    }

    std::uint64_t GetContextGeneration() noexcept
    {
        return detail::g_context_info.generation;
    }

    ContextStatus GetContextStatus() noexcept
    {
        return detail::g_context_info.status;
    }

    bool IsContextLost() noexcept
    {
        return detail::g_context_info.status == ContextStatus::Lost;
    }

    void MarkContextLost() noexcept
    {
        detail::InvalidateFunctionsAfterContextLoss();
        detail::ClearCurrentContextState(ContextStatus::Lost);
    }

    void MarkContextRestored() noexcept
    {
        detail::g_context_info.status = ContextStatus::Restored;
    }

    void SetContextInfo(ContextInfo info) noexcept
    {
        detail::g_context_info = std::move(info);
    }

    const Capabilities& GetCapabilities() noexcept
    {
        return detail::g_capabilities;
    }

    bool SupportsGLES20() noexcept { return detail::g_capabilities.gles20; }
    bool SupportsGLES30() noexcept { return detail::g_capabilities.gles30; }
    bool SupportsGLES31() noexcept { return detail::g_capabilities.gles31; }
    bool SupportsGLES32() noexcept { return detail::g_capabilities.gles32; }
    bool SupportsWebGL2() noexcept { return detail::g_capabilities.webgl2; }
    bool SupportsDesktopOpenGL() noexcept { return detail::g_capabilities.desktop_gl; }
    bool IsAngle() noexcept { return detail::g_capabilities.angle; }

    bool HasExtension(std::string_view extensionName) noexcept
    {
        const auto& exts = detail::g_capabilities.extensions;
        return std::any_of(exts.begin(), exts.end(),
            [&](const std::string& e) { return e == extensionName; });
    }

    void AddContextListener(ContextListener* listener)
    {
        if (!listener) return;
        if (std::find(detail::g_listeners.begin(), detail::g_listeners.end(), listener)
            != detail::g_listeners.end())
            return;
        detail::g_listeners.push_back(listener);
    }

    void RemoveContextListener(ContextListener* listener)
    {
        auto& v = detail::g_listeners;
        v.erase(std::remove(v.begin(), v.end(), listener), v.end());
    }

    void NotifyContextLost()
    {
        MarkContextLost();
        const auto snapshot = detail::g_listeners;
        for (auto* l : snapshot)
        {
            // Check if listener is still in the actual list before calling
            const auto& current = detail::g_listeners;
            if (std::find(current.begin(), current.end(), l) != current.end())
            {
                if (l) l->OnContextLost();
            }
        }
    }

    void NotifyContextRestored()
    {
        if (!IsInitialized())
        {
            if (GetContextStatus() != ContextStatus::NotCreated)
                MarkContextLost();
            return;
        }

        MarkContextRestored();
        const auto snapshot = detail::g_listeners;
        try
        {
            for (auto* l : snapshot)
            {
                const auto& current = detail::g_listeners;
                if (std::find(current.begin(), current.end(), l) != current.end())
                {
                    if (l) l->OnContextRestored();
                }
            }
        }
        catch (...)
        {
            detail::g_context_info.status = ContextStatus::Current;
            throw;
        }
        detail::g_context_info.status = ContextStatus::Current;
    }

    bool RestoreCurrentContext(GlGetProcAddressFn getProcAddress)
    {
        if (!LoadCurrentContext(getProcAddress))
            return false;

        NotifyContextRestored();
        return GetContextStatus() == ContextStatus::Current;
    }
}

// ---------------------------------------------------------------------------
// Emscripten platform hooks
// ---------------------------------------------------------------------------
#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>

namespace metagl
{
    static EM_BOOL emscripten_context_lost_cb(int, const void*, void*)
    {
        NotifyContextLost();
        return EM_TRUE;
    }

    static EM_BOOL emscripten_context_restored_cb(int, const void*, void*)
    {
        const bool restored = RestoreCurrentContext(
            reinterpret_cast<GlGetProcAddressFn>(
                emscripten_webgl_get_proc_address));
        return restored ? EM_TRUE : EM_FALSE;
    }

    bool InstallEmscriptenContextLossCallbacks(const char* canvasSelector)
    {
        const char* target = canvasSelector ? canvasSelector : "#canvas";
        EMSCRIPTEN_RESULT r1 = emscripten_set_webglcontextlost_callback(
            target, nullptr, EM_FALSE, emscripten_context_lost_cb);
        EMSCRIPTEN_RESULT r2 = emscripten_set_webglcontextrestored_callback(
            target, nullptr, EM_FALSE, emscripten_context_restored_cb);
        return (r1 == EMSCRIPTEN_RESULT_SUCCESS) && (r2 == EMSCRIPTEN_RESULT_SUCCESS);
    }
}
#endif // __EMSCRIPTEN__
