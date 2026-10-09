/**
 * @file Functions.hpp
 * @brief Procedural GL wrapper declarations for all 358 OpenGL ES 2.0–3.2 functions.
 *
 * Each wrapper in this header corresponds 1-to-1 with a raw `gl*` entry point,
 * but uses strongly-typed parameters from @ref Enums.hpp and @ref Types.hpp
 * in place of raw `GLenum`/`GLuint` where it improves safety.
 *
 * `std::span<const T>` overloads are provided for data-upload functions
 * (buffer data, texture images, compressed textures) as a convenience.
 * The raw `const void*` overloads are preserved for null-pointer (allocate-only)
 * use cases.
 *
 * Template-dispatch helpers at the bottom of this file (inside
 * "Convenience dispatch API") provide typed overloads for the uniform,
 * vertex attribute, texture parameter, sampler parameter, clear-buffer,
 * and vertex attrib query families via `constexpr if` dispatch.
 *
 * @note All functions require a prior successful call to
 *       @ref metagl::Initialize.
 *       An uninitialized context or missing function pointer is treated as
 *       an invalid-input contract violation (see below): `src/Functions.cpp`
 *       enforces it via `std::terminate()` in every wrapper, in both Debug
 *       and Release builds.
 *
 * @par Invalid Input Contract (R07, R11)
 *
 * This library enforces valid inputs even in Release builds. If a function is
 * called with invalid arguments that violate its contract (e.g. `size_t`
 * overflow, incomplete matrix data, or unsupported bitfields), the program
 * will be immediately terminated via `std::terminate()`.
 */
#pragma once

#include "metagl/Export.hpp"
#include "Types.hpp"
#include "Enums.hpp"

#include <array>
#include <concepts>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <limits>
#include <ranges>
#include <span>
#include <string_view>
#include <type_traits>

namespace metagl
{
    namespace detail
    {
        [[nodiscard]] inline GLsizei checked_glsizei(std::size_t value)
        {
            if (value > static_cast<std::size_t>(std::numeric_limits<GLsizei>::max())) {
                std::terminate();
            }
            return static_cast<GLsizei>(value);
        }

        [[nodiscard]] inline GLsizeiptr checked_glsizeiptr(
            std::size_t value)
        {
            if (value > static_cast<std::size_t>(std::numeric_limits<GLsizeiptr>::max())) {
                std::terminate();
            }
            return static_cast<GLsizeiptr>(value);
        }

        [[nodiscard]] inline GLsizei checked_element_count(
            std::size_t size, std::size_t elements_per_value)
        {
            if (elements_per_value == 0 || size % elements_per_value != 0) {
                std::terminate();
            }
            return checked_glsizei(size / elements_per_value);
        }

        [[nodiscard]] inline GLsizei checked_matrix_count(
            std::size_t size, std::size_t elements_per_matrix,
            GLboolean transpose)
        {
            // OpenGL ES requires GL_FALSE. The portable convenience API keeps
            // that rule even when the active context happens to be desktop GL.
            if (transpose != GL_FALSE) {
                std::terminate();
            }
            return checked_element_count(size, elements_per_matrix);
        }
    }

    /// @name State Management
    /// @{

    /// @brief Enables a server-side GL capability (e.g. depth test, blending, culling) (GL ES 2.0+)
    METAGL_API void glEnable(Capability cap);
    /// @brief Disables a server-side GL capability (GL ES 2.0+)
    METAGL_API void glDisable(Capability cap);
    /// @brief Enables a capability for a specific indexed target (per-draw-buffer) (GL ES 3.2+)
    METAGL_API void glEnablei(Capability target, GLuint index);
    /// @brief Disables a capability for a specific indexed target (GL ES 3.2+)
    METAGL_API void glDisablei(Capability target, GLuint index);
    /// @brief Returns whether a capability is currently enabled (GL ES 2.0+)
    [[nodiscard]] METAGL_API bool glIsEnabled(Capability cap);
    /// @brief Returns whether an indexed capability is enabled (GL ES 3.2+)
    [[nodiscard]] METAGL_API bool glIsEnabledi(Capability target, GLuint index);
    /// @brief Sets blend source and destination factors for all draw buffers (GL ES 2.0+)
    METAGL_API void glBlendFunc(BlendFactor sfactor, BlendFactor dfactor);
    /// @brief Sets separate blend factors for RGB and alpha for all draw buffers (GL ES 2.0+)
    METAGL_API void glBlendFuncSeparate(BlendFactor sfactorRGB, BlendFactor dfactorRGB, BlendFactor sfactorAlpha, BlendFactor dfactorAlpha);
    /// @brief Sets blend factors for a specific indexed draw buffer (GL ES 3.2+)
    METAGL_API void glBlendFunci(GLuint buf, BlendFactor src, BlendFactor dst);
    /// @brief Sets separate RGB/alpha blend factors for a specific draw buffer (GL ES 3.2+)
    METAGL_API void glBlendFuncSeparatei(GLuint buf, BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha);
    /// @brief Sets the blend equation (e.g. GL_FUNC_ADD) for all draw buffers (GL ES 2.0+)
    METAGL_API void glBlendEquation(BlendEquation mode);
    /// @brief Sets separate blend equations for RGB and alpha for all draw buffers (GL ES 2.0+)
    METAGL_API void glBlendEquationSeparate(BlendEquation modeRGB, BlendEquation modeAlpha);
    /// @brief Sets the blend equation for a specific indexed draw buffer (GL ES 3.2+)
    METAGL_API void glBlendEquationi(GLuint buf, BlendEquation mode);
    /// @brief Sets separate blend equations for a specific draw buffer (GL ES 3.2+)
    METAGL_API void glBlendEquationSeparatei(GLuint buf, BlendEquation modeRGB, BlendEquation modeAlpha);
    /// @brief Sets the constant blend color used in blend factor expressions (GL ES 2.0+)
    METAGL_API void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    /// @brief Ensures prior fragment writes are visible before next blending operation (GL ES 3.2+)
    METAGL_API void glBlendBarrier(void);
    /// @brief Enables/disables writing of R, G, B, A components for all draw buffers (GL ES 2.0+)
    METAGL_API void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    /// @brief Enables/disables writing of color components for a specific draw buffer (GL ES 3.2+)
    METAGL_API void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
    /// @brief Sets the depth comparison function (e.g. GL_LESS, GL_LEQUAL) (GL ES 2.0+)
    METAGL_API void glDepthFunc(CompareFunc func);
    /// @brief Enables or disables writing to the depth buffer (GL ES 2.0+)
    METAGL_API void glDepthMask(GLboolean flag);
    /// @brief Maps NDC depth to window-space depth via near/far plane values (GL ES 2.0+)
    METAGL_API void glDepthRangef(GLfloat n, GLfloat f);
    /// @brief Sets the stencil test function for both front and back faces (GL ES 2.0+)
    METAGL_API void glStencilFunc(CompareFunc func, GLint ref, GLuint mask);
    /// @brief Sets the stencil test function separately for front and back faces (GL ES 2.0+)
    METAGL_API void glStencilFuncSeparate(CullFace face, CompareFunc func, GLint ref, GLuint mask);
    /// @brief Sets stencil operations (sfail, dpfail, dppass) for both faces (GL ES 2.0+)
    METAGL_API void glStencilOp(StencilOp fail, StencilOp zfail, StencilOp zpass);
    /// @brief Sets stencil operations separately for front and back faces (GL ES 2.0+)
    METAGL_API void glStencilOpSeparate(CullFace face, StencilOp sfail, StencilOp dpfail, StencilOp dppass);
    /// @brief Sets the stencil write mask for both faces (GL ES 2.0+)
    METAGL_API void glStencilMask(GLuint mask);
    /// @brief Sets the stencil write mask separately for front and back faces (GL ES 2.0+)
    METAGL_API void glStencilMaskSeparate(CullFace face, GLuint mask);
    /// @brief Defines a rectangular region outside which all fragments are discarded (GL ES 2.0+)
    METAGL_API void glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
    /// @brief Sets the affine mapping from NDC to window-space coordinates (GL ES 2.0+)
    METAGL_API void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
    /// @brief Specifies whether front, back, or both polygon faces are culled (GL ES 2.0+)
    METAGL_API void glCullFace(CullFace mode);
    /// @brief Sets the winding order (CW or CCW) that defines front-facing polygons (GL ES 2.0+)
    METAGL_API void glFrontFace(FrontFace mode);
    /// @brief Sets the width of rasterized lines (only 1.0 is guaranteed portable) (GL ES 2.0+)
    METAGL_API void glLineWidth(GLfloat width);
    /// @brief Adds a scaled depth bias to polygon fragments (resolves z-fighting) (GL ES 2.0+)
    METAGL_API void glPolygonOffset(GLfloat factor, GLfloat units);
    /// @brief Sets a sample coverage mask used in multisampled rendering (GL ES 2.0+)
    METAGL_API void glSampleCoverage(GLfloat value, GLboolean invert);
    /// @brief Sets a bitmask qualifying which samples are written during MSAA (GL ES 3.1+)
    METAGL_API void glSampleMaski(GLuint maskNumber, SampleMaskValue mask);
    /// @brief Sets the minimum fraction of samples for which per-sample shading runs (GL ES 3.2+)
    METAGL_API void glMinSampleShading(GLfloat value);
    /// @brief Provides a quality/performance trade-off hint for certain operations (GL ES 2.0+)
    METAGL_API void glHint(HintTarget target, HintMode mode);
    /// @brief Sets pixel pack/unpack alignment and stride for texture transfers (GL ES 2.0+)
    METAGL_API void glPixelStorei(PixelStoreParam pname, GLint param);
    /// @brief Blocks the CPU until all pending GL commands have finished on the GPU (GL ES 2.0+)
    METAGL_API void glFinish(void);
    /// @brief Submits all pending GL commands to the GPU without waiting for completion (GL ES 2.0+)
    METAGL_API void glFlush(void);
    /// @brief Returns the most recent GL error flag and clears it (GL ES 2.0+)
    METAGL_API ErrorCode glGetError(void);
    /// @brief Queries a named GL state parameter as a boolean value (GL ES 2.0+)
    METAGL_API void glGetBooleanv(GetParameter pname, GLboolean * data);
    /// @brief Queries a named GL state parameter as a 32-bit integer (GL ES 2.0+)
    METAGL_API void glGetIntegerv(GetParameter pname, GLint * data);
    /// @brief Queries a named GL state parameter as a float (GL ES 2.0+)
    METAGL_API void glGetFloatv(GetParameter pname, GLfloat * data);
    /// @brief Queries a named GL state parameter as a 64-bit integer (GL ES 3.0+)
    METAGL_API void glGetInteger64v(GetParameter pname, GLint64 * data);
    /// @brief Queries an indexed GL state parameter as a 32-bit integer (GL ES 3.0+)
    METAGL_API void glGetIntegeri_v(GetParameter target, GLuint index, GLint * data);
    /// @brief Queries an indexed GL state parameter as a 64-bit integer (GL ES 3.0+)
    METAGL_API void glGetInteger64i_v(GetParameter target, GLuint index, GLint64 * data);
    /// @brief Queries an indexed GL state parameter as a boolean (GL ES 3.1+)
    METAGL_API void glGetBooleani_v(GetParameter target, GLuint index, GLboolean * data);
    /// @brief Returns a global implementation string (renderer, vendor, version, etc.) (GL ES 2.0+)
    [[nodiscard]] METAGL_API const GLubyte* glGetString(StringName name);
    /// @brief Returns an indexed string (e.g. the nth supported extension) (GL ES 3.0+)
    [[nodiscard]] METAGL_API const GLubyte* glGetStringi(StringName name, GLuint index);
    /// @brief Returns pointer-valued GL state such as debug callback pointers (GL ES 3.2+)
    METAGL_API void glGetPointerv(GetPointerParameter pname, void ** params);

    /// @}
    /// @name Buffer Objects
    /// @{

