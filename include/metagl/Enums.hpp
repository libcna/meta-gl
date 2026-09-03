/**
 * @file Enums.hpp
 * @brief Strongly-typed OpenGL ES enum classes for all GL constant domains.
 *
 * Defines one `enum class` per OpenGL ES domain so that unrelated constants
 * cannot be accidentally mixed.  All enumerators map 1-to-1 to the
 * corresponding `GL_*` constant from `<GLES3/gl32.h>`.
 *
 * Bitfield enums (e.g. @ref metagl::ClearBufferBit,
 * @ref metagl::MapBufferAccessMask) derive from `GLbitfield` and satisfy the
 * @ref metagl::GlBitfield concept, which enables
 * generic `operator|`, `operator&`, and `operator~` for them.
 *
 * Domain enums derive from `GLenum` and satisfy the @ref metagl::GlEnum concept
 * defined in @ref Types.hpp.
 *
 * Availability annotations in enumerator comments (`ES 3.0+`, `ES 3.1+`,
 * `ES 3.2+`) indicate the minimum OpenGL ES version required.
 */
#pragma once

// Types.hpp includes <GLES3/gl32.h> which defines all GL_* constants used below.
#include "Types.hpp"

// GL_EXT_texture_filter_anisotropic is not part of core GLES/GL and is not defined by
// <GLES3/gl32.h>; guard against redefinition in case a platform GL header already provides it.
#ifndef GL_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif
#ifndef GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif

// GL_EXT_texture_compression_s3tc is likewise not core GLES/GL. The same four values are also
// reached through WEBGL_compressed_texture_s3tc and the ANGLE dxt3/dxt5 extensions, so a context
// may advertise any of those spellings and mean these formats.
#ifndef GL_COMPRESSED_RGB_S3TC_DXT1_EXT
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT 0x83F0
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#endif
#ifndef GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#endif

namespace metagl
{
    template<GlBitfield T>
    [[nodiscard]] constexpr T operator|(T a, T b) noexcept
    {
        return static_cast<T>(
            static_cast<GLbitfield>(a) | static_cast<GLbitfield>(b));
    }

    template<GlBitfield T>
    [[nodiscard]] constexpr T operator&(T a, T b) noexcept
    {
        return static_cast<T>(
            static_cast<GLbitfield>(a) & static_cast<GLbitfield>(b));
    }

    template<GlBitfield T>
    [[nodiscard]] constexpr T operator~(T a) noexcept
    {
        return static_cast<T>(
            (~static_cast<GLbitfield>(a)) & GlBitfieldTraits<T>::all_bits);
    }

    /**
     * @brief Clear buffer mask — bitfield passed to glClear().
     */
    enum class ClearBufferBit : GLbitfield
    {
        Color   = GL_COLOR_BUFFER_BIT,   ///< Clear the colour buffer.
        Depth   = GL_DEPTH_BUFFER_BIT,   ///< Clear the depth buffer.
        Stencil = GL_STENCIL_BUFFER_BIT  ///< Clear the stencil buffer.
    };

    /**
     * @brief Primitive topology for draw calls (glDrawArrays, glDrawElements, etc.). ES 3.2 adds adjacency types for geometry shaders and patches for tessellation.
     */
    enum class PrimitiveType : GLenum
    {
        Points                 = GL_POINTS,
        Lines                  = GL_LINES,
        LineLoop               = GL_LINE_LOOP,
        LineStrip              = GL_LINE_STRIP,
        Triangles              = GL_TRIANGLES,
        TriangleStrip          = GL_TRIANGLE_STRIP,
        TriangleFan            = GL_TRIANGLE_FAN,
        LinesAdjacency         = GL_LINES_ADJACENCY,          ///< ES 3.2 geometry shader.
        LineStripAdjacency     = GL_LINE_STRIP_ADJACENCY,     ///< ES 3.2 geometry shader.
        TrianglesAdjacency     = GL_TRIANGLES_ADJACENCY,      ///< ES 3.2 geometry shader.
        TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY, ///< ES 3.2 geometry shader.
        Patches                = GL_PATCHES                   ///< ES 3.2 tessellation.
    };

    /**
     * @brief Source and destination blend factors for glBlendFunc / glBlendFunci.
     */
    enum class BlendFactor : GLenum
    {
        Zero                  = GL_ZERO,
        One                   = GL_ONE,
        SrcColor              = GL_SRC_COLOR,
        OneMinusSrcColor      = GL_ONE_MINUS_SRC_COLOR,
        SrcAlpha              = GL_SRC_ALPHA,
        OneMinusSrcAlpha      = GL_ONE_MINUS_SRC_ALPHA,
        DstAlpha              = GL_DST_ALPHA,
        OneMinusDstAlpha      = GL_ONE_MINUS_DST_ALPHA,
        DstColor              = GL_DST_COLOR,
        OneMinusDstColor      = GL_ONE_MINUS_DST_COLOR,
        SrcAlphaSaturate      = GL_SRC_ALPHA_SATURATE,
        ConstantColor         = GL_CONSTANT_COLOR,
        OneMinusConstantColor = GL_ONE_MINUS_CONSTANT_COLOR,
        ConstantAlpha         = GL_CONSTANT_ALPHA,
        OneMinusConstantAlpha = GL_ONE_MINUS_CONSTANT_ALPHA
    };

    /**
     * @brief Blend equation mode for glBlendEquation / glBlendEquationi.
     */
    enum class BlendEquation : GLenum
    {
        FuncAdd             = GL_FUNC_ADD,
        FuncSubtract        = GL_FUNC_SUBTRACT,
        FuncReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
        Min                 = GL_MIN,  ///< ES 3.0+
        Max                 = GL_MAX,  ///< ES 3.0+
        Multiply            = GL_MULTIPLY,
        Screen              = GL_SCREEN,
        Overlay             = GL_OVERLAY,
        Darken              = GL_DARKEN,
        Lighten             = GL_LIGHTEN,
        ColorDodge          = GL_COLORDODGE,
        ColorBurn           = GL_COLORBURN,
        HardLight           = GL_HARDLIGHT,
        SoftLight           = GL_SOFTLIGHT,
        Difference          = GL_DIFFERENCE,
        Exclusion           = GL_EXCLUSION,
        HslHue              = GL_HSL_HUE,
        HslSaturation       = GL_HSL_SATURATION,
        HslColor            = GL_HSL_COLOR,
        HslLuminosity       = GL_HSL_LUMINOSITY
    };

    /**
     * @brief Buffer binding targets for glBindBuffer / glBufferData, etc.
     */
    enum class BufferTarget : GLenum
    {
        Array            = GL_ARRAY_BUFFER,              ///< Vertex attribute data.
        ElementArray     = GL_ELEMENT_ARRAY_BUFFER,      ///< Vertex index data.
        CopyRead         = GL_COPY_READ_BUFFER,           ///< Source for buffer copies. ES 3.0+
        CopyWrite        = GL_COPY_WRITE_BUFFER,          ///< Destination for buffer copies. ES 3.0+
        PixelPack        = GL_PIXEL_PACK_BUFFER,          ///< Pixel read destination. ES 3.0+
        PixelUnpack      = GL_PIXEL_UNPACK_BUFFER,        ///< Pixel upload source. ES 3.0+
        Uniform          = GL_UNIFORM_BUFFER,             ///< Uniform block data. ES 3.0+
        TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER, ///< Transform feedback output. ES 3.0+
        DrawIndirect     = GL_DRAW_INDIRECT_BUFFER,       ///< Indirect draw parameters. ES 3.1+
        DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER,   ///< Indirect dispatch parameters. ES 3.1+
        ShaderStorage    = GL_SHADER_STORAGE_BUFFER,      ///< Shader storage block data. ES 3.1+
        AtomicCounter    = GL_ATOMIC_COUNTER_BUFFER       ///< Atomic counter data. ES 3.1+
    };

    /**
     * @brief Usage hints for glBufferData — describes expected access pattern.
     */
    enum class BufferUsage : GLenum
    {
        StreamDraw  = GL_STREAM_DRAW,
        StreamRead  = GL_STREAM_READ,
        StreamCopy  = GL_STREAM_COPY,
        StaticDraw  = GL_STATIC_DRAW,
        StaticRead  = GL_STATIC_READ,
        StaticCopy  = GL_STATIC_COPY,
        DynamicDraw = GL_DYNAMIC_DRAW,
        DynamicRead = GL_DYNAMIC_READ,
        DynamicCopy = GL_DYNAMIC_COPY
    };

    /**
     * @brief Parameters queryable via glGetBufferParameteriv / glGetBufferParameteri64v. GL_BUFFER_MAP_POINTER is intentionally excluded — use BufferPointerParameter with glGetBufferPointerv instead.
     */
    enum class BufferParameter : GLenum
    {
        Size        = GL_BUFFER_SIZE,
        Usage       = GL_BUFFER_USAGE,
        Mapped      = GL_BUFFER_MAPPED,        ///< ES 3.0+
        AccessFlags = GL_BUFFER_ACCESS_FLAGS,  ///< ES 3.0+
        MapLength   = GL_BUFFER_MAP_LENGTH,    ///< ES 3.0+
        MapOffset   = GL_BUFFER_MAP_OFFSET     ///< ES 3.0+
    };

    /**
     * @brief The single valid pname for glGetBufferPointerv.
     */
    enum class BufferPointerParameter : GLenum
    {
        MapPointer = GL_BUFFER_MAP_POINTER   ///< ES 3.0+
    };

    /**
     * @brief Access flags for glMapBufferRange (bitfield).
     */
    enum class MapBufferAccessMask : GLbitfield
    {
        Read             = GL_MAP_READ_BIT,
        Write            = GL_MAP_WRITE_BIT,
        InvalidateRange  = GL_MAP_INVALIDATE_RANGE_BIT,
        InvalidateBuffer = GL_MAP_INVALIDATE_BUFFER_BIT,
        FlushExplicit    = GL_MAP_FLUSH_EXPLICIT_BIT,
        Unsynchronized   = GL_MAP_UNSYNCHRONIZED_BIT
    };

    /**
     * @brief Per-word sample coverage mask for glSampleMaski() (ES 3.1+). Each bit position corresponds to one sample index within the word. Use operator| to combine individual sample bits.
     */
    enum class SampleMaskValue : GLbitfield
    {
        None = 0,
        All  = 0xFFFFFFFFu
    };

    /**
     * @brief Server-side capabilities toggled with glEnable / glDisable.
     */
    enum class Capability : GLenum
    {
        Blend                       = GL_BLEND,
        CullFace                    = GL_CULL_FACE,
        DepthTest                   = GL_DEPTH_TEST,
        Dither                      = GL_DITHER,
        PolygonOffsetFill           = GL_POLYGON_OFFSET_FILL,
        SampleAlphaToCoverage       = GL_SAMPLE_ALPHA_TO_COVERAGE,
        SampleCoverage              = GL_SAMPLE_COVERAGE,
        ScissorTest                 = GL_SCISSOR_TEST,
        StencilTest                 = GL_STENCIL_TEST,
        RasterizerDiscard           = GL_RASTERIZER_DISCARD,         ///< ES 3.0+
        PrimitiveRestartFixedIndex  = GL_PRIMITIVE_RESTART_FIXED_INDEX, ///< ES 3.0+
        SampleMask                  = GL_SAMPLE_MASK,                ///< ES 3.1+
        DebugOutput                 = GL_DEBUG_OUTPUT,               ///< ES 3.2+
        DebugOutputSynchronous      = GL_DEBUG_OUTPUT_SYNCHRONOUS,   ///< ES 3.2+
        SampleShading               = GL_SAMPLE_SHADING              ///< ES 3.2+
    };

    /**
     * @brief OpenGL error codes returned by glGetError().
     */
    enum class ErrorCode : GLenum
    {
        NoError                   = GL_NO_ERROR,
        InvalidEnum               = GL_INVALID_ENUM,
        InvalidValue              = GL_INVALID_VALUE,
        InvalidOperation          = GL_INVALID_OPERATION,
        OutOfMemory               = GL_OUT_OF_MEMORY,
        InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
        StackOverflow             = GL_STACK_OVERFLOW,   ///< ES 3.2+
        StackUnderflow            = GL_STACK_UNDERFLOW,  ///< ES 3.2+
        ContextLost               = GL_CONTEXT_LOST      ///< ES 3.2+ robust context
    };

    /**
     * @brief Front-face winding order for glFrontFace().
     */
    enum class FrontFace : GLenum
    {
        CW  = GL_CW,
        CCW = GL_CCW
    };

    /**
     * @brief Face selection used by glCullFace() and glStencilFuncSeparate().
     */
    enum class CullFace : GLenum
    {
        Front        = GL_FRONT,
        Back         = GL_BACK,
        FrontAndBack = GL_FRONT_AND_BACK
    };

    /**
     * @brief Hint target for glHint().
     */
    enum class HintTarget : GLenum
    {
        GenerateMipmap            = GL_GENERATE_MIPMAP_HINT,
        FragmentShaderDerivative  = GL_FRAGMENT_SHADER_DERIVATIVE_HINT  ///< ES 3.0+
    };

    /**
     * @brief Hint mode for glHint().
     */
    enum class HintMode : GLenum
    {
        DontCare = GL_DONT_CARE,
        Fastest  = GL_FASTEST,
        Nicest   = GL_NICEST
    };

    /**
     * @brief Scalar data types used for vertex attributes, index buffers, and uniforms.
     */
    enum class DataType : GLenum
    {
        Byte                         = GL_BYTE,
        UnsignedByte                 = GL_UNSIGNED_BYTE,
        Short                        = GL_SHORT,
        UnsignedShort                = GL_UNSIGNED_SHORT,
        Int                          = GL_INT,
        UnsignedInt                  = GL_UNSIGNED_INT,
        Float                        = GL_FLOAT,
        Fixed                        = GL_FIXED,
        HalfFloat                    = GL_HALF_FLOAT,              ///< ES 3.0+
        Int2101010Rev                = GL_INT_2_10_10_10_REV,      ///< ES 3.0+ packed
        UnsignedInt2101010Rev        = GL_UNSIGNED_INT_2_10_10_10_REV, ///< ES 3.0+
        UnsignedInt10F11F11FRev      = GL_UNSIGNED_INT_10F_11F_11F_REV ///< ES 3.0+
    };

