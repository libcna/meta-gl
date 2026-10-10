# meta-gl

`meta-gl` is a low-level, type-safe C++23 wrapper targeting **OpenGL ES
2.0–3.2** and the common programmable subset of **desktop OpenGL 3.3+**.

OpenGL ES older than 2.0 and desktop OpenGL older than 3.3 are not supported.

It is the foundation layer used by [easy-gl](../easy-gl) and provides:

- Runtime OpenGL function loading via a host-supplied `GetProcAddress` callback.
- Type-safe `enum class` wrappers for OpenGL constants (buffer targets, shader types, texture formats, etc.).
- Thin inline-style wrapper functions in the `metagl` namespace (`metagl::glBindBuffer`, `metagl::glClear`, …).
- No windowing, no context creation — the host application owns the GL context lifecycle.

## Architecture

```
Host application
    └── provides GL context + GetProcAddress callback
            └── easy-gl   (OOP wrapper, namespace easygl)
                    └── meta-gl  (function pointers + type-safe API, namespace metagl)
                            └── actual OpenGL driver
```

## Requirements

- C++23 compiler
- CMake `3.23+`
- A host-side GL context (provided externally)

The public API uses Khronos GLES scalar and function-pointer types. The
required Khronos headers are vendored for source builds and installed with the
package, so consumers do not need a separate GLES development-header package.

## Version

Current release: **0.4.1** (pre-1.0 — a minor release may change the public API; see
`CHANGELOG.md` for what the release contains and `docs/releasing.md` for how versions are
managed). Compiled code reads the version it was built against from
`metagl::GetVersionString()` and the `METAGL_VERSION_*` macros in `<metagl/Version.hpp>`, a
header the build generates from `CMakeLists.txt`.

## Build

`meta-gl` is intended to be consumed as a CMake subdirectory dependency:

```cmake
add_subdirectory(../meta-gl meta-gl)
target_link_libraries(my-target PRIVATE meta-gl::meta-gl)
```

It can also be built standalone:

```bash
cmake -S . -B build
cmake --build build
```

By default a **static** library is produced. Pass `-DBUILD_SHARED_LIBS=ON` to build a shared library instead:

```bash
cmake -S . -B build -DBUILD_SHARED_LIBS=ON
cmake --build build
```

Project-specific options do not modify similarly named parent-project options:

| Option | Default | Purpose |
|---|---:|---|
| `METAGL_BUILD_TESTS` | `OFF` | Build and register meta-gl tests |
| `METAGL_BUILD_GPU_TESTS` | `OFF` | Add a headless EGL test using a real GL implementation |
| `METAGL_BUILD_EXAMPLES` | `OFF` | Build the no-GPU example |
| `METAGL_BUILD_DOCS` | `OFF` | Add the `metagl-docs` Doxygen target |
| `METAGL_SANITIZE` | `OFF` | Enable ASan and UBSan with GCC/Clang |
| `METAGL_ENABLE_DEBUG_LOGGING` | `OFF` | Compile per-call logging and `glGetError` checks |
| `METAGL_DEBUG_IMMEDIATE` | `OFF` | Flush every debug record immediately |

The old standalone `BUILD_TESTING`, `BUILD_EXAMPLES`, and `SANITIZE` cache
variables remain accepted as compatibility aliases when meta-gl is the
top-level project.

### Install and `find_package`

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
cmake --install build --prefix /path/to/prefix
```

Consumers can then use:

```cmake
find_package(meta-gl 0.4 CONFIG REQUIRED)
target_link_libraries(my-target PRIVATE meta-gl::meta-gl)
```

For `0.x` releases, package compatibility is limited to the same minor
version because a minor bump may contain breaking API changes.

### Invalid Input Contract

`meta-gl` enforces valid inputs even in **Release** builds to prevent undefined behavior from reaching the OpenGL driver. If a function is called with arguments that violate its contract (e.g. `size_t` overflow when converting to `GLsizei`, incomplete matrix data, or unsupported bitfields), the program will be immediately terminated via `std::terminate()`.

This policy ensures that:
- Overflows never reach raw GL calls.
- Divisibility requirements for vectors and matrices are strictly enforced.
- Invalid bitfield combinations or unsupported parameters are caught early.

### Tests and documentation

```bash
cmake -S . -B build -DMETAGL_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

The default tests include mock lifecycle/platform coverage, a fresh installed
package consumer, and an API consistency check for all 358 wrappers and the
exact 142/104/68/44-function mandatory sets added by GLES
2.0/3.0/3.1/3.2. To exercise a real headless context when EGL and Mesa (or
another EGL implementation) are installed:

```bash
cmake -S . -B build-gpu \
  -DMETAGL_BUILD_TESTS=ON \
  -DMETAGL_BUILD_GPU_TESTS=ON
cmake --build build-gpu
ctest --test-dir build-gpu --output-on-failure
```

API documentation is generated with:

```bash
cmake -S . -B build-docs -DMETAGL_BUILD_DOCS=ON
cmake --build build-docs --target metagl-docs
```

### CMake presets

`CMakePresets.json` ships four configure/build presets:

| Preset | Description |
|--------|-------------|
| `default` | Debug build, host compiler |
| `release` | Optimized release, host compiler |
| `sanitize` | Debug + ASan/UBSan |
| `emscripten` | WebAssembly via Emscripten (requires `EMSDK` env var) |

```bash
cmake --preset default
cmake --build --preset default

# Emscripten (set EMSDK first)
cmake --preset emscripten
cmake --build --preset emscripten
```

### Emscripten / WebGL

Use the Emscripten toolchain wrappers:

```bash
emcmake cmake -S . -B build-wasm
emmake cmake --build build-wasm
```

