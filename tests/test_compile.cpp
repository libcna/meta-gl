#include <metagl/metagl.hpp>
#include <type_traits>

using namespace metagl;

// R32/R33 — Sized formats for glTexStorage
static_assert(requires { glTexStorage2D(TextureTarget::Texture2D, 1, SizedInternalFormat::R8, 1, 1); });
static_assert(requires { glTexStorage2D(TextureTarget::Texture2D, 1, CompressedInternalFormat::R11Eac, 1, 1); });

// R29/R30 — Texture parameter domains
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureParameterSetter::MinFilter, 0); });
static_assert(requires { glGetTexParameteriv(TextureTarget::Texture2D, TextureParameterQuery::ImmutableFormat, nullptr); });

// R26/R27 — Default framebuffer invalidation
static_assert(requires { glInvalidateFramebuffer(FramebufferTarget::DrawFramebuffer, std::span<const FramebufferAttachment>{}); });
static_assert(requires { glInvalidateFramebuffer(FramebufferTarget::DrawFramebuffer, std::span<const DefaultFramebufferAttachment>{}); });

template<typename T>
concept CanInvalidateFramebuffer = requires(std::span<const T> s) { glInvalidateFramebuffer(FramebufferTarget::DrawFramebuffer, s); };

static_assert(CanInvalidateFramebuffer<FramebufferAttachment>);
static_assert(CanInvalidateFramebuffer<DefaultFramebufferAttachment>);
static_assert(!CanInvalidateFramebuffer<GLenum>);

// R21/R22 — glMemoryBarrierByRegion mask domain
static_assert(requires { glMemoryBarrierByRegion(MemoryBarrierByRegionMask::AtomicCounter); });
static_assert(requires { glMemoryBarrierByRegion(MemoryBarrierByRegionMask::AllBarrierBits); });

template<typename T>
concept CanCallMemoryBarrierByRegion = requires(T t) { glMemoryBarrierByRegion(t); };

static_assert(!CanCallMemoryBarrierByRegion<MemoryBarrierMask>);
static_assert(!CanCallMemoryBarrierByRegion<GLbitfield>);
// Note: requires-expressions with local declarations are not allowed in C++23
// simple requirements; use the parameter form (requires(T* p){...}) instead.
// =============================================================================

// glGetUniform<T>
static_assert(requires(float* p)        { glGetUniform(ProgramId{}, UniformLocation{}, p); });
static_assert(requires(int* p)          { glGetUniform(ProgramId{}, UniformLocation{}, p); });
static_assert(requires(unsigned int* p) { glGetUniform(ProgramId{}, UniformLocation{}, p); });

// glGetnUniform<T>
static_assert(requires(float* p)        { glGetnUniform(ProgramId{}, UniformLocation{}, 4, p); });
static_assert(requires(int* p)          { glGetnUniform(ProgramId{}, UniformLocation{}, 4, p); });
static_assert(requires(unsigned int* p) { glGetnUniform(ProgramId{}, UniformLocation{}, 4, p); });

// glTexParameter<T>
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureParameterSetter::MinFilter, 0.0f); });
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureParameterSetter::MinFilter, 0); });
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureMinFilter::Linear); });
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureMagFilter::Linear); });
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureWrapParameter::WrapS, TextureWrapMode::Repeat); });
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureCompareMode::None); });
static_assert(requires { glTexParameter(TextureTarget::Texture2D, TextureSwizzleParameter::SwizzleR, TextureSwizzle::Red); });

// glSamplerParameter<T>
static_assert(requires { glSamplerParameter(SamplerId{}, SamplerParameter::MinFilter, 0.0f); });
static_assert(requires { glSamplerParameter(SamplerId{}, SamplerParameter::MinFilter, 0); });
static_assert(requires { glSamplerParameter(SamplerId{}, TextureMinFilter::Linear); });
static_assert(requires { glSamplerParameter(SamplerId{}, SamplerWrapParameter::WrapS, TextureWrapMode::Repeat); });

// glClearBuffer<T>: each value type has its own legal buffer-target domain.
template<typename Buffer, typename Value>
concept ClearBufferCallable = requires(Buffer buffer, Value* value)
{
    glClearBuffer(buffer, 0, value);
};