    /**
     * @brief Valid element index types for glDrawElements* calls.
     */
    enum class IndexType : GLenum
    {
        UnsignedByte  = GL_UNSIGNED_BYTE,
        UnsignedShort = GL_UNSIGNED_SHORT,
        UnsignedInt   = GL_UNSIGNED_INT ///< ES 3.0+
    };

    /**
     * @brief Pixel transfer format (base format) used in glTexImage2D, glReadPixels, etc.
     */
    enum class PixelFormat : GLenum
    {
        DepthComponent = GL_DEPTH_COMPONENT,
        Alpha          = GL_ALPHA,
        Rgb            = GL_RGB,
        Rgba           = GL_RGBA,
        Luminance      = GL_LUMINANCE,       ///< Legacy ES 2.0.
        LuminanceAlpha = GL_LUMINANCE_ALPHA, ///< Legacy ES 2.0.
        Red            = GL_RED,             ///< ES 3.0+
        Rg             = GL_RG,              ///< ES 3.0+
        RedInteger     = GL_RED_INTEGER,     ///< ES 3.0+ integer format.
        RgInteger      = GL_RG_INTEGER,      ///< ES 3.0+
        RgbInteger     = GL_RGB_INTEGER,     ///< ES 3.0+
        RgbaInteger    = GL_RGBA_INTEGER,    ///< ES 3.0+
        DepthStencil   = GL_DEPTH_STENCIL,   ///< ES 3.0+
        StencilIndex   = GL_STENCIL_INDEX,   ///< ES 3.1+
        // Extension value — not in core gl32.h; defined in GL_EXT_bgra.
        Bgra           = 0x80E1
    };

    /**
     * @brief Pixel data type used in glTexImage*, glReadPixels, etc.
     */
    enum class PixelType : GLenum
    {
        UnsignedByte                = GL_UNSIGNED_BYTE,
        UnsignedShort4444           = GL_UNSIGNED_SHORT_4_4_4_4,
        UnsignedShort5551           = GL_UNSIGNED_SHORT_5_5_5_1,
        UnsignedShort565            = GL_UNSIGNED_SHORT_5_6_5,
        Byte                        = GL_BYTE,
        Short                       = GL_SHORT,
        UnsignedShort               = GL_UNSIGNED_SHORT,
        Int                         = GL_INT,
        UnsignedInt                 = GL_UNSIGNED_INT,
        HalfFloat                   = GL_HALF_FLOAT,                   ///< ES 3.0+
        Float                       = GL_FLOAT,
        UnsignedInt2101010Rev       = GL_UNSIGNED_INT_2_10_10_10_REV,  ///< ES 3.0+
        UnsignedInt10F11F11FRev     = GL_UNSIGNED_INT_10F_11F_11F_REV, ///< ES 3.0+
        UnsignedInt5999Rev          = GL_UNSIGNED_INT_5_9_9_9_REV,     ///< ES 3.0+
        UnsignedInt248              = GL_UNSIGNED_INT_24_8,             ///< ES 3.0+
        Float32UnsignedInt248Rev    = GL_FLOAT_32_UNSIGNED_INT_24_8_REV ///< ES 3.0+
    };

    /**
     * @brief Sized / unsized internal formats for textures and renderbuffers.
     */
    enum class InternalFormat : GLenum
    {
        // Base unsized formats (ES 2.0)
        DepthComponent = GL_DEPTH_COMPONENT,
        Alpha          = GL_ALPHA,
        Rgb            = GL_RGB,
        Rgba           = GL_RGBA,
        Luminance      = GL_LUMINANCE,
        LuminanceAlpha = GL_LUMINANCE_ALPHA,

        // Sized colour formats (ES 2.0)
        Rgba4   = GL_RGBA4,
        Rgb5A1  = GL_RGB5_A1,
        Rgb565  = GL_RGB565,

        // Depth/stencil (ES 2.0)
        DepthComponent16 = GL_DEPTH_COMPONENT16,
        StencilIndex8    = GL_STENCIL_INDEX8,

        // ES 3.0 colour formats
        R8           = GL_R8,
        R8Snorm      = GL_R8_SNORM,
        R16F         = GL_R16F,
        R32F         = GL_R32F,
        R8UI         = GL_R8UI,
        R8I          = GL_R8I,
        R16UI        = GL_R16UI,
        R16I         = GL_R16I,
        R32UI        = GL_R32UI,
        R32I         = GL_R32I,
        Rg8          = GL_RG8,
        Rg8Snorm     = GL_RG8_SNORM,
        Rg16F        = GL_RG16F,
        Rg32F        = GL_RG32F,
        Rg8UI        = GL_RG8UI,
        Rg8I         = GL_RG8I,
        Rg16UI       = GL_RG16UI,
        Rg16I        = GL_RG16I,
        Rg32UI       = GL_RG32UI,
        Rg32I        = GL_RG32I,
        Rgb8         = GL_RGB8,
        Srgb8        = GL_SRGB8,
        Rgb565Sized  = GL_RGB565,
        Rgb8Snorm    = GL_RGB8_SNORM,
        R11FG11FB10F = GL_R11F_G11F_B10F,
        Rgb9E5       = GL_RGB9_E5,
        Rgb16F       = GL_RGB16F,
        Rgb32F       = GL_RGB32F,
        Rgb8UI       = GL_RGB8UI,
        Rgb8I        = GL_RGB8I,
        Rgb16UI      = GL_RGB16UI,
        Rgb16I       = GL_RGB16I,
        Rgb32UI      = GL_RGB32UI,
        Rgb32I       = GL_RGB32I,
        Rgba8        = GL_RGBA8,
        Srgb8Alpha8  = GL_SRGB8_ALPHA8,
        Rgba8Snorm   = GL_RGBA8_SNORM,
        Rgb10A2      = GL_RGB10_A2,
        Rgb10A2UI    = GL_RGB10_A2UI,
        Rgba4Sized   = GL_RGBA4,
        Rgba16F      = GL_RGBA16F,
        Rgba32F      = GL_RGBA32F,
        Rgba8UI      = GL_RGBA8UI,
        Rgba8I       = GL_RGBA8I,
        Rgba16UI     = GL_RGBA16UI,
        Rgba16I      = GL_RGBA16I,
        Rgba32UI     = GL_RGBA32UI,
        Rgba32I      = GL_RGBA32I,

        // Desktop GL normalized formats not present in the GLES headers.
        Rgba16       = 0x805B,

        // Depth/stencil ES 3.0
        DepthComponent24  = GL_DEPTH_COMPONENT24,
        DepthComponent32F = GL_DEPTH_COMPONENT32F,
        Depth24Stencil8   = GL_DEPTH24_STENCIL8,
        Depth32FStencil8  = GL_DEPTH32F_STENCIL8
    };

    /**
     * @brief Sized internal formats (uncompressed) for immutable storage (ES 3.0+).
     */
    enum class SizedInternalFormat : GLenum
    {
        // ES 3.0 colour formats
        R8           = GL_R8,
        R8Snorm      = GL_R8_SNORM,
        R16F         = GL_R16F,
        R32F         = GL_R32F,
        R8UI         = GL_R8UI,
        R8I          = GL_R8I,
        R16UI        = GL_R16UI,
        R16I         = GL_R16I,
        R32UI        = GL_R32UI,
        R32I         = GL_R32I,
        Rg8          = GL_RG8,
        Rg8Snorm     = GL_RG8_SNORM,
        Rg16F        = GL_RG16F,
        Rg32F        = GL_RG32F,
        Rg8UI        = GL_RG8UI,
        Rg8I         = GL_RG8I,
        Rg16UI       = GL_RG16UI,
        Rg16I        = GL_RG16I,
        Rg32UI       = GL_RG32UI,
        Rg32I        = GL_RG32I,
        Rgb8         = GL_RGB8,
        Srgb8        = GL_SRGB8,
        Rgb565       = GL_RGB565,
        Rgb8Snorm    = GL_RGB8_SNORM,
        R11FG11FB10F = GL_R11F_G11F_B10F,
        Rgb9E5       = GL_RGB9_E5,
        Rgb16F       = GL_RGB16F,
        Rgb32F       = GL_RGB32F,
        Rgb8UI       = GL_RGB8UI,
        Rgb8I        = GL_RGB8I,
        Rgb16UI      = GL_RGB16UI,
        Rgb16I       = GL_RGB16I,
        Rgb32UI      = GL_RGB32UI,
        Rgb32I       = GL_RGB32I,
        Rgba8        = GL_RGBA8,
        Srgb8Alpha8  = GL_SRGB8_ALPHA8,
        Rgba8Snorm   = GL_RGBA8_SNORM,
        Rgb10A2      = GL_RGB10_A2,
        Rgb10A2UI    = GL_RGB10_A2UI,
        Rgba4        = GL_RGBA4,
        Rgb5A1       = GL_RGB5_A1,
        Rgba16F      = GL_RGBA16F,
        Rgba32F      = GL_RGBA32F,
        Rgba8UI      = GL_RGBA8UI,
        Rgba8I       = GL_RGBA8I,
        Rgba16UI     = GL_RGBA16UI,
        Rgba16I      = GL_RGBA16I,
        Rgba32UI     = GL_RGBA32UI,
        Rgba32I      = GL_RGBA32I,

        // Depth/stencil ES 3.0
        DepthComponent16  = GL_DEPTH_COMPONENT16,
        DepthComponent24  = GL_DEPTH_COMPONENT24,
        DepthComponent32F = GL_DEPTH_COMPONENT32F,
        Depth24Stencil8   = GL_DEPTH24_STENCIL8,
        Depth32FStencil8  = GL_DEPTH32F_STENCIL8,
        StencilIndex8     = GL_STENCIL_INDEX8
    };

    /**
     * @brief ETC2 / EAC and ASTC compressed internal formats (ES 3.0+).
     */
    enum class CompressedInternalFormat : GLenum
    {
        // ETC2 / EAC (ES 3.0+)
        R11Eac                          = GL_COMPRESSED_R11_EAC,
        SignedR11Eac                    = GL_COMPRESSED_SIGNED_R11_EAC,
        Rg11Eac                         = GL_COMPRESSED_RG11_EAC,
        SignedRg11Eac                   = GL_COMPRESSED_SIGNED_RG11_EAC,
        Rgb8Etc2                        = GL_COMPRESSED_RGB8_ETC2,
        Srgb8Etc2                       = GL_COMPRESSED_SRGB8_ETC2,
        Rgb8PunchthroughAlpha1Etc2      = GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2,
        Srgb8PunchthroughAlpha1Etc2     = GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2,
        Rgba8Etc2Eac                    = GL_COMPRESSED_RGBA8_ETC2_EAC,
        Srgb8Alpha8Etc2Eac              = GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC,

        // ASTC LDR (ES 3.2+)
        RgbaAstc4x4                     = GL_COMPRESSED_RGBA_ASTC_4x4,
        RgbaAstc5x4                     = GL_COMPRESSED_RGBA_ASTC_5x4,
        RgbaAstc5x5                     = GL_COMPRESSED_RGBA_ASTC_5x5,
        RgbaAstc6x5                     = GL_COMPRESSED_RGBA_ASTC_6x5,
        RgbaAstc6x6                     = GL_COMPRESSED_RGBA_ASTC_6x6,
        RgbaAstc8x5                     = GL_COMPRESSED_RGBA_ASTC_8x5,
        RgbaAstc8x6                     = GL_COMPRESSED_RGBA_ASTC_8x6,
        RgbaAstc8x8                     = GL_COMPRESSED_RGBA_ASTC_8x8,
        RgbaAstc10x5                    = GL_COMPRESSED_RGBA_ASTC_10x5,
        RgbaAstc10x6                    = GL_COMPRESSED_RGBA_ASTC_10x6,
        RgbaAstc10x8                    = GL_COMPRESSED_RGBA_ASTC_10x8,
        RgbaAstc10x10                   = GL_COMPRESSED_RGBA_ASTC_10x10,
        RgbaAstc12x10                   = GL_COMPRESSED_RGBA_ASTC_12x10,
        RgbaAstc12x12                   = GL_COMPRESSED_RGBA_ASTC_12x12,
        Srgb8Alpha8Astc4x4              = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4,
        Srgb8Alpha8Astc5x4              = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4,
        Srgb8Alpha8Astc5x5              = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5,
        Srgb8Alpha8Astc6x5              = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5,
        Srgb8Alpha8Astc6x6              = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6,
        Srgb8Alpha8Astc8x5              = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5,
        Srgb8Alpha8Astc8x6              = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6,
        Srgb8Alpha8Astc8x8              = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8,
        Srgb8Alpha8Astc10x5             = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5,
        Srgb8Alpha8Astc10x6             = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6,
        Srgb8Alpha8Astc10x8             = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8,
        Srgb8Alpha8Astc10x10            = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10,
        Srgb8Alpha8Astc12x10            = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10,
        Srgb8Alpha8Astc12x12            = GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12,

        // S3TC / DXT (GL_EXT_texture_compression_s3tc) -- an extension rather than an ES-core set,
        // so a context must be asked for it before these are used. DXT1 has two entries because the
        // same 8-byte block is read as opaque RGB or as RGB with one bit of alpha depending on
        // which internal format it is given.
        RgbS3tcDxt1                     = GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
        RgbaS3tcDxt1                    = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
        RgbaS3tcDxt3                    = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
        RgbaS3tcDxt5                    = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
    };

    /**
     * @brief String identifiers for glGetString().
     */
    enum class StringName : GLenum
    {
        Vendor                 = GL_VENDOR,
        Renderer               = GL_RENDERER,
        Version                = GL_VERSION,
        Extensions             = GL_EXTENSIONS,
        ShadingLanguageVersion = GL_SHADING_LANGUAGE_VERSION
    };

