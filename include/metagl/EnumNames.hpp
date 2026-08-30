/**
 * @file EnumNames.hpp
 * @brief `to_string()` overloads for all meta-gl enum classes and handle types.
 *
 * Provides one `to_string()` overload per @ref Enums.hpp enum class.
 * Each function returns the enumerator name as a `std::string_view` literal,
 * or `"?"` for values not found in the enum.
 *
 * Handle type overloads (for @ref Types.hpp handle structs) return a
 * `std::string` of the form `"TypeName(value)"`, e.g. `"TextureId(42)"`.
 *
 * Usage example:
 * @code
 * metagl::ClearBufferBit mask = metagl::ClearBufferBit::Color;
 * std::cout << metagl::to_string(mask);  // prints "Color"
 *
 * metagl::TextureId tex{7};
 * std::cout << metagl::to_string(tex);   // prints "TextureId(7)"
 * @endcode
 *
 * The debug logging layer (@ref Debug.hpp) uses these functions to produce
 * human-readable output for every GL call when `METAGLDEBUG` is defined.
 *
 * Include this header via @ref metagl.hpp (included by default unless
 * `METAGL_NO_ENUM_NAMES` is defined before the first metagl include).
 */
#pragma once
#include "metagl/Enums.hpp"
#include "metagl/Types.hpp"
#include "metagl/Context.hpp"
#include <string>
#include <string_view>