template<typename Buffer>
concept LegacyClearBufferFiCallable = requires(Buffer buffer)
{
    glClearBufferfi(buffer, 0, 1.0f, 0);
};

static_assert(ClearBufferCallable<FloatClearBuffer, float>);
static_assert(ClearBufferCallable<SignedIntegerClearBuffer, int>);
static_assert(ClearBufferCallable<UnsignedIntegerClearBuffer, unsigned int>);
static_assert(!ClearBufferCallable<FloatClearBuffer, int>);
static_assert(!ClearBufferCallable<SignedIntegerClearBuffer, float>);
static_assert(!ClearBufferCallable<UnsignedIntegerClearBuffer, int>);
static_assert(!std::is_convertible_v<FloatClearBuffer, SignedIntegerClearBuffer>);
static_assert(!std::is_convertible_v<SignedIntegerClearBuffer, UnsignedIntegerClearBuffer>);
static_assert(requires { glClearBufferfi(1.0f, 0); });
static_assert(!LegacyClearBufferFiCallable<FloatClearBuffer>);
static_assert(!LegacyClearBufferFiCallable<SignedIntegerClearBuffer>);
static_assert(!LegacyClearBufferFiCallable<UnsignedIntegerClearBuffer>);

// glCopyImageSubData: all four texture/renderbuffer endpoint combinations.
static_assert(requires {
    glCopyImageSubData(
        TextureId{}, ImageCopyTextureTarget::Texture2D, 0, 0, 0, 0,
        TextureId{}, ImageCopyTextureTarget::Texture2DArray, 0, 0, 0, 0,
        1, 1, 1);
});
static_assert(requires {
    glCopyImageSubData(
        TextureId{}, ImageCopyTextureTarget::TextureCubeMap, 0, 0, 0, 0,
        RenderbufferId{}, 0, 0, 1, 1);
});
static_assert(requires {
    glCopyImageSubData(
        RenderbufferId{}, 0, 0,
        TextureId{}, ImageCopyTextureTarget::Texture3D, 0, 0, 0, 0,
        1, 1);
});
static_assert(requires {
    glCopyImageSubData(
        RenderbufferId{}, 0, 0,
        RenderbufferId{}, 0, 0, 1, 1);
});
// The existing easy-gl-style raw overload remains source-compatible.
static_assert(requires {
    glCopyImageSubData(
        GLuint{}, TextureTarget::Texture2D, 0, 0, 0, 0,
        GLuint{}, TextureTarget::Texture2D, 0, 0, 0, 0,
        1, 1, 1);
});
static_assert(!std::is_convertible_v<TextureTarget, ImageCopyTextureTarget>);

// glGetVertexAttrib<T>
static_assert(requires(float* v)        { glGetVertexAttrib(AttribLocation{}, VertexAttribParameter::CurrentVertexAttrib, v); });
static_assert(requires(int* v)          { glGetVertexAttrib(AttribLocation{}, VertexAttribParameter::CurrentVertexAttrib, v); });
static_assert(requires(unsigned int* v) { glGetVertexAttrib(AttribLocation{}, VertexAttribParameter::CurrentVertexAttrib, v); });

// =============================================================================
// I3 — Bitfield operators: operator| / & / ~ must return the original enum type
// =============================================================================

static_assert(std::is_same_v<decltype(ClearBufferBit::Color | ClearBufferBit::Depth),     ClearBufferBit>);
static_assert(std::is_same_v<decltype(ClearBufferBit::Color & ClearBufferBit::Depth),     ClearBufferBit>);
static_assert(std::is_same_v<decltype(~ClearBufferBit::Color),                             ClearBufferBit>);