    /**
     * @brief Integer state names for glGetIntegerv() — kept for backwards compatibility with existing Functions.hpp signature.
     */
    enum class IntegerName : GLenum
    {
        MajorVersion   = GL_MAJOR_VERSION,
        MinorVersion   = GL_MINOR_VERSION,
        NumExtensions  = GL_NUM_EXTENSIONS,
        MaxTextureSize = GL_MAX_TEXTURE_SIZE,
        Viewport       = GL_VIEWPORT  ///< Returns 4 integers: x, y, width, height.
    };

    /**
     * @brief Shader stage types for glCreateShader().
     */
    enum class ShaderType : GLenum
    {
        Vertex         = GL_VERTEX_SHADER,
        Fragment       = GL_FRAGMENT_SHADER,
        Geometry       = GL_GEOMETRY_SHADER,        ///< ES 3.2+
        TessControl    = GL_TESS_CONTROL_SHADER,    ///< ES 3.2+
        TessEvaluation = GL_TESS_EVALUATION_SHADER, ///< ES 3.2+
        Compute        = GL_COMPUTE_SHADER           ///< ES 3.1+
    };

    /**
     * @brief Shader stage bitfield for glUseProgramStages() (separable programs).
     */
    enum class ShaderStageMask : GLbitfield
    {
        Vertex         = GL_VERTEX_SHADER_BIT,
        Fragment       = GL_FRAGMENT_SHADER_BIT,
        Geometry       = GL_GEOMETRY_SHADER_BIT,       ///< ES 3.2+
        TessControl    = GL_TESS_CONTROL_SHADER_BIT,   ///< ES 3.2+
        TessEvaluation = GL_TESS_EVALUATION_SHADER_BIT, ///< ES 3.2+
        Compute        = GL_COMPUTE_SHADER_BIT,         ///< ES 3.1+
        AllShaderBits  = GL_ALL_SHADER_BITS
    };

    /**
     * @brief Shader object parameter names for glGetShaderiv().
     */
    enum class ShaderParameter : GLenum
    {
        ShaderType    = GL_SHADER_TYPE,
        DeleteStatus  = GL_DELETE_STATUS,
        CompileStatus = GL_COMPILE_STATUS,
        InfoLogLength = GL_INFO_LOG_LENGTH,
        SourceLength  = GL_SHADER_SOURCE_LENGTH
    };

    /**
     * @brief Floating-point precision qualifiers, for glGetShaderPrecisionFormat().
     */
    enum class PrecisionType : GLenum
    {
        LowFloat   = GL_LOW_FLOAT,
        MediumFloat = GL_MEDIUM_FLOAT,
        HighFloat  = GL_HIGH_FLOAT,
        LowInt     = GL_LOW_INT,
        MediumInt  = GL_MEDIUM_INT,
        HighInt    = GL_HIGH_INT
    };

    /**
     * @brief Program object parameter names for glGetProgramiv().
     */
    enum class ProgramParameter : GLenum
    {
        DeleteStatus                = GL_DELETE_STATUS,
        LinkStatus                  = GL_LINK_STATUS,
        ValidateStatus              = GL_VALIDATE_STATUS,
        InfoLogLength               = GL_INFO_LOG_LENGTH,
        AttachedShaders             = GL_ATTACHED_SHADERS,
        ActiveUniforms              = GL_ACTIVE_UNIFORMS,
        ActiveUniformMaxLength      = GL_ACTIVE_UNIFORM_MAX_LENGTH,
        ActiveAttributes            = GL_ACTIVE_ATTRIBUTES,
        ActiveAttributeMaxLength    = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
        ActiveUniformBlocks         = GL_ACTIVE_UNIFORM_BLOCKS,          ///< ES 3.0+
        ActiveUniformBlockMaxLength = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, ///< ES 3.0+
        TransformFeedbackVaryings   = GL_TRANSFORM_FEEDBACK_VARYINGS,    ///< ES 3.0+
        TransformFeedbackVaryingMaxLength = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, ///< ES 3.0+
        TransformFeedbackBufferMode = GL_TRANSFORM_FEEDBACK_BUFFER_MODE, ///< ES 3.0+
        BinaryLength                = GL_PROGRAM_BINARY_LENGTH,          ///< ES 3.0+
        BinaryRetrievableHint       = GL_PROGRAM_BINARY_RETRIEVABLE_HINT,///< ES 3.0+
        Separable                   = GL_PROGRAM_SEPARABLE,              ///< ES 3.1+
        ActiveAtomicCounterBuffers  = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,  ///< ES 3.1+
        ComputeWorkGroupSize        = GL_COMPUTE_WORK_GROUP_SIZE,        ///< ES 3.1+ compute
        GeometryVerticesOut         = GL_GEOMETRY_VERTICES_OUT,          ///< ES 3.2+
        GeometryInputType           = GL_GEOMETRY_INPUT_TYPE,            ///< ES 3.2+
        GeometryOutputType          = GL_GEOMETRY_OUTPUT_TYPE,           ///< ES 3.2+
        GeometryShaderInvocations   = GL_GEOMETRY_SHADER_INVOCATIONS,    ///< ES 3.2+
        TessControlOutputVertices   = GL_TESS_CONTROL_OUTPUT_VERTICES,   ///< ES 3.2+
        TessGenMode                 = GL_TESS_GEN_MODE,                  ///< ES 3.2+
        TessGenSpacing              = GL_TESS_GEN_SPACING,               ///< ES 3.2+
        TessGenVertexOrder          = GL_TESS_GEN_VERTEX_ORDER,          ///< ES 3.2+
        TessGenPointMode            = GL_TESS_GEN_POINT_MODE             ///< ES 3.2+
    };

    /**
     * @brief Interface types for glGetProgramInterfaceiv() (ES 3.1+).
     */
    enum class ProgramInterface : GLenum
    {
        Uniform                     = GL_UNIFORM,
        UniformBlock                = GL_UNIFORM_BLOCK,
        ProgramInput                = GL_PROGRAM_INPUT,
        ProgramOutput               = GL_PROGRAM_OUTPUT,
        BufferVariable              = GL_BUFFER_VARIABLE,
        ShaderStorageBlock          = GL_SHADER_STORAGE_BLOCK,
        AtomicCounterBuffer         = GL_ATOMIC_COUNTER_BUFFER,
        TransformFeedbackVarying    = GL_TRANSFORM_FEEDBACK_VARYING
    };

    /**
     * @brief Program interface query parameters for glGetProgramInterfaceiv() (ES 3.1+).
     */
    enum class ProgramInterfaceParameter : GLenum
    {
        ActiveResources      = GL_ACTIVE_RESOURCES,
        MaxNameLength        = GL_MAX_NAME_LENGTH,
        MaxNumActiveVariables = GL_MAX_NUM_ACTIVE_VARIABLES
    };

    /**
     * @brief Resource property tokens for glGetProgramResourceiv() (ES 3.1+).
     */
    enum class ProgramResourceProperty : GLenum
    {
        NameLength                      = GL_NAME_LENGTH,
        Type                            = GL_TYPE,
        ArraySize                       = GL_ARRAY_SIZE,
        Offset                          = GL_OFFSET,
        BlockIndex                      = GL_BLOCK_INDEX,
        ArrayStride                     = GL_ARRAY_STRIDE,
        MatrixStride                    = GL_MATRIX_STRIDE,
        IsRowMajor                      = GL_IS_ROW_MAJOR,
        AtomicCounterBufferIndex        = GL_ATOMIC_COUNTER_BUFFER_INDEX,
        BufferBinding                   = GL_BUFFER_BINDING,
        BufferDataSize                  = GL_BUFFER_DATA_SIZE,
        NumActiveVariables              = GL_NUM_ACTIVE_VARIABLES,
        ActiveVariables                 = GL_ACTIVE_VARIABLES,
        ReferencedByVertexShader        = GL_REFERENCED_BY_VERTEX_SHADER,
        ReferencedByFragmentShader      = GL_REFERENCED_BY_FRAGMENT_SHADER,
        ReferencedByComputeShader       = GL_REFERENCED_BY_COMPUTE_SHADER,
        ReferencedByGeometryShader      = GL_REFERENCED_BY_GEOMETRY_SHADER,     ///< ES 3.2+
        ReferencedByTessControlShader   = GL_REFERENCED_BY_TESS_CONTROL_SHADER, ///< ES 3.2+
        ReferencedByTessEvaluationShader = GL_REFERENCED_BY_TESS_EVALUATION_SHADER, ///< ES 3.2+
        TopLevelArraySize               = GL_TOP_LEVEL_ARRAY_SIZE,
        TopLevelArrayStride             = GL_TOP_LEVEL_ARRAY_STRIDE,
        Location                        = GL_LOCATION,
        IsPerPatch                      = GL_IS_PER_PATCH  ///< ES 3.2+ tessellation
    };

    /**
     * @brief GLSL uniform and sampler/image type tokens returned by glGetActiveUniform().
     */
    enum class UniformType : GLenum
    {
        // Scalars and vectors
        Float         = GL_FLOAT,
        FloatVec2     = GL_FLOAT_VEC2,
        FloatVec3     = GL_FLOAT_VEC3,
        FloatVec4     = GL_FLOAT_VEC4,
        Int           = GL_INT,
        IntVec2       = GL_INT_VEC2,
        IntVec3       = GL_INT_VEC3,
        IntVec4       = GL_INT_VEC4,
        UnsignedInt   = GL_UNSIGNED_INT,
        UnsignedIntVec2 = GL_UNSIGNED_INT_VEC2,
        UnsignedIntVec3 = GL_UNSIGNED_INT_VEC3,
        UnsignedIntVec4 = GL_UNSIGNED_INT_VEC4,
        Bool          = GL_BOOL,
        BoolVec2      = GL_BOOL_VEC2,
        BoolVec3      = GL_BOOL_VEC3,
        BoolVec4      = GL_BOOL_VEC4,
        // Matrices
        FloatMat2     = GL_FLOAT_MAT2,
        FloatMat3     = GL_FLOAT_MAT3,
        FloatMat4     = GL_FLOAT_MAT4,
        FloatMat2x3   = GL_FLOAT_MAT2x3,
        FloatMat2x4   = GL_FLOAT_MAT2x4,
        FloatMat3x2   = GL_FLOAT_MAT3x2,
        FloatMat3x4   = GL_FLOAT_MAT3x4,
        FloatMat4x2   = GL_FLOAT_MAT4x2,
        FloatMat4x3   = GL_FLOAT_MAT4x3,
        // Samplers
        Sampler2D              = GL_SAMPLER_2D,
        Sampler3D              = GL_SAMPLER_3D,
        SamplerCube            = GL_SAMPLER_CUBE,
        Sampler2DShadow        = GL_SAMPLER_2D_SHADOW,
        Sampler2DArray         = GL_SAMPLER_2D_ARRAY,
        Sampler2DArrayShadow   = GL_SAMPLER_2D_ARRAY_SHADOW,
        SamplerCubeShadow      = GL_SAMPLER_CUBE_SHADOW,
        IntSampler2D           = GL_INT_SAMPLER_2D,
        IntSampler3D           = GL_INT_SAMPLER_3D,
        IntSamplerCube         = GL_INT_SAMPLER_CUBE,
        IntSampler2DArray      = GL_INT_SAMPLER_2D_ARRAY,
        UnsignedIntSampler2D   = GL_UNSIGNED_INT_SAMPLER_2D,
        UnsignedIntSampler3D   = GL_UNSIGNED_INT_SAMPLER_3D,
        UnsignedIntSamplerCube = GL_UNSIGNED_INT_SAMPLER_CUBE,
        UnsignedIntSampler2DArray = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,
        Sampler2DMultisample   = GL_SAMPLER_2D_MULTISAMPLE,          ///< ES 3.1+
        IntSampler2DMultisample = GL_INT_SAMPLER_2D_MULTISAMPLE,     ///< ES 3.1+
        UnsignedIntSampler2DMultisample = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE, ///< ES 3.1+
        UnsignedIntAtomicCounter = GL_UNSIGNED_INT_ATOMIC_COUNTER,   ///< ES 3.1+
        // Image types ES 3.1+
        Image2D                 = GL_IMAGE_2D,
        Image3D                 = GL_IMAGE_3D,
        ImageCube               = GL_IMAGE_CUBE,
        Image2DArray            = GL_IMAGE_2D_ARRAY,
        IntImage2D              = GL_INT_IMAGE_2D,
        IntImage3D              = GL_INT_IMAGE_3D,
        IntImageCube            = GL_INT_IMAGE_CUBE,
        IntImage2DArray         = GL_INT_IMAGE_2D_ARRAY,
        UnsignedIntImage2D      = GL_UNSIGNED_INT_IMAGE_2D,
        UnsignedIntImage3D      = GL_UNSIGNED_INT_IMAGE_3D,
        UnsignedIntImageCube    = GL_UNSIGNED_INT_IMAGE_CUBE,
        UnsignedIntImage2DArray = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,
        // ES 3.2+ buffer/cube-array/multisample-array types
        SamplerBuffer                       = GL_SAMPLER_BUFFER,
        IntSamplerBuffer                    = GL_INT_SAMPLER_BUFFER,
        UnsignedIntSamplerBuffer            = GL_UNSIGNED_INT_SAMPLER_BUFFER,
        ImageBuffer                         = GL_IMAGE_BUFFER,
        IntImageBuffer                      = GL_INT_IMAGE_BUFFER,
        UnsignedIntImageBuffer              = GL_UNSIGNED_INT_IMAGE_BUFFER,
        SamplerCubeMapArray                 = GL_SAMPLER_CUBE_MAP_ARRAY,
        SamplerCubeMapArrayShadow           = GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW,
        IntSamplerCubeMapArray              = GL_INT_SAMPLER_CUBE_MAP_ARRAY,
        UnsignedIntSamplerCubeMapArray      = GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY,
        ImageCubeMapArray                   = GL_IMAGE_CUBE_MAP_ARRAY,
        IntImageCubeMapArray                = GL_INT_IMAGE_CUBE_MAP_ARRAY,
        UnsignedIntImageCubeMapArray        = GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY,
        Sampler2DMultisampleArray           = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,
        IntSampler2DMultisampleArray        = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,
        UnsignedIntSampler2DMultisampleArray = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY
    };