Link your application with `-lGL` (Emscripten maps this to WebGL automatically):

```cmake
target_link_libraries(my-app PRIVATE meta-gl::meta-gl -lGL)
```

After creating a WebGL context, install the context-loss callbacks so meta-gl
can track `webglcontextlost` / `webglcontextrestored` browser events:

```cpp
#include <metagl/metagl.hpp>  // includes Emscripten.hpp automatically

const bool initialized = metagl::Initialize(
    reinterpret_cast<metagl::GlGetProcAddressFn>(
        emscripten_webgl_get_proc_address));
metagl::InstallEmscriptenContextLossCallbacks("#canvas");
```

If you manage browser callbacks yourself, use the atomic restore helper:

```cpp
// Inside your webglcontextrestored handler:
const bool restored = metagl::RestoreCurrentContext(
    reinterpret_cast<metagl::GlGetProcAddressFn>(
        emscripten_webgl_get_proc_address));
```

### Desktop OpenGL

Pass the same host-supplied loader callback used by the rest of your
application (`SDL_GL_GetProcAddress`, `glfwGetProcAddress`,
`wglGetProcAddress`, or `glXGetProcAddress`). `ContextInfo::api` is reported
as `ApiKind::OpenGL`, and `SupportsDesktopOpenGL()` returns `true`.

Desktop GL exposes `glDepthRange` and `glClearDepth` with `double`
parameters instead of the GLES `*f` variants. Meta-gl adapts
`glDepthRangef()` and `glClearDepthf()` automatically. GLES-only
`glShaderBinary`, `glReleaseShaderCompiler`, and
`glGetShaderPrecisionFormat` are optional on desktop; check
`IsFunctionAvailable()` before calling wrappers without a desktop equivalent.

The enum surface remains GLES-oriented. APIs shared by GLES 2.0 and desktop
GL 3.3+ are supported; entry points from newer versions still require the
corresponding driver support.

### ANGLE

ANGLE-backed contexts are detected from the GL version, vendor, and renderer
strings. Use `metagl::IsAngle()` to select workarounds, but continue to use
`HasExtension()` and `IsFunctionAvailable()` as the source of truth: ANGLE
capabilities depend on its backend and host driver.

## Initialization

Before calling any `metagl::gl*` function, initialize the function pointer table by passing a `GetProcAddress`-style callback:

```cpp
#include <metagl/metagl.hpp>

bool ok = metagl::Initialize(my_get_proc_address);
```

The callback type is:

```cpp
using GlGetProcAddressFn = void* (*)(const char* name);
```

## Public API

All symbols live in the `metagl` namespace under `include/metagl/`:

| Header | Contents |
|---|---|
| `metagl/metagl.hpp` | Umbrella header — include this |
| `metagl/Types.hpp` | Primitive GL type aliases, handle structs (`ShaderId`, `BufferId`, …), concepts (`GlHandle`, `GlEnum`, `GlBitfield`, `SpanCompatible`) |
| `metagl/Enums.hpp` | Type-safe `enum class` wrappers for all GL constants |
| `metagl/Functions.hpp` | All 358 `metagl::gl*` wrapper functions plus typed template dispatch helpers |
| `metagl/Loader.hpp` | `Initialize()`, `RestoreCurrentContext()`, `IsInitialized()`, `AllFunctionsLoaded()`, `IsFunctionAvailable()` |
| `metagl/Context.hpp` | `ContextInfo` struct, `GetContextInfo()`, `GetContextStatus()`, `MarkContextLost/Restored()` |
| `metagl/Capabilities.hpp` | `Capabilities`, GLES/WebGL/desktop/ANGLE detection, `HasExtension()` |
| `metagl/ContextEvents.hpp` | `ContextListener` interface, `AddContextListener()`, `NotifyContextLost/Restored()` |
| `metagl/EnumNames.hpp` | `to_string()` overloads for all enum classes and handle types (opt-out: `METAGL_NO_ENUM_NAMES`) |
| `metagl/Debug.hpp` | GL call logging built with `METAGL_ENABLE_DEBUG_LOGGING` (header opt-out: `METAGL_NO_DEBUG`) |
| `metagl/Emscripten.hpp` | `InstallEmscriptenContextLossCallbacks()` — included automatically when `__EMSCRIPTEN__` is defined |
| `metagl/Version.hpp` | `GetVersionString()`, `GetVersionMajor/Minor/Patch()`, `METAGL_VERSION_*` macros — generated by CMake |

Buffered debug logging is flushed automatically at normal process exit on
non-Windows platforms. Windows applications should call
`metagl::FlushDebugLog()` before shutdown, because DLL teardown executes under
the Windows loader lock; `METAGL_DEBUG_IMMEDIATE=ON` is another safe option.

### Example

```cpp
#include <metagl/metagl.hpp>

// After Initialize():
metagl::glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
metagl::glClear(metagl::ClearBufferBit::Color | metagl::ClearBufferBit::Depth);

metagl::VertexArrayId vao{};
metagl::glGenVertexArrays(1, &vao);
metagl::glBindVertexArray(vao);

metagl::ShaderId shader = metagl::glCreateShader(metagl::ShaderType::Vertex);
```

## Design notes

- Raw OpenGL values (`GL_ARRAY_BUFFER`, `GL_VERTEX_SHADER`, …) stay **internal** to meta-gl.
- Callers use `enum class` values; conversions to `GLenum` happen inside `metagl::detail`.
- Public headers expose Khronos GLES scalar types through `Types.hpp`; the
  matching vendored headers are installed with meta-gl.
- OpenGL ES 2.0–3.2 and the common desktop OpenGL 3.3+ programmable subset
  are supported. Optional wrappers still require their entry points.