namespace metagl
{
    /// @brief Returns the enumerator name of a @ref ClearBufferBit value, or `"?"` for unknown values.
    inline std::string_view to_string(ClearBufferBit v)
    {
        if (v == ClearBufferBit::Color) return "Color";
        else if (v == ClearBufferBit::Depth) return "Depth";
        else if (v == ClearBufferBit::Stencil) return "Stencil";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref PrimitiveType value, or `"?"` for unknown values.
    inline std::string_view to_string(PrimitiveType v)
    {
        if (v == PrimitiveType::Points) return "Points";
        else if (v == PrimitiveType::Lines) return "Lines";
        else if (v == PrimitiveType::LineLoop) return "LineLoop";
        else if (v == PrimitiveType::LineStrip) return "LineStrip";
        else if (v == PrimitiveType::Triangles) return "Triangles";
        else if (v == PrimitiveType::TriangleStrip) return "TriangleStrip";
        else if (v == PrimitiveType::TriangleFan) return "TriangleFan";
        else if (v == PrimitiveType::LinesAdjacency) return "LinesAdjacency";
        else if (v == PrimitiveType::LineStripAdjacency) return "LineStripAdjacency";
        else if (v == PrimitiveType::TrianglesAdjacency) return "TrianglesAdjacency";
        else if (v == PrimitiveType::TriangleStripAdjacency) return "TriangleStripAdjacency";
        else if (v == PrimitiveType::Patches) return "Patches";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref BlendFactor value, or `"?"` for unknown values.
    inline std::string_view to_string(BlendFactor v)
    {
        if (v == BlendFactor::Zero) return "Zero";
        else if (v == BlendFactor::One) return "One";
        else if (v == BlendFactor::SrcColor) return "SrcColor";
        else if (v == BlendFactor::OneMinusSrcColor) return "OneMinusSrcColor";
        else if (v == BlendFactor::SrcAlpha) return "SrcAlpha";
        else if (v == BlendFactor::OneMinusSrcAlpha) return "OneMinusSrcAlpha";
        else if (v == BlendFactor::DstAlpha) return "DstAlpha";
        else if (v == BlendFactor::OneMinusDstAlpha) return "OneMinusDstAlpha";
        else if (v == BlendFactor::DstColor) return "DstColor";
        else if (v == BlendFactor::OneMinusDstColor) return "OneMinusDstColor";
        else if (v == BlendFactor::SrcAlphaSaturate) return "SrcAlphaSaturate";
        else if (v == BlendFactor::ConstantColor) return "ConstantColor";
        else if (v == BlendFactor::OneMinusConstantColor) return "OneMinusConstantColor";
        else if (v == BlendFactor::ConstantAlpha) return "ConstantAlpha";
        else if (v == BlendFactor::OneMinusConstantAlpha) return "OneMinusConstantAlpha";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref BlendEquation value, or `"?"` for unknown values.
    inline std::string_view to_string(BlendEquation v)
    {
        if (v == BlendEquation::FuncAdd) return "FuncAdd";
        else if (v == BlendEquation::FuncSubtract) return "FuncSubtract";
        else if (v == BlendEquation::FuncReverseSubtract) return "FuncReverseSubtract";
        else if (v == BlendEquation::Min) return "Min";
        else if (v == BlendEquation::Max) return "Max";
        else if (v == BlendEquation::Multiply) return "Multiply";
        else if (v == BlendEquation::Screen) return "Screen";
        else if (v == BlendEquation::Overlay) return "Overlay";
        else if (v == BlendEquation::Darken) return "Darken";
        else if (v == BlendEquation::Lighten) return "Lighten";
        else if (v == BlendEquation::ColorDodge) return "ColorDodge";
        else if (v == BlendEquation::ColorBurn) return "ColorBurn";
        else if (v == BlendEquation::HardLight) return "HardLight";
        else if (v == BlendEquation::SoftLight) return "SoftLight";
        else if (v == BlendEquation::Difference) return "Difference";
        else if (v == BlendEquation::Exclusion) return "Exclusion";
        else if (v == BlendEquation::HslHue) return "HslHue";
        else if (v == BlendEquation::HslSaturation) return "HslSaturation";
        else if (v == BlendEquation::HslColor) return "HslColor";
        else if (v == BlendEquation::HslLuminosity) return "HslLuminosity";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref BufferTarget value, or `"?"` for unknown values.
    inline std::string_view to_string(BufferTarget v)
    {
        if (v == BufferTarget::Array) return "Array";
        else if (v == BufferTarget::ElementArray) return "ElementArray";
        else if (v == BufferTarget::CopyRead) return "CopyRead";
        else if (v == BufferTarget::CopyWrite) return "CopyWrite";
        else if (v == BufferTarget::PixelPack) return "PixelPack";
        else if (v == BufferTarget::PixelUnpack) return "PixelUnpack";
        else if (v == BufferTarget::Uniform) return "Uniform";
        else if (v == BufferTarget::TransformFeedback) return "TransformFeedback";
        else if (v == BufferTarget::DrawIndirect) return "DrawIndirect";
        else if (v == BufferTarget::DispatchIndirect) return "DispatchIndirect";
        else if (v == BufferTarget::ShaderStorage) return "ShaderStorage";
        else if (v == BufferTarget::AtomicCounter) return "AtomicCounter";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref BufferUsage value, or `"?"` for unknown values.
    inline std::string_view to_string(BufferUsage v)
    {
        if (v == BufferUsage::StreamDraw) return "StreamDraw";
        else if (v == BufferUsage::StreamRead) return "StreamRead";
        else if (v == BufferUsage::StreamCopy) return "StreamCopy";
        else if (v == BufferUsage::StaticDraw) return "StaticDraw";
        else if (v == BufferUsage::StaticRead) return "StaticRead";
        else if (v == BufferUsage::StaticCopy) return "StaticCopy";
        else if (v == BufferUsage::DynamicDraw) return "DynamicDraw";
        else if (v == BufferUsage::DynamicRead) return "DynamicRead";
        else if (v == BufferUsage::DynamicCopy) return "DynamicCopy";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref BufferParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(BufferParameter v)
    {
        if (v == BufferParameter::Size) return "Size";
        else if (v == BufferParameter::Usage) return "Usage";
        else if (v == BufferParameter::Mapped) return "Mapped";
        else if (v == BufferParameter::AccessFlags) return "AccessFlags";
        else if (v == BufferParameter::MapLength) return "MapLength";
        else if (v == BufferParameter::MapOffset) return "MapOffset";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref BufferPointerParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(BufferPointerParameter v)
    {
        if (v == BufferPointerParameter::MapPointer) return "MapPointer";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref MapBufferAccessMask value, or `"?"` for unknown values.
    inline std::string_view to_string(MapBufferAccessMask v)
    {
        if (v == MapBufferAccessMask::Read) return "Read";
        else if (v == MapBufferAccessMask::Write) return "Write";
        else if (v == MapBufferAccessMask::InvalidateRange) return "InvalidateRange";
        else if (v == MapBufferAccessMask::InvalidateBuffer) return "InvalidateBuffer";
        else if (v == MapBufferAccessMask::FlushExplicit) return "FlushExplicit";
        else if (v == MapBufferAccessMask::Unsynchronized) return "Unsynchronized";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref SampleMaskValue value, or `"?"` for unknown values.
    inline std::string_view to_string(SampleMaskValue v)
    {
        if (v == SampleMaskValue::None) return "None";
        else if (v == SampleMaskValue::All) return "All";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref Capability value, or `"?"` for unknown values.
    inline std::string_view to_string(Capability v)
    {
        if (v == Capability::Blend) return "Blend";
        else if (v == Capability::CullFace) return "CullFace";
        else if (v == Capability::DepthTest) return "DepthTest";
        else if (v == Capability::Dither) return "Dither";
        else if (v == Capability::PolygonOffsetFill) return "PolygonOffsetFill";
        else if (v == Capability::SampleAlphaToCoverage) return "SampleAlphaToCoverage";
        else if (v == Capability::SampleCoverage) return "SampleCoverage";
        else if (v == Capability::ScissorTest) return "ScissorTest";
        else if (v == Capability::StencilTest) return "StencilTest";
        else if (v == Capability::RasterizerDiscard) return "RasterizerDiscard";
        else if (v == Capability::PrimitiveRestartFixedIndex) return "PrimitiveRestartFixedIndex";
        else if (v == Capability::SampleMask) return "SampleMask";
        else if (v == Capability::DebugOutput) return "DebugOutput";
        else if (v == Capability::DebugOutputSynchronous) return "DebugOutputSynchronous";
        else if (v == Capability::SampleShading) return "SampleShading";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ErrorCode value, or `"?"` for unknown values.
    inline std::string_view to_string(ErrorCode v)
    {
        if (v == ErrorCode::NoError) return "NoError";
        else if (v == ErrorCode::InvalidEnum) return "InvalidEnum";
        else if (v == ErrorCode::InvalidValue) return "InvalidValue";
        else if (v == ErrorCode::InvalidOperation) return "InvalidOperation";
        else if (v == ErrorCode::OutOfMemory) return "OutOfMemory";
        else if (v == ErrorCode::InvalidFramebufferOperation) return "InvalidFramebufferOperation";
        else if (v == ErrorCode::StackOverflow) return "StackOverflow";
        else if (v == ErrorCode::StackUnderflow) return "StackUnderflow";
        else if (v == ErrorCode::ContextLost) return "ContextLost";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref FrontFace value, or `"?"` for unknown values.
    inline std::string_view to_string(FrontFace v)
    {
        if (v == FrontFace::CW) return "CW";
        else if (v == FrontFace::CCW) return "CCW";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref CullFace value, or `"?"` for unknown values.
    inline std::string_view to_string(CullFace v)
    {
        if (v == CullFace::Front) return "Front";
        else if (v == CullFace::Back) return "Back";
        else if (v == CullFace::FrontAndBack) return "FrontAndBack";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref HintTarget value, or `"?"` for unknown values.
    inline std::string_view to_string(HintTarget v)
    {
        if (v == HintTarget::GenerateMipmap) return "GenerateMipmap";
        else if (v == HintTarget::FragmentShaderDerivative) return "FragmentShaderDerivative";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref HintMode value, or `"?"` for unknown values.
    inline std::string_view to_string(HintMode v)
    {
        if (v == HintMode::DontCare) return "DontCare";
        else if (v == HintMode::Fastest) return "Fastest";
        else if (v == HintMode::Nicest) return "Nicest";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref DataType value, or `"?"` for unknown values.
    inline std::string_view to_string(DataType v)
    {
        if (v == DataType::Byte) return "Byte";
        else if (v == DataType::UnsignedByte) return "UnsignedByte";
        else if (v == DataType::Short) return "Short";
        else if (v == DataType::UnsignedShort) return "UnsignedShort";
        else if (v == DataType::Int) return "Int";
        else if (v == DataType::UnsignedInt) return "UnsignedInt";
        else if (v == DataType::Float) return "Float";
        else if (v == DataType::Fixed) return "Fixed";
        else if (v == DataType::HalfFloat) return "HalfFloat";
        else if (v == DataType::Int2101010Rev) return "Int2101010Rev";
        else if (v == DataType::UnsignedInt2101010Rev) return "UnsignedInt2101010Rev";
        else if (v == DataType::UnsignedInt10F11F11FRev) return "UnsignedInt10F11F11FRev";
        return "?";
    }

    /// @brief Returns the enumerator name of an @ref IndexType value.
    inline std::string_view to_string(IndexType v)
    {
        if (v == IndexType::UnsignedByte) return "UnsignedByte";
        else if (v == IndexType::UnsignedShort) return "UnsignedShort";
        else if (v == IndexType::UnsignedInt) return "UnsignedInt";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref PixelFormat value, or `"?"` for unknown values.
    inline std::string_view to_string(PixelFormat v)
    {
        if (v == PixelFormat::DepthComponent) return "DepthComponent";
        else if (v == PixelFormat::Alpha) return "Alpha";
        else if (v == PixelFormat::Rgb) return "Rgb";
        else if (v == PixelFormat::Rgba) return "Rgba";
        else if (v == PixelFormat::Luminance) return "Luminance";
        else if (v == PixelFormat::LuminanceAlpha) return "LuminanceAlpha";
        else if (v == PixelFormat::Red) return "Red";
        else if (v == PixelFormat::Rg) return "Rg";
        else if (v == PixelFormat::RedInteger) return "RedInteger";
        else if (v == PixelFormat::RgInteger) return "RgInteger";
        else if (v == PixelFormat::RgbInteger) return "RgbInteger";
        else if (v == PixelFormat::RgbaInteger) return "RgbaInteger";
        else if (v == PixelFormat::DepthStencil) return "DepthStencil";
        else if (v == PixelFormat::StencilIndex) return "StencilIndex";
        else if (v == PixelFormat::Bgra) return "Bgra";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref PixelType value, or `"?"` for unknown values.
    inline std::string_view to_string(PixelType v)
    {
        if (v == PixelType::UnsignedByte) return "UnsignedByte";
        else if (v == PixelType::UnsignedShort4444) return "UnsignedShort4444";
        else if (v == PixelType::UnsignedShort5551) return "UnsignedShort5551";
        else if (v == PixelType::UnsignedShort565) return "UnsignedShort565";
        else if (v == PixelType::Byte) return "Byte";
        else if (v == PixelType::Short) return "Short";
        else if (v == PixelType::UnsignedShort) return "UnsignedShort";
        else if (v == PixelType::Int) return "Int";
        else if (v == PixelType::UnsignedInt) return "UnsignedInt";
        else if (v == PixelType::HalfFloat) return "HalfFloat";
        else if (v == PixelType::Float) return "Float";
        else if (v == PixelType::UnsignedInt2101010Rev) return "UnsignedInt2101010Rev";
        else if (v == PixelType::UnsignedInt10F11F11FRev) return "UnsignedInt10F11F11FRev";
        else if (v == PixelType::UnsignedInt5999Rev) return "UnsignedInt5999Rev";
        else if (v == PixelType::UnsignedInt248) return "UnsignedInt248";
        else if (v == PixelType::Float32UnsignedInt248Rev) return "Float32UnsignedInt248Rev";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref InternalFormat value, or `"?"` for unknown values.
    inline std::string_view to_string(InternalFormat v)
    {
        if (v == InternalFormat::DepthComponent) return "DepthComponent";
        else if (v == InternalFormat::Alpha) return "Alpha";
        else if (v == InternalFormat::Rgb) return "Rgb";
        else if (v == InternalFormat::Rgba) return "Rgba";
        else if (v == InternalFormat::Luminance) return "Luminance";
        else if (v == InternalFormat::LuminanceAlpha) return "LuminanceAlpha";
        else if (v == InternalFormat::Rgba4) return "Rgba4";
        else if (v == InternalFormat::Rgb5A1) return "Rgb5A1";
        else if (v == InternalFormat::Rgb565) return "Rgb565";
        else if (v == InternalFormat::DepthComponent16) return "DepthComponent16";
        else if (v == InternalFormat::StencilIndex8) return "StencilIndex8";
        else if (v == InternalFormat::R8) return "R8";
        else if (v == InternalFormat::R8Snorm) return "R8Snorm";
        else if (v == InternalFormat::R16F) return "R16F";
        else if (v == InternalFormat::R32F) return "R32F";
        else if (v == InternalFormat::R8UI) return "R8UI";
        else if (v == InternalFormat::R8I) return "R8I";
        else if (v == InternalFormat::R16UI) return "R16UI";
        else if (v == InternalFormat::R16I) return "R16I";
        else if (v == InternalFormat::R32UI) return "R32UI";
        else if (v == InternalFormat::R32I) return "R32I";
        else if (v == InternalFormat::Rg8) return "Rg8";
        else if (v == InternalFormat::Rg8Snorm) return "Rg8Snorm";
        else if (v == InternalFormat::Rg16F) return "Rg16F";
        else if (v == InternalFormat::Rg32F) return "Rg32F";
        else if (v == InternalFormat::Rg8UI) return "Rg8UI";
        else if (v == InternalFormat::Rg8I) return "Rg8I";
        else if (v == InternalFormat::Rg16UI) return "Rg16UI";
        else if (v == InternalFormat::Rg16I) return "Rg16I";
        else if (v == InternalFormat::Rg32UI) return "Rg32UI";
        else if (v == InternalFormat::Rg32I) return "Rg32I";
        else if (v == InternalFormat::Rgb8) return "Rgb8";
        else if (v == InternalFormat::Srgb8) return "Srgb8";
        else if (v == InternalFormat::Rgb8Snorm) return "Rgb8Snorm";
        else if (v == InternalFormat::R11FG11FB10F) return "R11FG11FB10F";
        else if (v == InternalFormat::Rgb9E5) return "Rgb9E5";
        else if (v == InternalFormat::Rgb16F) return "Rgb16F";
        else if (v == InternalFormat::Rgb32F) return "Rgb32F";
        else if (v == InternalFormat::Rgb8UI) return "Rgb8UI";
        else if (v == InternalFormat::Rgb8I) return "Rgb8I";
        else if (v == InternalFormat::Rgb16UI) return "Rgb16UI";
        else if (v == InternalFormat::Rgb16I) return "Rgb16I";
        else if (v == InternalFormat::Rgb32UI) return "Rgb32UI";
        else if (v == InternalFormat::Rgb32I) return "Rgb32I";
        else if (v == InternalFormat::Rgba8) return "Rgba8";
        else if (v == InternalFormat::Srgb8Alpha8) return "Srgb8Alpha8";
        else if (v == InternalFormat::Rgba8Snorm) return "Rgba8Snorm";
        else if (v == InternalFormat::Rgb10A2) return "Rgb10A2";
        else if (v == InternalFormat::Rgb10A2UI) return "Rgb10A2UI";
        else if (v == InternalFormat::Rgba16F) return "Rgba16F";
        else if (v == InternalFormat::Rgba32F) return "Rgba32F";
        else if (v == InternalFormat::Rgba8UI) return "Rgba8UI";
        else if (v == InternalFormat::Rgba8I) return "Rgba8I";
        else if (v == InternalFormat::Rgba16UI) return "Rgba16UI";
        else if (v == InternalFormat::Rgba16I) return "Rgba16I";
        else if (v == InternalFormat::Rgba32UI) return "Rgba32UI";
        else if (v == InternalFormat::Rgba32I) return "Rgba32I";
        else if (v == InternalFormat::DepthComponent24) return "DepthComponent24";
        else if (v == InternalFormat::DepthComponent32F) return "DepthComponent32F";
        else if (v == InternalFormat::Depth24Stencil8) return "Depth24Stencil8";
        else if (v == InternalFormat::Depth32FStencil8) return "Depth32FStencil8";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref CompressedInternalFormat value, or `"?"` for unknown values.
    inline std::string_view to_string(CompressedInternalFormat v)
    {
        if (v == CompressedInternalFormat::R11Eac) return "R11Eac";
        else if (v == CompressedInternalFormat::SignedR11Eac) return "SignedR11Eac";
        else if (v == CompressedInternalFormat::Rg11Eac) return "Rg11Eac";
        else if (v == CompressedInternalFormat::SignedRg11Eac) return "SignedRg11Eac";
        else if (v == CompressedInternalFormat::Rgb8Etc2) return "Rgb8Etc2";
        else if (v == CompressedInternalFormat::Srgb8Etc2) return "Srgb8Etc2";
        else if (v == CompressedInternalFormat::Rgb8PunchthroughAlpha1Etc2) return "Rgb8PunchthroughAlpha1Etc2";
        else if (v == CompressedInternalFormat::Srgb8PunchthroughAlpha1Etc2) return "Srgb8PunchthroughAlpha1Etc2";
        else if (v == CompressedInternalFormat::Rgba8Etc2Eac) return "Rgba8Etc2Eac";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Etc2Eac) return "Srgb8Alpha8Etc2Eac";
        else if (v == CompressedInternalFormat::RgbaAstc4x4) return "RgbaAstc4x4";
        else if (v == CompressedInternalFormat::RgbaAstc5x4) return "RgbaAstc5x4";
        else if (v == CompressedInternalFormat::RgbaAstc5x5) return "RgbaAstc5x5";
        else if (v == CompressedInternalFormat::RgbaAstc6x5) return "RgbaAstc6x5";
        else if (v == CompressedInternalFormat::RgbaAstc6x6) return "RgbaAstc6x6";
        else if (v == CompressedInternalFormat::RgbaAstc8x5) return "RgbaAstc8x5";
        else if (v == CompressedInternalFormat::RgbaAstc8x6) return "RgbaAstc8x6";
        else if (v == CompressedInternalFormat::RgbaAstc8x8) return "RgbaAstc8x8";
        else if (v == CompressedInternalFormat::RgbaAstc10x5) return "RgbaAstc10x5";
        else if (v == CompressedInternalFormat::RgbaAstc10x6) return "RgbaAstc10x6";
        else if (v == CompressedInternalFormat::RgbaAstc10x8) return "RgbaAstc10x8";
        else if (v == CompressedInternalFormat::RgbaAstc10x10) return "RgbaAstc10x10";
        else if (v == CompressedInternalFormat::RgbaAstc12x10) return "RgbaAstc12x10";
        else if (v == CompressedInternalFormat::RgbaAstc12x12) return "RgbaAstc12x12";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc4x4) return "Srgb8Alpha8Astc4x4";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc5x4) return "Srgb8Alpha8Astc5x4";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc5x5) return "Srgb8Alpha8Astc5x5";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc6x5) return "Srgb8Alpha8Astc6x5";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc6x6) return "Srgb8Alpha8Astc6x6";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc8x5) return "Srgb8Alpha8Astc8x5";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc8x6) return "Srgb8Alpha8Astc8x6";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc8x8) return "Srgb8Alpha8Astc8x8";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc10x5) return "Srgb8Alpha8Astc10x5";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc10x6) return "Srgb8Alpha8Astc10x6";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc10x8) return "Srgb8Alpha8Astc10x8";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc10x10) return "Srgb8Alpha8Astc10x10";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc12x10) return "Srgb8Alpha8Astc12x10";
        else if (v == CompressedInternalFormat::Srgb8Alpha8Astc12x12) return "Srgb8Alpha8Astc12x12";
        else if (v == CompressedInternalFormat::RgbS3tcDxt1) return "RgbS3tcDxt1";
        else if (v == CompressedInternalFormat::RgbaS3tcDxt1) return "RgbaS3tcDxt1";
        else if (v == CompressedInternalFormat::RgbaS3tcDxt3) return "RgbaS3tcDxt3";
        else if (v == CompressedInternalFormat::RgbaS3tcDxt5) return "RgbaS3tcDxt5";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref StringName value, or `"?"` for unknown values.
    inline std::string_view to_string(StringName v)
    {
        if (v == StringName::Vendor) return "Vendor";
        else if (v == StringName::Renderer) return "Renderer";
        else if (v == StringName::Version) return "Version";
        else if (v == StringName::Extensions) return "Extensions";
        else if (v == StringName::ShadingLanguageVersion) return "ShadingLanguageVersion";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref IntegerName value, or `"?"` for unknown values.
    inline std::string_view to_string(IntegerName v)
    {
        if (v == IntegerName::MajorVersion) return "MajorVersion";
        else if (v == IntegerName::MinorVersion) return "MinorVersion";
        else if (v == IntegerName::NumExtensions) return "NumExtensions";
        else if (v == IntegerName::MaxTextureSize) return "MaxTextureSize";
        else if (v == IntegerName::Viewport) return "Viewport";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ShaderType value, or `"?"` for unknown values.
    inline std::string_view to_string(ShaderType v)
    {
        if (v == ShaderType::Vertex) return "Vertex";
        else if (v == ShaderType::Fragment) return "Fragment";
        else if (v == ShaderType::Geometry) return "Geometry";
        else if (v == ShaderType::TessControl) return "TessControl";
        else if (v == ShaderType::TessEvaluation) return "TessEvaluation";
        else if (v == ShaderType::Compute) return "Compute";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ShaderStageMask value, or `"?"` for unknown values.
    inline std::string_view to_string(ShaderStageMask v)
    {
        if (v == ShaderStageMask::Vertex) return "Vertex";
        else if (v == ShaderStageMask::Fragment) return "Fragment";
        else if (v == ShaderStageMask::Geometry) return "Geometry";
        else if (v == ShaderStageMask::TessControl) return "TessControl";
        else if (v == ShaderStageMask::TessEvaluation) return "TessEvaluation";
        else if (v == ShaderStageMask::Compute) return "Compute";
        else if (v == ShaderStageMask::AllShaderBits) return "AllShaderBits";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ShaderParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(ShaderParameter v)
    {
        if (v == ShaderParameter::ShaderType) return "ShaderType";
        else if (v == ShaderParameter::DeleteStatus) return "DeleteStatus";
        else if (v == ShaderParameter::CompileStatus) return "CompileStatus";
        else if (v == ShaderParameter::InfoLogLength) return "InfoLogLength";
        else if (v == ShaderParameter::SourceLength) return "SourceLength";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref PrecisionType value, or `"?"` for unknown values.
    inline std::string_view to_string(PrecisionType v)
    {
        if (v == PrecisionType::LowFloat) return "LowFloat";
        else if (v == PrecisionType::MediumFloat) return "MediumFloat";
        else if (v == PrecisionType::HighFloat) return "HighFloat";
        else if (v == PrecisionType::LowInt) return "LowInt";
        else if (v == PrecisionType::MediumInt) return "MediumInt";
        else if (v == PrecisionType::HighInt) return "HighInt";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ProgramParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(ProgramParameter v)
    {
        if (v == ProgramParameter::DeleteStatus) return "DeleteStatus";
        else if (v == ProgramParameter::LinkStatus) return "LinkStatus";
        else if (v == ProgramParameter::ValidateStatus) return "ValidateStatus";
        else if (v == ProgramParameter::InfoLogLength) return "InfoLogLength";
        else if (v == ProgramParameter::AttachedShaders) return "AttachedShaders";
        else if (v == ProgramParameter::ActiveUniforms) return "ActiveUniforms";
        else if (v == ProgramParameter::ActiveUniformMaxLength) return "ActiveUniformMaxLength";
        else if (v == ProgramParameter::ActiveAttributes) return "ActiveAttributes";
        else if (v == ProgramParameter::ActiveAttributeMaxLength) return "ActiveAttributeMaxLength";
        else if (v == ProgramParameter::ActiveUniformBlocks) return "ActiveUniformBlocks";
        else if (v == ProgramParameter::ActiveUniformBlockMaxLength) return "ActiveUniformBlockMaxLength";
        else if (v == ProgramParameter::TransformFeedbackVaryings) return "TransformFeedbackVaryings";
        else if (v == ProgramParameter::TransformFeedbackVaryingMaxLength) return "TransformFeedbackVaryingMaxLength";
        else if (v == ProgramParameter::TransformFeedbackBufferMode) return "TransformFeedbackBufferMode";
        else if (v == ProgramParameter::BinaryLength) return "BinaryLength";
        else if (v == ProgramParameter::BinaryRetrievableHint) return "BinaryRetrievableHint";
        else if (v == ProgramParameter::Separable) return "Separable";
        else if (v == ProgramParameter::ActiveAtomicCounterBuffers) return "ActiveAtomicCounterBuffers";
        else if (v == ProgramParameter::ComputeWorkGroupSize) return "ComputeWorkGroupSize";
        else if (v == ProgramParameter::GeometryVerticesOut) return "GeometryVerticesOut";
        else if (v == ProgramParameter::GeometryInputType) return "GeometryInputType";
        else if (v == ProgramParameter::GeometryOutputType) return "GeometryOutputType";
        else if (v == ProgramParameter::GeometryShaderInvocations) return "GeometryShaderInvocations";
        else if (v == ProgramParameter::TessControlOutputVertices) return "TessControlOutputVertices";
        else if (v == ProgramParameter::TessGenMode) return "TessGenMode";
        else if (v == ProgramParameter::TessGenSpacing) return "TessGenSpacing";
        else if (v == ProgramParameter::TessGenVertexOrder) return "TessGenVertexOrder";
        else if (v == ProgramParameter::TessGenPointMode) return "TessGenPointMode";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ProgramInterface value, or `"?"` for unknown values.
    inline std::string_view to_string(ProgramInterface v)
    {
        if (v == ProgramInterface::Uniform) return "Uniform";
        else if (v == ProgramInterface::UniformBlock) return "UniformBlock";
        else if (v == ProgramInterface::ProgramInput) return "ProgramInput";
        else if (v == ProgramInterface::ProgramOutput) return "ProgramOutput";
        else if (v == ProgramInterface::BufferVariable) return "BufferVariable";
        else if (v == ProgramInterface::ShaderStorageBlock) return "ShaderStorageBlock";
        else if (v == ProgramInterface::AtomicCounterBuffer) return "AtomicCounterBuffer";
        else if (v == ProgramInterface::TransformFeedbackVarying) return "TransformFeedbackVarying";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ProgramInterfaceParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(ProgramInterfaceParameter v)
    {
        if (v == ProgramInterfaceParameter::ActiveResources) return "ActiveResources";
        else if (v == ProgramInterfaceParameter::MaxNameLength) return "MaxNameLength";
        else if (v == ProgramInterfaceParameter::MaxNumActiveVariables) return "MaxNumActiveVariables";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ProgramResourceProperty value, or `"?"` for unknown values.
    inline std::string_view to_string(ProgramResourceProperty v)
    {
        if (v == ProgramResourceProperty::NameLength) return "NameLength";
        else if (v == ProgramResourceProperty::Type) return "Type";
        else if (v == ProgramResourceProperty::ArraySize) return "ArraySize";
        else if (v == ProgramResourceProperty::Offset) return "Offset";
        else if (v == ProgramResourceProperty::BlockIndex) return "BlockIndex";
        else if (v == ProgramResourceProperty::ArrayStride) return "ArrayStride";
        else if (v == ProgramResourceProperty::MatrixStride) return "MatrixStride";
        else if (v == ProgramResourceProperty::IsRowMajor) return "IsRowMajor";
        else if (v == ProgramResourceProperty::AtomicCounterBufferIndex) return "AtomicCounterBufferIndex";
        else if (v == ProgramResourceProperty::BufferBinding) return "BufferBinding";
        else if (v == ProgramResourceProperty::BufferDataSize) return "BufferDataSize";
        else if (v == ProgramResourceProperty::NumActiveVariables) return "NumActiveVariables";
        else if (v == ProgramResourceProperty::ActiveVariables) return "ActiveVariables";
        else if (v == ProgramResourceProperty::ReferencedByVertexShader) return "ReferencedByVertexShader";
        else if (v == ProgramResourceProperty::ReferencedByFragmentShader) return "ReferencedByFragmentShader";
        else if (v == ProgramResourceProperty::ReferencedByComputeShader) return "ReferencedByComputeShader";
        else if (v == ProgramResourceProperty::ReferencedByGeometryShader) return "ReferencedByGeometryShader";
        else if (v == ProgramResourceProperty::ReferencedByTessControlShader) return "ReferencedByTessControlShader";
        else if (v == ProgramResourceProperty::ReferencedByTessEvaluationShader) return "ReferencedByTessEvaluationShader";
        else if (v == ProgramResourceProperty::TopLevelArraySize) return "TopLevelArraySize";
        else if (v == ProgramResourceProperty::TopLevelArrayStride) return "TopLevelArrayStride";
        else if (v == ProgramResourceProperty::Location) return "Location";
        else if (v == ProgramResourceProperty::IsPerPatch) return "IsPerPatch";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref UniformType value, or `"?"` for unknown values.
    inline std::string_view to_string(UniformType v)
    {
        if (v == UniformType::Float) return "Float";
        else if (v == UniformType::FloatVec2) return "FloatVec2";
        else if (v == UniformType::FloatVec3) return "FloatVec3";
        else if (v == UniformType::FloatVec4) return "FloatVec4";
        else if (v == UniformType::Int) return "Int";
        else if (v == UniformType::IntVec2) return "IntVec2";
        else if (v == UniformType::IntVec3) return "IntVec3";
        else if (v == UniformType::IntVec4) return "IntVec4";
        else if (v == UniformType::UnsignedInt) return "UnsignedInt";
        else if (v == UniformType::UnsignedIntVec2) return "UnsignedIntVec2";
        else if (v == UniformType::UnsignedIntVec3) return "UnsignedIntVec3";
        else if (v == UniformType::UnsignedIntVec4) return "UnsignedIntVec4";
        else if (v == UniformType::Bool) return "Bool";
        else if (v == UniformType::BoolVec2) return "BoolVec2";
        else if (v == UniformType::BoolVec3) return "BoolVec3";
        else if (v == UniformType::BoolVec4) return "BoolVec4";
        else if (v == UniformType::FloatMat2) return "FloatMat2";
        else if (v == UniformType::FloatMat3) return "FloatMat3";
        else if (v == UniformType::FloatMat4) return "FloatMat4";
        else if (v == UniformType::FloatMat2x3) return "FloatMat2x3";
        else if (v == UniformType::FloatMat2x4) return "FloatMat2x4";
        else if (v == UniformType::FloatMat3x2) return "FloatMat3x2";
        else if (v == UniformType::FloatMat3x4) return "FloatMat3x4";
        else if (v == UniformType::FloatMat4x2) return "FloatMat4x2";
        else if (v == UniformType::FloatMat4x3) return "FloatMat4x3";
        else if (v == UniformType::Sampler2D) return "Sampler2D";
        else if (v == UniformType::Sampler3D) return "Sampler3D";
        else if (v == UniformType::SamplerCube) return "SamplerCube";
        else if (v == UniformType::Sampler2DShadow) return "Sampler2DShadow";
        else if (v == UniformType::Sampler2DArray) return "Sampler2DArray";
        else if (v == UniformType::Sampler2DArrayShadow) return "Sampler2DArrayShadow";
        else if (v == UniformType::SamplerCubeShadow) return "SamplerCubeShadow";
        else if (v == UniformType::IntSampler2D) return "IntSampler2D";
        else if (v == UniformType::IntSampler3D) return "IntSampler3D";
        else if (v == UniformType::IntSamplerCube) return "IntSamplerCube";
        else if (v == UniformType::IntSampler2DArray) return "IntSampler2DArray";
        else if (v == UniformType::UnsignedIntSampler2D) return "UnsignedIntSampler2D";
        else if (v == UniformType::UnsignedIntSampler3D) return "UnsignedIntSampler3D";
        else if (v == UniformType::UnsignedIntSamplerCube) return "UnsignedIntSamplerCube";
        else if (v == UniformType::UnsignedIntSampler2DArray) return "UnsignedIntSampler2DArray";
        else if (v == UniformType::Sampler2DMultisample) return "Sampler2DMultisample";
        else if (v == UniformType::IntSampler2DMultisample) return "IntSampler2DMultisample";
        else if (v == UniformType::UnsignedIntSampler2DMultisample) return "UnsignedIntSampler2DMultisample";
        else if (v == UniformType::UnsignedIntAtomicCounter) return "UnsignedIntAtomicCounter";
        else if (v == UniformType::Image2D) return "Image2D";
        else if (v == UniformType::Image3D) return "Image3D";
        else if (v == UniformType::ImageCube) return "ImageCube";
        else if (v == UniformType::Image2DArray) return "Image2DArray";
        else if (v == UniformType::IntImage2D) return "IntImage2D";
        else if (v == UniformType::IntImage3D) return "IntImage3D";
        else if (v == UniformType::IntImageCube) return "IntImageCube";
        else if (v == UniformType::IntImage2DArray) return "IntImage2DArray";
        else if (v == UniformType::UnsignedIntImage2D) return "UnsignedIntImage2D";
        else if (v == UniformType::UnsignedIntImage3D) return "UnsignedIntImage3D";
        else if (v == UniformType::UnsignedIntImageCube) return "UnsignedIntImageCube";
        else if (v == UniformType::UnsignedIntImage2DArray) return "UnsignedIntImage2DArray";
        else if (v == UniformType::SamplerBuffer) return "SamplerBuffer";
        else if (v == UniformType::IntSamplerBuffer) return "IntSamplerBuffer";
        else if (v == UniformType::UnsignedIntSamplerBuffer) return "UnsignedIntSamplerBuffer";
        else if (v == UniformType::ImageBuffer) return "ImageBuffer";
        else if (v == UniformType::IntImageBuffer) return "IntImageBuffer";
        else if (v == UniformType::UnsignedIntImageBuffer) return "UnsignedIntImageBuffer";
        else if (v == UniformType::SamplerCubeMapArray) return "SamplerCubeMapArray";
        else if (v == UniformType::SamplerCubeMapArrayShadow) return "SamplerCubeMapArrayShadow";
        else if (v == UniformType::IntSamplerCubeMapArray) return "IntSamplerCubeMapArray";
        else if (v == UniformType::UnsignedIntSamplerCubeMapArray) return "UnsignedIntSamplerCubeMapArray";
        else if (v == UniformType::ImageCubeMapArray) return "ImageCubeMapArray";
        else if (v == UniformType::IntImageCubeMapArray) return "IntImageCubeMapArray";
        else if (v == UniformType::UnsignedIntImageCubeMapArray) return "UnsignedIntImageCubeMapArray";
        else if (v == UniformType::Sampler2DMultisampleArray) return "Sampler2DMultisampleArray";
        else if (v == UniformType::IntSampler2DMultisampleArray) return "IntSampler2DMultisampleArray";
        else if (v == UniformType::UnsignedIntSampler2DMultisampleArray) return "UnsignedIntSampler2DMultisampleArray";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref UniformBlockParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(UniformBlockParameter v)
    {
        if (v == UniformBlockParameter::Binding) return "Binding";
        else if (v == UniformBlockParameter::DataSize) return "DataSize";
        else if (v == UniformBlockParameter::NameLength) return "NameLength";
        else if (v == UniformBlockParameter::ActiveUniforms) return "ActiveUniforms";
        else if (v == UniformBlockParameter::ActiveUniformIndices) return "ActiveUniformIndices";
        else if (v == UniformBlockParameter::ReferencedByVertexShader) return "ReferencedByVertexShader";
        else if (v == UniformBlockParameter::ReferencedByFragmentShader) return "ReferencedByFragmentShader";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref UniformParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(UniformParameter v)
    {
        if (v == UniformParameter::Type) return "Type";
        else if (v == UniformParameter::Size) return "Size";
        else if (v == UniformParameter::NameLength) return "NameLength";
        else if (v == UniformParameter::BlockIndex) return "BlockIndex";
        else if (v == UniformParameter::Offset) return "Offset";
        else if (v == UniformParameter::ArrayStride) return "ArrayStride";
        else if (v == UniformParameter::MatrixStride) return "MatrixStride";
        else if (v == UniformParameter::IsRowMajor) return "IsRowMajor";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureTarget value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureTarget v)
    {
        if (v == TextureTarget::Texture2D) return "Texture2D";
        else if (v == TextureTarget::TextureCubeMap) return "TextureCubeMap";
        else if (v == TextureTarget::TextureCubeMapPositiveX) return "TextureCubeMapPositiveX";
        else if (v == TextureTarget::TextureCubeMapNegativeX) return "TextureCubeMapNegativeX";
        else if (v == TextureTarget::TextureCubeMapPositiveY) return "TextureCubeMapPositiveY";
        else if (v == TextureTarget::TextureCubeMapNegativeY) return "TextureCubeMapNegativeY";
        else if (v == TextureTarget::TextureCubeMapPositiveZ) return "TextureCubeMapPositiveZ";
        else if (v == TextureTarget::TextureCubeMapNegativeZ) return "TextureCubeMapNegativeZ";
        else if (v == TextureTarget::Texture3D) return "Texture3D";
        else if (v == TextureTarget::Texture2DArray) return "Texture2DArray";
        else if (v == TextureTarget::Texture2DMultisample) return "Texture2DMultisample";
        else if (v == TextureTarget::TextureBuffer) return "TextureBuffer";
        else if (v == TextureTarget::TextureCubeMapArray) return "TextureCubeMapArray";
        else if (v == TextureTarget::Texture2DMultisampleArray) return "Texture2DMultisampleArray";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureBindingTarget value.
    inline std::string_view to_string(TextureBindingTarget v)
    {
        if (v == TextureBindingTarget::Texture2D) return "Texture2D";
        else if (v == TextureBindingTarget::TextureCubeMap) return "TextureCubeMap";
        else if (v == TextureBindingTarget::Texture3D) return "Texture3D";
        else if (v == TextureBindingTarget::Texture2DArray) return "Texture2DArray";
        else if (v == TextureBindingTarget::Texture2DMultisample) return "Texture2DMultisample";
        else if (v == TextureBindingTarget::TextureBuffer) return "TextureBuffer";
        else if (v == TextureBindingTarget::TextureCubeMapArray) return "TextureCubeMapArray";
        else if (v == TextureBindingTarget::Texture2DMultisampleArray) return "Texture2DMultisampleArray";
        return "?";
    }

    /// @brief Returns the enumerator name of an @ref ImageCopyTextureTarget value.
    inline std::string_view to_string(ImageCopyTextureTarget v)
    {
        if (v == ImageCopyTextureTarget::Texture2D) return "Texture2D";
        else if (v == ImageCopyTextureTarget::TextureCubeMap) return "TextureCubeMap";
        else if (v == ImageCopyTextureTarget::Texture3D) return "Texture3D";
        else if (v == ImageCopyTextureTarget::Texture2DArray) return "Texture2DArray";
        else if (v == ImageCopyTextureTarget::Texture2DMultisample) return "Texture2DMultisample";
        else if (v == ImageCopyTextureTarget::TextureCubeMapArray) return "TextureCubeMapArray";
        else if (v == ImageCopyTextureTarget::Texture2DMultisampleArray) return "Texture2DMultisampleArray";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureParameter v)
    {
        if (v == TextureParameter::MinFilter) return "MinFilter";
        else if (v == TextureParameter::MagFilter) return "MagFilter";
        else if (v == TextureParameter::WrapS) return "WrapS";
        else if (v == TextureParameter::WrapT) return "WrapT";
        else if (v == TextureParameter::WrapR) return "WrapR";
        else if (v == TextureParameter::MinLod) return "MinLod";
        else if (v == TextureParameter::MaxLod) return "MaxLod";
        else if (v == TextureParameter::BaseLevel) return "BaseLevel";
        else if (v == TextureParameter::MaxLevel) return "MaxLevel";
        else if (v == TextureParameter::CompareMode) return "CompareMode";
        else if (v == TextureParameter::CompareFunc) return "CompareFunc";
        else if (v == TextureParameter::SwizzleR) return "SwizzleR";
        else if (v == TextureParameter::SwizzleG) return "SwizzleG";
        else if (v == TextureParameter::SwizzleB) return "SwizzleB";
        else if (v == TextureParameter::SwizzleA) return "SwizzleA";
        else if (v == TextureParameter::ImmutableFormat) return "ImmutableFormat";
        else if (v == TextureParameter::ImmutableLevels) return "ImmutableLevels";
        else if (v == TextureParameter::Samples) return "Samples";
        else if (v == TextureParameter::FixedSampleLocations) return "FixedSampleLocations";
        else if (v == TextureParameter::DepthStencilTextureMode) return "DepthStencilTextureMode";
        else if (v == TextureParameter::ImageFormatCompatibilityType) return "ImageFormatCompatibilityType";
        else if (v == TextureParameter::BorderColor) return "BorderColor";
        else if (v == TextureParameter::BufferDataStoreBinding) return "BufferDataStoreBinding";
        else if (v == TextureParameter::BufferOffset) return "BufferOffset";
        else if (v == TextureParameter::BufferSize) return "BufferSize";
        return "?";
    }

    inline std::string_view to_string(TextureWrapParameter v)
    {
        if (v == TextureWrapParameter::WrapS) return "WrapS";
        else if (v == TextureWrapParameter::WrapT) return "WrapT";
        else if (v == TextureWrapParameter::WrapR) return "WrapR";
        return "?";
    }

    inline std::string_view to_string(TextureSwizzleParameter v)
    {
        if (v == TextureSwizzleParameter::SwizzleR) return "SwizzleR";
        else if (v == TextureSwizzleParameter::SwizzleG) return "SwizzleG";
        else if (v == TextureSwizzleParameter::SwizzleB) return "SwizzleB";
        else if (v == TextureSwizzleParameter::SwizzleA) return "SwizzleA";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref SamplerParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(SamplerParameter v)
    {
        if (v == SamplerParameter::MinFilter) return "MinFilter";
        else if (v == SamplerParameter::MagFilter) return "MagFilter";
        else if (v == SamplerParameter::WrapS) return "WrapS";
        else if (v == SamplerParameter::WrapT) return "WrapT";
        else if (v == SamplerParameter::WrapR) return "WrapR";
        else if (v == SamplerParameter::MinLod) return "MinLod";
        else if (v == SamplerParameter::MaxLod) return "MaxLod";
        else if (v == SamplerParameter::CompareMode) return "CompareMode";
        else if (v == SamplerParameter::CompareFunc) return "CompareFunc";
        else if (v == SamplerParameter::BorderColor) return "BorderColor";
        else if (v == SamplerParameter::MaxAnisotropy) return "MaxAnisotropy";
        return "?";
    }

    inline std::string_view to_string(SamplerWrapParameter v)
    {
        if (v == SamplerWrapParameter::WrapS) return "WrapS";
        else if (v == SamplerWrapParameter::WrapT) return "WrapT";
        else if (v == SamplerWrapParameter::WrapR) return "WrapR";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureMinFilter value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureMinFilter v)
    {
        if (v == TextureMinFilter::Nearest) return "Nearest";
        else if (v == TextureMinFilter::Linear) return "Linear";
        else if (v == TextureMinFilter::NearestMipmapNearest) return "NearestMipmapNearest";
        else if (v == TextureMinFilter::LinearMipmapNearest) return "LinearMipmapNearest";
        else if (v == TextureMinFilter::NearestMipmapLinear) return "NearestMipmapLinear";
        else if (v == TextureMinFilter::LinearMipmapLinear) return "LinearMipmapLinear";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureMagFilter value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureMagFilter v)
    {
        if (v == TextureMagFilter::Nearest) return "Nearest";
        else if (v == TextureMagFilter::Linear) return "Linear";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref BlitFilter value, or `"?"` for unknown values.
    inline std::string_view to_string(BlitFilter v)
    {
        if (v == BlitFilter::Nearest) return "Nearest";
        else if (v == BlitFilter::Linear) return "Linear";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureWrapMode value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureWrapMode v)
    {
        if (v == TextureWrapMode::Repeat) return "Repeat";
        else if (v == TextureWrapMode::ClampToEdge) return "ClampToEdge";
        else if (v == TextureWrapMode::MirroredRepeat) return "MirroredRepeat";
        else if (v == TextureWrapMode::ClampToBorder) return "ClampToBorder";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureCompareMode value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureCompareMode v)
    {
        if (v == TextureCompareMode::None) return "None";
        else if (v == TextureCompareMode::CompareRefToTexture) return "CompareRefToTexture";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureSwizzle value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureSwizzle v)
    {
        if (v == TextureSwizzle::Red) return "Red";
        else if (v == TextureSwizzle::Green) return "Green";
        else if (v == TextureSwizzle::Blue) return "Blue";
        else if (v == TextureSwizzle::Alpha) return "Alpha";
        else if (v == TextureSwizzle::Zero) return "Zero";
        else if (v == TextureSwizzle::One) return "One";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureLevelParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureLevelParameter v)
    {
        if (v == TextureLevelParameter::Width) return "Width";
        else if (v == TextureLevelParameter::Height) return "Height";
        else if (v == TextureLevelParameter::Depth) return "Depth";
        else if (v == TextureLevelParameter::InternalFormat) return "InternalFormat";
        else if (v == TextureLevelParameter::RedSize) return "RedSize";
        else if (v == TextureLevelParameter::GreenSize) return "GreenSize";
        else if (v == TextureLevelParameter::BlueSize) return "BlueSize";
        else if (v == TextureLevelParameter::AlphaSize) return "AlphaSize";
        else if (v == TextureLevelParameter::DepthSize) return "DepthSize";
        else if (v == TextureLevelParameter::StencilSize) return "StencilSize";
        else if (v == TextureLevelParameter::SharedSize) return "SharedSize";
        else if (v == TextureLevelParameter::RedType) return "RedType";
        else if (v == TextureLevelParameter::GreenType) return "GreenType";
        else if (v == TextureLevelParameter::BlueType) return "BlueType";
        else if (v == TextureLevelParameter::AlphaType) return "AlphaType";
        else if (v == TextureLevelParameter::DepthType) return "DepthType";
        else if (v == TextureLevelParameter::Compressed) return "Compressed";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TextureUnit value, or `"?"` for unknown values.
    inline std::string_view to_string(TextureUnit v)
    {
        if (v == TextureUnit::Texture0) return "Texture0";
        else if (v == TextureUnit::Texture1) return "Texture1";
        else if (v == TextureUnit::Texture2) return "Texture2";
        else if (v == TextureUnit::Texture3) return "Texture3";
        else if (v == TextureUnit::Texture4) return "Texture4";
        else if (v == TextureUnit::Texture5) return "Texture5";
        else if (v == TextureUnit::Texture6) return "Texture6";
        else if (v == TextureUnit::Texture7) return "Texture7";
        else if (v == TextureUnit::Texture8) return "Texture8";
        else if (v == TextureUnit::Texture9) return "Texture9";
        else if (v == TextureUnit::Texture10) return "Texture10";
        else if (v == TextureUnit::Texture11) return "Texture11";
        else if (v == TextureUnit::Texture12) return "Texture12";
        else if (v == TextureUnit::Texture13) return "Texture13";
        else if (v == TextureUnit::Texture14) return "Texture14";
        else if (v == TextureUnit::Texture15) return "Texture15";
        else if (v == TextureUnit::Texture16) return "Texture16";
        else if (v == TextureUnit::Texture17) return "Texture17";
        else if (v == TextureUnit::Texture18) return "Texture18";
        else if (v == TextureUnit::Texture19) return "Texture19";
        else if (v == TextureUnit::Texture20) return "Texture20";
        else if (v == TextureUnit::Texture21) return "Texture21";
        else if (v == TextureUnit::Texture22) return "Texture22";
        else if (v == TextureUnit::Texture23) return "Texture23";
        else if (v == TextureUnit::Texture24) return "Texture24";
        else if (v == TextureUnit::Texture25) return "Texture25";
        else if (v == TextureUnit::Texture26) return "Texture26";
        else if (v == TextureUnit::Texture27) return "Texture27";
        else if (v == TextureUnit::Texture28) return "Texture28";
        else if (v == TextureUnit::Texture29) return "Texture29";
        else if (v == TextureUnit::Texture30) return "Texture30";
        else if (v == TextureUnit::Texture31) return "Texture31";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref PixelStoreParam value, or `"?"` for unknown values.
    inline std::string_view to_string(PixelStoreParam v)
    {
        if (v == PixelStoreParam::PackAlignment) return "PackAlignment";
        else if (v == PixelStoreParam::PackRowLength) return "PackRowLength";
        else if (v == PixelStoreParam::PackSkipRows) return "PackSkipRows";
        else if (v == PixelStoreParam::PackSkipPixels) return "PackSkipPixels";
        else if (v == PixelStoreParam::UnpackAlignment) return "UnpackAlignment";
        else if (v == PixelStoreParam::UnpackRowLength) return "UnpackRowLength";
        else if (v == PixelStoreParam::UnpackSkipRows) return "UnpackSkipRows";
        else if (v == PixelStoreParam::UnpackSkipPixels) return "UnpackSkipPixels";
        else if (v == PixelStoreParam::UnpackSkipImages) return "UnpackSkipImages";
        else if (v == PixelStoreParam::UnpackImageHeight) return "UnpackImageHeight";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref CompareFunc value, or `"?"` for unknown values.
    inline std::string_view to_string(CompareFunc v)
    {
        if (v == CompareFunc::Never) return "Never";
        else if (v == CompareFunc::Less) return "Less";
        else if (v == CompareFunc::Equal) return "Equal";
        else if (v == CompareFunc::Lequal) return "Lequal";
        else if (v == CompareFunc::Greater) return "Greater";
        else if (v == CompareFunc::Notequal) return "Notequal";
        else if (v == CompareFunc::Gequal) return "Gequal";
        else if (v == CompareFunc::Always) return "Always";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref StencilOp value, or `"?"` for unknown values.
    inline std::string_view to_string(StencilOp v)
    {
        if (v == StencilOp::Keep) return "Keep";
        else if (v == StencilOp::Zero) return "Zero";
        else if (v == StencilOp::Replace) return "Replace";
        else if (v == StencilOp::Incr) return "Incr";
        else if (v == StencilOp::Decr) return "Decr";
        else if (v == StencilOp::Invert) return "Invert";
        else if (v == StencilOp::IncrWrap) return "IncrWrap";
        else if (v == StencilOp::DecrWrap) return "DecrWrap";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref FramebufferTarget value, or `"?"` for unknown values.
    inline std::string_view to_string(FramebufferTarget v)
    {
        if (v == FramebufferTarget::Framebuffer) return "Framebuffer";
        else if (v == FramebufferTarget::DrawFramebuffer) return "DrawFramebuffer";
        else if (v == FramebufferTarget::ReadFramebuffer) return "ReadFramebuffer";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref RenderbufferTarget value, or `"?"` for unknown values.
    inline std::string_view to_string(RenderbufferTarget v)
    {
        if (v == RenderbufferTarget::Renderbuffer) return "Renderbuffer";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ColorAttachment value, or `"?"` for unknown values.
    inline std::string_view to_string(ColorAttachment v)
    {
        if (v == ColorAttachment::Color0) return "Color0";
        else if (v == ColorAttachment::Color1) return "Color1";
        else if (v == ColorAttachment::Color2) return "Color2";
        else if (v == ColorAttachment::Color3) return "Color3";
        else if (v == ColorAttachment::Color4) return "Color4";
        else if (v == ColorAttachment::Color5) return "Color5";
        else if (v == ColorAttachment::Color6) return "Color6";
        else if (v == ColorAttachment::Color7) return "Color7";
        else if (v == ColorAttachment::Color8) return "Color8";
        else if (v == ColorAttachment::Color9) return "Color9";
        else if (v == ColorAttachment::Color10) return "Color10";
        else if (v == ColorAttachment::Color11) return "Color11";
        else if (v == ColorAttachment::Color12) return "Color12";
        else if (v == ColorAttachment::Color13) return "Color13";
        else if (v == ColorAttachment::Color14) return "Color14";
        else if (v == ColorAttachment::Color15) return "Color15";
        else if (v == ColorAttachment::Color16) return "Color16";
        else if (v == ColorAttachment::Color17) return "Color17";
        else if (v == ColorAttachment::Color18) return "Color18";
        else if (v == ColorAttachment::Color19) return "Color19";
        else if (v == ColorAttachment::Color20) return "Color20";
        else if (v == ColorAttachment::Color21) return "Color21";
        else if (v == ColorAttachment::Color22) return "Color22";
        else if (v == ColorAttachment::Color23) return "Color23";
        else if (v == ColorAttachment::Color24) return "Color24";
        else if (v == ColorAttachment::Color25) return "Color25";
        else if (v == ColorAttachment::Color26) return "Color26";
        else if (v == ColorAttachment::Color27) return "Color27";
        else if (v == ColorAttachment::Color28) return "Color28";
        else if (v == ColorAttachment::Color29) return "Color29";
        else if (v == ColorAttachment::Color30) return "Color30";
        else if (v == ColorAttachment::Color31) return "Color31";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref FramebufferAttachment value, or `"?"` for unknown values.
    inline std::string_view to_string(FramebufferAttachment v)
    {
        if (v == FramebufferAttachment::None) return "None";
        else if (v == FramebufferAttachment::Depth) return "Depth";
        else if (v == FramebufferAttachment::Stencil) return "Stencil";
        else if (v == FramebufferAttachment::DepthStencil) return "DepthStencil";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref FramebufferStatus value, or `"?"` for unknown values.
    inline std::string_view to_string(FramebufferStatus v)
    {
        if (v == FramebufferStatus::Complete) return "Complete";
        else if (v == FramebufferStatus::Undefined) return "Undefined";
        else if (v == FramebufferStatus::IncompleteAttachment) return "IncompleteAttachment";
        else if (v == FramebufferStatus::IncompleteMissingAttachment) return "IncompleteMissingAttachment";
        else if (v == FramebufferStatus::IncompleteDimensions) return "IncompleteDimensions";
        else if (v == FramebufferStatus::Unsupported) return "Unsupported";
        else if (v == FramebufferStatus::IncompleteMultisample) return "IncompleteMultisample";
        else if (v == FramebufferStatus::IncompleteLayerTargets) return "IncompleteLayerTargets";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref FramebufferAttachmentParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(FramebufferAttachmentParameter v)
    {
        if (v == FramebufferAttachmentParameter::ObjectType) return "ObjectType";
        else if (v == FramebufferAttachmentParameter::ObjectName) return "ObjectName";
        else if (v == FramebufferAttachmentParameter::TextureLevel) return "TextureLevel";
        else if (v == FramebufferAttachmentParameter::TextureCubeMapFace) return "TextureCubeMapFace";
        else if (v == FramebufferAttachmentParameter::ColorEncoding) return "ColorEncoding";
        else if (v == FramebufferAttachmentParameter::ComponentType) return "ComponentType";
        else if (v == FramebufferAttachmentParameter::RedSize) return "RedSize";
        else if (v == FramebufferAttachmentParameter::GreenSize) return "GreenSize";
        else if (v == FramebufferAttachmentParameter::BlueSize) return "BlueSize";
        else if (v == FramebufferAttachmentParameter::AlphaSize) return "AlphaSize";
        else if (v == FramebufferAttachmentParameter::DepthSize) return "DepthSize";
        else if (v == FramebufferAttachmentParameter::StencilSize) return "StencilSize";
        else if (v == FramebufferAttachmentParameter::TextureLayer) return "TextureLayer";
        else if (v == FramebufferAttachmentParameter::Layered) return "Layered";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref FramebufferDefaultParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(FramebufferDefaultParameter v)
    {
        if (v == FramebufferDefaultParameter::Width) return "Width";
        else if (v == FramebufferDefaultParameter::Height) return "Height";
        else if (v == FramebufferDefaultParameter::Samples) return "Samples";
        else if (v == FramebufferDefaultParameter::FixedSampleLocations) return "FixedSampleLocations";
        else if (v == FramebufferDefaultParameter::Layers) return "Layers";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref RenderbufferParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(RenderbufferParameter v)
    {
        if (v == RenderbufferParameter::Width) return "Width";
        else if (v == RenderbufferParameter::Height) return "Height";
        else if (v == RenderbufferParameter::InternalFormat) return "InternalFormat";
        else if (v == RenderbufferParameter::RedSize) return "RedSize";
        else if (v == RenderbufferParameter::GreenSize) return "GreenSize";
        else if (v == RenderbufferParameter::BlueSize) return "BlueSize";
        else if (v == RenderbufferParameter::AlphaSize) return "AlphaSize";
        else if (v == RenderbufferParameter::DepthSize) return "DepthSize";
        else if (v == RenderbufferParameter::StencilSize) return "StencilSize";
        else if (v == RenderbufferParameter::Samples) return "Samples";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref VertexAttribParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(VertexAttribParameter v)
    {
        if (v == VertexAttribParameter::ArrayEnabled) return "ArrayEnabled";
        else if (v == VertexAttribParameter::ArraySize) return "ArraySize";
        else if (v == VertexAttribParameter::ArrayStride) return "ArrayStride";
        else if (v == VertexAttribParameter::ArrayType) return "ArrayType";
        else if (v == VertexAttribParameter::ArrayNormalized) return "ArrayNormalized";
        else if (v == VertexAttribParameter::ArrayPointer) return "ArrayPointer";
        else if (v == VertexAttribParameter::ArrayBufferBinding) return "ArrayBufferBinding";
        else if (v == VertexAttribParameter::CurrentVertexAttrib) return "CurrentVertexAttrib";
        else if (v == VertexAttribParameter::ArrayInteger) return "ArrayInteger";
        else if (v == VertexAttribParameter::ArrayDivisor) return "ArrayDivisor";
        else if (v == VertexAttribParameter::Binding) return "Binding";
        else if (v == VertexAttribParameter::RelativeOffset) return "RelativeOffset";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TransformFeedbackBufferMode value, or `"?"` for unknown values.
    inline std::string_view to_string(TransformFeedbackBufferMode v)
    {
        if (v == TransformFeedbackBufferMode::InterleavedAttribs) return "InterleavedAttribs";
        else if (v == TransformFeedbackBufferMode::SeparateAttribs) return "SeparateAttribs";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TransformFeedbackTarget value, or `"?"` for unknown values.
    inline std::string_view to_string(TransformFeedbackTarget v)
    {
        if (v == TransformFeedbackTarget::TransformFeedback) return "TransformFeedback";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TransformFeedbackPrimitive value, or `"?"` for unknown values.
    inline std::string_view to_string(TransformFeedbackPrimitive v)
    {
        if (v == TransformFeedbackPrimitive::Points) return "Points";
        else if (v == TransformFeedbackPrimitive::Lines) return "Lines";
        else if (v == TransformFeedbackPrimitive::Triangles) return "Triangles";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref QueryTarget value, or `"?"` for unknown values.
    inline std::string_view to_string(QueryTarget v)
    {
        if (v == QueryTarget::AnySamplesPassed) return "AnySamplesPassed";
        else if (v == QueryTarget::AnySamplesPassedConservative) return "AnySamplesPassedConservative";
        else if (v == QueryTarget::TransformFeedbackPrimitivesWritten) return "TransformFeedbackPrimitivesWritten";
        else if (v == QueryTarget::PrimitivesGenerated) return "PrimitivesGenerated";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref QueryParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(QueryParameter v)
    {
        if (v == QueryParameter::CurrentQuery) return "CurrentQuery";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref QueryObjectParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(QueryObjectParameter v)
    {
        if (v == QueryObjectParameter::Result) return "Result";
        else if (v == QueryObjectParameter::ResultAvailable) return "ResultAvailable";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref SyncCondition value, or `"?"` for unknown values.
    inline std::string_view to_string(SyncCondition v)
    {
        if (v == SyncCondition::GpuCommandsComplete) return "GpuCommandsComplete";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref SyncParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(SyncParameter v)
    {
        if (v == SyncParameter::ObjectType) return "ObjectType";
        else if (v == SyncParameter::Condition) return "Condition";
        else if (v == SyncParameter::Status) return "Status";
        else if (v == SyncParameter::Flags) return "Flags";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref SyncWaitResult value, or `"?"` for unknown values.
    inline std::string_view to_string(SyncWaitResult v)
    {
        if (v == SyncWaitResult::AlreadySignaled) return "AlreadySignaled";
        else if (v == SyncWaitResult::TimeoutExpired) return "TimeoutExpired";
        else if (v == SyncWaitResult::ConditionSatisfied) return "ConditionSatisfied";
        else if (v == SyncWaitResult::WaitFailed) return "WaitFailed";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref SyncFlushMask value, or `"?"` for unknown values.
    inline std::string_view to_string(SyncFlushMask v)
    {
        if (v == SyncFlushMask::None) return "None";
        else if (v == SyncFlushMask::Commands) return "Commands";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ImageAccess value, or `"?"` for unknown values.
    inline std::string_view to_string(ImageAccess v)
    {
        if (v == ImageAccess::ReadOnly) return "ReadOnly";
        else if (v == ImageAccess::WriteOnly) return "WriteOnly";
        else if (v == ImageAccess::ReadWrite) return "ReadWrite";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref MemoryBarrierMask value, or `"?"` for unknown values.
    inline std::string_view to_string(MemoryBarrierMask v)
    {
        if (v == MemoryBarrierMask::VertexAttribArray) return "VertexAttribArray";
        else if (v == MemoryBarrierMask::ElementArray) return "ElementArray";
        else if (v == MemoryBarrierMask::Uniform) return "Uniform";
        else if (v == MemoryBarrierMask::TextureFetch) return "TextureFetch";
        else if (v == MemoryBarrierMask::ShaderImageAccess) return "ShaderImageAccess";
        else if (v == MemoryBarrierMask::Command) return "Command";
        else if (v == MemoryBarrierMask::PixelBuffer) return "PixelBuffer";
        else if (v == MemoryBarrierMask::TextureUpdate) return "TextureUpdate";
        else if (v == MemoryBarrierMask::BufferUpdate) return "BufferUpdate";
        else if (v == MemoryBarrierMask::Framebuffer) return "Framebuffer";
        else if (v == MemoryBarrierMask::TransformFeedback) return "TransformFeedback";
        else if (v == MemoryBarrierMask::AtomicCounter) return "AtomicCounter";
        else if (v == MemoryBarrierMask::ShaderStorage) return "ShaderStorage";
        else if (v == MemoryBarrierMask::AllBarrierBits) return "AllBarrierBits";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ContextFlagMask value, or `"?"` for unknown values.
    inline std::string_view to_string(ContextFlagMask v)
    {
        if (v == ContextFlagMask::Debug) return "Debug";
        else if (v == ContextFlagMask::RobustAccess) return "RobustAccess";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref GraphicsResetStatus value, or `"?"` for unknown values.
    inline std::string_view to_string(GraphicsResetStatus v)
    {
        if (v == GraphicsResetStatus::NoError) return "NoError";
        else if (v == GraphicsResetStatus::Guilty) return "Guilty";
        else if (v == GraphicsResetStatus::Innocent) return "Innocent";
        else if (v == GraphicsResetStatus::Unknown) return "Unknown";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ResetNotificationStrategy value, or `"?"` for unknown values.
    inline std::string_view to_string(ResetNotificationStrategy v)
    {
        if (v == ResetNotificationStrategy::NoResetNotification) return "NoResetNotification";
        else if (v == ResetNotificationStrategy::LoseContextOnReset) return "LoseContextOnReset";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref DebugSource value, or `"?"` for unknown values.
    inline std::string_view to_string(DebugSource v)
    {
        if (v == DebugSource::DontCare) return "DontCare";
        else if (v == DebugSource::Api) return "Api";
        else if (v == DebugSource::WindowSystem) return "WindowSystem";
        else if (v == DebugSource::ShaderCompiler) return "ShaderCompiler";
        else if (v == DebugSource::ThirdParty) return "ThirdParty";
        else if (v == DebugSource::Application) return "Application";
        else if (v == DebugSource::Other) return "Other";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref DebugType value, or `"?"` for unknown values.
    inline std::string_view to_string(DebugType v)
    {
        if (v == DebugType::DontCare) return "DontCare";
        else if (v == DebugType::Error) return "Error";
        else if (v == DebugType::DeprecatedBehavior) return "DeprecatedBehavior";
        else if (v == DebugType::UndefinedBehavior) return "UndefinedBehavior";
        else if (v == DebugType::Portability) return "Portability";
        else if (v == DebugType::Performance) return "Performance";
        else if (v == DebugType::Other) return "Other";
        else if (v == DebugType::Marker) return "Marker";
        else if (v == DebugType::PushGroup) return "PushGroup";
        else if (v == DebugType::PopGroup) return "PopGroup";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref DebugSeverity value, or `"?"` for unknown values.
    inline std::string_view to_string(DebugSeverity v)
    {
        if (v == DebugSeverity::DontCare) return "DontCare";
        else if (v == DebugSeverity::High) return "High";
        else if (v == DebugSeverity::Medium) return "Medium";
        else if (v == DebugSeverity::Low) return "Low";
        else if (v == DebugSeverity::Notification) return "Notification";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref DebugObjectLabel value, or `"?"` for unknown values.
    inline std::string_view to_string(DebugObjectLabel v)
    {
        if (v == DebugObjectLabel::Buffer) return "Buffer";
        else if (v == DebugObjectLabel::Shader) return "Shader";
        else if (v == DebugObjectLabel::Program) return "Program";
        else if (v == DebugObjectLabel::VertexArray) return "VertexArray";
        else if (v == DebugObjectLabel::Query) return "Query";
        else if (v == DebugObjectLabel::ProgramPipeline) return "ProgramPipeline";
        else if (v == DebugObjectLabel::Sampler) return "Sampler";
        else if (v == DebugObjectLabel::Framebuffer) return "Framebuffer";
        else if (v == DebugObjectLabel::Renderbuffer) return "Renderbuffer";
        else if (v == DebugObjectLabel::Texture) return "Texture";
        else if (v == DebugObjectLabel::TransformFeedback) return "TransformFeedback";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ProvokingVertex value, or `"?"` for unknown values.
    inline std::string_view to_string(ProvokingVertex v)
    {
        if (v == ProvokingVertex::FirstVertex) return "FirstVertex";
        else if (v == ProvokingVertex::LastVertex) return "LastVertex";
        else if (v == ProvokingVertex::UndefinedVertex) return "UndefinedVertex";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TessGenMode value, or `"?"` for unknown values.
    inline std::string_view to_string(TessGenMode v)
    {
        if (v == TessGenMode::Quads) return "Quads";
        else if (v == TessGenMode::Triangles) return "Triangles";
        else if (v == TessGenMode::Isolines) return "Isolines";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TessGenSpacing value, or `"?"` for unknown values.
    inline std::string_view to_string(TessGenSpacing v)
    {
        if (v == TessGenSpacing::Equal) return "Equal";
        else if (v == TessGenSpacing::FractionalOdd) return "FractionalOdd";
        else if (v == TessGenSpacing::FractionalEven) return "FractionalEven";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref TessellationParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(TessellationParameter v)
    {
        if (v == TessellationParameter::PatchVertices) return "PatchVertices";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref GetParameter value, or `"?"` for unknown values.
    ///
    /// The comparisons intentionally use independent early-return `if`
    /// statements. A single 270-element `else if` chain exceeds MSVC's block
    /// nesting limit (C1061), while producing identical lookup semantics here.
    inline std::string_view to_string(GetParameter v)
    {
        if (v == GetParameter::Viewport) return "Viewport";
        if (v == GetParameter::ScissorBox) return "ScissorBox";
        if (v == GetParameter::MaxViewportDims) return "MaxViewportDims";
        if (v == GetParameter::LineWidth) return "LineWidth";
        if (v == GetParameter::AliasedPointSizeRange) return "AliasedPointSizeRange";
        if (v == GetParameter::AliasedLineWidthRange) return "AliasedLineWidthRange";
        if (v == GetParameter::CullFaceMode) return "CullFaceMode";
        if (v == GetParameter::FrontFace) return "FrontFace";
        if (v == GetParameter::DepthRange) return "DepthRange";
        if (v == GetParameter::DepthWritemask) return "DepthWritemask";
        if (v == GetParameter::DepthClearValue) return "DepthClearValue";
        if (v == GetParameter::DepthFunc) return "DepthFunc";
        if (v == GetParameter::DepthBits) return "DepthBits";
        if (v == GetParameter::StencilClearValue) return "StencilClearValue";
        if (v == GetParameter::StencilFunc) return "StencilFunc";
        if (v == GetParameter::StencilFail) return "StencilFail";
        if (v == GetParameter::StencilPassDepthFail) return "StencilPassDepthFail";
        if (v == GetParameter::StencilPassDepthPass) return "StencilPassDepthPass";
        if (v == GetParameter::StencilRef) return "StencilRef";
        if (v == GetParameter::StencilValueMask) return "StencilValueMask";
        if (v == GetParameter::StencilWritemask) return "StencilWritemask";
        if (v == GetParameter::StencilBackFunc) return "StencilBackFunc";
        if (v == GetParameter::StencilBackFail) return "StencilBackFail";
        if (v == GetParameter::StencilBackPassDepthFail) return "StencilBackPassDepthFail";
        if (v == GetParameter::StencilBackPassDepthPass) return "StencilBackPassDepthPass";
        if (v == GetParameter::StencilBackRef) return "StencilBackRef";
        if (v == GetParameter::StencilBackValueMask) return "StencilBackValueMask";
        if (v == GetParameter::StencilBackWritemask) return "StencilBackWritemask";
        if (v == GetParameter::StencilBits) return "StencilBits";
        if (v == GetParameter::ColorClearValue) return "ColorClearValue";
        if (v == GetParameter::ColorWritemask) return "ColorWritemask";
        if (v == GetParameter::RedBits) return "RedBits";
        if (v == GetParameter::GreenBits) return "GreenBits";
        if (v == GetParameter::BlueBits) return "BlueBits";
        if (v == GetParameter::AlphaBits) return "AlphaBits";
        if (v == GetParameter::PolygonOffsetUnits) return "PolygonOffsetUnits";
        if (v == GetParameter::PolygonOffsetFactor) return "PolygonOffsetFactor";
        if (v == GetParameter::SampleBuffers) return "SampleBuffers";
        if (v == GetParameter::Samples) return "Samples";
        if (v == GetParameter::SampleCoverageValue) return "SampleCoverageValue";
        if (v == GetParameter::SampleCoverageInvert) return "SampleCoverageInvert";
        if (v == GetParameter::SampleMaskValue) return "SampleMaskValue";
        if (v == GetParameter::SamplePosition) return "SamplePosition";
        if (v == GetParameter::MaxSampleMaskWords) return "MaxSampleMaskWords";
        if (v == GetParameter::MaxColorTextureSamples) return "MaxColorTextureSamples";
        if (v == GetParameter::MaxDepthTextureSamples) return "MaxDepthTextureSamples";
        if (v == GetParameter::MaxIntegerSamples) return "MaxIntegerSamples";
        if (v == GetParameter::MaxSamples) return "MaxSamples";
        if (v == GetParameter::MinSampleShadingValue) return "MinSampleShadingValue";
        if (v == GetParameter::NumCompressedTextureFormats) return "NumCompressedTextureFormats";
        if (v == GetParameter::CompressedTextureFormats) return "CompressedTextureFormats";
        if (v == GetParameter::MaxTextureSize) return "MaxTextureSize";
        if (v == GetParameter::MaxCubeMapTextureSize) return "MaxCubeMapTextureSize";
        if (v == GetParameter::Max3DTextureSize) return "Max3DTextureSize";
        if (v == GetParameter::MaxArrayTextureLayers) return "MaxArrayTextureLayers";
        if (v == GetParameter::MaxTextureBufferSize) return "MaxTextureBufferSize";
        if (v == GetParameter::MaxTextureLodBias) return "MaxTextureLodBias";
        if (v == GetParameter::MaxTextureMaxAnisotropy) return "MaxTextureMaxAnisotropy";
        if (v == GetParameter::TextureBinding2D) return "TextureBinding2D";
        if (v == GetParameter::TextureBindingCubeMap) return "TextureBindingCubeMap";
        if (v == GetParameter::TextureBinding3D) return "TextureBinding3D";
        if (v == GetParameter::TextureBinding2DArray) return "TextureBinding2DArray";
        if (v == GetParameter::TextureBinding2DMultisample) return "TextureBinding2DMultisample";
        if (v == GetParameter::TextureBindingBuffer) return "TextureBindingBuffer";
        if (v == GetParameter::TextureBindingCubeMapArray) return "TextureBindingCubeMapArray";
        if (v == GetParameter::TextureBinding2DMultisampleArray) return "TextureBinding2DMultisampleArray";
        if (v == GetParameter::SubpixelBits) return "SubpixelBits";
        if (v == GetParameter::ActiveTexture) return "ActiveTexture";
        if (v == GetParameter::SamplerBinding) return "SamplerBinding";
        if (v == GetParameter::ImplementationColorReadType) return "ImplementationColorReadType";
        if (v == GetParameter::ImplementationColorReadFormat) return "ImplementationColorReadFormat";
        if (v == GetParameter::BlendColor) return "BlendColor";
        if (v == GetParameter::BlendEquationRgb) return "BlendEquationRgb";
        if (v == GetParameter::BlendEquationAlpha) return "BlendEquationAlpha";
        if (v == GetParameter::BlendDstRgb) return "BlendDstRgb";
        if (v == GetParameter::BlendSrcRgb) return "BlendSrcRgb";
        if (v == GetParameter::BlendDstAlpha) return "BlendDstAlpha";
        if (v == GetParameter::BlendSrcAlpha) return "BlendSrcAlpha";
        if (v == GetParameter::ArrayBufferBinding) return "ArrayBufferBinding";
        if (v == GetParameter::ElementArrayBufferBinding) return "ElementArrayBufferBinding";
        if (v == GetParameter::PixelPackBufferBinding) return "PixelPackBufferBinding";
        if (v == GetParameter::PixelUnpackBufferBinding) return "PixelUnpackBufferBinding";
        if (v == GetParameter::UniformBufferBinding) return "UniformBufferBinding";
        if (v == GetParameter::UniformBufferStart) return "UniformBufferStart";
        if (v == GetParameter::UniformBufferSize) return "UniformBufferSize";
        if (v == GetParameter::TransformFeedbackBufferBinding) return "TransformFeedbackBufferBinding";
        if (v == GetParameter::TransformFeedbackBufferStart) return "TransformFeedbackBufferStart";
        if (v == GetParameter::TransformFeedbackBufferSize) return "TransformFeedbackBufferSize";
        if (v == GetParameter::CopyReadBufferBinding) return "CopyReadBufferBinding";
        if (v == GetParameter::CopyWriteBufferBinding) return "CopyWriteBufferBinding";
        if (v == GetParameter::DrawIndirectBufferBinding) return "DrawIndirectBufferBinding";
        if (v == GetParameter::DispatchIndirectBufferBinding) return "DispatchIndirectBufferBinding";
        if (v == GetParameter::ShaderStorageBufferBinding) return "ShaderStorageBufferBinding";
        if (v == GetParameter::ShaderStorageBufferStart) return "ShaderStorageBufferStart";
        if (v == GetParameter::ShaderStorageBufferSize) return "ShaderStorageBufferSize";
        if (v == GetParameter::AtomicCounterBufferBinding) return "AtomicCounterBufferBinding";
        if (v == GetParameter::AtomicCounterBufferStart) return "AtomicCounterBufferStart";
        if (v == GetParameter::AtomicCounterBufferSize) return "AtomicCounterBufferSize";
        if (v == GetParameter::VertexArrayBinding) return "VertexArrayBinding";
        if (v == GetParameter::VertexBindingDivisor) return "VertexBindingDivisor";
        if (v == GetParameter::VertexBindingOffset) return "VertexBindingOffset";
        if (v == GetParameter::VertexBindingStride) return "VertexBindingStride";
        if (v == GetParameter::VertexBindingBuffer) return "VertexBindingBuffer";
        if (v == GetParameter::MaxVertexAttribRelativeOffset) return "MaxVertexAttribRelativeOffset";
        if (v == GetParameter::MaxVertexAttribBindings) return "MaxVertexAttribBindings";
        if (v == GetParameter::MaxVertexAttribStride) return "MaxVertexAttribStride";
        if (v == GetParameter::FramebufferBinding) return "FramebufferBinding";
        if (v == GetParameter::ReadFramebufferBinding) return "ReadFramebufferBinding";
        if (v == GetParameter::RenderbufferBinding) return "RenderbufferBinding";
        if (v == GetParameter::MaxRenderbufferSize) return "MaxRenderbufferSize";
        if (v == GetParameter::MaxColorAttachments) return "MaxColorAttachments";
        if (v == GetParameter::MaxFramebufferWidth) return "MaxFramebufferWidth";
        if (v == GetParameter::MaxFramebufferHeight) return "MaxFramebufferHeight";
        if (v == GetParameter::MaxFramebufferSamples) return "MaxFramebufferSamples";
        if (v == GetParameter::MaxFramebufferLayers) return "MaxFramebufferLayers";
        if (v == GetParameter::ReadBuffer) return "ReadBuffer";
        if (v == GetParameter::MaxDrawBuffers) return "MaxDrawBuffers";
        if (v == GetParameter::DrawBuffer0) return "DrawBuffer0";
        if (v == GetParameter::DrawBuffer1) return "DrawBuffer1";
        if (v == GetParameter::DrawBuffer2) return "DrawBuffer2";
        if (v == GetParameter::DrawBuffer3) return "DrawBuffer3";
        if (v == GetParameter::DrawBuffer4) return "DrawBuffer4";
        if (v == GetParameter::DrawBuffer5) return "DrawBuffer5";
        if (v == GetParameter::DrawBuffer6) return "DrawBuffer6";
        if (v == GetParameter::DrawBuffer7) return "DrawBuffer7";
        if (v == GetParameter::DrawBuffer8) return "DrawBuffer8";
        if (v == GetParameter::DrawBuffer9) return "DrawBuffer9";
        if (v == GetParameter::DrawBuffer10) return "DrawBuffer10";
        if (v == GetParameter::DrawBuffer11) return "DrawBuffer11";
        if (v == GetParameter::DrawBuffer12) return "DrawBuffer12";
        if (v == GetParameter::DrawBuffer13) return "DrawBuffer13";
        if (v == GetParameter::DrawBuffer14) return "DrawBuffer14";
        if (v == GetParameter::DrawBuffer15) return "DrawBuffer15";
        if (v == GetParameter::MaxVertexAttribs) return "MaxVertexAttribs";
        if (v == GetParameter::MaxVertexUniformVectors) return "MaxVertexUniformVectors";
        if (v == GetParameter::MaxVaryingVectors) return "MaxVaryingVectors";
        if (v == GetParameter::MaxCombinedTextureImageUnits) return "MaxCombinedTextureImageUnits";
        if (v == GetParameter::MaxVertexTextureImageUnits) return "MaxVertexTextureImageUnits";
        if (v == GetParameter::MaxTextureImageUnits) return "MaxTextureImageUnits";
        if (v == GetParameter::MaxFragmentUniformVectors) return "MaxFragmentUniformVectors";
        if (v == GetParameter::MaxVertexUniformComponents) return "MaxVertexUniformComponents";
        if (v == GetParameter::MaxFragmentUniformComponents) return "MaxFragmentUniformComponents";
        if (v == GetParameter::MaxVaryingComponents) return "MaxVaryingComponents";
        if (v == GetParameter::MaxVertexOutputComponents) return "MaxVertexOutputComponents";
        if (v == GetParameter::MaxFragmentInputComponents) return "MaxFragmentInputComponents";
        if (v == GetParameter::MaxVertexUniformBlocks) return "MaxVertexUniformBlocks";
        if (v == GetParameter::MaxFragmentUniformBlocks) return "MaxFragmentUniformBlocks";
        if (v == GetParameter::MaxCombinedUniformBlocks) return "MaxCombinedUniformBlocks";
        if (v == GetParameter::MaxUniformBufferBindings) return "MaxUniformBufferBindings";
        if (v == GetParameter::MaxUniformBlockSize) return "MaxUniformBlockSize";
        if (v == GetParameter::MaxCombinedVertexUniformComponents) return "MaxCombinedVertexUniformComponents";
        if (v == GetParameter::MaxCombinedFragmentUniformComponents) return "MaxCombinedFragmentUniformComponents";
        if (v == GetParameter::UniformBufferOffsetAlignment) return "UniformBufferOffsetAlignment";
        if (v == GetParameter::MinProgramTexelOffset) return "MinProgramTexelOffset";
        if (v == GetParameter::MaxProgramTexelOffset) return "MaxProgramTexelOffset";
        if (v == GetParameter::MaxUniformLocations) return "MaxUniformLocations";
        if (v == GetParameter::MaxShaderStorageBufferBindings) return "MaxShaderStorageBufferBindings";
        if (v == GetParameter::MaxShaderStorageBlockSize) return "MaxShaderStorageBlockSize";
        if (v == GetParameter::ShaderStorageBufferOffsetAlignment) return "ShaderStorageBufferOffsetAlignment";
        if (v == GetParameter::MaxCombinedShaderStorageBlocks) return "MaxCombinedShaderStorageBlocks";
        if (v == GetParameter::MaxVertexShaderStorageBlocks) return "MaxVertexShaderStorageBlocks";
        if (v == GetParameter::MaxFragmentShaderStorageBlocks) return "MaxFragmentShaderStorageBlocks";
        if (v == GetParameter::MaxComputeShaderStorageBlocks) return "MaxComputeShaderStorageBlocks";
        if (v == GetParameter::MaxCombinedShaderOutputResources) return "MaxCombinedShaderOutputResources";
        if (v == GetParameter::MaxImageUnits) return "MaxImageUnits";
        if (v == GetParameter::MaxVertexImageUniforms) return "MaxVertexImageUniforms";
        if (v == GetParameter::MaxFragmentImageUniforms) return "MaxFragmentImageUniforms";
        if (v == GetParameter::MaxCombinedImageUniforms) return "MaxCombinedImageUniforms";
        if (v == GetParameter::MaxAtomicCounterBufferBindings) return "MaxAtomicCounterBufferBindings";
        if (v == GetParameter::MaxAtomicCounterBufferSize) return "MaxAtomicCounterBufferSize";
        if (v == GetParameter::MaxVertexAtomicCounterBuffers) return "MaxVertexAtomicCounterBuffers";
        if (v == GetParameter::MaxFragmentAtomicCounterBuffers) return "MaxFragmentAtomicCounterBuffers";
        if (v == GetParameter::MaxCombinedAtomicCounterBuffers) return "MaxCombinedAtomicCounterBuffers";
        if (v == GetParameter::MaxVertexAtomicCounters) return "MaxVertexAtomicCounters";
        if (v == GetParameter::MaxFragmentAtomicCounters) return "MaxFragmentAtomicCounters";
        if (v == GetParameter::MaxCombinedAtomicCounters) return "MaxCombinedAtomicCounters";
        if (v == GetParameter::MaxComputeUniformBlocks) return "MaxComputeUniformBlocks";
        if (v == GetParameter::MaxComputeTextureImageUnits) return "MaxComputeTextureImageUnits";
        if (v == GetParameter::MaxComputeImageUniforms) return "MaxComputeImageUniforms";
        if (v == GetParameter::MaxComputeSharedMemorySize) return "MaxComputeSharedMemorySize";
        if (v == GetParameter::MaxComputeUniformComponents) return "MaxComputeUniformComponents";
        if (v == GetParameter::MaxComputeAtomicCounterBuffers) return "MaxComputeAtomicCounterBuffers";
        if (v == GetParameter::MaxComputeAtomicCounters) return "MaxComputeAtomicCounters";
        if (v == GetParameter::MaxCombinedComputeUniformComponents) return "MaxCombinedComputeUniformComponents";
        if (v == GetParameter::MaxComputeWorkGroupInvocations) return "MaxComputeWorkGroupInvocations";
        if (v == GetParameter::MaxComputeWorkGroupCount) return "MaxComputeWorkGroupCount";
        if (v == GetParameter::MaxComputeWorkGroupSize) return "MaxComputeWorkGroupSize";
        if (v == GetParameter::MaxGeometryUniformComponents) return "MaxGeometryUniformComponents";
        if (v == GetParameter::MaxGeometryUniformBlocks) return "MaxGeometryUniformBlocks";
        if (v == GetParameter::MaxCombinedGeometryUniformComponents) return "MaxCombinedGeometryUniformComponents";
        if (v == GetParameter::MaxGeometryInputComponents) return "MaxGeometryInputComponents";
        if (v == GetParameter::MaxGeometryOutputComponents) return "MaxGeometryOutputComponents";
        if (v == GetParameter::MaxGeometryOutputVertices) return "MaxGeometryOutputVertices";
        if (v == GetParameter::MaxGeometryTotalOutputComponents) return "MaxGeometryTotalOutputComponents";
        if (v == GetParameter::MaxGeometryShaderInvocations) return "MaxGeometryShaderInvocations";
        if (v == GetParameter::MaxGeometryTextureImageUnits) return "MaxGeometryTextureImageUnits";
        if (v == GetParameter::MaxGeometryAtomicCounterBuffers) return "MaxGeometryAtomicCounterBuffers";
        if (v == GetParameter::MaxGeometryAtomicCounters) return "MaxGeometryAtomicCounters";
        if (v == GetParameter::MaxGeometryImageUniforms) return "MaxGeometryImageUniforms";
        if (v == GetParameter::MaxGeometryShaderStorageBlocks) return "MaxGeometryShaderStorageBlocks";
        if (v == GetParameter::LayerProvokingVertex) return "LayerProvokingVertex";
        if (v == GetParameter::MaxPatchVertices) return "MaxPatchVertices";
        if (v == GetParameter::MaxTessGenLevel) return "MaxTessGenLevel";
        if (v == GetParameter::MaxTessControlUniformComponents) return "MaxTessControlUniformComponents";
        if (v == GetParameter::MaxTessEvaluationUniformComponents) return "MaxTessEvaluationUniformComponents";
        if (v == GetParameter::MaxTessControlTextureImageUnits) return "MaxTessControlTextureImageUnits";
        if (v == GetParameter::MaxTessEvaluationTextureImageUnits) return "MaxTessEvaluationTextureImageUnits";
        if (v == GetParameter::MaxTessControlOutputComponents) return "MaxTessControlOutputComponents";
        if (v == GetParameter::MaxTessPatchComponents) return "MaxTessPatchComponents";
        if (v == GetParameter::MaxTessControlTotalOutputComponents) return "MaxTessControlTotalOutputComponents";
        if (v == GetParameter::MaxTessEvaluationOutputComponents) return "MaxTessEvaluationOutputComponents";
        if (v == GetParameter::MaxTessControlUniformBlocks) return "MaxTessControlUniformBlocks";
        if (v == GetParameter::MaxTessEvaluationUniformBlocks) return "MaxTessEvaluationUniformBlocks";
        if (v == GetParameter::MaxTessControlInputComponents) return "MaxTessControlInputComponents";
        if (v == GetParameter::MaxTessEvaluationInputComponents) return "MaxTessEvaluationInputComponents";
        if (v == GetParameter::MaxCombinedTessControlUniformComponents) return "MaxCombinedTessControlUniformComponents";
        if (v == GetParameter::MaxCombinedTessEvaluationUniformComponents) return "MaxCombinedTessEvaluationUniformComponents";
        if (v == GetParameter::MaxTessControlAtomicCounterBuffers) return "MaxTessControlAtomicCounterBuffers";
        if (v == GetParameter::MaxTessEvaluationAtomicCounterBuffers) return "MaxTessEvaluationAtomicCounterBuffers";
        if (v == GetParameter::MaxTessControlAtomicCounters) return "MaxTessControlAtomicCounters";
        if (v == GetParameter::MaxTessEvaluationAtomicCounters) return "MaxTessEvaluationAtomicCounters";
        if (v == GetParameter::MaxTessControlImageUniforms) return "MaxTessControlImageUniforms";
        if (v == GetParameter::MaxTessEvaluationImageUniforms) return "MaxTessEvaluationImageUniforms";
        if (v == GetParameter::MaxTessControlShaderStorageBlocks) return "MaxTessControlShaderStorageBlocks";
        if (v == GetParameter::MaxTessEvaluationShaderStorageBlocks) return "MaxTessEvaluationShaderStorageBlocks";
        if (v == GetParameter::PrimitiveRestartForPatchesSupported) return "PrimitiveRestartForPatchesSupported";
        if (v == GetParameter::MinFragmentInterpolationOffset) return "MinFragmentInterpolationOffset";
        if (v == GetParameter::MaxFragmentInterpolationOffset) return "MaxFragmentInterpolationOffset";
        if (v == GetParameter::FragmentInterpolationOffsetBits) return "FragmentInterpolationOffsetBits";
        if (v == GetParameter::MinProgramTextureGatherOffset) return "MinProgramTextureGatherOffset";
        if (v == GetParameter::MaxProgramTextureGatherOffset) return "MaxProgramTextureGatherOffset";
        if (v == GetParameter::TransformFeedbackActive) return "TransformFeedbackActive";
        if (v == GetParameter::TransformFeedbackPaused) return "TransformFeedbackPaused";
        if (v == GetParameter::TransformFeedbackBinding) return "TransformFeedbackBinding";
        if (v == GetParameter::MaxTransformFeedbackSeparateComponents) return "MaxTransformFeedbackSeparateComponents";
        if (v == GetParameter::MaxTransformFeedbackInterleavedComponents) return "MaxTransformFeedbackInterleavedComponents";
        if (v == GetParameter::MaxTransformFeedbackSeparateAttribs) return "MaxTransformFeedbackSeparateAttribs";
        if (v == GetParameter::ProgramPipelineBinding) return "ProgramPipelineBinding";
        if (v == GetParameter::CurrentProgram) return "CurrentProgram";
        if (v == GetParameter::NumProgramBinaryFormats) return "NumProgramBinaryFormats";
        if (v == GetParameter::ProgramBinaryFormats) return "ProgramBinaryFormats";
        if (v == GetParameter::ShaderCompiler) return "ShaderCompiler";
        if (v == GetParameter::ShaderBinaryFormats) return "ShaderBinaryFormats";
        if (v == GetParameter::NumShaderBinaryFormats) return "NumShaderBinaryFormats";
        if (v == GetParameter::MajorVersion) return "MajorVersion";
        if (v == GetParameter::MinorVersion) return "MinorVersion";
        if (v == GetParameter::NumExtensions) return "NumExtensions";
        if (v == GetParameter::MaxServerWaitTimeout) return "MaxServerWaitTimeout";
        if (v == GetParameter::MaxDebugMessageLength) return "MaxDebugMessageLength";
        if (v == GetParameter::MaxDebugLoggedMessages) return "MaxDebugLoggedMessages";
        if (v == GetParameter::DebugLoggedMessages) return "DebugLoggedMessages";
        if (v == GetParameter::DebugNextLoggedMessageLength) return "DebugNextLoggedMessageLength";
        if (v == GetParameter::MaxDebugGroupStackDepth) return "MaxDebugGroupStackDepth";
        if (v == GetParameter::DebugGroupStackDepth) return "DebugGroupStackDepth";
        if (v == GetParameter::MaxLabelLength) return "MaxLabelLength";
        if (v == GetParameter::ContextFlags) return "ContextFlags";
        if (v == GetParameter::ResetNotificationStrategy) return "ResetNotificationStrategy";
        if (v == GetParameter::MultisampleLineWidthRange) return "MultisampleLineWidthRange";
        if (v == GetParameter::MultisampleLineWidthGranularity) return "MultisampleLineWidthGranularity";
        if (v == GetParameter::MaxElementIndex) return "MaxElementIndex";
        if (v == GetParameter::MaxElementsVertices) return "MaxElementsVertices";
        if (v == GetParameter::MaxElementsIndices) return "MaxElementsIndices";
        if (v == GetParameter::NumSampleCounts) return "NumSampleCounts";
        if (v == GetParameter::PrimitiveRestartFixedIndex) return "PrimitiveRestartFixedIndex";
        if (v == GetParameter::ImageBindingName) return "ImageBindingName";
        if (v == GetParameter::ImageBindingLevel) return "ImageBindingLevel";
        if (v == GetParameter::ImageBindingLayered) return "ImageBindingLayered";
        if (v == GetParameter::ImageBindingLayer) return "ImageBindingLayer";
        if (v == GetParameter::ImageBindingAccess) return "ImageBindingAccess";
        if (v == GetParameter::ImageBindingFormat) return "ImageBindingFormat";
        if (v == GetParameter::PrimitiveBoundingBox) return "PrimitiveBoundingBox";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref FloatClearBuffer value, or `"?"` for unknown values.
    inline std::string_view to_string(FloatClearBuffer v)
    {
        if (v == FloatClearBuffer::Color) return "Color";
        else if (v == FloatClearBuffer::Depth) return "Depth";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref SignedIntegerClearBuffer value, or `"?"` for unknown values.
    inline std::string_view to_string(SignedIntegerClearBuffer v)
    {
        if (v == SignedIntegerClearBuffer::Color) return "Color";
        else if (v == SignedIntegerClearBuffer::Stencil) return "Stencil";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref UnsignedIntegerClearBuffer value, or `"?"` for unknown values.
    inline std::string_view to_string(UnsignedIntegerClearBuffer v)
    {
        if (v == UnsignedIntegerClearBuffer::Color) return "Color";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref DrawBuffer value, or `"?"` for unknown values.
    inline std::string_view to_string(DrawBuffer v)
    {
        if (v == DrawBuffer::None) return "None";
        else if (v == DrawBuffer::Back) return "Back";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ReadBuffer value, or `"?"` for unknown values.
    inline std::string_view to_string(ReadBuffer v)
    {
        if (v == ReadBuffer::None) return "None";
        else if (v == ReadBuffer::Back) return "Back";
        return "?";
    }

    inline std::string_view to_string(ShaderBinaryFormat) { return "ShaderBinaryFormat"; }

    inline std::string_view to_string(ProgramBinaryFormat) { return "ProgramBinaryFormat"; }

    /// @brief Returns the enumerator name of a @ref GetPointerParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(GetPointerParameter v)
    {
        if (v == GetPointerParameter::DebugCallbackFunction) return "DebugCallbackFunction";
        else if (v == GetPointerParameter::DebugCallbackUserParam) return "DebugCallbackUserParam";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref MultisampleParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(MultisampleParameter v)
    {
        if (v == MultisampleParameter::SamplePosition) return "SamplePosition";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref InternalFormatTarget value, or `"?"` for unknown values.
    inline std::string_view to_string(InternalFormatTarget v)
    {
        if (v == InternalFormatTarget::Renderbuffer) return "Renderbuffer";
        else if (v == InternalFormatTarget::Texture2DMultisample) return "Texture2DMultisample";
        else if (v == InternalFormatTarget::Texture2DMultisampleArray) return "Texture2DMultisampleArray";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref InternalFormatParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(InternalFormatParameter v)
    {
        if (v == InternalFormatParameter::Samples) return "Samples";
        else if (v == InternalFormatParameter::NumSampleCounts) return "NumSampleCounts";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref ProgramPipelineParameter value, or `"?"` for unknown values.
    inline std::string_view to_string(ProgramPipelineParameter v)
    {
        if (v == ProgramPipelineParameter::ActiveProgram) return "ActiveProgram";
        else if (v == ProgramPipelineParameter::ValidateStatus) return "ValidateStatus";
        else if (v == ProgramPipelineParameter::InfoLogLength) return "InfoLogLength";
        else if (v == ProgramPipelineParameter::VertexShader) return "VertexShader";
        else if (v == ProgramPipelineParameter::FragmentShader) return "FragmentShader";
        else if (v == ProgramPipelineParameter::GeometryShader) return "GeometryShader";
        else if (v == ProgramPipelineParameter::TessControlShader) return "TessControlShader";
        else if (v == ProgramPipelineParameter::TessEvaluationShader) return "TessEvaluationShader";
        else if (v == ProgramPipelineParameter::ComputeShader) return "ComputeShader";
        return "?";
    }

    /// @brief Returns the enumerator name of a @ref SyncFlag value, or `"?"` for unknown values.
    inline std::string_view to_string(SyncFlag v)
    {
        if (v == SyncFlag::None) return "None";
        return "?";
    }

    /// @name Handle type conversions
    /// @brief These overloads format a typed GL handle as `"TypeName(value)"`, e.g. `"TextureId(42)"`.
    /// @{
    /// @brief Formats a @ref ShaderId handle as `"ShaderId(value)"`.
    inline std::string to_string(ShaderId v)              { return "ShaderId("             + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref ProgramId handle as `"ProgramId(value)"`.
    inline std::string to_string(ProgramId v)             { return "ProgramId("            + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref TextureId handle as `"TextureId(value)"`.
    inline std::string to_string(TextureId v)             { return "TextureId("            + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref BufferId handle as `"BufferId(value)"`.
    inline std::string to_string(BufferId v)              { return "BufferId("             + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref FramebufferId handle as `"FramebufferId(value)"`.
    inline std::string to_string(FramebufferId v)         { return "FramebufferId("        + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref RenderbufferId handle as `"RenderbufferId(value)"`.
    inline std::string to_string(RenderbufferId v)        { return "RenderbufferId("       + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref SamplerId handle as `"SamplerId(value)"`.
    inline std::string to_string(SamplerId v)             { return "SamplerId("            + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref VertexArrayId handle as `"VertexArrayId(value)"`.
    inline std::string to_string(VertexArrayId v)         { return "VertexArrayId("        + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref QueryId handle as `"QueryId(value)"`.
    inline std::string to_string(QueryId v)               { return "QueryId("              + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref TransformFeedbackId handle as `"TransformFeedbackId(value)"`.
    inline std::string to_string(TransformFeedbackId v)   { return "TransformFeedbackId("  + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref ProgramPipelineId handle as `"ProgramPipelineId(value)"`.
    inline std::string to_string(ProgramPipelineId v)     { return "ProgramPipelineId("    + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref UniformLocation handle as `"UniformLocation(value)"`.
    inline std::string to_string(UniformLocation v)       { return "UniformLocation("      + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref AttribLocation handle as `"AttribLocation(value)"`.
    inline std::string to_string(AttribLocation v)        { return "AttribLocation("       + std::to_string(v.value) + ")"; }
    /// @brief Formats an @ref ActiveAttribIndex as `"ActiveAttribIndex(value)"`.
    inline std::string to_string(ActiveAttribIndex v)     { return "ActiveAttribIndex("    + std::to_string(v.value) + ")"; }
    /// @brief Formats a @ref ImageUnit handle as `"ImageUnit(value)"`.
    inline std::string to_string(ImageUnit v)             { return "ImageUnit("            + std::to_string(v.value) + ")"; }

    /// @}
} // namespace metagl