    /**
     * @brief Uniform block query parameters for glGetActiveUniformBlockiv().
     */
    enum class UniformBlockParameter : GLenum
    {
        Binding                      = GL_UNIFORM_BLOCK_BINDING,
        DataSize                     = GL_UNIFORM_BLOCK_DATA_SIZE,
        NameLength                   = GL_UNIFORM_BLOCK_NAME_LENGTH,
        ActiveUniforms               = GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,
        ActiveUniformIndices         = GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
        ReferencedByVertexShader     = GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER,
        ReferencedByFragmentShader   = GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER
    };

    /**
     * @brief Per-uniform property tokens for glGetActiveUniformsiv().
     */
    enum class UniformParameter : GLenum
    {
        Type          = GL_UNIFORM_TYPE,
        Size          = GL_UNIFORM_SIZE,
        NameLength    = GL_UNIFORM_NAME_LENGTH,
        BlockIndex    = GL_UNIFORM_BLOCK_INDEX,
        Offset        = GL_UNIFORM_OFFSET,
        ArrayStride   = GL_UNIFORM_ARRAY_STRIDE,
        MatrixStride  = GL_UNIFORM_MATRIX_STRIDE,
        IsRowMajor    = GL_UNIFORM_IS_ROW_MAJOR
    };

    /**
     * @brief Texture binding targets for glBindTexture(), glTexImage2D(), etc.
     */
    enum class TextureTarget : GLenum
    {
        Texture2D                = GL_TEXTURE_2D,
        TextureCubeMap           = GL_TEXTURE_CUBE_MAP,
        TextureCubeMapPositiveX  = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        TextureCubeMapNegativeX  = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        TextureCubeMapPositiveY  = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        TextureCubeMapNegativeY  = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        TextureCubeMapPositiveZ  = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        TextureCubeMapNegativeZ  = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
        Texture3D                = GL_TEXTURE_3D,               ///< ES 3.0+
        Texture2DArray           = GL_TEXTURE_2D_ARRAY,         ///< ES 3.0+
        Texture2DMultisample     = GL_TEXTURE_2D_MULTISAMPLE,   ///< ES 3.1+
        TextureBuffer            = GL_TEXTURE_BUFFER,           ///< ES 3.2+
        TextureCubeMapArray      = GL_TEXTURE_CUBE_MAP_ARRAY,   ///< ES 3.2+
        Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY ///< ES 3.2+
    };

    /**
     * @brief Targets valid for glBindTexture (cube-map faces are excluded).
     */
    enum class TextureBindingTarget : GLenum
    {
        Texture2D                 = GL_TEXTURE_2D,
        TextureCubeMap            = GL_TEXTURE_CUBE_MAP,
        Texture3D                 = GL_TEXTURE_3D,
        Texture2DArray            = GL_TEXTURE_2D_ARRAY,
        Texture2DMultisample      = GL_TEXTURE_2D_MULTISAMPLE,
        TextureBuffer             = GL_TEXTURE_BUFFER,
        TextureCubeMapArray       = GL_TEXTURE_CUBE_MAP_ARRAY,
        Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
    };

    /**
     * @brief Texture targets legal for glCopyImageSubData().
     *
     * Cube-map faces and texture buffers are deliberately excluded. A cube-map
     * face is selected by the z coordinate while the target remains
     * GL_TEXTURE_CUBE_MAP. Renderbuffer endpoints are represented by
     * RenderbufferId overloads and therefore need no enum value here.
     */
    enum class ImageCopyTextureTarget : GLenum
    {
        Texture2D                 = GL_TEXTURE_2D,
        TextureCubeMap            = GL_TEXTURE_CUBE_MAP,
        Texture3D                 = GL_TEXTURE_3D,
        Texture2DArray            = GL_TEXTURE_2D_ARRAY,
        Texture2DMultisample      = GL_TEXTURE_2D_MULTISAMPLE,
        TextureCubeMapArray       = GL_TEXTURE_CUBE_MAP_ARRAY,
        Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
    };

    /**
     * @brief Texture parameter names for glTexParameteri / glTexParameterf (write-only or read-write).
     */
    enum class TextureParameterSetter : GLenum
    {
        MinFilter              = GL_TEXTURE_MIN_FILTER,
        MagFilter              = GL_TEXTURE_MAG_FILTER,
        WrapS                  = GL_TEXTURE_WRAP_S,
        WrapT                  = GL_TEXTURE_WRAP_T,
        WrapR                  = GL_TEXTURE_WRAP_R,               ///< ES 3.0+
        MinLod                 = GL_TEXTURE_MIN_LOD,              ///< ES 3.0+
        MaxLod                 = GL_TEXTURE_MAX_LOD,              ///< ES 3.0+
        BaseLevel              = GL_TEXTURE_BASE_LEVEL,           ///< ES 3.0+
        MaxLevel               = GL_TEXTURE_MAX_LEVEL,            ///< ES 3.0+
        CompareMode            = GL_TEXTURE_COMPARE_MODE,         ///< ES 3.0+
        CompareFunc            = GL_TEXTURE_COMPARE_FUNC,         ///< ES 3.0+
        SwizzleR               = GL_TEXTURE_SWIZZLE_R,            ///< ES 3.0+
        SwizzleG               = GL_TEXTURE_SWIZZLE_G,            ///< ES 3.0+
        SwizzleB               = GL_TEXTURE_SWIZZLE_B,            ///< ES 3.0+
        SwizzleA               = GL_TEXTURE_SWIZZLE_A,            ///< ES 3.0+
        DepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,  ///< ES 3.1+
        BorderColor            = GL_TEXTURE_BORDER_COLOR          ///< ES 3.2+
    };

    /**
     * @brief Texture parameter names for glGetTexParameter* (read-only or read-write).
     */
    enum class TextureParameterQuery : GLenum
    {
        MinFilter              = GL_TEXTURE_MIN_FILTER,
        MagFilter              = GL_TEXTURE_MAG_FILTER,
        WrapS                  = GL_TEXTURE_WRAP_S,
        WrapT                  = GL_TEXTURE_WRAP_T,
        WrapR                  = GL_TEXTURE_WRAP_R,
        MinLod                 = GL_TEXTURE_MIN_LOD,
        MaxLod                 = GL_TEXTURE_MAX_LOD,
        BaseLevel              = GL_TEXTURE_BASE_LEVEL,
        MaxLevel               = GL_TEXTURE_MAX_LEVEL,
        CompareMode            = GL_TEXTURE_COMPARE_MODE,
        CompareFunc            = GL_TEXTURE_COMPARE_FUNC,
        SwizzleR               = GL_TEXTURE_SWIZZLE_R,
        SwizzleG               = GL_TEXTURE_SWIZZLE_G,
        SwizzleB               = GL_TEXTURE_SWIZZLE_B,
        SwizzleA               = GL_TEXTURE_SWIZZLE_A,
        DepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
        BorderColor            = GL_TEXTURE_BORDER_COLOR,
        ImmutableFormat        = GL_TEXTURE_IMMUTABLE_FORMAT,     ///< Read-only, ES 3.0+
        ImmutableLevels        = GL_TEXTURE_IMMUTABLE_LEVELS,     ///< Read-only, ES 3.0+
        Samples                = GL_TEXTURE_SAMPLES,              ///< Read-only, ES 3.1+
        FixedSampleLocations   = GL_TEXTURE_FIXED_SAMPLE_LOCATIONS, ///< Read-only, ES 3.1+
        ImageFormatCompatibilityType = GL_IMAGE_FORMAT_COMPATIBILITY_TYPE, ///< Read-only, ES 3.1+
        BufferDataStoreBinding = GL_TEXTURE_BUFFER_DATA_STORE_BINDING, ///< Read-only, ES 3.2+
        BufferOffset           = GL_TEXTURE_BUFFER_OFFSET,        ///< Read-only, ES 3.2+
        BufferSize             = GL_TEXTURE_BUFFER_SIZE           ///< Read-only, ES 3.2+
    };

    /**
     * @brief Texture parameter names (combined setter/query). Use TextureParameterSetter or TextureParameterQuery for specific API calls.
     */
    enum class TextureParameter : GLenum
    {
        MinFilter              = GL_TEXTURE_MIN_FILTER,
        MagFilter              = GL_TEXTURE_MAG_FILTER,
        WrapS                  = GL_TEXTURE_WRAP_S,
        WrapT                  = GL_TEXTURE_WRAP_T,
        WrapR                  = GL_TEXTURE_WRAP_R,
        MinLod                 = GL_TEXTURE_MIN_LOD,
        MaxLod                 = GL_TEXTURE_MAX_LOD,
        BaseLevel              = GL_TEXTURE_BASE_LEVEL,
        MaxLevel               = GL_TEXTURE_MAX_LEVEL,
        CompareMode            = GL_TEXTURE_COMPARE_MODE,
        CompareFunc            = GL_TEXTURE_COMPARE_FUNC,
        SwizzleR               = GL_TEXTURE_SWIZZLE_R,
        SwizzleG               = GL_TEXTURE_SWIZZLE_G,
        SwizzleB               = GL_TEXTURE_SWIZZLE_B,
        SwizzleA               = GL_TEXTURE_SWIZZLE_A,
        ImmutableFormat        = GL_TEXTURE_IMMUTABLE_FORMAT,
        ImmutableLevels        = GL_TEXTURE_IMMUTABLE_LEVELS,
        Samples                = GL_TEXTURE_SAMPLES,
        FixedSampleLocations   = GL_TEXTURE_FIXED_SAMPLE_LOCATIONS,
        DepthStencilTextureMode = GL_DEPTH_STENCIL_TEXTURE_MODE,
        ImageFormatCompatibilityType = GL_IMAGE_FORMAT_COMPATIBILITY_TYPE,
        BorderColor            = GL_TEXTURE_BORDER_COLOR,
        BufferDataStoreBinding = GL_TEXTURE_BUFFER_DATA_STORE_BINDING,
        BufferOffset           = GL_TEXTURE_BUFFER_OFFSET,
        BufferSize             = GL_TEXTURE_BUFFER_SIZE
    };

    /** @brief Texture coordinate selector for a wrap-mode parameter. */
    enum class TextureWrapParameter : GLenum
    {
        WrapS = GL_TEXTURE_WRAP_S,
        WrapT = GL_TEXTURE_WRAP_T,
        WrapR = GL_TEXTURE_WRAP_R
    };

    /** @brief Texture component selector for a swizzle parameter. */
    enum class TextureSwizzleParameter : GLenum
    {
        SwizzleR = GL_TEXTURE_SWIZZLE_R,
        SwizzleG = GL_TEXTURE_SWIZZLE_G,
        SwizzleB = GL_TEXTURE_SWIZZLE_B,
        SwizzleA = GL_TEXTURE_SWIZZLE_A
    };

    /**
     * @brief Sampler parameter names for glSamplerParameter* / glGetSamplerParameter*. Only the subset of texture parameters valid for sampler objects is included. GL_TEXTURE_BASE_LEVEL, GL_TEXTURE_MAX_LEVEL, swizzle, etc. are excluded because the GL ES spec does not allow them on sampler objects.
     */
    enum class SamplerParameter : GLenum
    {
        MinFilter    = GL_TEXTURE_MIN_FILTER,    ///< Minification filter.
        MagFilter    = GL_TEXTURE_MAG_FILTER,    ///< Magnification filter.
        WrapS        = GL_TEXTURE_WRAP_S,        ///< Wrap mode for S coordinate.
        WrapT        = GL_TEXTURE_WRAP_T,        ///< Wrap mode for T coordinate.
        WrapR        = GL_TEXTURE_WRAP_R,        ///< Wrap mode for R coordinate. ES 3.0+
        MinLod       = GL_TEXTURE_MIN_LOD,       ///< Minimum LOD level. ES 3.0+
        MaxLod       = GL_TEXTURE_MAX_LOD,       ///< Maximum LOD level. ES 3.0+
        CompareMode  = GL_TEXTURE_COMPARE_MODE,  ///< Shadow comparison mode. ES 3.0+
        CompareFunc  = GL_TEXTURE_COMPARE_FUNC,  ///< Shadow comparison function. ES 3.0+
        BorderColor  = GL_TEXTURE_BORDER_COLOR,  ///< Border color for clamp-to-border. ES 3.2+
        MaxAnisotropy = GL_TEXTURE_MAX_ANISOTROPY_EXT ///< Max anisotropic filtering samples. GL_EXT_texture_filter_anisotropic
    };

    /** @brief Sampler coordinate selector for a wrap-mode parameter. */
    enum class SamplerWrapParameter : GLenum
    {
        WrapS = GL_TEXTURE_WRAP_S,
        WrapT = GL_TEXTURE_WRAP_T,
        WrapR = GL_TEXTURE_WRAP_R
    };

    /**
     * @brief Minification filter for TextureParameter::MinFilter (glTexParameter*). Includes mipmap variants; use TextureMagFilter for magnification.
     */
    enum class TextureMinFilter : GLenum
    {
        Nearest              = GL_NEAREST,
        Linear               = GL_LINEAR,
        NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
        LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
        NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
        LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR
    };

    /**
     * @brief Magnification filter for TextureParameter::MagFilter (glTexParameter*). Only Nearest/Linear are valid; mipmap variants are not allowed here.
     */
    enum class TextureMagFilter : GLenum
    {
        Nearest = GL_NEAREST,
        Linear  = GL_LINEAR
    };

    /**
     * @brief Filter parameter for glBlitFramebuffer. Only Nearest/Linear are valid. Not related to texture sampling — kept separate to prevent misuse.
     */
    enum class BlitFilter : GLenum
    {
        Nearest = GL_NEAREST,
        Linear  = GL_LINEAR
    };