static_assert(std::is_same_v<decltype(MapBufferAccessMask::Read | MapBufferAccessMask::Write),   MapBufferAccessMask>);
static_assert(std::is_same_v<decltype(ShaderStageMask::Vertex   | ShaderStageMask::Fragment),    ShaderStageMask>);
static_assert(std::is_same_v<decltype(MemoryBarrierMask::VertexAttribArray | MemoryBarrierMask::ElementArray), MemoryBarrierMask>);
static_assert(std::is_same_v<decltype(MemoryBarrierByRegionMask::AtomicCounter | MemoryBarrierByRegionMask::Framebuffer), MemoryBarrierByRegionMask>);
static_assert(std::is_same_v<decltype(ContextFlagMask::Debug | ContextFlagMask::RobustAccess),   ContextFlagMask>);
static_assert(static_cast<GLbitfield>(~ClearBufferBit::Color)
              == (GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

// =============================================================================
// I2 — Concept membership checks
// =============================================================================

// GlHandle: satisfied by handle structs, not plain scalars
static_assert(GlHandle<TextureId>);
static_assert(GlHandle<BufferId>);
static_assert(GlHandle<ShaderId>);
static_assert(GlHandle<ProgramId>);
static_assert(!GlHandle<int>);
static_assert(!GlHandle<float>);
static_assert(!GlHandle<GLuint>);  // raw uint has no .value member

// GlBitfield: satisfied by GLbitfield-backed enum classes
static_assert(GlBitfield<ClearBufferBit>);
static_assert(GlBitfield<MapBufferAccessMask>);
static_assert(GlBitfield<ShaderStageMask>);
static_assert(GlBitfield<MemoryBarrierMask>);
static_assert(GlBitfield<ContextFlagMask>);
static_assert(!GlBitfield<int>);
static_assert(!GlBitfield<TextureTarget>);
static_assert(!GlBitfield<PrimitiveType>);
static_assert(GlEnum<TextureTarget>);
static_assert(!GlEnum<ClearBufferBit>);

// SpanCompatible: trivially copyable + standard layout
static_assert(SpanCompatible<float>);
static_assert(SpanCompatible<int>);
static_assert(SpanCompatible<TextureId>);

// =============================================================================
// I4 — Handle type isolation: distinct handle types must not be interchangeable
// =============================================================================

// No implicit conversion between any two distinct handle types
static_assert(!std::is_convertible_v<ShaderId,   ProgramId>);
static_assert(!std::is_convertible_v<ProgramId,  ShaderId>);
static_assert(!std::is_convertible_v<TextureId,  BufferId>);
static_assert(!std::is_convertible_v<BufferId,   TextureId>);
static_assert(!std::is_convertible_v<TextureId,  FramebufferId>);
static_assert(!std::is_convertible_v<SamplerId,  VertexArrayId>);
static_assert(!std::is_convertible_v<QueryId,    TransformFeedbackId>);

// No implicit construction of one handle type from another
static_assert(!std::is_constructible_v<ShaderId,   ProgramId>);
static_assert(!std::is_constructible_v<TextureId,  BufferId>);
static_assert(!std::is_constructible_v<FramebufferId, RenderbufferId>);
static_assert(TextureId{7} == TextureId{7});
static_assert(!(TextureId{7} == TextureId{8}));

// UniformLocation and AttribLocation are distinct signed-location structs.
static_assert(!std::is_convertible_v<UniformLocation, AttribLocation>);
static_assert(!std::is_convertible_v<AttribLocation,  UniformLocation>);
static_assert(std::is_constructible_v<AttribLocation, GLint>);
static_assert(std::is_constructible_v<AttribLocation, GLuint>);

// The safe indexed-draw path exposes only the three valid GL index types.
static_assert(requires {
    glDrawElements(PrimitiveType::Triangles, 3, IndexType::UnsignedShort, nullptr);
});
static_assert(requires(char* name, GLsizei* length, GLint* size, UniformType* type) {
    glGetActiveAttrib(ProgramId{}, ActiveAttribIndex{}, 1, length, size, type, name);
});

// Plain GLuint does not satisfy GlHandle — it has no .value member
static_assert(!GlHandle<GLuint>);
static_assert(!GlHandle<unsigned int>);

// Handle types do not satisfy GlEnum or GlBitfield
static_assert(!GlEnum<TextureId>);
static_assert(!GlBitfield<BufferId>);

// =============================================================================
// I8 — Runtime: every to_string() overload returns a non-empty, non-"?" string
// =============================================================================

#include <iostream>
#include <string>

int main()
{
    int failed = 0;
    // Lambda accepts std::string_view; std::string temporaries are valid for
    // the duration of the call (destroyed after the full expression).
    auto check = [&](const char* label, std::string_view sv)
    {
        if (sv.empty() || sv == "?") {
            std::cerr << "FAIL: to_string(" << label << ") = '"
                      << sv << "'\n";
            ++failed;
        }
    };

    // Enum types
    check("ClearBufferBit::Color",                       to_string(ClearBufferBit::Color));
    check("PrimitiveType::Triangles",                    to_string(PrimitiveType::Triangles));
    check("BlendFactor::Zero",                           to_string(BlendFactor::Zero));
    check("BlendEquation::FuncAdd",                      to_string(BlendEquation::FuncAdd));
    check("BufferTarget::Array",                         to_string(BufferTarget::Array));
    check("BufferUsage::StaticDraw",                     to_string(BufferUsage::StaticDraw));
    check("BufferParameter::Size",                       to_string(BufferParameter::Size));
    check("BufferPointerParameter::MapPointer",          to_string(BufferPointerParameter::MapPointer));
    check("MapBufferAccessMask::Read",                   to_string(MapBufferAccessMask::Read));
    check("SampleMaskValue::None",                       to_string(SampleMaskValue::None));
    check("Capability::Blend",                           to_string(Capability::Blend));
    check("ErrorCode::NoError",                          to_string(ErrorCode::NoError));
    check("FrontFace::CW",                               to_string(FrontFace::CW));
    check("CullFace::Front",                             to_string(CullFace::Front));
    check("HintTarget::GenerateMipmap",                  to_string(HintTarget::GenerateMipmap));
    check("HintMode::DontCare",                          to_string(HintMode::DontCare));
    check("DataType::Float",                             to_string(DataType::Float));
    check("IndexType::UnsignedShort",                    to_string(IndexType::UnsignedShort));
    check("PixelFormat::Rgba",                           to_string(PixelFormat::Rgba));
    check("PixelType::UnsignedByte",                     to_string(PixelType::UnsignedByte));
    check("InternalFormat::Rgba8",                       to_string(InternalFormat::Rgba8));
    check("InternalFormat::Rgba16",                      to_string(InternalFormat::Rgba16));
    check("CompressedInternalFormat::R11Eac",            to_string(CompressedInternalFormat::R11Eac));
    check("StringName::Vendor",                          to_string(StringName::Vendor));
    check("IntegerName::MajorVersion",                   to_string(IntegerName::MajorVersion));
    check("ShaderType::Vertex",                          to_string(ShaderType::Vertex));
    check("ShaderStageMask::Vertex",                     to_string(ShaderStageMask::Vertex));
    check("ShaderParameter::ShaderType",                 to_string(ShaderParameter::ShaderType));
    check("PrecisionType::LowFloat",                     to_string(PrecisionType::LowFloat));
    check("ProgramParameter::DeleteStatus",              to_string(ProgramParameter::DeleteStatus));
    check("ProgramInterface::Uniform",                   to_string(ProgramInterface::Uniform));
    check("ProgramInterfaceParameter::ActiveResources",  to_string(ProgramInterfaceParameter::ActiveResources));
    check("ProgramResourceProperty::NameLength",         to_string(ProgramResourceProperty::NameLength));
    check("UniformType::Float",                          to_string(UniformType::Float));
    check("UniformBlockParameter::Binding",              to_string(UniformBlockParameter::Binding));
    check("UniformParameter::Type",                      to_string(UniformParameter::Type));
    check("TextureTarget::Texture2D",                    to_string(TextureTarget::Texture2D));
    check("TextureBindingTarget::Texture2D",             to_string(TextureBindingTarget::Texture2D));
    check("TextureParameter::MinFilter",                 to_string(TextureParameter::MinFilter));
    check("TextureWrapParameter::WrapS",                 to_string(TextureWrapParameter::WrapS));
    check("TextureSwizzleParameter::SwizzleR",           to_string(TextureSwizzleParameter::SwizzleR));
    check("SamplerParameter::MinFilter",                 to_string(SamplerParameter::MinFilter));
    check("SamplerWrapParameter::WrapS",                 to_string(SamplerWrapParameter::WrapS));
    check("TextureMinFilter::Nearest",                   to_string(TextureMinFilter::Nearest));
    check("TextureMagFilter::Nearest",                   to_string(TextureMagFilter::Nearest));
    check("BlitFilter::Nearest",                         to_string(BlitFilter::Nearest));
    check("TextureWrapMode::Repeat",                     to_string(TextureWrapMode::Repeat));
    check("TextureCompareMode::None",                    to_string(TextureCompareMode::None));
    check("TextureSwizzle::Red",                         to_string(TextureSwizzle::Red));
    check("TextureLevelParameter::Width",                to_string(TextureLevelParameter::Width));
    check("TextureUnit::Texture0",                       to_string(TextureUnit::Texture0));
    check("PixelStoreParam::PackAlignment",              to_string(PixelStoreParam::PackAlignment));
    check("CompareFunc::Never",                          to_string(CompareFunc::Never));
    check("StencilOp::Keep",                             to_string(StencilOp::Keep));
    check("FramebufferTarget::Framebuffer",              to_string(FramebufferTarget::Framebuffer));
    check("RenderbufferTarget::Renderbuffer",            to_string(RenderbufferTarget::Renderbuffer));
    check("ColorAttachment::Color0",                     to_string(ColorAttachment::Color0));
    check("FramebufferAttachment::None",                 to_string(FramebufferAttachment::None));
    check("FramebufferStatus::Complete",                 to_string(FramebufferStatus::Complete));
    check("FramebufferAttachmentParameter::ObjectType",  to_string(FramebufferAttachmentParameter::ObjectType));
    check("FramebufferDefaultParameter::Width",          to_string(FramebufferDefaultParameter::Width));
    check("RenderbufferParameter::Width",                to_string(RenderbufferParameter::Width));
    check("VertexAttribParameter::ArrayEnabled",         to_string(VertexAttribParameter::ArrayEnabled));
    check("TransformFeedbackBufferMode::InterleavedAttribs", to_string(TransformFeedbackBufferMode::InterleavedAttribs));
    check("TransformFeedbackTarget::TransformFeedback",  to_string(TransformFeedbackTarget::TransformFeedback));
    check("QueryTarget::AnySamplesPassed",               to_string(QueryTarget::AnySamplesPassed));
    check("QueryParameter::CurrentQuery",                to_string(QueryParameter::CurrentQuery));
    check("QueryObjectParameter::Result",                to_string(QueryObjectParameter::Result));
    check("SyncCondition::GpuCommandsComplete",          to_string(SyncCondition::GpuCommandsComplete));
    check("SyncParameter::ObjectType",                   to_string(SyncParameter::ObjectType));
    check("SyncWaitResult::AlreadySignaled",             to_string(SyncWaitResult::AlreadySignaled));
    check("SyncFlushMask::None",                         to_string(SyncFlushMask::None));
    check("ImageAccess::ReadOnly",                       to_string(ImageAccess::ReadOnly));
    check("MemoryBarrierMask::VertexAttribArray",        to_string(MemoryBarrierMask::VertexAttribArray));
    check("ContextFlagMask::Debug",                      to_string(ContextFlagMask::Debug));
    check("GraphicsResetStatus::NoError",                to_string(GraphicsResetStatus::NoError));
    check("ResetNotificationStrategy::NoResetNotification", to_string(ResetNotificationStrategy::NoResetNotification));
    check("DebugSource::DontCare",                       to_string(DebugSource::DontCare));
    check("DebugType::DontCare",                         to_string(DebugType::DontCare));
    check("DebugSeverity::DontCare",                     to_string(DebugSeverity::DontCare));
    // R23/R24: complete DebugObjectLabel domain (all 11 identifiers)
    check("DebugObjectLabel::Buffer",                    to_string(DebugObjectLabel::Buffer));
    check("DebugObjectLabel::Shader",                    to_string(DebugObjectLabel::Shader));
    check("DebugObjectLabel::Program",                   to_string(DebugObjectLabel::Program));
    check("DebugObjectLabel::VertexArray",               to_string(DebugObjectLabel::VertexArray));
    check("DebugObjectLabel::Query",                     to_string(DebugObjectLabel::Query));
    check("DebugObjectLabel::ProgramPipeline",           to_string(DebugObjectLabel::ProgramPipeline));
    check("DebugObjectLabel::Sampler",                   to_string(DebugObjectLabel::Sampler));
    check("DebugObjectLabel::Framebuffer",               to_string(DebugObjectLabel::Framebuffer));
    check("DebugObjectLabel::Renderbuffer",              to_string(DebugObjectLabel::Renderbuffer));
    check("DebugObjectLabel::Texture",                   to_string(DebugObjectLabel::Texture));
    check("DebugObjectLabel::TransformFeedback",         to_string(DebugObjectLabel::TransformFeedback));
    // R34/R35: TransformFeedbackPrimitive exact domain (Points, Lines, Triangles only)
    check("TransformFeedbackPrimitive::Points",          to_string(TransformFeedbackPrimitive::Points));
    check("TransformFeedbackPrimitive::Lines",           to_string(TransformFeedbackPrimitive::Lines));
    check("TransformFeedbackPrimitive::Triangles",       to_string(TransformFeedbackPrimitive::Triangles));
    check("ProvokingVertex::FirstVertex",                to_string(ProvokingVertex::FirstVertex));
    check("TessGenMode::Quads",                          to_string(TessGenMode::Quads));
    check("TessGenSpacing::Equal",                       to_string(TessGenSpacing::Equal));
    check("TessellationParameter::PatchVertices",        to_string(TessellationParameter::PatchVertices));
    check("GetParameter::Viewport",                      to_string(GetParameter::Viewport));
    check("FloatClearBuffer::Depth",                     to_string(FloatClearBuffer::Depth));
    check("SignedIntegerClearBuffer::Stencil",           to_string(SignedIntegerClearBuffer::Stencil));
    check("UnsignedIntegerClearBuffer::Color",           to_string(UnsignedIntegerClearBuffer::Color));
    check("ImageCopyTextureTarget::TextureCubeMap",      to_string(ImageCopyTextureTarget::TextureCubeMap));
    check("DrawBuffer::None",                            to_string(DrawBuffer::None));
    check("ReadBuffer::None",                            to_string(ReadBuffer::None));
    check("ShaderBinaryFormat(0)",                       to_string(static_cast<ShaderBinaryFormat>(0)));
    check("ProgramBinaryFormat(0)",                      to_string(static_cast<ProgramBinaryFormat>(0)));
    check("GetPointerParameter::DebugCallbackFunction",  to_string(GetPointerParameter::DebugCallbackFunction));
    check("MultisampleParameter::SamplePosition",        to_string(MultisampleParameter::SamplePosition));
    check("InternalFormatTarget::Renderbuffer",          to_string(InternalFormatTarget::Renderbuffer));
    check("InternalFormatParameter::Samples",            to_string(InternalFormatParameter::Samples));
    check("ProgramPipelineParameter::ActiveProgram",     to_string(ProgramPipelineParameter::ActiveProgram));
    check("SyncFlag::None",                              to_string(SyncFlag::None));

    // Handle types (to_string returns std::string, always non-empty)
    check("ShaderId{42}",            to_string(ShaderId{42}));
    check("ProgramId{1}",            to_string(ProgramId{1}));
    check("TextureId{7}",            to_string(TextureId{7}));
    check("BufferId{3}",             to_string(BufferId{3}));
    check("FramebufferId{2}",        to_string(FramebufferId{2}));
    check("RenderbufferId{5}",       to_string(RenderbufferId{5}));
    check("SamplerId{4}",            to_string(SamplerId{4}));
    check("VertexArrayId{6}",        to_string(VertexArrayId{6}));
    check("QueryId{8}",              to_string(QueryId{8}));
    check("TransformFeedbackId{9}",  to_string(TransformFeedbackId{9}));
    check("ProgramPipelineId{10}",   to_string(ProgramPipelineId{10}));
    check("UniformLocation{0}",      to_string(UniformLocation{0}));
    check("AttribLocation{0}",       to_string(AttribLocation{0}));
    check("ActiveAttribIndex{0}",    to_string(ActiveAttribIndex{0}));
    check("ImageUnit{0}",            to_string(ImageUnit{0}));

    if (AttribLocation{}.value != -1)
    {
        std::cerr << "FAIL: default AttribLocation must be -1\n";
        ++failed;
    }

    if (failed > 0)
        std::cerr << failed << " to_string test(s) failed.\n";
    return failed;
}