    /// @brief Generates one or more buffer object names (GL ES 2.0+)
    METAGL_API void glGenBuffers(GLsizei n, BufferId * buffers);
    inline void glGenBuffers(std::span<BufferId> buffers) { glGenBuffers(detail::checked_glsizei(buffers.size()), buffers.data()); }
    /// @brief Deletes buffer objects and frees their GPU memory (GL ES 2.0+)
    METAGL_API void glDeleteBuffers(GLsizei n, const BufferId * buffers);
    inline void glDeleteBuffers(std::span<const BufferId> buffers) { glDeleteBuffers(detail::checked_glsizei(buffers.size()), buffers.data()); }
    /// @brief Binds a buffer to a target (ARRAY_BUFFER, ELEMENT_ARRAY_BUFFER, etc.) (GL ES 2.0+)
    METAGL_API void glBindBuffer(BufferTarget target, BufferId buffer);
    /// @brief Binds a buffer to an indexed binding point (e.g. UBO slot N) (GL ES 3.0+)
    METAGL_API void glBindBufferBase(BufferTarget target, GLuint index, BufferId buffer);
    /// @brief Binds a sub-range of a buffer to an indexed binding point (GL ES 3.0+)
    METAGL_API void glBindBufferRange(BufferTarget target, GLuint index, BufferId buffer, GLintptr offset, GLsizeiptr size);
    /// @brief Allocates and optionally initializes a buffer's GPU data store (GL ES 2.0+)
    METAGL_API void glBufferData(BufferTarget target, GLsizeiptr size, const void * data, BufferUsage usage);
    template<SpanCompatible T>
    inline void glBufferData(BufferTarget target, std::span<const T> data, BufferUsage usage)
    {
        glBufferData(target, detail::checked_glsizeiptr(data.size_bytes()), data.data(), usage);
    }
    /// @brief Updates a sub-range of an existing buffer without reallocating (GL ES 2.0+)
    METAGL_API void glBufferSubData(BufferTarget target, GLintptr offset, GLsizeiptr size, const void * data);
    template<SpanCompatible T>
    inline void glBufferSubData(BufferTarget target, GLintptr offset, std::span<const T> data)
    {
        glBufferSubData(target, offset, detail::checked_glsizeiptr(data.size_bytes()), data.data());
    }
    /// @brief Copies a region from one buffer to another entirely on the GPU (GL ES 3.0+)
    METAGL_API void glCopyBufferSubData(BufferTarget readTarget, BufferTarget writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
    /// @brief Maps a buffer sub-range into CPU address space for read/write (GL ES 3.0+)
    [[nodiscard]] METAGL_API void* glMapBufferRange(BufferTarget target, GLintptr offset, GLsizeiptr length, MapBufferAccessMask access);
    /// @brief Flushes explicitly mapped writes when GL_MAP_FLUSH_EXPLICIT_BIT is set (GL ES 3.0+)
    METAGL_API void glFlushMappedBufferRange(BufferTarget target, GLintptr offset, GLsizeiptr length);
    /// @brief Releases a buffer mapping; returns GL_FALSE if data was corrupted (GL ES 3.0+)
    [[nodiscard]] METAGL_API GLboolean glUnmapBuffer(BufferTarget target);
    /// @brief Returns GL_TRUE if the name is a valid buffer object (GL ES 2.0+)
    [[nodiscard]] METAGL_API bool glIsBuffer(BufferId buffer);
    /// @brief Queries buffer parameters (size, usage, map status) as 32-bit integer (GL ES 2.0+)
    METAGL_API void glGetBufferParameteriv(BufferTarget target, BufferParameter pname, GLint * params);
    /// @brief Queries buffer parameters (e.g. size on large buffers) as 64-bit integer (GL ES 3.0+)
    METAGL_API void glGetBufferParameteri64v(BufferTarget target, BufferParameter pname, GLint64 * params);
    /// @brief Returns the pointer to the currently mapped buffer data store (GL ES 3.0+)
    METAGL_API void glGetBufferPointerv(BufferTarget target, BufferPointerParameter pname, void ** params);

    /// @}
    /// @name Vertex Arrays
    /// @{

    /// @brief Generates one or more Vertex Array Object (VAO) names (GL ES 3.0+)
    METAGL_API void glGenVertexArrays(GLsizei n, VertexArrayId * arrays);
    inline void glGenVertexArrays(std::span<VertexArrayId> arrays) { glGenVertexArrays(detail::checked_glsizei(arrays.size()), arrays.data()); }
    /// @brief Deletes VAOs (GL ES 3.0+)
    METAGL_API void glDeleteVertexArrays(GLsizei n, const VertexArrayId * arrays);
    inline void glDeleteVertexArrays(std::span<const VertexArrayId> arrays) { glDeleteVertexArrays(detail::checked_glsizei(arrays.size()), arrays.data()); }
    /// @brief Binds a VAO; all subsequent attribute state is recorded into it (GL ES 3.0+)
    METAGL_API void glBindVertexArray(VertexArrayId array);
    /// @brief Returns GL_TRUE if the name is a valid VAO (GL ES 3.0+)
    [[nodiscard]] METAGL_API bool glIsVertexArray(VertexArrayId array);
    /// @brief Enables a generic vertex attribute array at a given index (GL ES 2.0+)
    METAGL_API void glEnableVertexAttribArray(AttribLocation index);
    /// @brief Disables a generic vertex attribute array; attribute uses constant value (GL ES 2.0+)
    METAGL_API void glDisableVertexAttribArray(AttribLocation index);
    /// @brief Defines layout/source of a float or normalized-integer vertex attribute (GL ES 2.0+)
    METAGL_API void glVertexAttribPointer(AttribLocation index, GLint size, DataType type, GLboolean normalized, GLsizei stride, const void * pointer);
    /// @brief Defines layout/source of an integer vertex attribute (no normalization) (GL ES 3.0+)
    METAGL_API void glVertexAttribIPointer(AttribLocation index, GLint size, DataType type, GLsizei stride, const void * pointer);
    /// @brief Sets the instancing divisor for an attribute (0=per-vertex, N=per-N-instances) (GL ES 3.0+)
    METAGL_API void glVertexAttribDivisor(AttribLocation index, GLuint divisor);
    /// @brief Sets a constant float scalar value for a vertex attribute (GL ES 2.0+)
    METAGL_API void glVertexAttrib1f(AttribLocation index, GLfloat x);
    /// @brief Sets a constant vec2 float value for a vertex attribute (GL ES 2.0+)
    METAGL_API void glVertexAttrib2f(AttribLocation index, GLfloat x, GLfloat y);
    /// @brief Sets a constant vec3 float value for a vertex attribute (GL ES 2.0+)
    METAGL_API void glVertexAttrib3f(AttribLocation index, GLfloat x, GLfloat y, GLfloat z);
    /// @brief Sets a constant vec4 float value for a vertex attribute (GL ES 2.0+)
    METAGL_API void glVertexAttrib4f(AttribLocation index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    /// @brief Sets a constant float scalar for a vertex attribute from a pointer (GL ES 2.0+)
    METAGL_API void glVertexAttrib1fv(AttribLocation index, const GLfloat * v);
    /// @brief Sets a constant vec2 float value for a vertex attribute from a pointer (GL ES 2.0+)
    METAGL_API void glVertexAttrib2fv(AttribLocation index, const GLfloat * v);
    /// @brief Sets a constant vec3 float value for a vertex attribute from a pointer (GL ES 2.0+)
    METAGL_API void glVertexAttrib3fv(AttribLocation index, const GLfloat * v);
    /// @brief Sets a constant vec4 float value for a vertex attribute from a pointer (GL ES 2.0+)
    METAGL_API void glVertexAttrib4fv(AttribLocation index, const GLfloat * v);
    /// @brief Sets a constant ivec4 signed integer value for a vertex attribute (GL ES 3.0+)
    METAGL_API void glVertexAttribI4i(AttribLocation index, GLint x, GLint y, GLint z, GLint w);
    /// @brief Sets a constant uvec4 unsigned integer value for a vertex attribute (GL ES 3.0+)
    METAGL_API void glVertexAttribI4ui(AttribLocation index, GLuint x, GLuint y, GLuint z, GLuint w);
    /// @brief Sets a constant ivec4 value for a vertex attribute from a pointer (GL ES 3.0+)
    METAGL_API void glVertexAttribI4iv(AttribLocation index, const GLint * v);
    /// @brief Sets a constant uvec4 value for a vertex attribute from a pointer (GL ES 3.0+)
    METAGL_API void glVertexAttribI4uiv(AttribLocation index, const GLuint * v);
    /// @brief Queries float state of a vertex attribute (type, size, stride, etc.) (GL ES 2.0+)
    METAGL_API void glGetVertexAttribfv(AttribLocation index, VertexAttribParameter pname, GLfloat * params);
    /// @brief Queries integer state of a vertex attribute (GL ES 2.0+)
    METAGL_API void glGetVertexAttribiv(AttribLocation index, VertexAttribParameter pname, GLint * params);
    /// @brief Queries integer state of an integer-type vertex attribute (GL ES 3.0+)
    METAGL_API void glGetVertexAttribIiv(AttribLocation index, VertexAttribParameter pname, GLint * params);
    /// @brief Queries unsigned integer state of an unsigned-integer vertex attribute (GL ES 3.0+)
    METAGL_API void glGetVertexAttribIuiv(AttribLocation index, VertexAttribParameter pname, GLuint * params);
    /// @brief Returns the offset/pointer stored for a vertex attribute (GL ES 2.0+)
    METAGL_API void glGetVertexAttribPointerv(AttribLocation index, VertexAttribParameter pname, void ** pointer);
    /// @brief Specifies float attribute format independently from buffer binding (GL ES 3.1+)
    METAGL_API void glVertexAttribFormat(AttribLocation attribindex, GLint size, DataType type, GLboolean normalized, GLuint relativeoffset);
    /// @brief Specifies integer attribute format independently from buffer binding (GL ES 3.1+)
    METAGL_API void glVertexAttribIFormat(AttribLocation attribindex, GLint size, DataType type, GLuint relativeoffset);
    /// @brief Associates a vertex attribute index with a vertex buffer binding point (GL ES 3.1+)
    METAGL_API void glVertexAttribBinding(AttribLocation attribindex, GLuint bindingindex);
    /// @brief Binds a buffer to a vertex buffer binding point with offset and stride (GL ES 3.1+)
    METAGL_API void glBindVertexBuffer(GLuint bindingindex, BufferId buffer, GLintptr offset, GLsizei stride);
    /// @brief Sets the instancing divisor for a vertex buffer binding point (GL ES 3.1+)
    METAGL_API void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor);

    /// @}
    /// @name Drawing Commands
    /// @{

    /// @brief Renders primitives from vertex arrays starting at a given offset (GL ES 2.0+)
    METAGL_API void glDrawArrays(PrimitiveType mode, GLint first, GLsizei count);
    /// @brief Renders multiple instances of geometry using vertex arrays (GL ES 3.0+)
    METAGL_API void glDrawArraysInstanced(PrimitiveType mode, GLint first, GLsizei count, GLsizei instancecount);
    /// @brief Renders instances; draw parameters read from GL_DRAW_INDIRECT_BUFFER (GL ES 3.1+)
    METAGL_API void glDrawArraysIndirect(PrimitiveType mode, const void * indirect);
    /// @brief Renders indexed primitives from vertex arrays and an index buffer (GL ES 2.0+)
    METAGL_API void glDrawElements(PrimitiveType mode, GLsizei count, DataType type, const void * indices);
    inline void glDrawElements(PrimitiveType mode, GLsizei count, IndexType type, const void* indices)
    {
        glDrawElements(mode, count, static_cast<DataType>(type), indices);
    }
    /// @brief Renders multiple instances using indexed drawing (GL ES 3.0+)
    METAGL_API void glDrawElementsInstanced(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLsizei instancecount);
    inline void glDrawElementsInstanced(PrimitiveType mode, GLsizei count, IndexType type, const void* indices, GLsizei instancecount)
    {
        glDrawElementsInstanced(mode, count, static_cast<DataType>(type), indices, instancecount);
    }
    /// @brief Indexed draw with index range hints for driver prefetch optimization (GL ES 3.0+)
    METAGL_API void glDrawRangeElements(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, DataType type, const void * indices);
    inline void glDrawRangeElements(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, IndexType type, const void* indices)
    {
        glDrawRangeElements(mode, start, end, count, static_cast<DataType>(type), indices);
    }
    /// @brief Indexed draw with a constant base vertex offset added to each index (GL ES 3.2+)
    METAGL_API void glDrawElementsBaseVertex(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLint basevertex);
    inline void glDrawElementsBaseVertex(PrimitiveType mode, GLsizei count, IndexType type, const void* indices, GLint basevertex)
    {
        glDrawElementsBaseVertex(mode, count, static_cast<DataType>(type), indices, basevertex);
    }
    /// @brief Instanced indexed draw with a base vertex offset (GL ES 3.2+)
    METAGL_API void glDrawElementsInstancedBaseVertex(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLsizei instancecount, GLint basevertex);
    inline void glDrawElementsInstancedBaseVertex(PrimitiveType mode, GLsizei count, IndexType type, const void* indices, GLsizei instancecount, GLint basevertex)
    {
        glDrawElementsInstancedBaseVertex(mode, count, static_cast<DataType>(type), indices, instancecount, basevertex);
    }
    /// @brief Range-indexed draw with a base vertex offset (GL ES 3.2+)
    METAGL_API void glDrawRangeElementsBaseVertex(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, DataType type, const void * indices, GLint basevertex);
    inline void glDrawRangeElementsBaseVertex(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, IndexType type, const void* indices, GLint basevertex)
    {
        glDrawRangeElementsBaseVertex(mode, start, end, count, static_cast<DataType>(type), indices, basevertex);
    }
    /// @brief Indexed instanced draw; parameters read from GL_DRAW_INDIRECT_BUFFER (GL ES 3.1+)
    METAGL_API void glDrawElementsIndirect(PrimitiveType mode, DataType type, const void * indirect);
    inline void glDrawElementsIndirect(PrimitiveType mode, IndexType type, const void* indirect)
    {
        glDrawElementsIndirect(mode, static_cast<DataType>(type), indirect);
    }
    /// @brief Specifies the list of color buffers that fragment outputs are written to (GL ES 3.0+)
    METAGL_API void glDrawBuffers(GLsizei n, const DrawBuffer * bufs);
    inline void glDrawBuffers(std::span<const DrawBuffer> bufs) { glDrawBuffers(detail::checked_glsizei(bufs.size()), bufs.data()); }
    /// @brief Selects a color buffer as the source for glReadPixels and copy operations (GL ES 3.0+)
    METAGL_API void glReadBuffer(ReadBuffer src);
    /// @brief Reads a rectangular block of pixels from the framebuffer into CPU memory (GL ES 2.0+)
    METAGL_API void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelFormat format, PixelType type, void * pixels);
    /// @brief Reads pixels with an explicit destination buffer size for robustness (GL ES 3.2+)
    METAGL_API void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelFormat format, PixelType type, GLsizei bufSize, void * data);
    /// @brief Clears color, depth, and/or stencil buffers to their clear values (GL ES 2.0+)
    METAGL_API void glClear(ClearBufferBit mask);
    /// @brief Sets the RGBA value used when clearing the color buffer (GL ES 2.0+)
    METAGL_API void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
    /// @brief Sets the float depth value (0.0–1.0) used when clearing the depth buffer (GL ES 2.0+)
    METAGL_API void glClearDepthf(GLfloat d);
    /// @brief Sets the integer value used when clearing the stencil buffer (GL ES 2.0+)
    METAGL_API void glClearStencil(GLint s);
    /**
     * @brief Clears a float color or depth buffer attachment (GL ES 3.0+).
     * @note `drawbuffer` must be zero when `buffer` is
     *       `FloatClearBuffer::Depth`.
     */
    METAGL_API void glClearBufferfv(FloatClearBuffer buffer, GLint drawbuffer, const GLfloat * value);
    /**
     * @brief Clears a signed integer color or stencil buffer attachment (GL ES 3.0+).
     * @note `drawbuffer` must be zero when `buffer` is
     *       `SignedIntegerClearBuffer::Stencil`.
     */
    METAGL_API void glClearBufferiv(SignedIntegerClearBuffer buffer, GLint drawbuffer, const GLint * value);
    /// @brief Clears an unsigned integer color buffer attachment to a given value (GL ES 3.0+)
    METAGL_API void glClearBufferuiv(UnsignedIntegerClearBuffer buffer, GLint drawbuffer, const GLuint * value);
    /**
     * @brief Clears the depth and stencil attachments together (GL ES 3.0+).
     *
     * OpenGL requires the raw `buffer` and `drawbuffer` arguments to be
     * `GL_DEPTH_STENCIL` and zero respectively. This safe wrapper supplies
     * both fixed values so callers cannot form an invalid combination.
     */
    METAGL_API void glClearBufferfi(GLfloat depth, GLint stencil);

    /// @}
    /// @name Shaders and Programs
    /// @{

    /// @brief Creates a shader object of the given type and returns its handle (GL ES 2.0+)
    [[nodiscard]] METAGL_API ShaderId glCreateShader(ShaderType type);
    /// @brief Marks a shader for deletion (deferred until detached from all programs) (GL ES 2.0+)
    METAGL_API void glDeleteShader(ShaderId shader);
    /// @brief Loads GLSL source strings into a shader object (GL ES 2.0+)
    METAGL_API void glShaderSource(ShaderId shader, GLsizei count, const GLchar *const* string, const GLint * length);
    inline void glShaderSource(ShaderId shader, std::string_view source) { const GLchar* ptr = source.data(); const GLint len = detail::checked_glsizei(source.size()); glShaderSource(shader, 1, &ptr, &len); }
    /// @brief Compiles the GLSL source previously loaded into a shader object (GL ES 2.0+)
    METAGL_API void glCompileShader(ShaderId shader);
    /// @brief Loads pre-compiled binary shader code into one or more shader objects (GL ES 2.0+)
    METAGL_API void glShaderBinary(GLsizei count, const ShaderId * shaders, ShaderBinaryFormat binaryFormat, const void * binary, GLsizei length);
    /// @brief Hints that the GLSL compiler resources may be freed (GL ES 2.0+)
    METAGL_API void glReleaseShaderCompiler(void);
    /// @brief Queries shader parameters (compile status, type, source length, etc.) (GL ES 2.0+)
    METAGL_API void glGetShaderiv(ShaderId shader, ShaderParameter pname, GLint * params);
    /// @brief Returns the compiler info log for a shader (errors and warnings) (GL ES 2.0+)
    METAGL_API void glGetShaderInfoLog(ShaderId shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
    /// @brief Returns the GLSL source code stored in a shader object (GL ES 2.0+)
    METAGL_API void glGetShaderSource(ShaderId shader, GLsizei bufSize, GLsizei * length, GLchar * source);
    /// @brief Returns the precision range for lowp/mediump/highp in vertex/fragment shaders (GL ES 2.0+)
    METAGL_API void glGetShaderPrecisionFormat(ShaderType shadertype, PrecisionType precisiontype, GLint * range, GLint * precision);
    /// @brief Returns GL_TRUE if the name is a valid shader object (GL ES 2.0+)
    [[nodiscard]] METAGL_API bool glIsShader(ShaderId shader);
    /// @brief Creates a program object and returns its handle (GL ES 2.0+)
    [[nodiscard]] METAGL_API ProgramId glCreateProgram(void);
    /// @brief Deletes a program object (deferred until no longer in use) (GL ES 2.0+)
    METAGL_API void glDeleteProgram(ProgramId program);
    /// @brief Attaches a compiled shader to a program for the next link operation (GL ES 2.0+)
    METAGL_API void glAttachShader(ProgramId program, ShaderId shader);
    /// @brief Detaches a shader from a program (GL ES 2.0+)
    METAGL_API void glDetachShader(ProgramId program, ShaderId shader);
    /// @brief Links all attached shaders into an executable GPU program (GL ES 2.0+)
    METAGL_API void glLinkProgram(ProgramId program);
    /// @brief Installs a linked program as part of the current rendering state (GL ES 2.0+)
    METAGL_API void glUseProgram(ProgramId program);
    /// @brief Validates whether a program can execute given the current GL state (GL ES 2.0+)
    METAGL_API void glValidateProgram(ProgramId program);
    /// @brief Queries program parameters (link status, active uniforms, etc.) (GL ES 2.0+)
    METAGL_API void glGetProgramiv(ProgramId program, ProgramParameter pname, GLint * params);
    /// @brief Returns the linker info log for a program (errors and warnings) (GL ES 2.0+)
    METAGL_API void glGetProgramInfoLog(ProgramId program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
    /// @brief Returns GL_TRUE if the name is a valid program object (GL ES 2.0+)
    [[nodiscard]] METAGL_API bool glIsProgram(ProgramId program);
    /// @brief Returns the shader objects currently attached to a program (GL ES 2.0+)
    METAGL_API void glGetAttachedShaders(ProgramId program, GLsizei maxCount, GLsizei * count, ShaderId * shaders);
    /// @brief Associates a vertex shader input variable with an attribute index before link (GL ES 2.0+)
    METAGL_API void glBindAttribLocation(ProgramId program, AttribLocation index, const GLchar * name);
    /// @brief Returns the attribute index of a named vertex shader input in a linked program (GL ES 2.0+)
    [[nodiscard]] METAGL_API AttribLocation glGetAttribLocation(ProgramId program, const GLchar * name);
    /// @brief Returns name, type, and size of an active vertex attribute variable (GL ES 2.0+)
    METAGL_API void glGetActiveAttrib(ProgramId program, ActiveAttribIndex index, GLsizei bufSize, GLsizei * length, GLint * size, UniformType * type, GLchar * name);
    inline void glGetActiveAttrib(ProgramId program, AttribLocation index, GLsizei bufSize, GLsizei* length, GLint* size, UniformType* type, GLchar* name)
    {
        glGetActiveAttrib(program,
            ActiveAttribIndex{static_cast<GLuint>(index.value)},
            bufSize, length, size, type, name);
    }
    /// @brief Returns the binary representation of a linked program for caching (GL ES 3.0+)
    METAGL_API void glGetProgramBinary(ProgramId program, GLsizei bufSize, GLsizei * length, ProgramBinaryFormat * binaryFormat, void * binary);
    /// @brief Loads a cached binary into a program, bypassing compilation and linking (GL ES 3.0+)
    METAGL_API void glProgramBinary(ProgramId program, ProgramBinaryFormat binaryFormat, const void * binary, GLsizei length);
    /// @brief Sets program parameters (binary retrievable hint, separable flag) (GL ES 3.0+)
    METAGL_API void glProgramParameteri(ProgramId program, ProgramParameter pname, GLint value);
    /// @brief Returns the fragment output location for a named output variable (GL ES 3.0+)
    [[nodiscard]] METAGL_API GLint glGetFragDataLocation(ProgramId program, const GLchar * name);
    /// @brief Queries properties of a program interface (e.g. number of active uniforms) (GL ES 3.1+)
    METAGL_API void glGetProgramInterfaceiv(ProgramId program, ProgramInterface programInterface, ProgramInterfaceParameter pname, GLint * params);
    /// @brief Returns the index of a named resource within a program interface (GL ES 3.1+)
    [[nodiscard]] METAGL_API GLuint glGetProgramResourceIndex(ProgramId program, ProgramInterface programInterface, const GLchar * name);
    /// @brief Returns the name of a resource at a given index in a program interface (GL ES 3.1+)
    METAGL_API void glGetProgramResourceName(ProgramId program, ProgramInterface programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
    /// @brief Returns multiple properties of a program interface resource in one call (GL ES 3.1+)
    METAGL_API void glGetProgramResourceiv(ProgramId program, ProgramInterface programInterface, GLuint index, GLsizei propCount, const ProgramResourceProperty * props, GLsizei count, GLsizei * length, GLint * params);
    inline void glGetProgramResourceiv(ProgramId program, ProgramInterface programInterface, GLuint index, std::span<const ProgramResourceProperty> props, GLsizei count, GLsizei * length, GLint * params) { glGetProgramResourceiv(program, programInterface, index, detail::checked_glsizei(props.size()), props.data(), count, length, params); }
    /// @brief Returns the location of a named resource within a program interface (GL ES 3.1+)
    [[nodiscard]] METAGL_API GLint glGetProgramResourceLocation(ProgramId program, ProgramInterface programInterface, const GLchar * name);

    /// @}
    /// @name Uniform Variables
    /// @{

    /// @brief Returns the integer location of a named uniform in a linked program (GL ES 2.0+)
    [[nodiscard]] METAGL_API UniformLocation glGetUniformLocation(ProgramId program, const GLchar * name);
    /// @brief Returns the name, type, and size of an active uniform variable (GL ES 2.0+)
    METAGL_API void glGetActiveUniform(ProgramId program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, UniformType * type, GLchar * name);
    /// @brief Queries parameters for multiple uniforms by index in one call (GL ES 3.0+)
    METAGL_API void glGetActiveUniformsiv(ProgramId program, GLsizei uniformCount, const GLuint * uniformIndices, UniformParameter pname, GLint * params);
    /// @brief Returns the indices of multiple named uniform variables (GL ES 3.0+)
    METAGL_API void glGetUniformIndices(ProgramId program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
    /// @brief Returns the index of a named uniform block in a linked program (GL ES 3.0+)
    [[nodiscard]] METAGL_API GLuint glGetUniformBlockIndex(ProgramId program, const GLchar * uniformBlockName);
    /// @brief Queries parameters of a uniform block (size, binding, member count) (GL ES 3.0+)
    METAGL_API void glGetActiveUniformBlockiv(ProgramId program, GLuint uniformBlockIndex, UniformBlockParameter pname, GLint * params);
    /// @brief Returns the name string of a uniform block at a given index (GL ES 3.0+)
    METAGL_API void glGetActiveUniformBlockName(ProgramId program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
    /// @brief Assigns a uniform block to a specific uniform buffer binding point (GL ES 3.0+)
    METAGL_API void glUniformBlockBinding(ProgramId program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
    /// @brief Sets a float scalar uniform in the current program (GL ES 2.0+)
    METAGL_API void glUniform1f(UniformLocation location, GLfloat v0);
    /// @brief Sets a vec2 float uniform in the current program (GL ES 2.0+)
    METAGL_API void glUniform2f(UniformLocation location, GLfloat v0, GLfloat v1);
    /// @brief Sets a vec3 float uniform in the current program (GL ES 2.0+)
    METAGL_API void glUniform3f(UniformLocation location, GLfloat v0, GLfloat v1, GLfloat v2);
    /// @brief Sets a vec4 float uniform in the current program (GL ES 2.0+)
    METAGL_API void glUniform4f(UniformLocation location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    /// @brief Sets an array of float scalar uniforms in the current program (GL ES 2.0+)
    METAGL_API void glUniform1fv(UniformLocation location, GLsizei count, const GLfloat * value);
    /// @brief Sets an array of vec2 uniforms in the current program (GL ES 2.0+)
    METAGL_API void glUniform2fv(UniformLocation location, GLsizei count, const GLfloat * value);
    /// @brief Sets an array of vec3 uniforms in the current program (GL ES 2.0+)
    METAGL_API void glUniform3fv(UniformLocation location, GLsizei count, const GLfloat * value);
    /// @brief Sets an array of vec4 uniforms in the current program (GL ES 2.0+)
    METAGL_API void glUniform4fv(UniformLocation location, GLsizei count, const GLfloat * value);
    /// @brief Sets an int scalar uniform; also used to assign sampler texture units (GL ES 2.0+)
    METAGL_API void glUniform1i(UniformLocation location, GLint v0);
    /// @brief Sets an ivec2 uniform in the current program (GL ES 2.0+)
    METAGL_API void glUniform2i(UniformLocation location, GLint v0, GLint v1);
    /// @brief Sets an ivec3 uniform in the current program (GL ES 2.0+)
    METAGL_API void glUniform3i(UniformLocation location, GLint v0, GLint v1, GLint v2);
    /// @brief Sets an ivec4 uniform in the current program (GL ES 2.0+)
    METAGL_API void glUniform4i(UniformLocation location, GLint v0, GLint v1, GLint v2, GLint v3);
    /// @brief Sets an array of int scalar uniforms in the current program (GL ES 2.0+)
    METAGL_API void glUniform1iv(UniformLocation location, GLsizei count, const GLint * value);
    /// @brief Sets an array of ivec2 uniforms in the current program (GL ES 2.0+)
    METAGL_API void glUniform2iv(UniformLocation location, GLsizei count, const GLint * value);
    /// @brief Sets an array of ivec3 uniforms in the current program (GL ES 2.0+)
    METAGL_API void glUniform3iv(UniformLocation location, GLsizei count, const GLint * value);
    /// @brief Sets an array of ivec4 uniforms in the current program (GL ES 2.0+)
    METAGL_API void glUniform4iv(UniformLocation location, GLsizei count, const GLint * value);
    /// @brief Sets an unsigned int scalar uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniform1ui(UniformLocation location, GLuint v0);
    /// @brief Sets a uvec2 uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniform2ui(UniformLocation location, GLuint v0, GLuint v1);
    /// @brief Sets a uvec3 uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniform3ui(UniformLocation location, GLuint v0, GLuint v1, GLuint v2);
    /// @brief Sets a uvec4 uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniform4ui(UniformLocation location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    /// @brief Sets an array of unsigned int scalar uniforms (GL ES 3.0+)
    METAGL_API void glUniform1uiv(UniformLocation location, GLsizei count, const GLuint * value);
    /// @brief Sets an array of uvec2 uniforms (GL ES 3.0+)
    METAGL_API void glUniform2uiv(UniformLocation location, GLsizei count, const GLuint * value);
    /// @brief Sets an array of uvec3 uniforms (GL ES 3.0+)
    METAGL_API void glUniform3uiv(UniformLocation location, GLsizei count, const GLuint * value);
    /// @brief Sets an array of uvec4 uniforms (GL ES 3.0+)
    METAGL_API void glUniform4uiv(UniformLocation location, GLsizei count, const GLuint * value);
    /// @brief Sets a mat2 uniform (or array of mat2) in the current program (GL ES 2.0+)
    METAGL_API void glUniformMatrix2fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat3 uniform (or array of mat3) in the current program (GL ES 2.0+)
    METAGL_API void glUniformMatrix3fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat4 uniform (or array of mat4) in the current program (GL ES 2.0+)
    METAGL_API void glUniformMatrix4fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat2x3 uniform (2 columns, 3 rows); non-square matrices not in ES 2.0 (GL ES 3.0+)
    METAGL_API void glUniformMatrix2x3fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat2x4 uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniformMatrix2x4fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat3x2 uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniformMatrix3x2fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat3x4 uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniformMatrix3x4fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat4x2 uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniformMatrix4x2fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat4x3 uniform in the current program (GL ES 3.0+)
    METAGL_API void glUniformMatrix4x3fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Returns the current value of a float uniform from a linked program (GL ES 2.0+)
    METAGL_API void glGetUniformfv(ProgramId program, UniformLocation location, GLfloat * params);
    /// @brief Returns the current value of an integer uniform from a linked program (GL ES 2.0+)
    METAGL_API void glGetUniformiv(ProgramId program, UniformLocation location, GLint * params);
    /// @brief Returns the current value of an unsigned integer uniform (GL ES 3.0+)
    METAGL_API void glGetUniformuiv(ProgramId program, UniformLocation location, GLuint * params);
    /// @brief Returns float uniform values with an explicit destination buffer size for robustness (GL ES 3.2+)
    METAGL_API void glGetnUniformfv(ProgramId program, UniformLocation location, GLsizei bufSize, GLfloat * params);
    /// @brief Returns integer uniform values with an explicit destination buffer size for robustness (GL ES 3.2+)
    METAGL_API void glGetnUniformiv(ProgramId program, UniformLocation location, GLsizei bufSize, GLint * params);
    /// @brief Returns unsigned integer uniform values with an explicit destination buffer size for robustness (GL ES 3.2+)
    METAGL_API void glGetnUniformuiv(ProgramId program, UniformLocation location, GLsizei bufSize, GLuint * params);
    /// @brief Sets a float scalar uniform in a specific program without binding it (GL ES 3.1+)
    METAGL_API void glProgramUniform1f(ProgramId program, UniformLocation location, GLfloat v0);
    /// @brief Sets a vec2 float uniform in a specific program without binding it (GL ES 3.1+)
    METAGL_API void glProgramUniform2f(ProgramId program, UniformLocation location, GLfloat v0, GLfloat v1);
    /// @brief Sets a vec3 float uniform in a specific program without binding it (GL ES 3.1+)
    METAGL_API void glProgramUniform3f(ProgramId program, UniformLocation location, GLfloat v0, GLfloat v1, GLfloat v2);
    /// @brief Sets a vec4 float uniform in a specific program without binding it (GL ES 3.1+)
    METAGL_API void glProgramUniform4f(ProgramId program, UniformLocation location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
    /// @brief Sets an array of float scalar uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform1fv(ProgramId program, UniformLocation location, GLsizei count, const GLfloat * value);
    /// @brief Sets an array of vec2 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform2fv(ProgramId program, UniformLocation location, GLsizei count, const GLfloat * value);
    /// @brief Sets an array of vec3 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform3fv(ProgramId program, UniformLocation location, GLsizei count, const GLfloat * value);
    /// @brief Sets an array of vec4 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform4fv(ProgramId program, UniformLocation location, GLsizei count, const GLfloat * value);
    /// @brief Sets an int scalar uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform1i(ProgramId program, UniformLocation location, GLint v0);
    /// @brief Sets an ivec2 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform2i(ProgramId program, UniformLocation location, GLint v0, GLint v1);
    /// @brief Sets an ivec3 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform3i(ProgramId program, UniformLocation location, GLint v0, GLint v1, GLint v2);
    /// @brief Sets an ivec4 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform4i(ProgramId program, UniformLocation location, GLint v0, GLint v1, GLint v2, GLint v3);
    /// @brief Sets an array of int scalars in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform1iv(ProgramId program, UniformLocation location, GLsizei count, const GLint * value);
    /// @brief Sets an array of ivec2 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform2iv(ProgramId program, UniformLocation location, GLsizei count, const GLint * value);
    /// @brief Sets an array of ivec3 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform3iv(ProgramId program, UniformLocation location, GLsizei count, const GLint * value);
    /// @brief Sets an array of ivec4 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform4iv(ProgramId program, UniformLocation location, GLsizei count, const GLint * value);
    /// @brief Sets an unsigned int scalar uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform1ui(ProgramId program, UniformLocation location, GLuint v0);
    /// @brief Sets a uvec2 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform2ui(ProgramId program, UniformLocation location, GLuint v0, GLuint v1);
    /// @brief Sets a uvec3 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform3ui(ProgramId program, UniformLocation location, GLuint v0, GLuint v1, GLuint v2);
    /// @brief Sets a uvec4 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform4ui(ProgramId program, UniformLocation location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
    /// @brief Sets an array of unsigned int scalars in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform1uiv(ProgramId program, UniformLocation location, GLsizei count, const GLuint * value);
    /// @brief Sets an array of uvec2 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform2uiv(ProgramId program, UniformLocation location, GLsizei count, const GLuint * value);
    /// @brief Sets an array of uvec3 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform3uiv(ProgramId program, UniformLocation location, GLsizei count, const GLuint * value);
    /// @brief Sets an array of uvec4 uniforms in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniform4uiv(ProgramId program, UniformLocation location, GLsizei count, const GLuint * value);
    /// @brief Sets a mat2 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix2fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat3 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix3fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat4 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix4fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat2x3 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix2x3fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat2x4 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix2x4fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat3x2 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix3x2fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat3x4 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix3x4fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat4x2 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix4x2fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);
    /// @brief Sets a mat4x3 uniform in a specific program (GL ES 3.1+)
    METAGL_API void glProgramUniformMatrix4x3fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value);

    /// @}
    /// @name Texture Objects
    /// @{

    /// @brief Generates one or more texture object names (GL ES 2.0+)
    METAGL_API void glGenTextures(GLsizei n, TextureId * textures);
    inline void glGenTextures(std::span<TextureId> textures) { glGenTextures(detail::checked_glsizei(textures.size()), textures.data()); }
    /// @brief Deletes texture objects and frees their GPU memory (GL ES 2.0+)
    METAGL_API void glDeleteTextures(GLsizei n, const TextureId * textures);
    inline void glDeleteTextures(std::span<const TextureId> textures) { glDeleteTextures(detail::checked_glsizei(textures.size()), textures.data()); }
    /// @brief Binds a texture to a target in the active texture unit (GL ES 2.0+)
    METAGL_API void glBindTexture(TextureTarget target, TextureId texture);
    inline void glBindTexture(TextureBindingTarget target, TextureId texture)
    {
        glBindTexture(static_cast<TextureTarget>(target), texture);
    }
    /// @brief Selects the active texture unit for subsequent texture operations (GL ES 2.0+)
    METAGL_API void glActiveTexture(TextureUnit texture);
    /// @brief Returns GL_TRUE if the name is a valid texture object (GL ES 2.0+)
    [[nodiscard]] METAGL_API bool glIsTexture(TextureId texture);
    /// @brief Specifies a 2D texture image and allocates GPU storage (GL ES 2.0+)
    METAGL_API void glTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat, GLsizei width, GLsizei height, GLint border, PixelFormat format, PixelType type, const void * pixels);
    /// @brief Specifies a 3D or 2D-array texture image and allocates GPU storage (GL ES 3.0+)
    METAGL_API void glTexImage3D(TextureTarget target, GLint level, InternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, PixelFormat format, PixelType type, const void * pixels);
    /// @brief Updates a sub-region of an existing 2D texture image (GL ES 2.0+)
    METAGL_API void glTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, PixelFormat format, PixelType type, const void * pixels);
    /// @brief Updates a sub-region of an existing 3D or 2D-array texture (GL ES 3.0+)
    METAGL_API void glTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, PixelFormat format, PixelType type, const void * pixels);
    /// @brief Allocates immutable storage for all mip levels of a 2D texture with a sized format (GL ES 3.0+)
    METAGL_API void glTexStorage2D(TextureTarget target, GLsizei levels, SizedInternalFormat internalformat, GLsizei width, GLsizei height);
    /// @brief Allocates immutable storage for all mip levels of a 2D texture with a compressed format (GL ES 3.0+)
    METAGL_API void glTexStorage2D(TextureTarget target, GLsizei levels, CompressedInternalFormat internalformat, GLsizei width, GLsizei height);

    /// @brief Allocates immutable storage for all mip levels of a 3D or array texture with a sized format (GL ES 3.0+)
    METAGL_API void glTexStorage3D(TextureTarget target, GLsizei levels, SizedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth);
    /// @brief Allocates immutable storage for all mip levels of a 3D or array texture with a compressed format (GL ES 3.0+)
    METAGL_API void glTexStorage3D(TextureTarget target, GLsizei levels, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth);

    /// @brief Allocates immutable multisample storage for a 2D MSAA texture (GL ES 3.1+)
    METAGL_API void glTexStorage2DMultisample(TextureTarget target, GLsizei samples, SizedInternalFormat internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);

    /// @brief Allocates immutable multisample storage for a 2D MSAA array texture (GL ES 3.2+)
    METAGL_API void glTexStorage3DMultisample(TextureTarget target, GLsizei samples, SizedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
    /// @brief Loads compressed image data (ETC2, ASTC, etc.) into a 2D texture (GL ES 2.0+)
    METAGL_API void glCompressedTexImage2D(TextureTarget target, GLint level, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
    /// @brief Loads compressed image data into a 3D or 2D-array texture (GL ES 3.0+)
    METAGL_API void glCompressedTexImage3D(TextureTarget target, GLint level, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
    /// @brief Updates a sub-region of an existing compressed 2D texture (GL ES 2.0+)
    METAGL_API void glCompressedTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, CompressedInternalFormat format, GLsizei imageSize, const void * data);
    /// @brief Updates a sub-region of an existing compressed 3D or array texture (GL ES 3.0+)
    METAGL_API void glCompressedTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, CompressedInternalFormat format, GLsizei imageSize, const void * data);
    /// @brief Copies pixels from the read framebuffer into a 2D texture image (GL ES 2.0+)
    METAGL_API void glCopyTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
    /// @brief Copies a framebuffer region into a sub-region of a 2D texture (GL ES 2.0+)
    METAGL_API void glCopyTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    /// @brief Copies a framebuffer region into a slice of a 3D or array texture (GL ES 3.0+)
    METAGL_API void glCopyTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    /**
     * @brief Compatibility overload for copying between texture images (GL ES 3.2+).
     *
     * This original raw-name overload remains available for existing consumers.
     * Prefer the typed overloads below: they restrict texture targets and also
     * represent texture/renderbuffer copies without casts.
     */
    METAGL_API void glCopyImageSubData(GLuint srcName, TextureTarget srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, TextureTarget dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
    /// @brief Copies a region between two texture images (GL ES 3.2+).
    METAGL_API void glCopyImageSubData(TextureId srcName, ImageCopyTextureTarget srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, TextureId dstName, ImageCopyTextureTarget dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);
    /// @brief Copies one texture layer or slice into a renderbuffer (GL ES 3.2+).
    METAGL_API void glCopyImageSubData(TextureId srcName, ImageCopyTextureTarget srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, RenderbufferId dstName, GLint dstX, GLint dstY, GLsizei width, GLsizei height);
    /// @brief Copies a renderbuffer into one texture layer or slice (GL ES 3.2+).
    METAGL_API void glCopyImageSubData(RenderbufferId srcName, GLint srcX, GLint srcY, TextureId dstName, ImageCopyTextureTarget dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height);
    /// @brief Copies a two-dimensional region between renderbuffers (GL ES 3.2+).
    METAGL_API void glCopyImageSubData(RenderbufferId srcName, GLint srcX, GLint srcY, RenderbufferId dstName, GLint dstX, GLint dstY, GLsizei width, GLsizei height);
    /// @brief Auto-generates all mipmap levels below the base level by downsampling (GL ES 2.0+)
    METAGL_API void glGenerateMipmap(TextureTarget target);
    /// @brief Sets a float texture sampling parameter (filter, LOD, wrap mode) (GL ES 2.0+)
    METAGL_API void glTexParameterf(TextureTarget target, TextureParameterSetter pname, GLfloat param);
    /// @brief Sets an integer texture sampling parameter (GL ES 2.0+)
    METAGL_API void glTexParameteri(TextureTarget target, TextureParameterSetter pname, GLint param);
    /// @brief Sets multiple float texture parameters from a pointer (GL ES 2.0+)
    METAGL_API void glTexParameterfv(TextureTarget target, TextureParameterSetter pname, const GLfloat * params);
    /// @brief Sets multiple integer texture parameters from a pointer (GL ES 2.0+)
    METAGL_API void glTexParameteriv(TextureTarget target, TextureParameterSetter pname, const GLint * params);
    /// @brief Sets integer texture parameters without integer-to-float conversion (GL ES 3.2+)
    METAGL_API void glTexParameterIiv(TextureTarget target, TextureParameterSetter pname, const GLint * params);
    /// @brief Sets unsigned integer texture parameters without conversion (GL ES 3.2+)
    METAGL_API void glTexParameterIuiv(TextureTarget target, TextureParameterSetter pname, const GLuint * params);
    /// @brief Returns float texture sampling parameters (GL ES 2.0+)
    METAGL_API void glGetTexParameterfv(TextureTarget target, TextureParameterQuery pname, GLfloat * params);
    /// @brief Returns integer texture sampling parameters (GL ES 2.0+)
    METAGL_API void glGetTexParameteriv(TextureTarget target, TextureParameterQuery pname, GLint * params);
    /// @brief Returns integer texture parameters as raw integers (GL ES 3.2+)
    METAGL_API void glGetTexParameterIiv(TextureTarget target, TextureParameterQuery pname, GLint * params);
    /// @brief Returns unsigned integer texture parameters as raw unsigned integers (GL ES 3.2+)
    METAGL_API void glGetTexParameterIuiv(TextureTarget target, TextureParameterQuery pname, GLuint * params);
    /// @brief Returns integer parameters of a specific texture mipmap level (GL ES 3.1+)
    METAGL_API void glGetTexLevelParameteriv(TextureTarget target, GLint level, TextureLevelParameter pname, GLint * params);
    /// @brief Returns float parameters of a specific texture mipmap level (GL ES 3.1+)
    METAGL_API void glGetTexLevelParameterfv(TextureTarget target, GLint level, TextureLevelParameter pname, GLfloat * params);
    /// @brief Attaches a buffer object's data store to a buffer texture (GL ES 3.2+)
    METAGL_API void glTexBuffer(TextureTarget target, InternalFormat internalformat, BufferId buffer);
    /// @brief Attaches a sub-range of a buffer object to a buffer texture (GL ES 3.2+)
    METAGL_API void glTexBufferRange(TextureTarget target, InternalFormat internalformat, BufferId buffer, GLintptr offset, GLsizeiptr size);
    /// @brief Returns the location of a specific sample in a multisample texture (GL ES 3.1+)
    METAGL_API void glGetMultisamplefv(MultisampleParameter pname, GLuint index, GLfloat * val);
    /// @brief Queries implementation properties for a given internal format and target (GL ES 3.0+)
    METAGL_API void glGetInternalformativ(InternalFormatTarget target, InternalFormat internalformat, InternalFormatParameter pname, GLsizei count, GLint * params);
    /// @brief Binds a texture level to an image unit for image load/store in shaders (GL ES 3.1+)
    METAGL_API void glBindImageTexture(ImageUnit unit, TextureId texture, GLint level, GLboolean layered, GLint layer, ImageAccess access, InternalFormat format);

    /// @}
    /// @name Sampler Objects
    /// @{

    /// @brief Generates one or more sampler object names (GL ES 3.0+)
    METAGL_API void glGenSamplers(GLsizei count, SamplerId * samplers);
    inline void glGenSamplers(std::span<SamplerId> samplers) { glGenSamplers(detail::checked_glsizei(samplers.size()), samplers.data()); }
    /// @brief Deletes sampler objects (GL ES 3.0+)
    METAGL_API void glDeleteSamplers(GLsizei count, const SamplerId * samplers);
    inline void glDeleteSamplers(std::span<const SamplerId> samplers) { glDeleteSamplers(detail::checked_glsizei(samplers.size()), samplers.data()); }
    /// @brief Binds a sampler to a texture unit, overriding the texture's own sampling state (GL ES 3.0+)
    METAGL_API void glBindSampler(GLuint unit, SamplerId sampler);
    /// @brief Returns GL_TRUE if the name is a valid sampler object (GL ES 3.0+)
    [[nodiscard]] METAGL_API bool glIsSampler(SamplerId sampler);
    /// @brief Sets a float sampling parameter on a sampler object (GL ES 3.0+)
    METAGL_API void glSamplerParameterf(SamplerId sampler, SamplerParameter pname, GLfloat param);
    /// @brief Sets an integer sampling parameter on a sampler object (GL ES 3.0+)
    METAGL_API void glSamplerParameteri(SamplerId sampler, SamplerParameter pname, GLint param);
    /// @brief Sets multiple float sampling parameters on a sampler from a pointer (GL ES 3.0+)
    METAGL_API void glSamplerParameterfv(SamplerId sampler, SamplerParameter pname, const GLfloat * param);
    /// @brief Sets multiple integer sampling parameters on a sampler from a pointer (GL ES 3.0+)
    METAGL_API void glSamplerParameteriv(SamplerId sampler, SamplerParameter pname, const GLint * param);
    /// @brief Sets signed integer sampler parameters without conversion (GL ES 3.2+)
    METAGL_API void glSamplerParameterIiv(SamplerId sampler, SamplerParameter pname, const GLint * param);
    /// @brief Sets unsigned integer sampler parameters without conversion (GL ES 3.2+)
    METAGL_API void glSamplerParameterIuiv(SamplerId sampler, SamplerParameter pname, const GLuint * param);
    /// @brief Returns float sampling parameters from a sampler object (GL ES 3.0+)
    METAGL_API void glGetSamplerParameterfv(SamplerId sampler, SamplerParameter pname, GLfloat * params);
    /// @brief Returns integer sampling parameters from a sampler object (GL ES 3.0+)
    METAGL_API void glGetSamplerParameteriv(SamplerId sampler, SamplerParameter pname, GLint * params);
    /// @brief Returns signed integer sampler parameters as raw integers (GL ES 3.2+)
    METAGL_API void glGetSamplerParameterIiv(SamplerId sampler, SamplerParameter pname, GLint * params);
    /// @brief Returns unsigned integer sampler parameters as raw unsigned integers (GL ES 3.2+)
    METAGL_API void glGetSamplerParameterIuiv(SamplerId sampler, SamplerParameter pname, GLuint * params);

    /// @}
    /// @name Framebuffer Objects
    /// @{

    /// @brief Generates one or more framebuffer object names (GL ES 2.0+)
    METAGL_API void glGenFramebuffers(GLsizei n, FramebufferId * framebuffers);
    inline void glGenFramebuffers(std::span<FramebufferId> framebuffers) { glGenFramebuffers(detail::checked_glsizei(framebuffers.size()), framebuffers.data()); }
    /// @brief Deletes framebuffer objects (GL ES 2.0+)
    METAGL_API void glDeleteFramebuffers(GLsizei n, const FramebufferId * framebuffers);
    inline void glDeleteFramebuffers(std::span<const FramebufferId> framebuffers) { glDeleteFramebuffers(detail::checked_glsizei(framebuffers.size()), framebuffers.data()); }
    /// @brief Binds a framebuffer to GL_FRAMEBUFFER, GL_READ_FRAMEBUFFER, or GL_DRAW_FRAMEBUFFER (GL ES 2.0+)
    METAGL_API void glBindFramebuffer(FramebufferTarget target, FramebufferId framebuffer);
    /// @brief Returns GL_TRUE if the name is a valid framebuffer object (GL ES 2.0+)
    [[nodiscard]] METAGL_API bool glIsFramebuffer(FramebufferId framebuffer);
    /// @brief Returns the completeness status of the bound framebuffer (GL ES 2.0+)
    [[nodiscard]] METAGL_API FramebufferStatus glCheckFramebufferStatus(FramebufferTarget target);
    /// @brief Attaches a 2D texture level as a framebuffer color/depth/stencil attachment (GL ES 2.0+)
    METAGL_API void glFramebufferTexture2D(FramebufferTarget target, FramebufferAttachment attachment, TextureTarget textarget, TextureId texture, GLint level);
    /// @brief Attaches a single layer of a layered texture to a framebuffer attachment point (GL ES 3.0+)
    METAGL_API void glFramebufferTextureLayer(FramebufferTarget target, FramebufferAttachment attachment, TextureId texture, GLint level, GLint layer);
    /// @brief Attaches an entire layered texture to a framebuffer (for geometry shader layered rendering) (GL ES 3.2+)
    METAGL_API void glFramebufferTexture(FramebufferTarget target, FramebufferAttachment attachment, TextureId texture, GLint level);
    /// @brief Attaches a renderbuffer as a framebuffer color/depth/stencil attachment (GL ES 2.0+)
    METAGL_API void glFramebufferRenderbuffer(FramebufferTarget target, FramebufferAttachment attachment, RenderbufferTarget renderbuffertarget, RenderbufferId renderbuffer);
    /// @brief Sets default parameters on a framebuffer that has no attachments (GL ES 3.1+)
    METAGL_API void glFramebufferParameteri(FramebufferTarget target, FramebufferDefaultParameter pname, GLint param);
    /// @brief Returns parameters set on a framebuffer via glFramebufferParameteri (GL ES 3.1+)
    METAGL_API void glGetFramebufferParameteriv(FramebufferTarget target, FramebufferDefaultParameter pname, GLint * params);
    /// @brief Returns parameters of a specific framebuffer attachment (GL ES 2.0+)
    METAGL_API void glGetFramebufferAttachmentParameteriv(FramebufferTarget target, FramebufferAttachment attachment, FramebufferAttachmentParameter pname, GLint * params);
    /// @brief Copies a rectangle between framebuffers; also resolves MSAA (GL ES 3.0+)
    METAGL_API void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, ClearBufferBit mask, BlitFilter filter);
    /// @brief Hints that attachment contents are no longer needed (bandwidth optimization) (GL ES 3.0+)
    METAGL_API void glInvalidateFramebuffer(FramebufferTarget target, GLsizei numAttachments, const FramebufferAttachment * attachments);
    inline void glInvalidateFramebuffer(FramebufferTarget target, std::span<const FramebufferAttachment> attachments) { glInvalidateFramebuffer(target, detail::checked_glsizei(attachments.size()), attachments.data()); }

    /// @brief Invalidates default framebuffer (id=0) attachments (GL ES 3.0+)
    METAGL_API void glInvalidateFramebuffer(FramebufferTarget target, GLsizei numAttachments, const DefaultFramebufferAttachment * attachments);
    inline void glInvalidateFramebuffer(FramebufferTarget target, std::span<const DefaultFramebufferAttachment> attachments) { glInvalidateFramebuffer(target, detail::checked_glsizei(attachments.size()), attachments.data()); }

    /// @brief Invalidates a sub-rectangle of framebuffer attachments (GL ES 3.0+)
    METAGL_API void glInvalidateSubFramebuffer(FramebufferTarget target, GLsizei numAttachments, const FramebufferAttachment * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
    inline void glInvalidateSubFramebuffer(FramebufferTarget target, std::span<const FramebufferAttachment> attachments, GLint x, GLint y, GLsizei width, GLsizei height) { glInvalidateSubFramebuffer(target, detail::checked_glsizei(attachments.size()), attachments.data(), x, y, width, height); }

    /// @brief Invalidates a sub-rectangle of default framebuffer (id=0) attachments (GL ES 3.0+)
    METAGL_API void glInvalidateSubFramebuffer(FramebufferTarget target, GLsizei numAttachments, const DefaultFramebufferAttachment * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
    inline void glInvalidateSubFramebuffer(FramebufferTarget target, std::span<const DefaultFramebufferAttachment> attachments, GLint x, GLint y, GLsizei width, GLsizei height) { glInvalidateSubFramebuffer(target, detail::checked_glsizei(attachments.size()), attachments.data(), x, y, width, height); }

    /// @}
    /// @name Renderbuffer Objects
    /// @{

    /// @brief Generates one or more renderbuffer object names (GL ES 2.0+)
    METAGL_API void glGenRenderbuffers(GLsizei n, RenderbufferId * renderbuffers);
    inline void glGenRenderbuffers(std::span<RenderbufferId> renderbuffers) { glGenRenderbuffers(detail::checked_glsizei(renderbuffers.size()), renderbuffers.data()); }
    /// @brief Deletes renderbuffer objects and frees their GPU memory (GL ES 2.0+)
    METAGL_API void glDeleteRenderbuffers(GLsizei n, const RenderbufferId * renderbuffers);
    inline void glDeleteRenderbuffers(std::span<const RenderbufferId> renderbuffers) { glDeleteRenderbuffers(detail::checked_glsizei(renderbuffers.size()), renderbuffers.data()); }
    /// @brief Binds a renderbuffer to the GL_RENDERBUFFER target (GL ES 2.0+)
    METAGL_API void glBindRenderbuffer(RenderbufferTarget target, RenderbufferId renderbuffer);
    /// @brief Returns GL_TRUE if the name is a valid renderbuffer object (GL ES 2.0+)
    [[nodiscard]] METAGL_API bool glIsRenderbuffer(RenderbufferId renderbuffer);
    /// @brief Allocates single-sample GPU storage for a renderbuffer (GL ES 2.0+)
    METAGL_API void glRenderbufferStorage(RenderbufferTarget target, InternalFormat internalformat, GLsizei width, GLsizei height);
    /// @brief Allocates multisample GPU storage for a renderbuffer (for MSAA) (GL ES 3.0+)
    METAGL_API void glRenderbufferStorageMultisample(RenderbufferTarget target, GLsizei samples, InternalFormat internalformat, GLsizei width, GLsizei height);
    /// @brief Returns parameters of the bound renderbuffer (width, height, format, samples) (GL ES 2.0+)
    METAGL_API void glGetRenderbufferParameteriv(RenderbufferTarget target, RenderbufferParameter pname, GLint * params);

    /// @}
    /// @name Transform Feedback
    /// @{

    /// @brief Generates one or more transform feedback object names (GL ES 3.0+)
    METAGL_API void glGenTransformFeedbacks(GLsizei n, TransformFeedbackId * ids);
    inline void glGenTransformFeedbacks(std::span<TransformFeedbackId> ids) { glGenTransformFeedbacks(detail::checked_glsizei(ids.size()), ids.data()); }
    /// @brief Deletes transform feedback objects (GL ES 3.0+)
    METAGL_API void glDeleteTransformFeedbacks(GLsizei n, const TransformFeedbackId * ids);
    inline void glDeleteTransformFeedbacks(std::span<const TransformFeedbackId> ids) { glDeleteTransformFeedbacks(detail::checked_glsizei(ids.size()), ids.data()); }
    /// @brief Binds a transform feedback object to capture its output buffer state (GL ES 3.0+)
    METAGL_API void glBindTransformFeedback(TransformFeedbackTarget target, TransformFeedbackId id);
    /// @brief Returns GL_TRUE if the name is a valid transform feedback object (GL ES 3.0+)
    [[nodiscard]] METAGL_API bool glIsTransformFeedback(TransformFeedbackId id);
    /// @brief Starts capturing vertex shader outputs into transform feedback buffers (GL ES 3.0+)
    METAGL_API void glBeginTransformFeedback(PrimitiveType primitiveMode);
    /// @brief Typed overload accepting only the exact primitives legal for transform feedback (Points, Lines, Triangles) (GL ES 3.0+)
    inline void glBeginTransformFeedback(TransformFeedbackPrimitive primitiveMode) { glBeginTransformFeedback(static_cast<PrimitiveType>(static_cast<GLenum>(primitiveMode))); }
    /// @brief Ends the current transform feedback capture session (GL ES 3.0+)
    METAGL_API void glEndTransformFeedback(void);
    /// @brief Pauses an active transform feedback session (can be resumed) (GL ES 3.0+)
    METAGL_API void glPauseTransformFeedback(void);
    /// @brief Resumes a previously paused transform feedback session (GL ES 3.0+)
    METAGL_API void glResumeTransformFeedback(void);
    /// @brief Specifies which vertex shader outputs to capture before linking (GL ES 3.0+)
    METAGL_API void glTransformFeedbackVaryings(ProgramId program, GLsizei count, const GLchar *const* varyings, TransformFeedbackBufferMode bufferMode);
    /// @brief Returns name, type, and size of a transform feedback varying by index (GL ES 3.0+)
    METAGL_API void glGetTransformFeedbackVarying(ProgramId program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, UniformType * type, GLchar * name);

    /// @}
    /// @name Query Objects
    /// @{

    /// @brief Generates one or more query object names (GL ES 3.0+)
    METAGL_API void glGenQueries(GLsizei n, QueryId * ids);
    inline void glGenQueries(std::span<QueryId> ids) { glGenQueries(detail::checked_glsizei(ids.size()), ids.data()); }
    /// @brief Deletes query objects (GL ES 3.0+)
    METAGL_API void glDeleteQueries(GLsizei n, const QueryId * ids);
    inline void glDeleteQueries(std::span<const QueryId> ids) { glDeleteQueries(detail::checked_glsizei(ids.size()), ids.data()); }
    /// @brief Returns GL_TRUE if the name is a valid query object (GL ES 3.0+)
    [[nodiscard]] METAGL_API bool glIsQuery(QueryId id);
    /// @brief Begins recording a GPU query (occlusion, primitives written, etc.) (GL ES 3.0+)
    METAGL_API void glBeginQuery(QueryTarget target, QueryId id);
    /// @brief Ends a query; result becomes available asynchronously (GL ES 3.0+)
    METAGL_API void glEndQuery(QueryTarget target);
    /// @brief Returns info about a query target (active query name, counter bits) (GL ES 3.0+)
    METAGL_API void glGetQueryiv(QueryTarget target, QueryParameter pname, GLint * params);
    /// @brief Returns the result of a completed query as an unsigned integer (GL ES 3.0+)
    METAGL_API void glGetQueryObjectuiv(QueryId id, QueryObjectParameter pname, GLuint * params);

    /// @}
    /// @name Sync Objects
    /// @{

    /// @brief Creates a sync object and inserts a fence into the GL command stream (GL ES 3.0+)
    [[nodiscard]] METAGL_API GLsync glFenceSync(SyncCondition condition, SyncFlag flags);
    /// @brief Deletes a sync object (GL ES 3.0+)
    METAGL_API void glDeleteSync(GLsync sync);
    /// @brief Returns GL_TRUE if the object is a valid sync (GL ES 3.0+)
    [[nodiscard]] METAGL_API bool glIsSync(GLsync sync);
    /// @brief Blocks the CPU until a sync is signaled or the timeout expires (GL ES 3.0+)
    [[nodiscard]] METAGL_API SyncWaitResult glClientWaitSync(GLsync sync, SyncFlushMask flags, GLuint64 timeout);
    /// @brief Blocks the GPU command processor until a sync is signaled (CPU not blocked) (GL ES 3.0+)
    METAGL_API void glWaitSync(GLsync sync, SyncFlag flags, GLuint64 timeout);
    /// @brief Returns the status or type of a sync object (signaled / unsignaled) (GL ES 3.0+)
    METAGL_API void glGetSynciv(GLsync sync, SyncParameter pname, GLsizei count, GLsizei * length, GLint * values);

    /// @}
    /// @name Compute Shaders
    /// @{

    /// @brief Launches a compute shader with a 3D grid of work groups (GL ES 3.1+)
    METAGL_API void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
    /// @brief Launches compute; work group dimensions read from GL_DISPATCH_INDIRECT_BUFFER (GL ES 3.1+)
    METAGL_API void glDispatchComputeIndirect(GLintptr indirect);
    /// @brief Inserts a memory barrier ensuring visibility of image/SSBO/atomic writes (GL ES 3.1+)
    METAGL_API void glMemoryBarrier(MemoryBarrierMask barriers);
    /// @brief Tile-friendly memory barrier guaranteeing visibility within the current region (GL ES 3.1+)
    METAGL_API void glMemoryBarrierByRegion(MemoryBarrierByRegionMask barriers);

    /// @}
    /// @name Program Pipelines
    /// @{

    /// @brief Generates one or more program pipeline object names (GL ES 3.1+)
    METAGL_API void glGenProgramPipelines(GLsizei n, ProgramPipelineId * pipelines);
    inline void glGenProgramPipelines(std::span<ProgramPipelineId> pipelines) { glGenProgramPipelines(detail::checked_glsizei(pipelines.size()), pipelines.data()); }
    /// @brief Deletes program pipeline objects (GL ES 3.1+)
    METAGL_API void glDeleteProgramPipelines(GLsizei n, const ProgramPipelineId * pipelines);
    inline void glDeleteProgramPipelines(std::span<const ProgramPipelineId> pipelines) { glDeleteProgramPipelines(detail::checked_glsizei(pipelines.size()), pipelines.data()); }
    /// @brief Binds a program pipeline for rendering (GL ES 3.1+)
    METAGL_API void glBindProgramPipeline(ProgramPipelineId pipeline);
    /// @brief Returns GL_TRUE if the name is a valid program pipeline object (GL ES 3.1+)
    [[nodiscard]] METAGL_API bool glIsProgramPipeline(ProgramPipelineId pipeline);
    /// @brief Installs shader stages from a separable program into a pipeline (GL ES 3.1+)
    METAGL_API void glUseProgramStages(ProgramPipelineId pipeline, ShaderStageMask stages, ProgramId program);
    /// @brief Sets the active program in a pipeline for direct uniform calls (GL ES 3.1+)
    METAGL_API void glActiveShaderProgram(ProgramPipelineId pipeline, ProgramId program);
    /// @brief Compiles, links, and creates a separable program in one step (GL ES 3.1+)
    [[nodiscard]] METAGL_API ProgramId glCreateShaderProgramv(ShaderType type, GLsizei count, const GLchar *const* strings);
    /// @brief Validates a pipeline can execute given current GL state (GL ES 3.1+)
    METAGL_API void glValidateProgramPipeline(ProgramPipelineId pipeline);
    /// @brief Returns parameters of a program pipeline (installed stages, validate status) (GL ES 3.1+)
    METAGL_API void glGetProgramPipelineiv(ProgramPipelineId pipeline, ProgramPipelineParameter pname, GLint * params);
    /// @brief Returns the info log for a pipeline (validation results, linker messages) (GL ES 3.1+)
    METAGL_API void glGetProgramPipelineInfoLog(ProgramPipelineId pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);

    /// @}
    /// @name Geometry and Tessellation
    /// @{

    /// @brief Sets the number of vertices per patch for tessellation (GL_PATCH_VERTICES) (GL ES 3.2+)
    METAGL_API void glPatchParameteri(TessellationParameter pname, GLint value);
    /// @brief Provides a bounding box hint for tessellated/geometry-shader geometry (GL ES 3.2+)
    METAGL_API void glPrimitiveBoundingBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);

    /// @}
    /// @name Debug Output
    /// @{

    /// @brief Registers a callback invoked when the GL generates a debug message (GL ES 3.2+)
    METAGL_API void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam);
    /// @brief Filters which debug messages are generated by source, type, and severity (GL ES 3.2+)
    METAGL_API void glDebugMessageControl(DebugSource source, DebugType type, DebugSeverity severity, GLsizei count, const GLuint * ids, GLboolean enabled);
    inline void glDebugMessageControl(DebugSource source, DebugType type, DebugSeverity severity, std::span<const GLuint> ids, GLboolean enabled) { glDebugMessageControl(source, type, severity, detail::checked_glsizei(ids.size()), ids.data(), enabled); }
    /// @brief Inserts an application-generated message into the GL debug stream (GL ES 3.2+)
    METAGL_API void glDebugMessageInsert(DebugSource source, DebugType type, GLuint id, DebugSeverity severity, GLsizei length, const GLchar * buf);
    /// @brief Retrieves queued debug messages from the GL internal message log (GL ES 3.2+)
    [[nodiscard]] METAGL_API GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, DebugSource * sources, DebugType * types, GLuint * ids, DebugSeverity * severities, GLsizei * lengths, GLchar * messageLog);
    /// @brief Pushes a named debug group onto the stack (visible in GPU debuggers) (GL ES 3.2+)
    METAGL_API void glPushDebugGroup(DebugSource source, GLuint id, GLsizei length, const GLchar * message);
    /// @brief Pops the innermost debug group from the stack (GL ES 3.2+)
    METAGL_API void glPopDebugGroup(void);
    /// @brief Assigns a human-readable label to any GL object for GPU debugger tools. (GL ES 3.2+)
    // `name` is a raw GLuint intentionally: the identifier parameter selects the object type
    // (GL_TEXTURE, GL_BUFFER, GL_PROGRAM, …) at runtime, so a single typed overload per handle
    // type would require a separate function for each — adding no safety benefit over the GL API.
    METAGL_API void glObjectLabel(DebugObjectLabel identifier, GLuint name, GLsizei length, const GLchar * label);
    /// @brief Assigns a label to a sync object (identified by pointer) (GL ES 3.2+)
    METAGL_API void glObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label);
    /// @brief Returns the label previously assigned to a GL object (same rationale as #354) (GL ES 3.2+)
    METAGL_API void glGetObjectLabel(DebugObjectLabel identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label);
    /// @brief Returns the label previously assigned to a sync object (GL ES 3.2+)
    METAGL_API void glGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label);

    /// @}
    /// @name Robustness
    /// @{

    /// @brief Returns the graphics reset status for robustness/error recovery (GL ES 3.2+)
    [[nodiscard]] METAGL_API GraphicsResetStatus glGetGraphicsResetStatus(void);

    /// @}
    // -------------------------------------------------------------------------
    /// @name Convenience Dispatch API
    /// @{
    // These helpers keep the 358 gl* wrappers above one-to-one with OpenGL_ES.md,
    // -------------------------------------------------------------------------
    // These helpers keep the 358 gl* wrappers above one-to-one with OpenGL_ES.md,
    // while providing a smaller C++ API on top. They use concepts and if constexpr,
    // so dispatch is resolved at compile time and there are no runtime branches.
    // The helper names still start with gl; only the typed suffix is removed
    // (for example glUniform1f/glUniform1i/glUniform1ui -> glUniform).

    template<typename T>
    concept UniformScalar =
        std::same_as<std::remove_cvref_t<T>, GLfloat> ||
        std::same_as<std::remove_cvref_t<T>, GLint> ||
        std::same_as<std::remove_cvref_t<T>, GLuint>;

    template<typename T>
    concept UniformFloatScalar =
        std::same_as<std::remove_cvref_t<T>, GLfloat>;

    template<typename T>
    concept UniformVector =
        std::ranges::contiguous_range<T> &&
        std::ranges::sized_range<T> &&
        UniformScalar<std::ranges::range_value_t<T>>;

    template<typename T>
    concept UniformFloatVector =
        std::ranges::contiguous_range<T> &&
        std::ranges::sized_range<T> &&
        UniformFloatScalar<std::ranges::range_value_t<T>>;

    namespace detail
    {
        template<std::size_t Components>
        inline constexpr bool IsUniformComponentCount = Components >= 1 && Components <= 4;

        template<std::size_t Columns, std::size_t Rows>
        concept UniformMatrixShape =
            Columns >= 2 && Columns <= 4 &&
            Rows >= 2 && Rows <= 4;

        // #166-#185 - dispatch helper for glUniform*v variants.
        template<std::size_t Components, UniformScalar T>
        inline void glUniformVectorDispatch(UniformLocation location, GLsizei count, const T* data)
        {
            using Value = std::remove_cvref_t<T>;

            if constexpr (std::same_as<Value, GLfloat>)
            {
                if constexpr (Components == 1) { glUniform1fv(location, count, data); }
                else if constexpr (Components == 2) { glUniform2fv(location, count, data); }
                else if constexpr (Components == 3) { glUniform3fv(location, count, data); }
                else if constexpr (Components == 4) { glUniform4fv(location, count, data); }
            }
            else if constexpr (std::same_as<Value, GLint>)
            {
                if constexpr (Components == 1) { glUniform1iv(location, count, data); }
                else if constexpr (Components == 2) { glUniform2iv(location, count, data); }
                else if constexpr (Components == 3) { glUniform3iv(location, count, data); }
                else if constexpr (Components == 4) { glUniform4iv(location, count, data); }
            }
            else if constexpr (std::same_as<Value, GLuint>)
            {
                if constexpr (Components == 1) { glUniform1uiv(location, count, data); }
                else if constexpr (Components == 2) { glUniform2uiv(location, count, data); }
                else if constexpr (Components == 3) { glUniform3uiv(location, count, data); }
                else if constexpr (Components == 4) { glUniform4uiv(location, count, data); }
            }
        }

        // #205-#224 - dispatch helper for glProgramUniform*v variants.
        template<std::size_t Components, UniformScalar T>
        inline void glProgramUniformVectorDispatch(ProgramId program, UniformLocation location, GLsizei count, const T* data)
        {
            using Value = std::remove_cvref_t<T>;

            if constexpr (std::same_as<Value, GLfloat>)
            {
                if constexpr (Components == 1) { glProgramUniform1fv(program, location, count, data); }
                else if constexpr (Components == 2) { glProgramUniform2fv(program, location, count, data); }
                else if constexpr (Components == 3) { glProgramUniform3fv(program, location, count, data); }
                else if constexpr (Components == 4) { glProgramUniform4fv(program, location, count, data); }
            }
            else if constexpr (std::same_as<Value, GLint>)
            {
                if constexpr (Components == 1) { glProgramUniform1iv(program, location, count, data); }
                else if constexpr (Components == 2) { glProgramUniform2iv(program, location, count, data); }
                else if constexpr (Components == 3) { glProgramUniform3iv(program, location, count, data); }
                else if constexpr (Components == 4) { glProgramUniform4iv(program, location, count, data); }
            }
            else if constexpr (std::same_as<Value, GLuint>)
            {
                if constexpr (Components == 1) { glProgramUniform1uiv(program, location, count, data); }
                else if constexpr (Components == 2) { glProgramUniform2uiv(program, location, count, data); }
                else if constexpr (Components == 3) { glProgramUniform3uiv(program, location, count, data); }
                else if constexpr (Components == 4) { glProgramUniform4uiv(program, location, count, data); }
            }
        }

        // #186-#194 - dispatch helper for glUniformMatrix*fv variants.
        template<std::size_t Columns, std::size_t Rows>
        inline void glUniformMatrixDispatch(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat* data)
        {
            if constexpr (Columns == 2 && Rows == 2) { glUniformMatrix2fv(location, count, transpose, data); }
            else if constexpr (Columns == 3 && Rows == 3) { glUniformMatrix3fv(location, count, transpose, data); }
            else if constexpr (Columns == 4 && Rows == 4) { glUniformMatrix4fv(location, count, transpose, data); }
            else if constexpr (Columns == 2 && Rows == 3) { glUniformMatrix2x3fv(location, count, transpose, data); }
            else if constexpr (Columns == 2 && Rows == 4) { glUniformMatrix2x4fv(location, count, transpose, data); }
            else if constexpr (Columns == 3 && Rows == 2) { glUniformMatrix3x2fv(location, count, transpose, data); }
            else if constexpr (Columns == 3 && Rows == 4) { glUniformMatrix3x4fv(location, count, transpose, data); }
            else if constexpr (Columns == 4 && Rows == 2) { glUniformMatrix4x2fv(location, count, transpose, data); }
            else if constexpr (Columns == 4 && Rows == 3) { glUniformMatrix4x3fv(location, count, transpose, data); }
        }

        // #225-#233 - dispatch helper for glProgramUniformMatrix*fv variants.
        template<std::size_t Columns, std::size_t Rows>
        inline void glProgramUniformMatrixDispatch(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat* data)
        {
            if constexpr (Columns == 2 && Rows == 2) { glProgramUniformMatrix2fv(program, location, count, transpose, data); }
            else if constexpr (Columns == 3 && Rows == 3) { glProgramUniformMatrix3fv(program, location, count, transpose, data); }
            else if constexpr (Columns == 4 && Rows == 4) { glProgramUniformMatrix4fv(program, location, count, transpose, data); }
            else if constexpr (Columns == 2 && Rows == 3) { glProgramUniformMatrix2x3fv(program, location, count, transpose, data); }
            else if constexpr (Columns == 2 && Rows == 4) { glProgramUniformMatrix2x4fv(program, location, count, transpose, data); }
            else if constexpr (Columns == 3 && Rows == 2) { glProgramUniformMatrix3x2fv(program, location, count, transpose, data); }
            else if constexpr (Columns == 3 && Rows == 4) { glProgramUniformMatrix3x4fv(program, location, count, transpose, data); }
            else if constexpr (Columns == 4 && Rows == 2) { glProgramUniformMatrix4x2fv(program, location, count, transpose, data); }
            else if constexpr (Columns == 4 && Rows == 3) { glProgramUniformMatrix4x3fv(program, location, count, transpose, data); }
        }
    }

    // #162/#170/#178 - scalar uniform dispatch: float, int, unsigned int.
    template<UniformScalar T>
    inline void glUniform(UniformLocation location, T value)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glUniform1f(location, value);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glUniform1i(location, value);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glUniform1ui(location, value);
        }
    }

    // #163/#171/#179 - vec2/ivec2/uvec2 uniform dispatch.
    template<UniformScalar T>
    inline void glUniform(UniformLocation location, T v0, T v1)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glUniform2f(location, v0, v1);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glUniform2i(location, v0, v1);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glUniform2ui(location, v0, v1);
        }
    }

    // #164/#172/#180 - vec3/ivec3/uvec3 uniform dispatch.
    template<UniformScalar T>
    inline void glUniform(UniformLocation location, T v0, T v1, T v2)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glUniform3f(location, v0, v1, v2);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glUniform3i(location, v0, v1, v2);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glUniform3ui(location, v0, v1, v2);
        }
    }

    // #165/#173/#181 - vec4/ivec4/uvec4 uniform dispatch.
    template<UniformScalar T>
    inline void glUniform(UniformLocation location, T v0, T v1, T v2, T v3)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glUniform4f(location, v0, v1, v2, v3);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glUniform4i(location, v0, v1, v2, v3);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glUniform4ui(location, v0, v1, v2, v3);
        }
    }

    // #166-#185 - contiguous range uniform dispatch.
    // Components=1 maps to glUniform1*v, Components=2 to glUniform2*v, etc.
    template<std::size_t Components = 1, UniformVector Vec>
        requires detail::IsUniformComponentCount<Components>
    inline void glUniform(UniformLocation location, const Vec& values)
    {
        using Value = std::ranges::range_value_t<Vec>;

        const auto* data = std::ranges::data(values);
        const auto count = detail::checked_element_count(
            std::ranges::size(values), Components);
        detail::glUniformVectorDispatch<Components, Value>(location, count, data);
    }

    // #166-#185 - fixed-size std::array convenience; N=2/3/4 means vec2/vec3/vec4.
    template<UniformScalar T, std::size_t N>
        requires detail::IsUniformComponentCount<N>
    inline void glUniform(UniformLocation location, const std::array<T, N>& values)
    {
        detail::glUniformVectorDispatch<N, T>(location, 1, values.data());
    }

    // #166-#185 - fixed-size C array convenience; N=2/3/4 means vec2/vec3/vec4.
    template<UniformScalar T, std::size_t N>
        requires detail::IsUniformComponentCount<N>
    inline void glUniform(UniformLocation location, const T (&values)[N])
    {
        detail::glUniformVectorDispatch<N, T>(location, 1, values);
    }

    // #166-#185 - initializer_list overload for contiguous range dispatch.
    template<std::size_t Components = 1, UniformScalar T>
        requires detail::IsUniformComponentCount<Components>
    inline void glUniform(UniformLocation location, std::initializer_list<T> values)
    {
        const auto count = detail::checked_element_count(
            values.size(), Components);
        detail::glUniformVectorDispatch<Components, T>(location, count, values.begin());
    }

    // #186-#194 - square matrix uniform dispatch. Size=2/3/4 maps to mat2/mat3/mat4.
    template<std::size_t Size, UniformFloatVector Vec>
        requires (Size >= 2 && Size <= 4)
    inline void glUniformMatrix(UniformLocation location, const Vec& values, GLboolean transpose = GL_FALSE)
    {
        const auto* data = std::ranges::data(values);
        const auto count = detail::checked_matrix_count(
            std::ranges::size(values), Size * Size, transpose);
        detail::glUniformMatrixDispatch<Size, Size>(location, count, transpose, data);
    }

    // #186-#194 - rectangular matrix uniform dispatch. Columns x Rows maps to glUniformMatrixCxRfv.
    template<std::size_t Columns, std::size_t Rows, UniformFloatVector Vec>
        requires detail::UniformMatrixShape<Columns, Rows>
    inline void glUniformMatrix(UniformLocation location, const Vec& values, GLboolean transpose = GL_FALSE)
    {
        const auto* data = std::ranges::data(values);
        const auto count = detail::checked_matrix_count(
            std::ranges::size(values), Columns * Rows, transpose);
        detail::glUniformMatrixDispatch<Columns, Rows>(location, count, transpose, data);
    }

    // #186-#194 - square matrix initializer_list overload.
    template<std::size_t Size>
        requires (Size >= 2 && Size <= 4)
    inline void glUniformMatrix(UniformLocation location, std::initializer_list<GLfloat> values, GLboolean transpose = GL_FALSE)
    {
        const auto count = detail::checked_matrix_count(
            values.size(), Size * Size, transpose);
        detail::glUniformMatrixDispatch<Size, Size>(location, count, transpose, values.begin());
    }

    // #186-#194 - rectangular matrix initializer_list overload.
    template<std::size_t Columns, std::size_t Rows>
        requires detail::UniformMatrixShape<Columns, Rows>
    inline void glUniformMatrix(UniformLocation location, std::initializer_list<GLfloat> values, GLboolean transpose = GL_FALSE)
    {
        const auto count = detail::checked_matrix_count(
            values.size(), Columns * Rows, transpose);
        detail::glUniformMatrixDispatch<Columns, Rows>(location, count, transpose, values.begin());
    }

    // #201/#209/#217 - scalar program-uniform dispatch: float, int, unsigned int.
    template<UniformScalar T>
    inline void glProgramUniform(ProgramId program, UniformLocation location, T value)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glProgramUniform1f(program, location, value);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glProgramUniform1i(program, location, value);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glProgramUniform1ui(program, location, value);
        }
    }

    // #202/#210/#218 - vec2/ivec2/uvec2 program-uniform dispatch.
    template<UniformScalar T>
    inline void glProgramUniform(ProgramId program, UniformLocation location, T v0, T v1)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glProgramUniform2f(program, location, v0, v1);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glProgramUniform2i(program, location, v0, v1);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glProgramUniform2ui(program, location, v0, v1);
        }
    }

    // #203/#211/#219 - vec3/ivec3/uvec3 program-uniform dispatch.
    template<UniformScalar T>
    inline void glProgramUniform(ProgramId program, UniformLocation location, T v0, T v1, T v2)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glProgramUniform3f(program, location, v0, v1, v2);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glProgramUniform3i(program, location, v0, v1, v2);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glProgramUniform3ui(program, location, v0, v1, v2);
        }
    }

    // #204/#212/#220 - vec4/ivec4/uvec4 program-uniform dispatch.
    template<UniformScalar T>
    inline void glProgramUniform(ProgramId program, UniformLocation location, T v0, T v1, T v2, T v3)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glProgramUniform4f(program, location, v0, v1, v2, v3);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glProgramUniform4i(program, location, v0, v1, v2, v3);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glProgramUniform4ui(program, location, v0, v1, v2, v3);
        }
    }

    // #205-#224 - contiguous range program-uniform dispatch.
    template<std::size_t Components = 1, UniformVector Vec>
        requires detail::IsUniformComponentCount<Components>
    inline void glProgramUniform(ProgramId program, UniformLocation location, const Vec& values)
    {
        using Value = std::ranges::range_value_t<Vec>;

        const auto* data = std::ranges::data(values);
        const auto count = detail::checked_element_count(
            std::ranges::size(values), Components);
        detail::glProgramUniformVectorDispatch<Components, Value>(program, location, count, data);
    }

    // #205-#224 - fixed-size std::array program-uniform convenience; N=2/3/4 means vec2/vec3/vec4.
    template<UniformScalar T, std::size_t N>
        requires detail::IsUniformComponentCount<N>
    inline void glProgramUniform(ProgramId program, UniformLocation location, const std::array<T, N>& values)
    {
        detail::glProgramUniformVectorDispatch<N, T>(program, location, 1, values.data());
    }

    // #205-#224 - fixed-size C array program-uniform convenience; N=2/3/4 means vec2/vec3/vec4.
    template<UniformScalar T, std::size_t N>
        requires detail::IsUniformComponentCount<N>
    inline void glProgramUniform(ProgramId program, UniformLocation location, const T (&values)[N])
    {
        detail::glProgramUniformVectorDispatch<N, T>(program, location, 1, values);
    }

    // #205-#224 - initializer_list program-uniform overload.
    template<std::size_t Components = 1, UniformScalar T>
        requires detail::IsUniformComponentCount<Components>
    inline void glProgramUniform(ProgramId program, UniformLocation location, std::initializer_list<T> values)
    {
        const auto count = detail::checked_element_count(
            values.size(), Components);
        detail::glProgramUniformVectorDispatch<Components, T>(program, location, count, values.begin());
    }

    // #225-#233 - square matrix program-uniform dispatch. Size=2/3/4 maps to mat2/mat3/mat4.
    template<std::size_t Size, UniformFloatVector Vec>
        requires (Size >= 2 && Size <= 4)
    inline void glProgramUniformMatrix(ProgramId program, UniformLocation location, const Vec& values, GLboolean transpose = GL_FALSE)
    {
        const auto* data = std::ranges::data(values);
        const auto count = detail::checked_matrix_count(
            std::ranges::size(values), Size * Size, transpose);
        detail::glProgramUniformMatrixDispatch<Size, Size>(program, location, count, transpose, data);
    }

    // #225-#233 - rectangular matrix program-uniform dispatch. Columns x Rows maps to glProgramUniformMatrixCxRfv.
    template<std::size_t Columns, std::size_t Rows, UniformFloatVector Vec>
        requires detail::UniformMatrixShape<Columns, Rows>
    inline void glProgramUniformMatrix(ProgramId program, UniformLocation location, const Vec& values, GLboolean transpose = GL_FALSE)
    {
        const auto* data = std::ranges::data(values);
        const auto count = detail::checked_matrix_count(
            std::ranges::size(values), Columns * Rows, transpose);
        detail::glProgramUniformMatrixDispatch<Columns, Rows>(program, location, count, transpose, data);
    }

    // #225-#233 - square matrix program-uniform initializer_list overload.
    template<std::size_t Size>
        requires (Size >= 2 && Size <= 4)
    inline void glProgramUniformMatrix(ProgramId program, UniformLocation location, std::initializer_list<GLfloat> values, GLboolean transpose = GL_FALSE)
    {
        const auto count = detail::checked_matrix_count(
            values.size(), Size * Size, transpose);
        detail::glProgramUniformMatrixDispatch<Size, Size>(program, location, count, transpose, values.begin());
    }

    // #225-#233 - rectangular matrix program-uniform initializer_list overload.
    template<std::size_t Columns, std::size_t Rows>
        requires detail::UniformMatrixShape<Columns, Rows>
    inline void glProgramUniformMatrix(ProgramId program, UniformLocation location, std::initializer_list<GLfloat> values, GLboolean transpose = GL_FALSE)
    {
        const auto count = detail::checked_matrix_count(
            values.size(), Columns * Rows, transpose);
        detail::glProgramUniformMatrixDispatch<Columns, Rows>(program, location, count, transpose, values.begin());
    }

    struct FloatTag {};
    struct IntTag {};
    struct UIntTag {};

    namespace detail
    {
        template<typename T>
        struct VertexAttributeTraits;

        template<>
        struct VertexAttributeTraits<GLfloat>
        {
            using Tag = FloatTag;
            static constexpr DataType Type = DataType::Float;
        };

        template<>
        struct VertexAttributeTraits<GLint>
        {
            using Tag = IntTag;
            static constexpr DataType Type = DataType::Int;
        };

        template<>
        struct VertexAttributeTraits<GLuint>
        {
            using Tag = UIntTag;
            static constexpr DataType Type = DataType::UnsignedInt;
        };

        // #73 - dispatch helper for floating-point vertex attributes.
        template<typename T>
        inline void glVertexAttribPointerDispatch(FloatTag, AttribLocation index, GLint size, GLboolean normalized, GLsizei stride, const void* pointer)
        {
            glVertexAttribPointer(index, size, VertexAttributeTraits<T>::Type, normalized, stride, pointer);
        }

        // #74 - dispatch helper for signed integer vertex attributes.
        template<typename T>
        inline void glVertexAttribPointerDispatch(IntTag, AttribLocation index, GLint size, GLboolean, GLsizei stride, const void* pointer)
        {
            glVertexAttribIPointer(index, size, VertexAttributeTraits<T>::Type, stride, pointer);
        }

        // #74 - dispatch helper for unsigned integer vertex attributes.
        template<typename T>
        inline void glVertexAttribPointerDispatch(UIntTag, AttribLocation index, GLint size, GLboolean, GLsizei stride, const void* pointer)
        {
            glVertexAttribIPointer(index, size, VertexAttributeTraits<T>::Type, stride, pointer);
        }
    }

    template<typename T>
    concept VertexAttributeScalar = requires
    {
        typename detail::VertexAttributeTraits<std::remove_cvref_t<T>>::Tag;
    };

    // #73-#74 - tag/constexpr dispatch for float/int/unsigned vertex attribute pointers.
    // GLfloat dispatches to glVertexAttribPointer; GLint/GLuint dispatch to glVertexAttribIPointer.
    template<VertexAttributeScalar T>
    inline void glVertexAttribPointer(AttribLocation index, GLint size, GLboolean normalized = GL_FALSE, GLsizei stride = 0, const void* pointer = nullptr)
    {
        using Value = std::remove_cvref_t<T>;
        using Tag = typename detail::VertexAttributeTraits<Value>::Tag;

        detail::glVertexAttribPointerDispatch<Value>(Tag{}, index, size, normalized, stride, pointer);
    }

    // #76 - scalar float vertex attribute dispatch.
    inline void glVertexAttrib(AttribLocation index, GLfloat x)
    {
        glVertexAttrib1f(index, x);
    }

    // #77 - vec2 float vertex attribute dispatch.
    inline void glVertexAttrib(AttribLocation index, GLfloat x, GLfloat y)
    {
        glVertexAttrib2f(index, x, y);
    }

    // #78 - vec3 float vertex attribute dispatch.
    inline void glVertexAttrib(AttribLocation index, GLfloat x, GLfloat y, GLfloat z)
    {
        glVertexAttrib3f(index, x, y, z);
    }

    // #79/#84/#85 - vec4/ivec4/uvec4 vertex attribute dispatch.
    template<VertexAttributeScalar T>
    inline void glVertexAttrib(AttribLocation index, T x, T y, T z, T w)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            glVertexAttrib4f(index, x, y, z, w);
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            glVertexAttribI4i(index, x, y, z, w);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            glVertexAttribI4ui(index, x, y, z, w);
        }
    }

    // #80-#83/#86-#87 - pointer/range vertex attribute dispatch.
    template<std::size_t Components = 4, VertexAttributeScalar T>
        requires detail::IsUniformComponentCount<Components>
    inline void glVertexAttrib(AttribLocation index, const T* values)
    {
        using Value = std::remove_cvref_t<T>;

        if constexpr (std::same_as<Value, GLfloat>)
        {
            if constexpr (Components == 1) { glVertexAttrib1fv(index, values); }
            else if constexpr (Components == 2) { glVertexAttrib2fv(index, values); }
            else if constexpr (Components == 3) { glVertexAttrib3fv(index, values); }
            else if constexpr (Components == 4) { glVertexAttrib4fv(index, values); }
        }
        else if constexpr (std::same_as<Value, GLint>)
        {
            static_assert(Components == 4, "OpenGL ES only has glVertexAttribI4iv for integer constant attributes.");
            glVertexAttribI4iv(index, values);
        }
        else if constexpr (std::same_as<Value, GLuint>)
        {
            static_assert(Components == 4, "OpenGL ES only has glVertexAttribI4uiv for unsigned integer constant attributes.");
            glVertexAttribI4uiv(index, values);
        }
    }

    // #80-#83/#86-#87 - fixed-size std::array vertex attribute dispatch.
    template<VertexAttributeScalar T, std::size_t N>
        requires detail::IsUniformComponentCount<N>
    inline void glVertexAttrib(AttribLocation index, const std::array<T, N>& values)
    {
        glVertexAttrib<N, T>(index, values.data());
    }

    // #80-#83/#86-#87 - fixed-size C array vertex attribute dispatch.
    template<VertexAttributeScalar T, std::size_t N>
        requires detail::IsUniformComponentCount<N>
    inline void glVertexAttrib(AttribLocation index, const T (&values)[N])
    {
        glVertexAttrib<N, T>(index, values);
    }

    // #195-#197 - typed dispatch: glGetUniform<float/int/unsigned int>(program, location, params)
    template<UniformScalar T>
    inline void glGetUniform(ProgramId program, UniformLocation location, T* params)
    {
        using Value = std::remove_cvref_t<T>;
        if constexpr (std::same_as<Value, GLfloat>)      { glGetUniformfv(program, location, params); }
        else if constexpr (std::same_as<Value, GLint>)   { glGetUniformiv(program, location, params); }
        else if constexpr (std::same_as<Value, GLuint>)  { glGetUniformuiv(program, location, params); }
    }

    // #198-#200 - typed dispatch: glGetnUniform<float/int/unsigned int>(program, location, bufSize, params)
    template<UniformScalar T>
    inline void glGetnUniform(ProgramId program, UniformLocation location, GLsizei bufSize, T* params)
    {
        using Value = std::remove_cvref_t<T>;
        if constexpr (std::same_as<Value, GLfloat>)      { glGetnUniformfv(program, location, bufSize, params); }
        else if constexpr (std::same_as<Value, GLint>)   { glGetnUniformiv(program, location, bufSize, params); }
        else if constexpr (std::same_as<Value, GLuint>)  { glGetnUniformuiv(program, location, bufSize, params); }
    }

    // #256-#257 - typed dispatch: glTexParameter<float/int>(target, pname, param)
    template<typename T>
        requires std::same_as<std::remove_cvref_t<T>, GLfloat> || std::same_as<std::remove_cvref_t<T>, GLint>
    inline void glTexParameter(TextureTarget target, TextureParameterSetter pname, T param)
    {
        using Value = std::remove_cvref_t<T>;
        if constexpr (std::same_as<Value, GLfloat>) { glTexParameterf(target, pname, param); }
        else                                         { glTexParameteri(target, pname, param); }
    }

    inline void glTexParameter(TextureTarget target, TextureMinFilter value)
    {
        glTexParameteri(target, TextureParameterSetter::MinFilter,
            static_cast<GLint>(value));
    }

    inline void glTexParameter(TextureTarget target, TextureMagFilter value)
    {
        glTexParameteri(target, TextureParameterSetter::MagFilter,
            static_cast<GLint>(value));
    }

    inline void glTexParameter(TextureTarget target,
        TextureWrapParameter pname, TextureWrapMode value)
    {
        glTexParameteri(target, static_cast<TextureParameterSetter>(pname),
            static_cast<GLint>(value));
    }

    inline void glTexParameter(TextureTarget target, TextureCompareMode value)
    {
        glTexParameteri(target, TextureParameterSetter::CompareMode,
            static_cast<GLint>(value));
    }

    inline void glTexParameter(TextureTarget target, CompareFunc value)
    {
        glTexParameteri(target, TextureParameterSetter::CompareFunc,
            static_cast<GLint>(value));
    }

    inline void glTexParameter(TextureTarget target,
        TextureSwizzleParameter pname, TextureSwizzle value)
    {
        glTexParameteri(target, static_cast<TextureParameterSetter>(pname),
            static_cast<GLint>(value));
    }

    // #277-#278 - typed dispatch: glSamplerParameter<float/int>(sampler, pname, param)
    template<typename T>
        requires std::same_as<std::remove_cvref_t<T>, GLfloat> || std::same_as<std::remove_cvref_t<T>, GLint>
    inline void glSamplerParameter(SamplerId sampler, SamplerParameter pname, T param)
    {
        using Value = std::remove_cvref_t<T>;
        if constexpr (std::same_as<Value, GLfloat>) { glSamplerParameterf(sampler, pname, param); }
        else                                         { glSamplerParameteri(sampler, pname, param); }
    }

    inline void glSamplerParameter(SamplerId sampler, TextureMinFilter value)
    {
        glSamplerParameteri(sampler, SamplerParameter::MinFilter,
            static_cast<GLint>(value));
    }

    inline void glSamplerParameter(SamplerId sampler, TextureMagFilter value)
    {
        glSamplerParameteri(sampler, SamplerParameter::MagFilter,
            static_cast<GLint>(value));
    }

    inline void glSamplerParameter(SamplerId sampler,
        SamplerWrapParameter pname, TextureWrapMode value)
    {
        glSamplerParameteri(sampler, static_cast<SamplerParameter>(pname),
            static_cast<GLint>(value));
    }

    inline void glSamplerParameter(SamplerId sampler, TextureCompareMode value)
    {
        glSamplerParameteri(sampler, SamplerParameter::CompareMode,
            static_cast<GLint>(value));
    }

    inline void glSamplerParameter(SamplerId sampler, CompareFunc value)
    {
        glSamplerParameteri(sampler, SamplerParameter::CompareFunc,
            static_cast<GLint>(value));
    }

    // #116-#118 - typed dispatch with an exact target domain for each value type.
    template<std::same_as<GLfloat> T>
    inline void glClearBuffer(
        FloatClearBuffer buffer, GLint drawbuffer, const T* value)
    {
        glClearBufferfv(buffer, drawbuffer, value);
    }

    template<std::same_as<GLint> T>
    inline void glClearBuffer(
        SignedIntegerClearBuffer buffer, GLint drawbuffer, const T* value)
    {
        glClearBufferiv(buffer, drawbuffer, value);
    }

    template<std::same_as<GLuint> T>
    inline void glClearBuffer(
        UnsignedIntegerClearBuffer buffer, GLint drawbuffer, const T* value)
    {
        glClearBufferuiv(buffer, drawbuffer, value);
    }

    // #88-#91 - typed dispatch: glGetVertexAttrib<float/int/unsigned int>(index, pname, params)
    // GLfloat -> glGetVertexAttribfv; GLint -> glGetVertexAttribiv (normalized/int attrs);
    // For pure integer attrs use glGetVertexAttribIiv (GLint) / glGetVertexAttribIuiv (GLuint).
    template<UniformScalar T>
    inline void glGetVertexAttrib(AttribLocation index, VertexAttribParameter pname, T* params)
    {
        using Value = std::remove_cvref_t<T>;
        if constexpr (std::same_as<Value, GLfloat>)     { glGetVertexAttribfv(index, pname, params); }
        else if constexpr (std::same_as<Value, GLint>)  { glGetVertexAttribiv(index, pname, params); }
        else if constexpr (std::same_as<Value, GLuint>) { glGetVertexAttribIuiv(index, pname, params); }
    }

    // -------------------------------------------------------------------------
    // std::span overloads for texture upload functions (C5)
    // The raw const-void* overloads are preserved for nullptr (mutable storage).
    // -------------------------------------------------------------------------

    template<SpanCompatible T>
    inline void glTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat,
        GLsizei width, GLsizei height, GLint border,
        PixelFormat format, PixelType type, std::span<const T> pixels)
    {
        glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels.data());
    }

    template<SpanCompatible T>
    inline void glTexImage3D(TextureTarget target, GLint level, InternalFormat internalformat,
        GLsizei width, GLsizei height, GLsizei depth, GLint border,
        PixelFormat format, PixelType type, std::span<const T> pixels)
    {
        glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels.data());
    }

    template<SpanCompatible T>
    inline void glTexSubImage2D(TextureTarget target, GLint level,
        GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
        PixelFormat format, PixelType type, std::span<const T> pixels)
    {
        glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels.data());
    }

    template<SpanCompatible T>
    inline void glTexSubImage3D(TextureTarget target, GLint level,
        GLint xoffset, GLint yoffset, GLint zoffset,
        GLsizei width, GLsizei height, GLsizei depth,
        PixelFormat format, PixelType type, std::span<const T> pixels)
    {
        glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels.data());
    }

    // -------------------------------------------------------------------------
    // std::span overloads for compressed texture upload functions (C6)
    // imageSize is derived from pixels.size_bytes(); raw void* overloads kept.
    // -------------------------------------------------------------------------

    template<SpanCompatible T>
    inline void glCompressedTexImage2D(TextureTarget target, GLint level,
        CompressedInternalFormat internalformat,
        GLsizei width, GLsizei height, GLint border,
        std::span<const T> pixels)
    {
        glCompressedTexImage2D(target, level, internalformat, width, height, border,
            detail::checked_glsizei(pixels.size_bytes()), pixels.data());
    }

    template<SpanCompatible T>
    inline void glCompressedTexImage3D(TextureTarget target, GLint level,
        CompressedInternalFormat internalformat,
        GLsizei width, GLsizei height, GLsizei depth, GLint border,
        std::span<const T> pixels)
    {
        glCompressedTexImage3D(target, level, internalformat, width, height, depth, border,
            detail::checked_glsizei(pixels.size_bytes()), pixels.data());
    }

    template<SpanCompatible T>
    inline void glCompressedTexSubImage2D(TextureTarget target, GLint level,
        GLint xoffset, GLint yoffset, GLsizei width, GLsizei height,
        CompressedInternalFormat format, std::span<const T> pixels)
    {
        glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height,
            format, detail::checked_glsizei(pixels.size_bytes()), pixels.data());
    }

    template<SpanCompatible T>
    inline void glCompressedTexSubImage3D(TextureTarget target, GLint level,
        GLint xoffset, GLint yoffset, GLint zoffset,
        GLsizei width, GLsizei height, GLsizei depth,
        CompressedInternalFormat format, std::span<const T> pixels)
    {
        glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset,
            width, height, depth, format,
            detail::checked_glsizei(pixels.size_bytes()), pixels.data());
    }

}