    /**
     * @brief Texture wrap modes for TextureParameter::WrapS/T/R.
     */
    enum class TextureWrapMode : GLenum
    {
        Repeat         = GL_REPEAT,
        ClampToEdge    = GL_CLAMP_TO_EDGE,
        MirroredRepeat = GL_MIRRORED_REPEAT,
        ClampToBorder  = GL_CLAMP_TO_BORDER  ///< ES 3.2+
    };

    /**
     * @brief Texture compare mode for shadow samplers (TextureParameter::CompareMode).
     */
    enum class TextureCompareMode : GLenum
    {
        None                 = GL_NONE,
        CompareRefToTexture  = GL_COMPARE_REF_TO_TEXTURE  ///< ES 3.0+
    };

    /**
     * @brief Swizzle component values for TextureParameter::SwizzleR/G/B/A (ES 3.0+).
     */
    enum class TextureSwizzle : GLenum
    {
        Red   = GL_RED,
        Green = GL_GREEN,
        Blue  = GL_BLUE,
        Alpha = GL_ALPHA,
        Zero  = GL_ZERO,
        One   = GL_ONE
    };

    /**
     * @brief Texture level parameters for glGetTexLevelParameteriv() (ES 3.1+).
     */
    enum class TextureLevelParameter : GLenum
    {
        Width               = GL_TEXTURE_WIDTH,
        Height              = GL_TEXTURE_HEIGHT,
        Depth               = GL_TEXTURE_DEPTH,
        InternalFormat      = GL_TEXTURE_INTERNAL_FORMAT,
        RedSize             = GL_TEXTURE_RED_SIZE,
        GreenSize           = GL_TEXTURE_GREEN_SIZE,
        BlueSize            = GL_TEXTURE_BLUE_SIZE,
        AlphaSize           = GL_TEXTURE_ALPHA_SIZE,
        DepthSize           = GL_TEXTURE_DEPTH_SIZE,
        StencilSize         = GL_TEXTURE_STENCIL_SIZE,
        SharedSize          = GL_TEXTURE_SHARED_SIZE,
        RedType             = GL_TEXTURE_RED_TYPE,
        GreenType           = GL_TEXTURE_GREEN_TYPE,
        BlueType            = GL_TEXTURE_BLUE_TYPE,
        AlphaType           = GL_TEXTURE_ALPHA_TYPE,
        DepthType           = GL_TEXTURE_DEPTH_TYPE,
        Compressed          = GL_TEXTURE_COMPRESSED
    };

    /**
     * @brief Texture unit tokens for glActiveTexture() (GL_TEXTURE0 … GL_TEXTURE31).
     */
    enum class TextureUnit : GLenum
    {
        Texture0  = GL_TEXTURE0,  Texture1  = GL_TEXTURE1,
        Texture2  = GL_TEXTURE2,  Texture3  = GL_TEXTURE3,
        Texture4  = GL_TEXTURE4,  Texture5  = GL_TEXTURE5,
        Texture6  = GL_TEXTURE6,  Texture7  = GL_TEXTURE7,
        Texture8  = GL_TEXTURE8,  Texture9  = GL_TEXTURE9,
        Texture10 = GL_TEXTURE10, Texture11 = GL_TEXTURE11,
        Texture12 = GL_TEXTURE12, Texture13 = GL_TEXTURE13,
        Texture14 = GL_TEXTURE14, Texture15 = GL_TEXTURE15,
        Texture16 = GL_TEXTURE16, Texture17 = GL_TEXTURE17,
        Texture18 = GL_TEXTURE18, Texture19 = GL_TEXTURE19,
        Texture20 = GL_TEXTURE20, Texture21 = GL_TEXTURE21,
        Texture22 = GL_TEXTURE22, Texture23 = GL_TEXTURE23,
        Texture24 = GL_TEXTURE24, Texture25 = GL_TEXTURE25,
        Texture26 = GL_TEXTURE26, Texture27 = GL_TEXTURE27,
        Texture28 = GL_TEXTURE28, Texture29 = GL_TEXTURE29,
        Texture30 = GL_TEXTURE30, Texture31 = GL_TEXTURE31
    };

    /**
     * @brief Pixel pack/unpack storage parameters for glPixelStorei().
     */
    enum class PixelStoreParam : GLenum
    {
        PackAlignment    = GL_PACK_ALIGNMENT,
        PackRowLength    = GL_PACK_ROW_LENGTH,     ///< ES 3.0+
        PackSkipRows     = GL_PACK_SKIP_ROWS,      ///< ES 3.0+
        PackSkipPixels   = GL_PACK_SKIP_PIXELS,    ///< ES 3.0+
        UnpackAlignment  = GL_UNPACK_ALIGNMENT,
        UnpackRowLength  = GL_UNPACK_ROW_LENGTH,   ///< ES 3.0+
        UnpackSkipRows   = GL_UNPACK_SKIP_ROWS,    ///< ES 3.0+
        UnpackSkipPixels = GL_UNPACK_SKIP_PIXELS,  ///< ES 3.0+
        UnpackSkipImages = GL_UNPACK_SKIP_IMAGES,  ///< ES 3.0+
        UnpackImageHeight = GL_UNPACK_IMAGE_HEIGHT  ///< ES 3.0+
    };

    /**
     * @brief Depth/stencil comparison function for glDepthFunc(), glStencilFunc(), etc.
     */
    enum class CompareFunc : GLenum
    {
        Never        = GL_NEVER,
        Less         = GL_LESS,
        Equal        = GL_EQUAL,
        Lequal       = GL_LEQUAL,
        Greater      = GL_GREATER,
        Notequal     = GL_NOTEQUAL,
        Gequal       = GL_GEQUAL,
        Always       = GL_ALWAYS
    };

    /**
     * @brief Stencil operation codes for glStencilOp().
     */
    enum class StencilOp : GLenum
    {
        Keep      = GL_KEEP,
        Zero      = GL_ZERO,
        Replace   = GL_REPLACE,
        Incr      = GL_INCR,
        Decr      = GL_DECR,
        Invert    = GL_INVERT,
        IncrWrap  = GL_INCR_WRAP,
        DecrWrap  = GL_DECR_WRAP
    };

    /**
     * @brief Framebuffer binding targets for glBindFramebuffer().
     */
    enum class FramebufferTarget : GLenum
    {
        Framebuffer     = GL_FRAMEBUFFER,
        DrawFramebuffer = GL_DRAW_FRAMEBUFFER,  ///< ES 3.0+
        ReadFramebuffer = GL_READ_FRAMEBUFFER   ///< ES 3.0+
    };

    /**
     * @brief Renderbuffer binding target for glBindRenderbuffer().
     */
    enum class RenderbufferTarget : GLenum
    {
        Renderbuffer = GL_RENDERBUFFER
    };

    /**
     * @brief Framebuffer attachment points. The 32 color attachment points shared by FramebufferAttachment, DrawBuffer, and ReadBuffer. Defined once here; use the constexpr conversion helpers below to convert to the target enum when needed.
     */
    enum class ColorAttachment : GLenum
    {
        Color0  = GL_COLOR_ATTACHMENT0,
        Color1  = GL_COLOR_ATTACHMENT1,
        Color2  = GL_COLOR_ATTACHMENT2,
        Color3  = GL_COLOR_ATTACHMENT3,
        Color4  = GL_COLOR_ATTACHMENT4,
        Color5  = GL_COLOR_ATTACHMENT5,
        Color6  = GL_COLOR_ATTACHMENT6,
        Color7  = GL_COLOR_ATTACHMENT7,
        Color8  = GL_COLOR_ATTACHMENT8,
        Color9  = GL_COLOR_ATTACHMENT9,
        Color10 = GL_COLOR_ATTACHMENT10,
        Color11 = GL_COLOR_ATTACHMENT11,
        Color12 = GL_COLOR_ATTACHMENT12,
        Color13 = GL_COLOR_ATTACHMENT13,
        Color14 = GL_COLOR_ATTACHMENT14,
        Color15 = GL_COLOR_ATTACHMENT15,
        Color16 = GL_COLOR_ATTACHMENT16,
        Color17 = GL_COLOR_ATTACHMENT17,
        Color18 = GL_COLOR_ATTACHMENT18,
        Color19 = GL_COLOR_ATTACHMENT19,
        Color20 = GL_COLOR_ATTACHMENT20,
        Color21 = GL_COLOR_ATTACHMENT21,
        Color22 = GL_COLOR_ATTACHMENT22,
        Color23 = GL_COLOR_ATTACHMENT23,
        Color24 = GL_COLOR_ATTACHMENT24,
        Color25 = GL_COLOR_ATTACHMENT25,
        Color26 = GL_COLOR_ATTACHMENT26,
        Color27 = GL_COLOR_ATTACHMENT27,
        Color28 = GL_COLOR_ATTACHMENT28,
        Color29 = GL_COLOR_ATTACHMENT29,
        Color30 = GL_COLOR_ATTACHMENT30,
        Color31 = GL_COLOR_ATTACHMENT31
    };

    /**
     * @brief Framebuffer attachment points for the default framebuffer (id=0).
     */
    enum class DefaultFramebufferAttachment : GLenum
    {
        Color   = GL_COLOR,
        Depth   = GL_DEPTH,
        Stencil = GL_STENCIL
    };

    /**
     * @brief Framebuffer attachment points. Color attachments are represented by ColorAttachment; use to_framebuffer_attachment() to convert.
     */
    enum class FramebufferAttachment : GLenum
    {
        None         = GL_NONE,
        Depth        = GL_DEPTH_ATTACHMENT,
        Stencil      = GL_STENCIL_ATTACHMENT,
        DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT  ///< ES 3.0+
    };

    constexpr FramebufferAttachment to_framebuffer_attachment(ColorAttachment a) noexcept
    {
        return static_cast<FramebufferAttachment>(static_cast<GLenum>(a));
    }

    /**
     * @brief Framebuffer completeness status returned by glCheckFramebufferStatus().
     */
    enum class FramebufferStatus : GLenum
    {
        Complete                    = GL_FRAMEBUFFER_COMPLETE,
        Undefined                   = GL_FRAMEBUFFER_UNDEFINED,               ///< ES 3.0+
        IncompleteAttachment        = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
        IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
        IncompleteDimensions        = GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS,
        Unsupported                 = GL_FRAMEBUFFER_UNSUPPORTED,
        IncompleteMultisample       = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,  ///< ES 3.0+
        IncompleteLayerTargets      = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS ///< ES 3.2+
    };

    /**
     * @brief Framebuffer attachment query parameters for glGetFramebufferAttachmentParameteriv().
     */
    enum class FramebufferAttachmentParameter : GLenum
    {
        ObjectType          = GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE,
        ObjectName          = GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
        TextureLevel        = GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL,
        TextureCubeMapFace  = GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE,
        ColorEncoding       = GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING,        ///< ES 3.0+
        ComponentType       = GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE,        ///< ES 3.0+
        RedSize             = GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE,              ///< ES 3.0+
        GreenSize           = GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE,            ///< ES 3.0+
        BlueSize            = GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE,             ///< ES 3.0+
        AlphaSize           = GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE,            ///< ES 3.0+
        DepthSize           = GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE,            ///< ES 3.0+
        StencilSize         = GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE,          ///< ES 3.0+
        TextureLayer        = GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER,         ///< ES 3.0+
        Layered             = GL_FRAMEBUFFER_ATTACHMENT_LAYERED                ///< ES 3.2+
    };

    /**
     * @brief Framebuffer default parameter names for glFramebufferParameteri() (ES 3.1+).
     */
    enum class FramebufferDefaultParameter : GLenum
    {
        Width               = GL_FRAMEBUFFER_DEFAULT_WIDTH,
        Height              = GL_FRAMEBUFFER_DEFAULT_HEIGHT,
        Samples             = GL_FRAMEBUFFER_DEFAULT_SAMPLES,
        FixedSampleLocations = GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS,
        Layers              = GL_FRAMEBUFFER_DEFAULT_LAYERS  ///< ES 3.2+
    };

    /**
     * @brief Renderbuffer object parameters for glGetRenderbufferParameteriv().
     */
    enum class RenderbufferParameter : GLenum
    {
        Width          = GL_RENDERBUFFER_WIDTH,
        Height         = GL_RENDERBUFFER_HEIGHT,
        InternalFormat = GL_RENDERBUFFER_INTERNAL_FORMAT,
        RedSize        = GL_RENDERBUFFER_RED_SIZE,
        GreenSize      = GL_RENDERBUFFER_GREEN_SIZE,
        BlueSize       = GL_RENDERBUFFER_BLUE_SIZE,
        AlphaSize      = GL_RENDERBUFFER_ALPHA_SIZE,
        DepthSize      = GL_RENDERBUFFER_DEPTH_SIZE,
        StencilSize    = GL_RENDERBUFFER_STENCIL_SIZE,
        Samples        = GL_RENDERBUFFER_SAMPLES  ///< ES 3.0+
    };

    /**
     * @brief Vertex attribute array query parameters for glGetVertexAttribiv(), etc.
     */
    enum class VertexAttribParameter : GLenum
    {
        ArrayEnabled        = GL_VERTEX_ATTRIB_ARRAY_ENABLED,
        ArraySize           = GL_VERTEX_ATTRIB_ARRAY_SIZE,
        ArrayStride         = GL_VERTEX_ATTRIB_ARRAY_STRIDE,
        ArrayType           = GL_VERTEX_ATTRIB_ARRAY_TYPE,
        ArrayNormalized     = GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,
        ArrayPointer        = GL_VERTEX_ATTRIB_ARRAY_POINTER,
        ArrayBufferBinding  = GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,
        CurrentVertexAttrib = GL_CURRENT_VERTEX_ATTRIB,
        ArrayInteger        = GL_VERTEX_ATTRIB_ARRAY_INTEGER,     ///< ES 3.0+
        ArrayDivisor        = GL_VERTEX_ATTRIB_ARRAY_DIVISOR,     ///< ES 3.0+
        Binding             = GL_VERTEX_ATTRIB_BINDING,           ///< ES 3.1+
        RelativeOffset      = GL_VERTEX_ATTRIB_RELATIVE_OFFSET    ///< ES 3.1+
    };

