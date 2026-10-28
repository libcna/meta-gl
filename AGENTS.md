AI must not be used to generate code for contributions to this project.

"AI" in this case means a Large Language Model ("LLM"), such as ChatGPT,
Claude, Copilot, Grok, etc.

AI-generated code is based upon sources of unknown origins and may not be 
compatible with the licenses applicable to this project, or may introduce 
conflicting license terms if it includes code from other projects.

AI can be used to identify issues with contributions to this project, but the
solutions to those issues should be authored by humans.

We have found that AI will frequently hallucinate issues that are not actually
problems in practice, report incorrect information, and describe problems that
are actually not issues at all. If AI identifies a problem with this codebase,
please make sure you understand what it is saying and have independently
confirmed that the issue exists before submitting a bug report or pull request.

By submitting a pull request to this project, you confirm that you are the
author of your changes, have the necessary rights to contribute them, and
comply with all applicable licensing requirements of this project.

# CLAUDE.md — meta-gl

## Project role

meta-gl is the low-level, procedural, type-safe wrapper over OpenGL / OpenGL ES.

It should make raw OpenGL safer and clearer, but it must stay thin. It is not an engine layer and it must not own OpenGL resources through RAII classes.

Layering:

```text
OpenGL / OpenGL ES
        ↓
meta-gl
  - procedural API
  - type-safe enums and lightweight wrapper types
  - std::span for data views
  - constexpr-if/type-trait dispatch for typed GL variants
  - small concepts where they improve compile-time validation
        ↓
easy-gl
  - OOP/RAII resource classes
  - higher-level convenience API
  - ownership and lifetime management
```

## Main goals

- Replace unsafe raw OpenGL parameters with strongly typed C++ wrappers where useful.
- Avoid accidental mixing of unrelated OpenGL enum categories.
- Keep the API close to OpenGL, predictable, and easy to map back to GL calls.
- Prefer zero-overhead abstractions.
- Keep patches small, buildable, and easy to review.

## C++ standard

Target C++23 as the portable baseline.

Allowed and encouraged:

- `enum class`
- `std::span`
- `constexpr if`
- simple `concept`s
- type traits
- tag dispatching where useful
- lightweight strong typedefs / small wrapper structs

Use carefully:

- `std::ranges`, only when it stays simple and portable
- `consteval`, only for small compile-time validation helpers

Do not introduce:

- C++ modules
- C++26-only features
- `std::expected` as the core low-level error model
- heavy template metaprogramming
- complex range pipelines
- large framework abstractions

## API design rules

### Prefer `enum class` over raw `GLenum`

Use separate enum types for separate OpenGL domains.

Examples:

```cpp
enum class TextureTarget : uint32_t;
enum class BufferTarget : uint32_t;
enum class ShaderType : uint32_t;
enum class TextureMinFilter : uint32_t;
enum class TextureMagFilter : uint32_t;
enum class TextureWrapMode : uint32_t;
```

Do not use one generic enum for unrelated OpenGL concepts.

### Keep the API procedural

meta-gl functions should look like safe OpenGL functions, not like engine objects.

Good:

```cpp
void bindTexture(TextureTarget target, TextureId texture);
void setTextureParameter(TextureTarget target, TextureMinFilter filter);
template<typename T>
void bufferData(BufferTarget target, std::span<const T> data, BufferUsage usage);
```

Avoid:

```cpp
class Texture;
class Buffer;
class ShaderProgram;
```

Those belong in easy-gl.

### Use lightweight handle types

Prefer explicit handle wrappers over raw `GLuint` where it improves safety.

Example:

```cpp
struct TextureId { GLuint value{}; };
struct BufferId  { GLuint value{}; };
struct ProgramId { GLuint value{}; };
```

These types must not own resources. They are just typed identifiers.

### Use `std::span` for data input

Prefer:

```cpp
template<typename T>
void bufferData(BufferTarget target, std::span<const T> data, BufferUsage usage);
```

Avoid raw pointer + size pairs unless required for direct GL compatibility.

### Use `constexpr if` for typed GL variants

For APIs such as uniforms or vertex attributes, prefer one readable template dispatch instead of many copy-pasted overloads.

Example pattern:

```cpp
template<typename T>
void uniform1(UniformLocation location, T value) {
    if constexpr (std::same_as<T, float>) {
        glUniform1f(location.value, value);
    } else if constexpr (std::same_as<T, int>) {
        glUniform1i(location.value, value);
    } else if constexpr (std::same_as<T, unsigned int>) {
        glUniform1ui(location.value, value);
    } else {
        static_assert(always_false<T>, "Unsupported uniform type");
    }
}
```

### Use concepts only when they simplify the code

Small concepts are allowed for clear API boundaries.

Good:

```cpp
template<typename T>
concept UniformScalar =
    std::same_as<T, float> ||
    std::same_as<T, int> ||
    std::same_as<T, unsigned int>;
```

Avoid large concept hierarchies that make compiler errors hard to understand.

## Error handling

meta-gl should not become a large error-handling framework.

Prefer:

- debug assertions
- optional debug validation helpers
- OpenGL debug callback support where appropriate
- simple return values for query-like operations

Avoid making every function return `expected` or custom result objects.

## Dependencies

Keep dependencies minimal.

Do not add large external libraries for basic OpenGL wrapping.

## Relationship to easy-gl

meta-gl must not depend on easy-gl.

easy-gl depends on meta-gl.

meta-gl should expose safe low-level operations that easy-gl can use to implement OOP/RAII resource classes.

## Refactoring rules for Claude

When modifying this project:

1. Read this file first.
2. Keep changes small and reviewable.
3. Prefer one concept or enum group at a time.
4. Do not redesign the whole project in one patch.
5. Do not introduce RAII or OOP resource ownership into meta-gl.
6. Do not add modules or experimental C++26 features.
7. Build after changes when possible.
8. Show the diff before continuing with more refactoring.

## Preferred first steps

Good initial refactoring steps:

1. Introduce typed OpenGL enum classes for one domain, such as texture targets.
2. Replace a few raw `GLenum` parameters with those enum classes.
3. Add `std::span` to buffer upload functions.
4. Add typed dispatch for one uniform function family.
5. Add typed handle wrappers for textures, buffers, shaders, and programs.

Avoid large all-at-once rewrites.