    /**
     * @brief Transform feedback buffer mode for glTransformFeedbackVaryings() (ES 3.0+).
     */
    enum class TransformFeedbackBufferMode : GLenum
    {
        InterleavedAttribs = GL_INTERLEAVED_ATTRIBS,
        SeparateAttribs    = GL_SEPARATE_ATTRIBS
    };

    /**
     * @brief Transform feedback object binding target for glBindTransformFeedback() (ES 3.0+).
     */
    enum class TransformFeedbackTarget : GLenum
    {
        TransformFeedback = GL_TRANSFORM_FEEDBACK
    };

    /**
     * @brief Exact primitive modes accepted by glBeginTransformFeedback() (ES 3.0+).
     *
     * Only Points, Lines, and Triangles are legal for transform feedback capture.
     * Use this instead of the broad PrimitiveType to prevent passing disallowed
     * modes (e.g. TriangleFan, TriangleStrip, LineStrip) at compile time.
     */
    enum class TransformFeedbackPrimitive : GLenum
    {
        Points    = GL_POINTS,
        Lines     = GL_LINES,
        Triangles = GL_TRIANGLES
    };

    /**
     * @brief Occlusion and primitives-written query targets (ES 3.0+).
     */
    enum class QueryTarget : GLenum
    {
        AnySamplesPassed             = GL_ANY_SAMPLES_PASSED,              ///< ES 3.0+
        AnySamplesPassedConservative = GL_ANY_SAMPLES_PASSED_CONSERVATIVE, ///< ES 3.0+
        TransformFeedbackPrimitivesWritten = GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, ///< ES 3.0+
        PrimitivesGenerated          = GL_PRIMITIVES_GENERATED             ///< ES 3.2+
    };

    /**
     * @brief Query target state parameters for glGetQueryiv() (ES 3.0+).
     */
    enum class QueryParameter : GLenum
    {
        CurrentQuery = GL_CURRENT_QUERY
    };

    /**
     * @brief Per-query-object parameters for glGetQueryObjectuiv() (ES 3.0+).
     */
    enum class QueryObjectParameter : GLenum
    {
        Result          = GL_QUERY_RESULT,
        ResultAvailable = GL_QUERY_RESULT_AVAILABLE
    };

    /**
     * @brief Fence sync condition for glFenceSync() (ES 3.0+).
     */
    enum class SyncCondition : GLenum
    {
        GpuCommandsComplete = GL_SYNC_GPU_COMMANDS_COMPLETE
    };

    /**
     * @brief Sync object parameter names for glGetSynciv() (ES 3.0+).
     */
    enum class SyncParameter : GLenum
    {
        ObjectType = GL_OBJECT_TYPE,
        Condition  = GL_SYNC_CONDITION,
        Status     = GL_SYNC_STATUS,
        Flags      = GL_SYNC_FLAGS
    };

    /**
     * @brief Sync wait result values returned by glClientWaitSync() (ES 3.0+).
     */
    enum class SyncWaitResult : GLenum
    {
        AlreadySignaled    = GL_ALREADY_SIGNALED,
        TimeoutExpired     = GL_TIMEOUT_EXPIRED,
        ConditionSatisfied = GL_CONDITION_SATISFIED,
        WaitFailed         = GL_WAIT_FAILED
    };

    /**
     * @brief Flush flag bitfield for glClientWaitSync() (ES 3.0+).
     */
    enum class SyncFlushMask : GLbitfield
    {
        None     = 0,
        Commands = GL_SYNC_FLUSH_COMMANDS_BIT
    };

    /**
     * @brief Image unit access mode for glBindImageTexture() (ES 3.1+).
     */
    enum class ImageAccess : GLenum
    {
        ReadOnly  = GL_READ_ONLY,
        WriteOnly = GL_WRITE_ONLY,
        ReadWrite = GL_READ_WRITE
    };

    /**
     * @brief Memory barrier bits for glMemoryBarrier() (ES 3.1+).
     */
    enum class MemoryBarrierMask : GLbitfield
    {
        VertexAttribArray   = GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT,
        ElementArray        = GL_ELEMENT_ARRAY_BARRIER_BIT,
        Uniform             = GL_UNIFORM_BARRIER_BIT,
        TextureFetch        = GL_TEXTURE_FETCH_BARRIER_BIT,
        ShaderImageAccess   = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
        Command             = GL_COMMAND_BARRIER_BIT,
        PixelBuffer         = GL_PIXEL_BUFFER_BARRIER_BIT,
        TextureUpdate       = GL_TEXTURE_UPDATE_BARRIER_BIT,
        BufferUpdate        = GL_BUFFER_UPDATE_BARRIER_BIT,
        Framebuffer         = GL_FRAMEBUFFER_BARRIER_BIT,
        TransformFeedback   = GL_TRANSFORM_FEEDBACK_BARRIER_BIT,
        AtomicCounter       = GL_ATOMIC_COUNTER_BARRIER_BIT,
        ShaderStorage       = GL_SHADER_STORAGE_BARRIER_BIT,
        AllBarrierBits      = GL_ALL_BARRIER_BITS
    };

    /**
     * @brief Memory barrier bits for glMemoryBarrierByRegion() (ES 3.1+).
     */
    enum class MemoryBarrierByRegionMask : GLbitfield
    {
        AtomicCounter     = GL_ATOMIC_COUNTER_BARRIER_BIT,
        Framebuffer       = GL_FRAMEBUFFER_BARRIER_BIT,
        ShaderImageAccess = GL_SHADER_IMAGE_ACCESS_BARRIER_BIT,
        ShaderStorage     = GL_SHADER_STORAGE_BARRIER_BIT,
        TextureFetch      = GL_TEXTURE_FETCH_BARRIER_BIT,
        Uniform           = GL_UNIFORM_BARRIER_BIT,
        AllBarrierBits    = GL_ALL_BARRIER_BITS
    };

    /**
     * @brief Context flag bits returned by glGetIntegerv(GL_CONTEXT_FLAGS) (ES 3.2+).
     */
    enum class ContextFlagMask : GLbitfield
    {
        Debug        = GL_CONTEXT_FLAG_DEBUG_BIT,
        RobustAccess = GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT
    };

    /**
     * @brief Graphics reset status returned by glGetGraphicsResetStatus() (ES 3.2+).
     */
    enum class GraphicsResetStatus : GLenum
    {
        NoError   = GL_NO_ERROR,
        Guilty    = GL_GUILTY_CONTEXT_RESET,
        Innocent  = GL_INNOCENT_CONTEXT_RESET,
        Unknown   = GL_UNKNOWN_CONTEXT_RESET
    };

    /**
     * @brief Reset notification strategy tokens (ES 3.2+ robust context).
     */
    enum class ResetNotificationStrategy : GLenum
    {
        NoResetNotification = GL_NO_RESET_NOTIFICATION,
        LoseContextOnReset  = GL_LOSE_CONTEXT_ON_RESET
    };

    /**
     * @brief Debug message sources for glDebugMessageControl() / callback (ES 3.2+).
     */
    enum class DebugSource : GLenum
    {
        DontCare = GL_DONT_CARE,
        Api            = GL_DEBUG_SOURCE_API,
        WindowSystem   = GL_DEBUG_SOURCE_WINDOW_SYSTEM,
        ShaderCompiler = GL_DEBUG_SOURCE_SHADER_COMPILER,
        ThirdParty     = GL_DEBUG_SOURCE_THIRD_PARTY,
        Application    = GL_DEBUG_SOURCE_APPLICATION,
        Other          = GL_DEBUG_SOURCE_OTHER
    };

    /**
     * @brief Debug message type tokens (ES 3.2+).
     */
    enum class DebugType : GLenum
    {
        DontCare = GL_DONT_CARE,
        Error               = GL_DEBUG_TYPE_ERROR,
        DeprecatedBehavior  = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
        UndefinedBehavior   = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
        Portability         = GL_DEBUG_TYPE_PORTABILITY,
        Performance         = GL_DEBUG_TYPE_PERFORMANCE,
        Other               = GL_DEBUG_TYPE_OTHER,
        Marker              = GL_DEBUG_TYPE_MARKER,
        PushGroup           = GL_DEBUG_TYPE_PUSH_GROUP,
        PopGroup            = GL_DEBUG_TYPE_POP_GROUP
    };

    /**
     * @brief Debug message severity levels (ES 3.2+).
     */
    enum class DebugSeverity : GLenum
    {
        DontCare = GL_DONT_CARE,
        High         = GL_DEBUG_SEVERITY_HIGH,
        Medium       = GL_DEBUG_SEVERITY_MEDIUM,
        Low          = GL_DEBUG_SEVERITY_LOW,
        Notification = GL_DEBUG_SEVERITY_NOTIFICATION
    };

    /**
     * @brief Object identifier tokens for glObjectLabel() / glGetObjectLabel() (ES 3.2+).
     */
    enum class DebugObjectLabel : GLenum
    {
        Buffer            = GL_BUFFER,
        Shader            = GL_SHADER,
        Program           = GL_PROGRAM,
        VertexArray       = GL_VERTEX_ARRAY,
        Query             = GL_QUERY,
        ProgramPipeline   = GL_PROGRAM_PIPELINE,
        Sampler           = GL_SAMPLER,
        Framebuffer       = GL_FRAMEBUFFER,
        Renderbuffer      = GL_RENDERBUFFER,
        Texture           = GL_TEXTURE,
        TransformFeedback = GL_TRANSFORM_FEEDBACK
    };

    /**
     * @brief Provoking-vertex convention for geometry shaders (ES 3.2+).
     */
    enum class ProvokingVertex : GLenum
    {
        FirstVertex     = GL_FIRST_VERTEX_CONVENTION,
        LastVertex      = GL_LAST_VERTEX_CONVENTION,
        UndefinedVertex = GL_UNDEFINED_VERTEX
    };

    /**
     * @brief Tessellation generation mode for glPatchParameteri (ES 3.2+).
     */
    enum class TessGenMode : GLenum
    {
        Quads     = GL_QUADS,
        Triangles = GL_TRIANGLES,
        Isolines  = GL_ISOLINES
    };

    /**
     * @brief Tessellation spacing for glPatchParameteri (ES 3.2+).
     */
    enum class TessGenSpacing : GLenum
    {
        Equal         = GL_EQUAL,
        FractionalOdd  = GL_FRACTIONAL_ODD,
        FractionalEven = GL_FRACTIONAL_EVEN
    };

    /**
     * @brief Patch parameter names for glPatchParameteri() (ES 3.2+).
     */
    enum class TessellationParameter : GLenum
    {
        PatchVertices = GL_PATCH_VERTICES
    };

    /**
     * @brief Large state-query token set — used with glGetBooleanv, glGetIntegerv, glGetInteger64v, glGetFloatv.  Grouped by functional area.
     */
    enum class GetParameter : GLenum
    {
        // Viewport / scissor
        Viewport              = GL_VIEWPORT,
        ScissorBox            = GL_SCISSOR_BOX,
        MaxViewportDims       = GL_MAX_VIEWPORT_DIMS,

        // Line
        LineWidth             = GL_LINE_WIDTH,
        AliasedPointSizeRange = GL_ALIASED_POINT_SIZE_RANGE,
        AliasedLineWidthRange = GL_ALIASED_LINE_WIDTH_RANGE,

        // Cull / face
        CullFaceMode = GL_CULL_FACE_MODE,
        FrontFace    = GL_FRONT_FACE,

        // Depth
        DepthRange        = GL_DEPTH_RANGE,
        DepthWritemask    = GL_DEPTH_WRITEMASK,
        DepthClearValue   = GL_DEPTH_CLEAR_VALUE,
        DepthFunc         = GL_DEPTH_FUNC,
        DepthBits         = GL_DEPTH_BITS,

        // Stencil
        StencilClearValue        = GL_STENCIL_CLEAR_VALUE,
        StencilFunc              = GL_STENCIL_FUNC,
        StencilFail              = GL_STENCIL_FAIL,
        StencilPassDepthFail     = GL_STENCIL_PASS_DEPTH_FAIL,
        StencilPassDepthPass     = GL_STENCIL_PASS_DEPTH_PASS,
        StencilRef               = GL_STENCIL_REF,
        StencilValueMask         = GL_STENCIL_VALUE_MASK,
        StencilWritemask         = GL_STENCIL_WRITEMASK,
        StencilBackFunc          = GL_STENCIL_BACK_FUNC,
        StencilBackFail          = GL_STENCIL_BACK_FAIL,
        StencilBackPassDepthFail = GL_STENCIL_BACK_PASS_DEPTH_FAIL,
        StencilBackPassDepthPass = GL_STENCIL_BACK_PASS_DEPTH_PASS,
        StencilBackRef           = GL_STENCIL_BACK_REF,
        StencilBackValueMask     = GL_STENCIL_BACK_VALUE_MASK,
        StencilBackWritemask     = GL_STENCIL_BACK_WRITEMASK,
        StencilBits              = GL_STENCIL_BITS,

        // Colour
        ColorClearValue    = GL_COLOR_CLEAR_VALUE,
        ColorWritemask     = GL_COLOR_WRITEMASK,
        RedBits            = GL_RED_BITS,
        GreenBits          = GL_GREEN_BITS,
        BlueBits           = GL_BLUE_BITS,
        AlphaBits          = GL_ALPHA_BITS,

        // Polygon offset
        PolygonOffsetUnits  = GL_POLYGON_OFFSET_UNITS,
        PolygonOffsetFactor = GL_POLYGON_OFFSET_FACTOR,

        // Multisample
        SampleBuffers          = GL_SAMPLE_BUFFERS,
        Samples                = GL_SAMPLES,
        SampleCoverageValue    = GL_SAMPLE_COVERAGE_VALUE,
        SampleCoverageInvert   = GL_SAMPLE_COVERAGE_INVERT,
        SampleMaskValue        = GL_SAMPLE_MASK_VALUE,         ///< ES 3.1+
        SamplePosition         = GL_SAMPLE_POSITION,           ///< ES 3.1+
        MaxSampleMaskWords     = GL_MAX_SAMPLE_MASK_WORDS,     ///< ES 3.1+
        MaxColorTextureSamples = GL_MAX_COLOR_TEXTURE_SAMPLES, ///< ES 3.1+
        MaxDepthTextureSamples = GL_MAX_DEPTH_TEXTURE_SAMPLES, ///< ES 3.1+
        MaxIntegerSamples      = GL_MAX_INTEGER_SAMPLES,       ///< ES 3.1+
        MaxSamples             = GL_MAX_SAMPLES,               ///< ES 3.0+
        MinSampleShadingValue  = GL_MIN_SAMPLE_SHADING_VALUE,  ///< ES 3.2+

        // Texture
        NumCompressedTextureFormats  = GL_NUM_COMPRESSED_TEXTURE_FORMATS,
        CompressedTextureFormats     = GL_COMPRESSED_TEXTURE_FORMATS,
        MaxTextureSize               = GL_MAX_TEXTURE_SIZE,
        MaxCubeMapTextureSize        = GL_MAX_CUBE_MAP_TEXTURE_SIZE,
        Max3DTextureSize             = GL_MAX_3D_TEXTURE_SIZE,          ///< ES 3.0+
        MaxArrayTextureLayers        = GL_MAX_ARRAY_TEXTURE_LAYERS,     ///< ES 3.0+
        MaxTextureBufferSize         = GL_MAX_TEXTURE_BUFFER_SIZE,      ///< ES 3.2+
        MaxTextureLodBias            = GL_MAX_TEXTURE_LOD_BIAS,         ///< ES 3.0+
        MaxTextureMaxAnisotropy      = GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, ///< GL_EXT_texture_filter_anisotropic
        TextureBinding2D             = GL_TEXTURE_BINDING_2D,
        TextureBindingCubeMap        = GL_TEXTURE_BINDING_CUBE_MAP,
        TextureBinding3D             = GL_TEXTURE_BINDING_3D,           ///< ES 3.0+
        TextureBinding2DArray        = GL_TEXTURE_BINDING_2D_ARRAY,     ///< ES 3.0+
        TextureBinding2DMultisample  = GL_TEXTURE_BINDING_2D_MULTISAMPLE, ///< ES 3.1+
        TextureBindingBuffer         = GL_TEXTURE_BINDING_BUFFER,       ///< ES 3.2+
        TextureBindingCubeMapArray   = GL_TEXTURE_BINDING_CUBE_MAP_ARRAY,///< ES 3.2+
        TextureBinding2DMultisampleArray = GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, ///< ES 3.2+
        SubpixelBits                 = GL_SUBPIXEL_BITS,
        ActiveTexture                = GL_ACTIVE_TEXTURE,
        SamplerBinding               = GL_SAMPLER_BINDING,              ///< ES 3.0+

        // Pixel operations
        ImplementationColorReadType   = GL_IMPLEMENTATION_COLOR_READ_TYPE,
        ImplementationColorReadFormat = GL_IMPLEMENTATION_COLOR_READ_FORMAT,

        // Blend
        BlendColor        = GL_BLEND_COLOR,
        BlendEquationRgb  = GL_BLEND_EQUATION_RGB,
        BlendEquationAlpha = GL_BLEND_EQUATION_ALPHA,
        BlendDstRgb       = GL_BLEND_DST_RGB,
        BlendSrcRgb       = GL_BLEND_SRC_RGB,
        BlendDstAlpha     = GL_BLEND_DST_ALPHA,
        BlendSrcAlpha     = GL_BLEND_SRC_ALPHA,

        // Buffer bindings
        ArrayBufferBinding          = GL_ARRAY_BUFFER_BINDING,
        ElementArrayBufferBinding   = GL_ELEMENT_ARRAY_BUFFER_BINDING,
        PixelPackBufferBinding      = GL_PIXEL_PACK_BUFFER_BINDING,        ///< ES 3.0+
        PixelUnpackBufferBinding    = GL_PIXEL_UNPACK_BUFFER_BINDING,      ///< ES 3.0+
        UniformBufferBinding        = GL_UNIFORM_BUFFER_BINDING,           ///< ES 3.0+
        UniformBufferStart          = GL_UNIFORM_BUFFER_START,             ///< ES 3.0+
        UniformBufferSize           = GL_UNIFORM_BUFFER_SIZE,              ///< ES 3.0+
        TransformFeedbackBufferBinding = GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, ///< ES 3.0+
        TransformFeedbackBufferStart   = GL_TRANSFORM_FEEDBACK_BUFFER_START,   ///< ES 3.0+
        TransformFeedbackBufferSize    = GL_TRANSFORM_FEEDBACK_BUFFER_SIZE,    ///< ES 3.0+
        CopyReadBufferBinding       = GL_COPY_READ_BUFFER_BINDING,         ///< ES 3.0+
        CopyWriteBufferBinding      = GL_COPY_WRITE_BUFFER_BINDING,        ///< ES 3.0+
        DrawIndirectBufferBinding   = GL_DRAW_INDIRECT_BUFFER_BINDING,     ///< ES 3.1+
        DispatchIndirectBufferBinding = GL_DISPATCH_INDIRECT_BUFFER_BINDING, ///< ES 3.1+
        ShaderStorageBufferBinding  = GL_SHADER_STORAGE_BUFFER_BINDING,    ///< ES 3.1+
        ShaderStorageBufferStart    = GL_SHADER_STORAGE_BUFFER_START,      ///< ES 3.1+
        ShaderStorageBufferSize     = GL_SHADER_STORAGE_BUFFER_SIZE,       ///< ES 3.1+
        AtomicCounterBufferBinding  = GL_ATOMIC_COUNTER_BUFFER_BINDING,    ///< ES 3.1+
        AtomicCounterBufferStart    = GL_ATOMIC_COUNTER_BUFFER_START,      ///< ES 3.1+
        AtomicCounterBufferSize     = GL_ATOMIC_COUNTER_BUFFER_SIZE,       ///< ES 3.1+

        // VAO
        VertexArrayBinding          = GL_VERTEX_ARRAY_BINDING,             ///< ES 3.0+
        VertexBindingDivisor        = GL_VERTEX_BINDING_DIVISOR,           ///< ES 3.1+
        VertexBindingOffset         = GL_VERTEX_BINDING_OFFSET,            ///< ES 3.1+
        VertexBindingStride         = GL_VERTEX_BINDING_STRIDE,            ///< ES 3.1+
        VertexBindingBuffer         = GL_VERTEX_BINDING_BUFFER,            ///< ES 3.1+
        MaxVertexAttribRelativeOffset = GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, ///< ES 3.1+
        MaxVertexAttribBindings     = GL_MAX_VERTEX_ATTRIB_BINDINGS,       ///< ES 3.1+
        MaxVertexAttribStride       = GL_MAX_VERTEX_ATTRIB_STRIDE,         ///< ES 3.1+

        // Framebuffer
        FramebufferBinding         = GL_FRAMEBUFFER_BINDING,
        DrawFramebufferBinding     = GL_DRAW_FRAMEBUFFER_BINDING,          ///< Alias of FramebufferBinding in GLES; to_string() returns the canonical name.
        ReadFramebufferBinding     = GL_READ_FRAMEBUFFER_BINDING,          ///< ES 3.0+
        RenderbufferBinding        = GL_RENDERBUFFER_BINDING,
        MaxRenderbufferSize        = GL_MAX_RENDERBUFFER_SIZE,
        MaxColorAttachments        = GL_MAX_COLOR_ATTACHMENTS,             ///< ES 3.0+
        MaxFramebufferWidth        = GL_MAX_FRAMEBUFFER_WIDTH,             ///< ES 3.1+
        MaxFramebufferHeight       = GL_MAX_FRAMEBUFFER_HEIGHT,            ///< ES 3.1+
        MaxFramebufferSamples      = GL_MAX_FRAMEBUFFER_SAMPLES,           ///< ES 3.1+
        MaxFramebufferLayers       = GL_MAX_FRAMEBUFFER_LAYERS,            ///< ES 3.2+

        // Draw buffers
        ReadBuffer    = GL_READ_BUFFER,                                     ///< ES 3.0+
        MaxDrawBuffers = GL_MAX_DRAW_BUFFERS,                               ///< ES 3.0+
        DrawBuffer0   = GL_DRAW_BUFFER0,   DrawBuffer1  = GL_DRAW_BUFFER1,
        DrawBuffer2   = GL_DRAW_BUFFER2,   DrawBuffer3  = GL_DRAW_BUFFER3,
        DrawBuffer4   = GL_DRAW_BUFFER4,   DrawBuffer5  = GL_DRAW_BUFFER5,
        DrawBuffer6   = GL_DRAW_BUFFER6,   DrawBuffer7  = GL_DRAW_BUFFER7,
        DrawBuffer8   = GL_DRAW_BUFFER8,   DrawBuffer9  = GL_DRAW_BUFFER9,
        DrawBuffer10  = GL_DRAW_BUFFER10,  DrawBuffer11 = GL_DRAW_BUFFER11,
        DrawBuffer12  = GL_DRAW_BUFFER12,  DrawBuffer13 = GL_DRAW_BUFFER13,
        DrawBuffer14  = GL_DRAW_BUFFER14,  DrawBuffer15 = GL_DRAW_BUFFER15,

        // Shader limits
        MaxVertexAttribs                = GL_MAX_VERTEX_ATTRIBS,
        MaxVertexUniformVectors         = GL_MAX_VERTEX_UNIFORM_VECTORS,
        MaxVaryingVectors               = GL_MAX_VARYING_VECTORS,
        MaxCombinedTextureImageUnits    = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        MaxVertexTextureImageUnits      = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
        MaxTextureImageUnits            = GL_MAX_TEXTURE_IMAGE_UNITS,
        MaxFragmentUniformVectors       = GL_MAX_FRAGMENT_UNIFORM_VECTORS,
        MaxVertexUniformComponents      = GL_MAX_VERTEX_UNIFORM_COMPONENTS,   ///< ES 3.0+
        MaxFragmentUniformComponents    = GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, ///< ES 3.0+
        MaxVaryingComponents            = GL_MAX_VARYING_COMPONENTS,          ///< ES 3.0+
        MaxVertexOutputComponents       = GL_MAX_VERTEX_OUTPUT_COMPONENTS,    ///< ES 3.0+
        MaxFragmentInputComponents      = GL_MAX_FRAGMENT_INPUT_COMPONENTS,   ///< ES 3.0+
        MaxVertexUniformBlocks          = GL_MAX_VERTEX_UNIFORM_BLOCKS,       ///< ES 3.0+
        MaxFragmentUniformBlocks        = GL_MAX_FRAGMENT_UNIFORM_BLOCKS,     ///< ES 3.0+
        MaxCombinedUniformBlocks        = GL_MAX_COMBINED_UNIFORM_BLOCKS,     ///< ES 3.0+
        MaxUniformBufferBindings        = GL_MAX_UNIFORM_BUFFER_BINDINGS,     ///< ES 3.0+
        MaxUniformBlockSize             = GL_MAX_UNIFORM_BLOCK_SIZE,          ///< ES 3.0+
        MaxCombinedVertexUniformComponents   = GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,  ///< ES 3.0+
        MaxCombinedFragmentUniformComponents = GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,///< ES 3.0+
        UniformBufferOffsetAlignment    = GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, ///< ES 3.0+
        MinProgramTexelOffset           = GL_MIN_PROGRAM_TEXEL_OFFSET,        ///< ES 3.0+
        MaxProgramTexelOffset           = GL_MAX_PROGRAM_TEXEL_OFFSET,        ///< ES 3.0+
        MaxUniformLocations             = GL_MAX_UNIFORM_LOCATIONS,           ///< ES 3.1+
        MaxShaderStorageBufferBindings  = GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, ///< ES 3.1+
        MaxShaderStorageBlockSize       = GL_MAX_SHADER_STORAGE_BLOCK_SIZE,   ///< ES 3.1+
        ShaderStorageBufferOffsetAlignment = GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, ///< ES 3.1+
        MaxCombinedShaderStorageBlocks  = GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS, ///< ES 3.1+
        MaxVertexShaderStorageBlocks    = GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS,///< ES 3.1+
        MaxFragmentShaderStorageBlocks  = GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS,///< ES 3.1+
        MaxComputeShaderStorageBlocks   = GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS,///< ES 3.1+
        MaxCombinedShaderOutputResources = GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES, ///< ES 3.1+
        MaxImageUnits                   = GL_MAX_IMAGE_UNITS,                ///< ES 3.1+
        MaxVertexImageUniforms          = GL_MAX_VERTEX_IMAGE_UNIFORMS,      ///< ES 3.1+
        MaxFragmentImageUniforms        = GL_MAX_FRAGMENT_IMAGE_UNIFORMS,    ///< ES 3.1+
        MaxCombinedImageUniforms        = GL_MAX_COMBINED_IMAGE_UNIFORMS,    ///< ES 3.1+
        MaxAtomicCounterBufferBindings  = GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS, ///< ES 3.1+
        MaxAtomicCounterBufferSize      = GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE, ///< ES 3.1+
        MaxVertexAtomicCounterBuffers   = GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS, ///< ES 3.1+
        MaxFragmentAtomicCounterBuffers = GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS,///< ES 3.1+
        MaxCombinedAtomicCounterBuffers = GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS,///< ES 3.1+
        MaxVertexAtomicCounters         = GL_MAX_VERTEX_ATOMIC_COUNTERS,     ///< ES 3.1+
        MaxFragmentAtomicCounters       = GL_MAX_FRAGMENT_ATOMIC_COUNTERS,   ///< ES 3.1+
        MaxCombinedAtomicCounters       = GL_MAX_COMBINED_ATOMIC_COUNTERS,   ///< ES 3.1+

        // Compute (ES 3.1+)
        MaxComputeUniformBlocks          = GL_MAX_COMPUTE_UNIFORM_BLOCKS,
        MaxComputeTextureImageUnits      = GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS,
        MaxComputeImageUniforms          = GL_MAX_COMPUTE_IMAGE_UNIFORMS,
        MaxComputeSharedMemorySize       = GL_MAX_COMPUTE_SHARED_MEMORY_SIZE,
        MaxComputeUniformComponents      = GL_MAX_COMPUTE_UNIFORM_COMPONENTS,
        MaxComputeAtomicCounterBuffers   = GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
        MaxComputeAtomicCounters         = GL_MAX_COMPUTE_ATOMIC_COUNTERS,
        MaxCombinedComputeUniformComponents = GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,
        MaxComputeWorkGroupInvocations   = GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS,
        MaxComputeWorkGroupCount         = GL_MAX_COMPUTE_WORK_GROUP_COUNT,
        MaxComputeWorkGroupSize          = GL_MAX_COMPUTE_WORK_GROUP_SIZE,

        // Geometry shader (ES 3.2+)
        MaxGeometryUniformComponents     = GL_MAX_GEOMETRY_UNIFORM_COMPONENTS,
        MaxGeometryUniformBlocks         = GL_MAX_GEOMETRY_UNIFORM_BLOCKS,
        MaxCombinedGeometryUniformComponents = GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,
        MaxGeometryInputComponents       = GL_MAX_GEOMETRY_INPUT_COMPONENTS,
        MaxGeometryOutputComponents      = GL_MAX_GEOMETRY_OUTPUT_COMPONENTS,
        MaxGeometryOutputVertices        = GL_MAX_GEOMETRY_OUTPUT_VERTICES,
        MaxGeometryTotalOutputComponents = GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS,
        MaxGeometryShaderInvocations     = GL_MAX_GEOMETRY_SHADER_INVOCATIONS,
        MaxGeometryTextureImageUnits     = GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS,
        MaxGeometryAtomicCounterBuffers  = GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS,
        MaxGeometryAtomicCounters        = GL_MAX_GEOMETRY_ATOMIC_COUNTERS,
        MaxGeometryImageUniforms         = GL_MAX_GEOMETRY_IMAGE_UNIFORMS,
        MaxGeometryShaderStorageBlocks   = GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS,
        LayerProvokingVertex             = GL_LAYER_PROVOKING_VERTEX,

        // Tessellation (ES 3.2+)
        MaxPatchVertices                     = GL_MAX_PATCH_VERTICES,
        MaxTessGenLevel                      = GL_MAX_TESS_GEN_LEVEL,
        MaxTessControlUniformComponents      = GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS,
        MaxTessEvaluationUniformComponents   = GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS,
        MaxTessControlTextureImageUnits      = GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS,
        MaxTessEvaluationTextureImageUnits   = GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS,
        MaxTessControlOutputComponents       = GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS,
        MaxTessPatchComponents               = GL_MAX_TESS_PATCH_COMPONENTS,
        MaxTessControlTotalOutputComponents  = GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS,
        MaxTessEvaluationOutputComponents    = GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS,
        MaxTessControlUniformBlocks          = GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS,
        MaxTessEvaluationUniformBlocks       = GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS,
        MaxTessControlInputComponents        = GL_MAX_TESS_CONTROL_INPUT_COMPONENTS,
        MaxTessEvaluationInputComponents     = GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS,
        MaxCombinedTessControlUniformComponents   = GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS,
        MaxCombinedTessEvaluationUniformComponents = GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS,
        MaxTessControlAtomicCounterBuffers   = GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS,
        MaxTessEvaluationAtomicCounterBuffers = GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS,
        MaxTessControlAtomicCounters         = GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS,
        MaxTessEvaluationAtomicCounters      = GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS,
        MaxTessControlImageUniforms          = GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS,
        MaxTessEvaluationImageUniforms       = GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS,
        MaxTessControlShaderStorageBlocks    = GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS,
        MaxTessEvaluationShaderStorageBlocks = GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS,
        PrimitiveRestartForPatchesSupported  = GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED,

        // Fragment shader
        MinFragmentInterpolationOffset  = GL_MIN_FRAGMENT_INTERPOLATION_OFFSET,  ///< ES 3.2+
        MaxFragmentInterpolationOffset  = GL_MAX_FRAGMENT_INTERPOLATION_OFFSET,  ///< ES 3.2+
        FragmentInterpolationOffsetBits = GL_FRAGMENT_INTERPOLATION_OFFSET_BITS, ///< ES 3.2+
        MinProgramTextureGatherOffset   = GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET,  ///< ES 3.1+
        MaxProgramTextureGatherOffset   = GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET,  ///< ES 3.1+

        // Transform feedback (ES 3.0+)
        TransformFeedbackActive  = GL_TRANSFORM_FEEDBACK_ACTIVE,
        TransformFeedbackPaused  = GL_TRANSFORM_FEEDBACK_PAUSED,
        TransformFeedbackBinding = GL_TRANSFORM_FEEDBACK_BINDING,
        MaxTransformFeedbackSeparateComponents   = GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS,
        MaxTransformFeedbackInterleavedComponents = GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS,
        MaxTransformFeedbackSeparateAttribs      = GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS,

        // Program pipelines (ES 3.1+)
        ProgramPipelineBinding = GL_PROGRAM_PIPELINE_BINDING,
        CurrentProgram         = GL_CURRENT_PROGRAM,

        // Program binary (ES 3.0+)
        NumProgramBinaryFormats = GL_NUM_PROGRAM_BINARY_FORMATS,
        ProgramBinaryFormats    = GL_PROGRAM_BINARY_FORMATS,

        // Shader binary
        ShaderCompiler         = GL_SHADER_COMPILER,
        ShaderBinaryFormats    = GL_SHADER_BINARY_FORMATS,
        NumShaderBinaryFormats = GL_NUM_SHADER_BINARY_FORMATS,

        // Version info
        MajorVersion  = GL_MAJOR_VERSION,
        MinorVersion  = GL_MINOR_VERSION,
        NumExtensions = GL_NUM_EXTENSIONS,

        // Sync (ES 3.0+)
        MaxServerWaitTimeout = GL_MAX_SERVER_WAIT_TIMEOUT,

        // Debug (ES 3.2+)
        MaxDebugMessageLength       = GL_MAX_DEBUG_MESSAGE_LENGTH,
        MaxDebugLoggedMessages      = GL_MAX_DEBUG_LOGGED_MESSAGES,
        DebugLoggedMessages         = GL_DEBUG_LOGGED_MESSAGES,
        DebugNextLoggedMessageLength = GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH,
        MaxDebugGroupStackDepth     = GL_MAX_DEBUG_GROUP_STACK_DEPTH,
        DebugGroupStackDepth        = GL_DEBUG_GROUP_STACK_DEPTH,
        MaxLabelLength              = GL_MAX_LABEL_LENGTH,
        ContextFlags                = GL_CONTEXT_FLAGS,
        ResetNotificationStrategy   = GL_RESET_NOTIFICATION_STRATEGY,

        // Multiline width (ES 3.2+)
        MultisampleLineWidthRange       = GL_MULTISAMPLE_LINE_WIDTH_RANGE,
        MultisampleLineWidthGranularity = GL_MULTISAMPLE_LINE_WIDTH_GRANULARITY,

        // Element index (ES 3.0+)
        MaxElementIndex    = GL_MAX_ELEMENT_INDEX,
        MaxElementsVertices = GL_MAX_ELEMENTS_VERTICES,
        MaxElementsIndices  = GL_MAX_ELEMENTS_INDICES,

        // Misc
        NumSampleCounts         = GL_NUM_SAMPLE_COUNTS,
        PrimitiveRestartFixedIndex = GL_PRIMITIVE_RESTART_FIXED_INDEX,
        ImageBindingName        = GL_IMAGE_BINDING_NAME,
        ImageBindingLevel       = GL_IMAGE_BINDING_LEVEL,
        ImageBindingLayered     = GL_IMAGE_BINDING_LAYERED,
        ImageBindingLayer       = GL_IMAGE_BINDING_LAYER,
        ImageBindingAccess      = GL_IMAGE_BINDING_ACCESS,
        ImageBindingFormat      = GL_IMAGE_BINDING_FORMAT,
        PrimitiveBoundingBox    = GL_PRIMITIVE_BOUNDING_BOX    ///< ES 3.2+
    };

    /**
     * @brief Legal buffer targets for glClearBufferfv().
     */
    enum class FloatClearBuffer : GLenum
    {
        Color = GL_COLOR,
        Depth = GL_DEPTH
    };

    /**
     * @brief Legal buffer targets for glClearBufferiv().
     */
    enum class SignedIntegerClearBuffer : GLenum
    {
        Color   = GL_COLOR,
        Stencil = GL_STENCIL
    };

    /**
     * @brief Legal buffer target for glClearBufferuiv().
     */
    enum class UnsignedIntegerClearBuffer : GLenum
    {
        Color = GL_COLOR
    };


    // -------------------------------------------------------------------------
    // Additional exact API categories used by generated Functions wrappers.
    // -------------------------------------------------------------------------
    /**
     * @brief Draw buffer target for glDrawBuffers(). Non-color cases only.
     * Convert @ref ColorAttachment values via @ref to_draw_buffer().
     */
    enum class DrawBuffer : GLenum
    {
        None = GL_NONE,
        Back = GL_BACK
    };

    constexpr DrawBuffer to_draw_buffer(ColorAttachment a) noexcept
    {
        return static_cast<DrawBuffer>(static_cast<GLenum>(a));
    }

    /**
     * @brief Read buffer source for glReadBuffer(). Non-color cases only.
     * Convert @ref ColorAttachment values via @ref to_read_buffer().
     */
    enum class ReadBuffer : GLenum
    {
        None = GL_NONE,
        Back = GL_BACK
    };

    constexpr ReadBuffer to_read_buffer(ColorAttachment a) noexcept
    {
        return static_cast<ReadBuffer>(static_cast<GLenum>(a));
    }

    /// @brief Opaque shader binary format token reported by the driver via GL_SHADER_BINARY_FORMATS.
    enum class ShaderBinaryFormat : GLenum {};
    /// @brief Opaque program binary format token reported by the driver via GL_PROGRAM_BINARY_FORMATS.
    enum class ProgramBinaryFormat : GLenum {};

    /** @brief Pointer parameter names for glGetPointerv() (ES 3.2+). */
    enum class GetPointerParameter : GLenum
    {
        DebugCallbackFunction = GL_DEBUG_CALLBACK_FUNCTION,
        DebugCallbackUserParam = GL_DEBUG_CALLBACK_USER_PARAM
    };

    /** @brief Parameter name for glGetMultisamplefv() (ES 3.1+). */
    enum class MultisampleParameter : GLenum
    {
        SamplePosition = GL_SAMPLE_POSITION
    };

    /** @brief Target type for glGetInternalformativ() (ES 3.0+). */
    enum class InternalFormatTarget : GLenum
    {
        Renderbuffer = GL_RENDERBUFFER,
        Texture2DMultisample = GL_TEXTURE_2D_MULTISAMPLE,
        Texture2DMultisampleArray = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
    };

    /** @brief Query parameter for glGetInternalformativ() (ES 3.0+). */
    enum class InternalFormatParameter : GLenum
    {
        Samples = GL_SAMPLES,
        NumSampleCounts = GL_NUM_SAMPLE_COUNTS
    };

    /** @brief Parameter names for glGetProgramPipelineiv() (ES 3.1+). */
    enum class ProgramPipelineParameter : GLenum
    {
        ActiveProgram = GL_ACTIVE_PROGRAM,
        ValidateStatus = GL_VALIDATE_STATUS,
        InfoLogLength = GL_INFO_LOG_LENGTH,
        VertexShader = GL_VERTEX_SHADER,
        FragmentShader = GL_FRAGMENT_SHADER,
        GeometryShader = GL_GEOMETRY_SHADER,
        TessControlShader = GL_TESS_CONTROL_SHADER,
        TessEvaluationShader = GL_TESS_EVALUATION_SHADER,
        ComputeShader = GL_COMPUTE_SHADER
    };

    /** @brief Reserved flags parameter for glWaitSync() — currently must be zero. */
    enum class SyncFlag : GLbitfield
    {
        None = 0
    };

    // GLbitfield and GLenum are aliases on common platforms. Explicit trait
    // specializations are therefore the authoritative list of bitfield domains.
    template<> struct GlBitfieldTraits<ClearBufferBit>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits =
            GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    };

    template<> struct GlBitfieldTraits<MapBufferAccessMask>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits =
            GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT
            | GL_MAP_INVALIDATE_BUFFER_BIT | GL_MAP_FLUSH_EXPLICIT_BIT
            | GL_MAP_UNSYNCHRONIZED_BIT;
    };

    template<> struct GlBitfieldTraits<SampleMaskValue>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits = 0xFFFFFFFFu;
    };

    template<> struct GlBitfieldTraits<ShaderStageMask>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits = GL_ALL_SHADER_BITS;
    };

    template<> struct GlBitfieldTraits<SyncFlushMask>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits = GL_SYNC_FLUSH_COMMANDS_BIT;
    };

    template<> struct GlBitfieldTraits<MemoryBarrierMask>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits = GL_ALL_BARRIER_BITS;
    };

    template<> struct GlBitfieldTraits<MemoryBarrierByRegionMask>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits = GL_ALL_BARRIER_BITS;
    };

    template<> struct GlBitfieldTraits<ContextFlagMask>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits =
            GL_CONTEXT_FLAG_DEBUG_BIT | GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT;
    };

    template<> struct GlBitfieldTraits<SyncFlag>
    {
        static constexpr bool enabled = true;
        static constexpr GLbitfield all_bits = 0;
    };

} // namespace metagl
