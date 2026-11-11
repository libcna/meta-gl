#include "metagl/metagl.hpp"
#include "metagl/Debug.hpp"
#include "metagl/DesktopEsTier.hpp"

#include <functional>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>

namespace metagl::detail
{
    template <typename Enum>
    constexpr GLenum to_gl_enum(Enum value) noexcept
    {
        return static_cast<GLenum>(value);
    }

    template <typename Enum>
    constexpr GLbitfield to_gl_bitfield(Enum value) noexcept
    {
        return static_cast<GLbitfield>(value);
    }

    struct GlTable
    {
        using DesktopDepthRangeProc = void (GL_APIENTRY *)(double, double);
        using DesktopClearDepthProc = void (GL_APIENTRY *)(double);

        bool initialized = false;

        PFNGLENABLEPROC Enable = nullptr;
        PFNGLDISABLEPROC Disable = nullptr;
        PFNGLENABLEIPROC Enablei = nullptr;
        PFNGLDISABLEIPROC Disablei = nullptr;
        PFNGLISENABLEDPROC IsEnabled = nullptr;
        PFNGLISENABLEDIPROC IsEnabledi = nullptr;
        PFNGLBLENDFUNCPROC BlendFunc = nullptr;
        PFNGLBLENDFUNCSEPARATEPROC BlendFuncSeparate = nullptr;
        PFNGLBLENDFUNCIPROC BlendFunci = nullptr;
        PFNGLBLENDFUNCSEPARATEIPROC BlendFuncSeparatei = nullptr;
        PFNGLBLENDEQUATIONPROC BlendEquation = nullptr;
        PFNGLBLENDEQUATIONSEPARATEPROC BlendEquationSeparate = nullptr;
        PFNGLBLENDEQUATIONIPROC BlendEquationi = nullptr;
        PFNGLBLENDEQUATIONSEPARATEIPROC BlendEquationSeparatei = nullptr;
        PFNGLBLENDCOLORPROC BlendColor = nullptr;
        PFNGLBLENDBARRIERPROC BlendBarrier = nullptr;
        PFNGLCOLORMASKPROC ColorMask = nullptr;
        PFNGLCOLORMASKIPROC ColorMaski = nullptr;
        PFNGLDEPTHFUNCPROC DepthFunc = nullptr;
        PFNGLDEPTHMASKPROC DepthMask = nullptr;
        PFNGLDEPTHRANGEFPROC DepthRangef = nullptr;
        DesktopDepthRangeProc DesktopDepthRange = nullptr;
        PFNGLSTENCILFUNCPROC StencilFunc = nullptr;
        PFNGLSTENCILFUNCSEPARATEPROC StencilFuncSeparate = nullptr;
        PFNGLSTENCILOPPROC StencilOp = nullptr;
        PFNGLSTENCILOPSEPARATEPROC StencilOpSeparate = nullptr;
        PFNGLSTENCILMASKPROC StencilMask = nullptr;
        PFNGLSTENCILMASKSEPARATEPROC StencilMaskSeparate = nullptr;
        PFNGLSCISSORPROC Scissor = nullptr;
        PFNGLVIEWPORTPROC Viewport = nullptr;
        PFNGLCULLFACEPROC CullFace = nullptr;
        PFNGLFRONTFACEPROC FrontFace = nullptr;
        PFNGLLINEWIDTHPROC LineWidth = nullptr;
        PFNGLPOLYGONOFFSETPROC PolygonOffset = nullptr;
        PFNGLSAMPLECOVERAGEPROC SampleCoverage = nullptr;
        PFNGLSAMPLEMASKIPROC SampleMaski = nullptr;
        PFNGLMINSAMPLESHADINGPROC MinSampleShading = nullptr;
        PFNGLHINTPROC Hint = nullptr;
        PFNGLPIXELSTOREIPROC PixelStorei = nullptr;
        PFNGLFINISHPROC Finish = nullptr;
        PFNGLFLUSHPROC Flush = nullptr;
        PFNGLGETERRORPROC GetError = nullptr;
        PFNGLGETBOOLEANVPROC GetBooleanv = nullptr;
        PFNGLGETINTEGERVPROC GetIntegerv = nullptr;
        PFNGLGETFLOATVPROC GetFloatv = nullptr;
        PFNGLGETINTEGER64VPROC GetInteger64v = nullptr;
        PFNGLGETINTEGERI_VPROC GetIntegeri_v = nullptr;
        PFNGLGETINTEGER64I_VPROC GetInteger64i_v = nullptr;
        PFNGLGETBOOLEANI_VPROC GetBooleani_v = nullptr;
        PFNGLGETSTRINGPROC GetString = nullptr;
        PFNGLGETSTRINGIPROC GetStringi = nullptr;
        PFNGLGETPOINTERVPROC GetPointerv = nullptr;
        PFNGLGENBUFFERSPROC GenBuffers = nullptr;
        PFNGLDELETEBUFFERSPROC DeleteBuffers = nullptr;
        PFNGLBINDBUFFERPROC BindBuffer = nullptr;
        PFNGLBINDBUFFERBASEPROC BindBufferBase = nullptr;
        PFNGLBINDBUFFERRANGEPROC BindBufferRange = nullptr;
        PFNGLBUFFERDATAPROC BufferData = nullptr;
        PFNGLBUFFERSUBDATAPROC BufferSubData = nullptr;
        PFNGLCOPYBUFFERSUBDATAPROC CopyBufferSubData = nullptr;
        PFNGLMAPBUFFERRANGEPROC MapBufferRange = nullptr;
        PFNGLFLUSHMAPPEDBUFFERRANGEPROC FlushMappedBufferRange = nullptr;
        PFNGLUNMAPBUFFERPROC UnmapBuffer = nullptr;
        PFNGLISBUFFERPROC IsBuffer = nullptr;
        PFNGLGETBUFFERPARAMETERIVPROC GetBufferParameteriv = nullptr;
        PFNGLGETBUFFERPARAMETERI64VPROC GetBufferParameteri64v = nullptr;
        PFNGLGETBUFFERPOINTERVPROC GetBufferPointerv = nullptr;
        PFNGLGENVERTEXARRAYSPROC GenVertexArrays = nullptr;
        PFNGLDELETEVERTEXARRAYSPROC DeleteVertexArrays = nullptr;
        PFNGLBINDVERTEXARRAYPROC BindVertexArray = nullptr;
        PFNGLISVERTEXARRAYPROC IsVertexArray = nullptr;
        PFNGLENABLEVERTEXATTRIBARRAYPROC EnableVertexAttribArray = nullptr;
        PFNGLDISABLEVERTEXATTRIBARRAYPROC DisableVertexAttribArray = nullptr;
        PFNGLVERTEXATTRIBPOINTERPROC VertexAttribPointer = nullptr;
        PFNGLVERTEXATTRIBIPOINTERPROC VertexAttribIPointer = nullptr;
        PFNGLVERTEXATTRIBDIVISORPROC VertexAttribDivisor = nullptr;
        PFNGLVERTEXATTRIB1FPROC VertexAttrib1f = nullptr;
        PFNGLVERTEXATTRIB2FPROC VertexAttrib2f = nullptr;
        PFNGLVERTEXATTRIB3FPROC VertexAttrib3f = nullptr;
        PFNGLVERTEXATTRIB4FPROC VertexAttrib4f = nullptr;
        PFNGLVERTEXATTRIB1FVPROC VertexAttrib1fv = nullptr;
        PFNGLVERTEXATTRIB2FVPROC VertexAttrib2fv = nullptr;
        PFNGLVERTEXATTRIB3FVPROC VertexAttrib3fv = nullptr;
        PFNGLVERTEXATTRIB4FVPROC VertexAttrib4fv = nullptr;
        PFNGLVERTEXATTRIBI4IPROC VertexAttribI4i = nullptr;
        PFNGLVERTEXATTRIBI4UIPROC VertexAttribI4ui = nullptr;
        PFNGLVERTEXATTRIBI4IVPROC VertexAttribI4iv = nullptr;
        PFNGLVERTEXATTRIBI4UIVPROC VertexAttribI4uiv = nullptr;
        PFNGLGETVERTEXATTRIBFVPROC GetVertexAttribfv = nullptr;
        PFNGLGETVERTEXATTRIBIVPROC GetVertexAttribiv = nullptr;
        PFNGLGETVERTEXATTRIBIIVPROC GetVertexAttribIiv = nullptr;
        PFNGLGETVERTEXATTRIBIUIVPROC GetVertexAttribIuiv = nullptr;
        PFNGLGETVERTEXATTRIBPOINTERVPROC GetVertexAttribPointerv = nullptr;
        PFNGLVERTEXATTRIBFORMATPROC VertexAttribFormat = nullptr;
        PFNGLVERTEXATTRIBIFORMATPROC VertexAttribIFormat = nullptr;
        PFNGLVERTEXATTRIBBINDINGPROC VertexAttribBinding = nullptr;
        PFNGLBINDVERTEXBUFFERPROC BindVertexBuffer = nullptr;
        PFNGLVERTEXBINDINGDIVISORPROC VertexBindingDivisor = nullptr;
        PFNGLDRAWARRAYSPROC DrawArrays = nullptr;
        PFNGLDRAWARRAYSINSTANCEDPROC DrawArraysInstanced = nullptr;
        PFNGLDRAWARRAYSINDIRECTPROC DrawArraysIndirect = nullptr;
        PFNGLDRAWELEMENTSPROC DrawElements = nullptr;
        PFNGLDRAWELEMENTSINSTANCEDPROC DrawElementsInstanced = nullptr;
        PFNGLDRAWRANGEELEMENTSPROC DrawRangeElements = nullptr;
        PFNGLDRAWELEMENTSBASEVERTEXPROC DrawElementsBaseVertex = nullptr;
        PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC DrawElementsInstancedBaseVertex = nullptr;
        PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC DrawRangeElementsBaseVertex = nullptr;
        PFNGLDRAWELEMENTSINDIRECTPROC DrawElementsIndirect = nullptr;
        PFNGLDRAWBUFFERSPROC DrawBuffers = nullptr;
        PFNGLREADBUFFERPROC ReadBuffer = nullptr;
        PFNGLREADPIXELSPROC ReadPixels = nullptr;
        PFNGLREADNPIXELSPROC ReadnPixels = nullptr;
        PFNGLCLEARPROC Clear = nullptr;
        PFNGLCLEARCOLORPROC ClearColor = nullptr;
        PFNGLCLEARDEPTHFPROC ClearDepthf = nullptr;
        DesktopClearDepthProc DesktopClearDepth = nullptr;
        PFNGLCLEARSTENCILPROC ClearStencil = nullptr;
        PFNGLCLEARBUFFERFVPROC ClearBufferfv = nullptr;
        PFNGLCLEARBUFFERIVPROC ClearBufferiv = nullptr;
        PFNGLCLEARBUFFERUIVPROC ClearBufferuiv = nullptr;
        PFNGLCLEARBUFFERFIPROC ClearBufferfi = nullptr;
        PFNGLCREATESHADERPROC CreateShader = nullptr;
        PFNGLDELETESHADERPROC DeleteShader = nullptr;
        PFNGLSHADERSOURCEPROC ShaderSource = nullptr;
        PFNGLCOMPILESHADERPROC CompileShader = nullptr;
        PFNGLSHADERBINARYPROC ShaderBinary = nullptr;
        PFNGLRELEASESHADERCOMPILERPROC ReleaseShaderCompiler = nullptr;
        PFNGLGETSHADERIVPROC GetShaderiv = nullptr;
        PFNGLGETSHADERINFOLOGPROC GetShaderInfoLog = nullptr;
        PFNGLGETSHADERSOURCEPROC GetShaderSource = nullptr;
        PFNGLGETSHADERPRECISIONFORMATPROC GetShaderPrecisionFormat = nullptr;
        PFNGLISSHADERPROC IsShader = nullptr;
        PFNGLCREATEPROGRAMPROC CreateProgram = nullptr;
        PFNGLDELETEPROGRAMPROC DeleteProgram = nullptr;
        PFNGLATTACHSHADERPROC AttachShader = nullptr;
        PFNGLDETACHSHADERPROC DetachShader = nullptr;
        PFNGLLINKPROGRAMPROC LinkProgram = nullptr;
        PFNGLUSEPROGRAMPROC UseProgram = nullptr;
        PFNGLVALIDATEPROGRAMPROC ValidateProgram = nullptr;
        PFNGLGETPROGRAMIVPROC GetProgramiv = nullptr;
        PFNGLGETPROGRAMINFOLOGPROC GetProgramInfoLog = nullptr;
        PFNGLISPROGRAMPROC IsProgram = nullptr;
        PFNGLGETATTACHEDSHADERSPROC GetAttachedShaders = nullptr;
        PFNGLBINDATTRIBLOCATIONPROC BindAttribLocation = nullptr;
        PFNGLGETATTRIBLOCATIONPROC GetAttribLocation = nullptr;
        PFNGLGETACTIVEATTRIBPROC GetActiveAttrib = nullptr;
        PFNGLGETPROGRAMBINARYPROC GetProgramBinary = nullptr;
        PFNGLPROGRAMBINARYPROC ProgramBinary = nullptr;
        PFNGLPROGRAMPARAMETERIPROC ProgramParameteri = nullptr;
        PFNGLGETFRAGDATALOCATIONPROC GetFragDataLocation = nullptr;
        PFNGLGETPROGRAMINTERFACEIVPROC GetProgramInterfaceiv = nullptr;
        PFNGLGETPROGRAMRESOURCEINDEXPROC GetProgramResourceIndex = nullptr;
        PFNGLGETPROGRAMRESOURCENAMEPROC GetProgramResourceName = nullptr;
        PFNGLGETPROGRAMRESOURCEIVPROC GetProgramResourceiv = nullptr;
        PFNGLGETPROGRAMRESOURCELOCATIONPROC GetProgramResourceLocation = nullptr;
        PFNGLGETUNIFORMLOCATIONPROC GetUniformLocation = nullptr;
        PFNGLGETACTIVEUNIFORMPROC GetActiveUniform = nullptr;
        PFNGLGETACTIVEUNIFORMSIVPROC GetActiveUniformsiv = nullptr;
        PFNGLGETUNIFORMINDICESPROC GetUniformIndices = nullptr;
        PFNGLGETUNIFORMBLOCKINDEXPROC GetUniformBlockIndex = nullptr;
        PFNGLGETACTIVEUNIFORMBLOCKIVPROC GetActiveUniformBlockiv = nullptr;
        PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC GetActiveUniformBlockName = nullptr;
        PFNGLUNIFORMBLOCKBINDINGPROC UniformBlockBinding = nullptr;
        PFNGLUNIFORM1FPROC Uniform1f = nullptr;
        PFNGLUNIFORM2FPROC Uniform2f = nullptr;
        PFNGLUNIFORM3FPROC Uniform3f = nullptr;
        PFNGLUNIFORM4FPROC Uniform4f = nullptr;
        PFNGLUNIFORM1FVPROC Uniform1fv = nullptr;
        PFNGLUNIFORM2FVPROC Uniform2fv = nullptr;
        PFNGLUNIFORM3FVPROC Uniform3fv = nullptr;
        PFNGLUNIFORM4FVPROC Uniform4fv = nullptr;
        PFNGLUNIFORM1IPROC Uniform1i = nullptr;
        PFNGLUNIFORM2IPROC Uniform2i = nullptr;
        PFNGLUNIFORM3IPROC Uniform3i = nullptr;
        PFNGLUNIFORM4IPROC Uniform4i = nullptr;
        PFNGLUNIFORM1IVPROC Uniform1iv = nullptr;
        PFNGLUNIFORM2IVPROC Uniform2iv = nullptr;
        PFNGLUNIFORM3IVPROC Uniform3iv = nullptr;
        PFNGLUNIFORM4IVPROC Uniform4iv = nullptr;
        PFNGLUNIFORM1UIPROC Uniform1ui = nullptr;
        PFNGLUNIFORM2UIPROC Uniform2ui = nullptr;
        PFNGLUNIFORM3UIPROC Uniform3ui = nullptr;
        PFNGLUNIFORM4UIPROC Uniform4ui = nullptr;
        PFNGLUNIFORM1UIVPROC Uniform1uiv = nullptr;
        PFNGLUNIFORM2UIVPROC Uniform2uiv = nullptr;
        PFNGLUNIFORM3UIVPROC Uniform3uiv = nullptr;
        PFNGLUNIFORM4UIVPROC Uniform4uiv = nullptr;
        PFNGLUNIFORMMATRIX2FVPROC UniformMatrix2fv = nullptr;
        PFNGLUNIFORMMATRIX3FVPROC UniformMatrix3fv = nullptr;
        PFNGLUNIFORMMATRIX4FVPROC UniformMatrix4fv = nullptr;
        PFNGLUNIFORMMATRIX2X3FVPROC UniformMatrix2x3fv = nullptr;
        PFNGLUNIFORMMATRIX2X4FVPROC UniformMatrix2x4fv = nullptr;
        PFNGLUNIFORMMATRIX3X2FVPROC UniformMatrix3x2fv = nullptr;
        PFNGLUNIFORMMATRIX3X4FVPROC UniformMatrix3x4fv = nullptr;
        PFNGLUNIFORMMATRIX4X2FVPROC UniformMatrix4x2fv = nullptr;
        PFNGLUNIFORMMATRIX4X3FVPROC UniformMatrix4x3fv = nullptr;
        PFNGLGETUNIFORMFVPROC GetUniformfv = nullptr;
        PFNGLGETUNIFORMIVPROC GetUniformiv = nullptr;
        PFNGLGETUNIFORMUIVPROC GetUniformuiv = nullptr;
        PFNGLGETNUNIFORMFVPROC GetnUniformfv = nullptr;
        PFNGLGETNUNIFORMIVPROC GetnUniformiv = nullptr;
        PFNGLGETNUNIFORMUIVPROC GetnUniformuiv = nullptr;
        PFNGLPROGRAMUNIFORM1FPROC ProgramUniform1f = nullptr;
        PFNGLPROGRAMUNIFORM2FPROC ProgramUniform2f = nullptr;
        PFNGLPROGRAMUNIFORM3FPROC ProgramUniform3f = nullptr;
        PFNGLPROGRAMUNIFORM4FPROC ProgramUniform4f = nullptr;
        PFNGLPROGRAMUNIFORM1FVPROC ProgramUniform1fv = nullptr;
        PFNGLPROGRAMUNIFORM2FVPROC ProgramUniform2fv = nullptr;
        PFNGLPROGRAMUNIFORM3FVPROC ProgramUniform3fv = nullptr;
        PFNGLPROGRAMUNIFORM4FVPROC ProgramUniform4fv = nullptr;
        PFNGLPROGRAMUNIFORM1IPROC ProgramUniform1i = nullptr;
        PFNGLPROGRAMUNIFORM2IPROC ProgramUniform2i = nullptr;
        PFNGLPROGRAMUNIFORM3IPROC ProgramUniform3i = nullptr;
        PFNGLPROGRAMUNIFORM4IPROC ProgramUniform4i = nullptr;
        PFNGLPROGRAMUNIFORM1IVPROC ProgramUniform1iv = nullptr;
        PFNGLPROGRAMUNIFORM2IVPROC ProgramUniform2iv = nullptr;
        PFNGLPROGRAMUNIFORM3IVPROC ProgramUniform3iv = nullptr;
        PFNGLPROGRAMUNIFORM4IVPROC ProgramUniform4iv = nullptr;
        PFNGLPROGRAMUNIFORM1UIPROC ProgramUniform1ui = nullptr;
        PFNGLPROGRAMUNIFORM2UIPROC ProgramUniform2ui = nullptr;
        PFNGLPROGRAMUNIFORM3UIPROC ProgramUniform3ui = nullptr;
        PFNGLPROGRAMUNIFORM4UIPROC ProgramUniform4ui = nullptr;
        PFNGLPROGRAMUNIFORM1UIVPROC ProgramUniform1uiv = nullptr;
        PFNGLPROGRAMUNIFORM2UIVPROC ProgramUniform2uiv = nullptr;
        PFNGLPROGRAMUNIFORM3UIVPROC ProgramUniform3uiv = nullptr;
        PFNGLPROGRAMUNIFORM4UIVPROC ProgramUniform4uiv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX2FVPROC ProgramUniformMatrix2fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX3FVPROC ProgramUniformMatrix3fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX4FVPROC ProgramUniformMatrix4fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC ProgramUniformMatrix2x3fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC ProgramUniformMatrix2x4fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC ProgramUniformMatrix3x2fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC ProgramUniformMatrix3x4fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC ProgramUniformMatrix4x2fv = nullptr;
        PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC ProgramUniformMatrix4x3fv = nullptr;
        PFNGLGENTEXTURESPROC GenTextures = nullptr;
        PFNGLDELETETEXTURESPROC DeleteTextures = nullptr;
        PFNGLBINDTEXTUREPROC BindTexture = nullptr;
        PFNGLACTIVETEXTUREPROC ActiveTexture = nullptr;
        PFNGLISTEXTUREPROC IsTexture = nullptr;
        PFNGLTEXIMAGE2DPROC TexImage2D = nullptr;
        PFNGLTEXIMAGE3DPROC TexImage3D = nullptr;
        PFNGLTEXSUBIMAGE2DPROC TexSubImage2D = nullptr;
        PFNGLTEXSUBIMAGE3DPROC TexSubImage3D = nullptr;
        PFNGLTEXSTORAGE2DPROC TexStorage2D = nullptr;
        PFNGLTEXSTORAGE3DPROC TexStorage3D = nullptr;
        PFNGLTEXSTORAGE2DMULTISAMPLEPROC TexStorage2DMultisample = nullptr;
        PFNGLTEXSTORAGE3DMULTISAMPLEPROC TexStorage3DMultisample = nullptr;
        PFNGLCOMPRESSEDTEXIMAGE2DPROC CompressedTexImage2D = nullptr;
        PFNGLCOMPRESSEDTEXIMAGE3DPROC CompressedTexImage3D = nullptr;
        PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC CompressedTexSubImage2D = nullptr;
        PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC CompressedTexSubImage3D = nullptr;
        PFNGLCOPYTEXIMAGE2DPROC CopyTexImage2D = nullptr;
        PFNGLCOPYTEXSUBIMAGE2DPROC CopyTexSubImage2D = nullptr;
        PFNGLCOPYTEXSUBIMAGE3DPROC CopyTexSubImage3D = nullptr;
        PFNGLCOPYIMAGESUBDATAPROC CopyImageSubData = nullptr;
        PFNGLGENERATEMIPMAPPROC GenerateMipmap = nullptr;
        PFNGLTEXPARAMETERFPROC TexParameterf = nullptr;
        PFNGLTEXPARAMETERIPROC TexParameteri = nullptr;
        PFNGLTEXPARAMETERFVPROC TexParameterfv = nullptr;
        PFNGLTEXPARAMETERIVPROC TexParameteriv = nullptr;
        PFNGLTEXPARAMETERIIVPROC TexParameterIiv = nullptr;
        PFNGLTEXPARAMETERIUIVPROC TexParameterIuiv = nullptr;
        PFNGLGETTEXPARAMETERFVPROC GetTexParameterfv = nullptr;
        PFNGLGETTEXPARAMETERIVPROC GetTexParameteriv = nullptr;
        PFNGLGETTEXPARAMETERIIVPROC GetTexParameterIiv = nullptr;
        PFNGLGETTEXPARAMETERIUIVPROC GetTexParameterIuiv = nullptr;
        PFNGLGETTEXLEVELPARAMETERIVPROC GetTexLevelParameteriv = nullptr;
        PFNGLGETTEXLEVELPARAMETERFVPROC GetTexLevelParameterfv = nullptr;
        PFNGLTEXBUFFERPROC TexBuffer = nullptr;
        PFNGLTEXBUFFERRANGEPROC TexBufferRange = nullptr;
        PFNGLGETMULTISAMPLEFVPROC GetMultisamplefv = nullptr;
        PFNGLGETINTERNALFORMATIVPROC GetInternalformativ = nullptr;
        PFNGLBINDIMAGETEXTUREPROC BindImageTexture = nullptr;
        PFNGLGENSAMPLERSPROC GenSamplers = nullptr;
        PFNGLDELETESAMPLERSPROC DeleteSamplers = nullptr;
        PFNGLBINDSAMPLERPROC BindSampler = nullptr;
        PFNGLISSAMPLERPROC IsSampler = nullptr;
        PFNGLSAMPLERPARAMETERFPROC SamplerParameterf = nullptr;
        PFNGLSAMPLERPARAMETERIPROC SamplerParameteri = nullptr;
        PFNGLSAMPLERPARAMETERFVPROC SamplerParameterfv = nullptr;
        PFNGLSAMPLERPARAMETERIVPROC SamplerParameteriv = nullptr;
        PFNGLSAMPLERPARAMETERIIVPROC SamplerParameterIiv = nullptr;
        PFNGLSAMPLERPARAMETERIUIVPROC SamplerParameterIuiv = nullptr;
        PFNGLGETSAMPLERPARAMETERFVPROC GetSamplerParameterfv = nullptr;
        PFNGLGETSAMPLERPARAMETERIVPROC GetSamplerParameteriv = nullptr;
        PFNGLGETSAMPLERPARAMETERIIVPROC GetSamplerParameterIiv = nullptr;
        PFNGLGETSAMPLERPARAMETERIUIVPROC GetSamplerParameterIuiv = nullptr;
        PFNGLGENFRAMEBUFFERSPROC GenFramebuffers = nullptr;
        PFNGLDELETEFRAMEBUFFERSPROC DeleteFramebuffers = nullptr;
        PFNGLBINDFRAMEBUFFERPROC BindFramebuffer = nullptr;
        PFNGLISFRAMEBUFFERPROC IsFramebuffer = nullptr;
        PFNGLCHECKFRAMEBUFFERSTATUSPROC CheckFramebufferStatus = nullptr;
        PFNGLFRAMEBUFFERTEXTURE2DPROC FramebufferTexture2D = nullptr;
        PFNGLFRAMEBUFFERTEXTURELAYERPROC FramebufferTextureLayer = nullptr;
        PFNGLFRAMEBUFFERTEXTUREPROC FramebufferTexture = nullptr;
        PFNGLFRAMEBUFFERRENDERBUFFERPROC FramebufferRenderbuffer = nullptr;
        PFNGLFRAMEBUFFERPARAMETERIPROC FramebufferParameteri = nullptr;
        PFNGLGETFRAMEBUFFERPARAMETERIVPROC GetFramebufferParameteriv = nullptr;
        PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC GetFramebufferAttachmentParameteriv = nullptr;
        PFNGLBLITFRAMEBUFFERPROC BlitFramebuffer = nullptr;
        PFNGLINVALIDATEFRAMEBUFFERPROC InvalidateFramebuffer = nullptr;
        PFNGLINVALIDATESUBFRAMEBUFFERPROC InvalidateSubFramebuffer = nullptr;
        PFNGLGENRENDERBUFFERSPROC GenRenderbuffers = nullptr;
        PFNGLDELETERENDERBUFFERSPROC DeleteRenderbuffers = nullptr;
        PFNGLBINDRENDERBUFFERPROC BindRenderbuffer = nullptr;
        PFNGLISRENDERBUFFERPROC IsRenderbuffer = nullptr;
        PFNGLRENDERBUFFERSTORAGEPROC RenderbufferStorage = nullptr;
        PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC RenderbufferStorageMultisample = nullptr;
        PFNGLGETRENDERBUFFERPARAMETERIVPROC GetRenderbufferParameteriv = nullptr;
        PFNGLGENTRANSFORMFEEDBACKSPROC GenTransformFeedbacks = nullptr;
        PFNGLDELETETRANSFORMFEEDBACKSPROC DeleteTransformFeedbacks = nullptr;
        PFNGLBINDTRANSFORMFEEDBACKPROC BindTransformFeedback = nullptr;
        PFNGLISTRANSFORMFEEDBACKPROC IsTransformFeedback = nullptr;
        PFNGLBEGINTRANSFORMFEEDBACKPROC BeginTransformFeedback = nullptr;
        PFNGLENDTRANSFORMFEEDBACKPROC EndTransformFeedback = nullptr;
        PFNGLPAUSETRANSFORMFEEDBACKPROC PauseTransformFeedback = nullptr;
        PFNGLRESUMETRANSFORMFEEDBACKPROC ResumeTransformFeedback = nullptr;
        PFNGLTRANSFORMFEEDBACKVARYINGSPROC TransformFeedbackVaryings = nullptr;
        PFNGLGETTRANSFORMFEEDBACKVARYINGPROC GetTransformFeedbackVarying = nullptr;
        PFNGLGENQUERIESPROC GenQueries = nullptr;
        PFNGLDELETEQUERIESPROC DeleteQueries = nullptr;
        PFNGLISQUERYPROC IsQuery = nullptr;
        PFNGLBEGINQUERYPROC BeginQuery = nullptr;
        PFNGLENDQUERYPROC EndQuery = nullptr;
        PFNGLGETQUERYIVPROC GetQueryiv = nullptr;
        PFNGLGETQUERYOBJECTUIVPROC GetQueryObjectuiv = nullptr;
        PFNGLFENCESYNCPROC FenceSync = nullptr;
        PFNGLDELETESYNCPROC DeleteSync = nullptr;
        PFNGLISSYNCPROC IsSync = nullptr;
        PFNGLCLIENTWAITSYNCPROC ClientWaitSync = nullptr;
        PFNGLWAITSYNCPROC WaitSync = nullptr;
        PFNGLGETSYNCIVPROC GetSynciv = nullptr;
        PFNGLDISPATCHCOMPUTEPROC DispatchCompute = nullptr;
        PFNGLDISPATCHCOMPUTEINDIRECTPROC DispatchComputeIndirect = nullptr;
        PFNGLMEMORYBARRIERPROC MemoryBarrier = nullptr;
        PFNGLMEMORYBARRIERBYREGIONPROC MemoryBarrierByRegion = nullptr;
        PFNGLGENPROGRAMPIPELINESPROC GenProgramPipelines = nullptr;
        PFNGLDELETEPROGRAMPIPELINESPROC DeleteProgramPipelines = nullptr;
        PFNGLBINDPROGRAMPIPELINEPROC BindProgramPipeline = nullptr;
        PFNGLISPROGRAMPIPELINEPROC IsProgramPipeline = nullptr;
        PFNGLUSEPROGRAMSTAGESPROC UseProgramStages = nullptr;
        PFNGLACTIVESHADERPROGRAMPROC ActiveShaderProgram = nullptr;
        PFNGLCREATESHADERPROGRAMVPROC CreateShaderProgramv = nullptr;
        PFNGLVALIDATEPROGRAMPIPELINEPROC ValidateProgramPipeline = nullptr;
        PFNGLGETPROGRAMPIPELINEIVPROC GetProgramPipelineiv = nullptr;
        PFNGLGETPROGRAMPIPELINEINFOLOGPROC GetProgramPipelineInfoLog = nullptr;
        PFNGLPATCHPARAMETERIPROC PatchParameteri = nullptr;
        PFNGLPRIMITIVEBOUNDINGBOXPROC PrimitiveBoundingBox = nullptr;
        PFNGLDEBUGMESSAGECALLBACKPROC DebugMessageCallback = nullptr;
        PFNGLDEBUGMESSAGECONTROLPROC DebugMessageControl = nullptr;
        PFNGLDEBUGMESSAGEINSERTPROC DebugMessageInsert = nullptr;
        PFNGLGETDEBUGMESSAGELOGPROC GetDebugMessageLog = nullptr;
        PFNGLPUSHDEBUGGROUPPROC PushDebugGroup = nullptr;
        PFNGLPOPDEBUGGROUPPROC PopDebugGroup = nullptr;
        PFNGLOBJECTLABELPROC ObjectLabel = nullptr;
        PFNGLOBJECTPTRLABELPROC ObjectPtrLabel = nullptr;
        PFNGLGETOBJECTLABELPROC GetObjectLabel = nullptr;
        PFNGLGETOBJECTPTRLABELPROC GetObjectPtrLabel = nullptr;
        PFNGLGETGRAPHICSRESETSTATUSPROC GetGraphicsResetStatus = nullptr;
    };

    thread_local GlTable g_gl;

    // Forward declarations — implemented in Context.cpp.
    void UpdateContextAfterLoad();
    void ResetContextAfterLoadFailure() noexcept;

    struct TransparentStringHash
    {
        using is_transparent = void;

        [[nodiscard]] std::size_t operator()(std::string_view value) const noexcept
        {
            return std::hash<std::string_view>{}(value);
        }
    };

    // Maps each GL function name to whether it was successfully loaded.
    // Transparent lookup keeps IsFunctionAvailable noexcept without creating
    // an allocating std::string temporary.
    thread_local std::unordered_map<std::string, bool,
        TransparentStringHash, std::equal_to<>> g_function_availability;

    // R76 — internal desktop OpenGL ES-tier diagnostic (see DesktopEsTier.hpp).
    // Reset alongside the rest of the loader/context state on any failure or
    // context loss so it never reports a stale tier.
    thread_local DesktopEsTier g_desktop_es_tier = DesktopEsTier::None;

    void InvalidateFunctionsAfterContextLoss() noexcept
    {
        g_gl.initialized = false;
        g_function_availability.clear();
        g_desktop_es_tier = DesktopEsTier::None;
#ifdef METAGLDEBUG
        metagl::debug::set_get_error_fn(nullptr);
#endif
    }

    template <typename T>
    static T load(GlGetProcAddressFn loader, const char* name)
    {
        void* ptr = loader(name);
        g_function_availability[name] = (ptr != nullptr);
        return reinterpret_cast<T>(ptr);
    }

    // ---------------------------------------------------------------------------
    // Version-aware validation helpers
    // ---------------------------------------------------------------------------

    enum class RequiredApiLevel
    {
        Invalid,
        Gles20,
        Gles30,
        Gles31,
        Gles32,
        Webgl1,
        Webgl2,
        Desktop33,
        // R76 — desktop tiers analogous to native ES, checked internally
        // against the same gles30/31/32_required_names lists. Never returned
        // by detect_version(); only used by detect_desktop_es_tier() below.
        Desktop33Es30,
        Desktop33Es31,
        Desktop33Es32
    };

    struct DetectedVersion
    {
        RequiredApiLevel level = RequiredApiLevel::Invalid;
        int major = 0;
        int minor = 0;
    };

    static bool parse_major_minor(
        std::string_view version, std::size_t offset,
        int& major, int& minor) noexcept
    {
        while (offset < version.size() && version[offset] == ' ')
            ++offset;

        const auto major_begin = offset;
        major = 0;
        while (offset < version.size()
            && version[offset] >= '0' && version[offset] <= '9')
        {
            const int digit = version[offset] - '0';
            if (major > (99 - digit) / 10)
                return false;
            major = major * 10 + digit;
            ++offset;
        }
        if (offset == major_begin
            || offset >= version.size() || version[offset] != '.')
            return false;

        ++offset;
        const auto minor_begin = offset;
        minor = 0;
        while (offset < version.size()
            && version[offset] >= '0' && version[offset] <= '9')
        {
            const int digit = version[offset] - '0';
            if (minor > (99 - digit) / 10)
                return false;
            minor = minor * 10 + digit;
            ++offset;
        }
        return offset != minor_begin;
    }

    static DetectedVersion detect_version(const GlTable& gl) noexcept
    {
        if (!gl.GetString) return {};
        const auto* raw = gl.GetString(GL_VERSION);
        if (!raw) return {};

        const std::string_view version(
            reinterpret_cast<const char*>(raw));
        if (version.empty()) return {};

        DetectedVersion detected{};
        const auto webgl = version.find("WebGL");
        if (webgl != std::string_view::npos)
        {
            if (!parse_major_minor(
                    version, webgl + std::string_view("WebGL").size(),
                    detected.major, detected.minor))
                return {};

            if (detected.major == 1)
                detected.level = RequiredApiLevel::Webgl1;
            else if (detected.major == 2)
                detected.level = RequiredApiLevel::Webgl2;
            return detected;
        }

        const auto gles = version.find("OpenGL ES");
        if (gles != std::string_view::npos)
        {
            if (!parse_major_minor(
                    version, gles + std::string_view("OpenGL ES").size(),
                    detected.major, detected.minor))
                return {};

            if (detected.major == 2 && detected.minor == 0)
                detected.level = RequiredApiLevel::Gles20;
            else if (detected.major == 3 && detected.minor == 0)
                detected.level = RequiredApiLevel::Gles30;
            else if (detected.major == 3 && detected.minor == 1)
                detected.level = RequiredApiLevel::Gles31;
            else if (detected.major == 3 && detected.minor == 2)
                detected.level = RequiredApiLevel::Gles32;
            return detected;
        }

        if (!parse_major_minor(version, 0, detected.major, detected.minor))
            return {};
        if (detected.major > 3
            || (detected.major == 3 && detected.minor >= 3))
            detected.level = RequiredApiLevel::Desktop33;
        return detected;
    }

    /// Core common subset required for GLES 2.0 or desktop OpenGL 3.3+.
    static bool minimum_loaded(const GlTable& gl, bool desktop)
    {
        return
            // State management
            gl.Enable != nullptr &&
            gl.Disable != nullptr &&
            gl.BlendFunc != nullptr &&
            gl.BlendEquation != nullptr &&
            gl.ColorMask != nullptr &&
            gl.DepthFunc != nullptr &&
            gl.DepthMask != nullptr &&
            (gl.DepthRangef != nullptr
                || (desktop && gl.DesktopDepthRange != nullptr)) &&
            gl.StencilFunc != nullptr &&
            gl.StencilFuncSeparate != nullptr &&
            gl.StencilOp != nullptr &&
            gl.StencilOpSeparate != nullptr &&
            gl.StencilMask != nullptr &&
            gl.StencilMaskSeparate != nullptr &&
            gl.Scissor != nullptr &&
            gl.Viewport != nullptr &&
            gl.CullFace != nullptr &&
            gl.FrontFace != nullptr &&
            gl.LineWidth != nullptr &&
            gl.PolygonOffset != nullptr &&
            gl.SampleCoverage != nullptr &&
            gl.Hint != nullptr &&
            gl.PixelStorei != nullptr &&
            gl.Finish != nullptr &&
            gl.Flush != nullptr &&
            // Queries
            gl.GetError != nullptr &&
            gl.GetBooleanv != nullptr &&
            gl.GetIntegerv != nullptr &&
            gl.GetFloatv != nullptr &&
            gl.GetString != nullptr &&
            // Buffers
            gl.GenBuffers != nullptr &&
            gl.DeleteBuffers != nullptr &&
            gl.BindBuffer != nullptr &&
            gl.BufferData != nullptr &&
            gl.BufferSubData != nullptr &&
            gl.IsBuffer != nullptr &&
            gl.GetBufferParameteriv != nullptr &&
            // Vertex attributes
            gl.EnableVertexAttribArray != nullptr &&
            gl.DisableVertexAttribArray != nullptr &&
            gl.VertexAttribPointer != nullptr &&
            gl.VertexAttrib1f != nullptr &&
            gl.VertexAttrib2f != nullptr &&
            gl.VertexAttrib3f != nullptr &&
            gl.VertexAttrib4f != nullptr &&
            gl.VertexAttrib1fv != nullptr &&
            gl.VertexAttrib2fv != nullptr &&
            gl.VertexAttrib3fv != nullptr &&
            gl.VertexAttrib4fv != nullptr &&
            gl.GetVertexAttribfv != nullptr &&
            gl.GetVertexAttribiv != nullptr &&
            gl.GetVertexAttribPointerv != nullptr &&
            // Drawing
            gl.DrawArrays != nullptr &&
            gl.DrawElements != nullptr &&
            gl.ReadPixels != nullptr &&
            // Clear
            gl.Clear != nullptr &&
            gl.ClearColor != nullptr &&
            (gl.ClearDepthf != nullptr
                || (desktop && gl.DesktopClearDepth != nullptr)) &&
            gl.ClearStencil != nullptr &&
            // State queries
            gl.IsEnabled != nullptr &&
            // Blend (GLES2 core extended blend functions)
            gl.BlendColor != nullptr &&
            gl.BlendEquationSeparate != nullptr &&
            gl.BlendFuncSeparate != nullptr &&
            // Shaders
            gl.CreateShader != nullptr &&
            gl.DeleteShader != nullptr &&
            gl.ShaderSource != nullptr &&
            gl.CompileShader != nullptr &&
            gl.GetShaderiv != nullptr &&
            gl.GetShaderInfoLog != nullptr &&
            gl.GetShaderSource != nullptr &&
            (desktop || gl.GetShaderPrecisionFormat != nullptr) &&
            gl.IsShader != nullptr &&
            (desktop || gl.ShaderBinary != nullptr) &&
            (desktop || gl.ReleaseShaderCompiler != nullptr) &&
            // Programs
            gl.CreateProgram != nullptr &&
            gl.DeleteProgram != nullptr &&
            gl.AttachShader != nullptr &&
            gl.DetachShader != nullptr &&
            gl.GetAttachedShaders != nullptr &&
            gl.LinkProgram != nullptr &&
            gl.UseProgram != nullptr &&
            gl.ValidateProgram != nullptr &&
            gl.GetProgramiv != nullptr &&
            gl.GetProgramInfoLog != nullptr &&
            gl.IsProgram != nullptr &&
            gl.BindAttribLocation != nullptr &&
            gl.GetAttribLocation != nullptr &&
            gl.GetActiveAttrib != nullptr &&
            gl.GetUniformLocation != nullptr &&
            gl.GetActiveUniform != nullptr &&
            gl.Uniform1f != nullptr &&
            gl.Uniform2f != nullptr &&
            gl.Uniform3f != nullptr &&
            gl.Uniform4f != nullptr &&
            gl.Uniform1fv != nullptr &&
            gl.Uniform2fv != nullptr &&
            gl.Uniform3fv != nullptr &&
            gl.Uniform4fv != nullptr &&
            gl.Uniform1i != nullptr &&
            gl.Uniform2i != nullptr &&
            gl.Uniform3i != nullptr &&
            gl.Uniform4i != nullptr &&
            gl.Uniform1iv != nullptr &&
            gl.Uniform2iv != nullptr &&
            gl.Uniform3iv != nullptr &&
            gl.Uniform4iv != nullptr &&
            gl.UniformMatrix2fv != nullptr &&
            gl.UniformMatrix3fv != nullptr &&
            gl.UniformMatrix4fv != nullptr &&
            gl.GetUniformfv != nullptr &&
            gl.GetUniformiv != nullptr &&
            // Textures
            gl.GenTextures != nullptr &&
            gl.DeleteTextures != nullptr &&
            gl.BindTexture != nullptr &&
            gl.ActiveTexture != nullptr &&
            gl.IsTexture != nullptr &&
            gl.TexImage2D != nullptr &&
            gl.TexSubImage2D != nullptr &&
            gl.CompressedTexImage2D != nullptr &&
            gl.CompressedTexSubImage2D != nullptr &&
            gl.CopyTexImage2D != nullptr &&
            gl.CopyTexSubImage2D != nullptr &&
            gl.GenerateMipmap != nullptr &&
            gl.TexParameterf != nullptr &&
            gl.TexParameteri != nullptr &&
            gl.TexParameterfv != nullptr &&
            gl.TexParameteriv != nullptr &&
            gl.GetTexParameterfv != nullptr &&
            gl.GetTexParameteriv != nullptr &&
            // Framebuffers
            gl.GenFramebuffers != nullptr &&
            gl.DeleteFramebuffers != nullptr &&
            gl.BindFramebuffer != nullptr &&
            gl.IsFramebuffer != nullptr &&
            gl.CheckFramebufferStatus != nullptr &&
            gl.FramebufferTexture2D != nullptr &&
            gl.FramebufferRenderbuffer != nullptr &&
            gl.GetFramebufferAttachmentParameteriv != nullptr &&
            // Renderbuffers
            gl.GenRenderbuffers != nullptr &&
            gl.DeleteRenderbuffers != nullptr &&
            gl.BindRenderbuffer != nullptr &&
            gl.IsRenderbuffer != nullptr &&
            gl.RenderbufferStorage != nullptr &&
            gl.GetRenderbufferParameteriv != nullptr;
    }

#include "RequiredFunctions.inc"

    template <std::size_t N>
    static bool required_names_loaded(
        const std::string_view (&names)[N]) noexcept
    {
        for (const auto name : names)
        {
            const auto it = g_function_availability.find(name);
            if (it == g_function_availability.end() || !it->second)
                return false;
        }
        return true;
    }

    static bool required_version_loaded(
        const GlTable& gl, RequiredApiLevel level) noexcept
    {
        if (level == RequiredApiLevel::Invalid)
            return false;

        const bool desktop = level == RequiredApiLevel::Desktop33;
        if (!minimum_loaded(gl, desktop))
            return false;

        if (desktop)
            return gl.GetStringi != nullptr;
        if (level == RequiredApiLevel::Webgl1)
            return true;
        if (level == RequiredApiLevel::Webgl2)
            return gl.GetStringi != nullptr;

        if (level >= RequiredApiLevel::Gles30
            && !required_names_loaded(gles30_required_names))
            return false;
        if (level >= RequiredApiLevel::Gles31
            && !required_names_loaded(gles31_required_names))
            return false;
        if (level >= RequiredApiLevel::Gles32
            && !required_names_loaded(gles32_required_names))
            return false;
        return true;
    }

    // R77 — queries GL_EXTENSIONS directly via gl.GetStringi/gl.GetIntegerv.
    // Used only while detecting the R76 desktop ES tier, which runs before
    // UpdateContextAfterLoad() populates the public Capabilities::extensions
    // list, so that list is not available here yet.
    static bool has_extension_via_gl(
        const GlTable& gl, std::string_view name) noexcept
    {
        if (!gl.GetStringi || !gl.GetIntegerv)
            return false;

        GLint count = 0;
        gl.GetIntegerv(GL_NUM_EXTENSIONS, &count);
        for (GLint i = 0; i < count; ++i)
        {
            const auto* raw = gl.GetStringi(
                GL_EXTENSIONS, static_cast<GLuint>(i));
            if (raw && name == reinterpret_cast<const char*>(raw))
                return true;
        }
        return false;
    }

    // R76 — desktop-only diagnostic tier, checked only after a desktop 3.3+
    // context has already passed required_version_loaded()'s ES-2.0-
    // equivalent baseline gate. Reuses the same mandatory-entry-point lists
    // as native OpenGL ES; GL_ARB_ES3_1/3_2_compatibility (R77) is a fast
    // additional signal that stands in for missing individual entry points,
    // replacing any per-function ARB extension fallback.
    static RequiredApiLevel detect_desktop_es_tier(const GlTable& gl) noexcept
    {
        if (!required_names_loaded(gles30_required_names))
            return RequiredApiLevel::Desktop33;

        const bool es31_signal =
            required_names_loaded(gles31_required_names)
            || has_extension_via_gl(gl, "GL_ARB_ES3_1_compatibility")
            || has_extension_via_gl(gl, "GL_ARB_ES3_2_compatibility");
        if (!es31_signal)
            return RequiredApiLevel::Desktop33Es30;

        const bool es32_signal =
            required_names_loaded(gles32_required_names)
            || has_extension_via_gl(gl, "GL_ARB_ES3_2_compatibility");
        if (!es32_signal)
            return RequiredApiLevel::Desktop33Es31;

        return RequiredApiLevel::Desktop33Es32;
    }

    static DesktopEsTier to_desktop_es_tier(RequiredApiLevel level) noexcept
    {
        switch (level)
        {
            case RequiredApiLevel::Desktop33Es30: return DesktopEsTier::Es30;
            case RequiredApiLevel::Desktop33Es31: return DesktopEsTier::Es31;
            case RequiredApiLevel::Desktop33Es32: return DesktopEsTier::Es32;
            default:                              return DesktopEsTier::Baseline;
        }
    }

    /// Legacy helper kept for diagnostics — checks all 358 GLES 3.2 functions.
    /// Not used by Initialize(); provided for completeness and testing.
    static bool all_loaded(const GlTable& gl)
    {
        return
            gl.Enable != nullptr &&
            gl.Disable != nullptr &&
            gl.Enablei != nullptr &&
            gl.Disablei != nullptr &&
            gl.IsEnabled != nullptr &&
            gl.IsEnabledi != nullptr &&
            gl.BlendFunc != nullptr &&
            gl.BlendFuncSeparate != nullptr &&
            gl.BlendFunci != nullptr &&
            gl.BlendFuncSeparatei != nullptr &&
            gl.BlendEquation != nullptr &&
            gl.BlendEquationSeparate != nullptr &&
            gl.BlendEquationi != nullptr &&
            gl.BlendEquationSeparatei != nullptr &&
            gl.BlendColor != nullptr &&
            gl.BlendBarrier != nullptr &&
            gl.ColorMask != nullptr &&
            gl.ColorMaski != nullptr &&
            gl.DepthFunc != nullptr &&
            gl.DepthMask != nullptr &&
            gl.DepthRangef != nullptr &&
            gl.StencilFunc != nullptr &&
            gl.StencilFuncSeparate != nullptr &&
            gl.StencilOp != nullptr &&
            gl.StencilOpSeparate != nullptr &&
            gl.StencilMask != nullptr &&
            gl.StencilMaskSeparate != nullptr &&
            gl.Scissor != nullptr &&
            gl.Viewport != nullptr &&
            gl.CullFace != nullptr &&
            gl.FrontFace != nullptr &&
            gl.LineWidth != nullptr &&
            gl.PolygonOffset != nullptr &&
            gl.SampleCoverage != nullptr &&
            gl.SampleMaski != nullptr &&
            gl.MinSampleShading != nullptr &&
            gl.Hint != nullptr &&
            gl.PixelStorei != nullptr &&
            gl.Finish != nullptr &&
            gl.Flush != nullptr &&
            gl.GetError != nullptr &&
            gl.GetBooleanv != nullptr &&
            gl.GetIntegerv != nullptr &&
            gl.GetFloatv != nullptr &&
            gl.GetInteger64v != nullptr &&
            gl.GetIntegeri_v != nullptr &&
            gl.GetInteger64i_v != nullptr &&
            gl.GetBooleani_v != nullptr &&
            gl.GetString != nullptr &&
            gl.GetStringi != nullptr &&
            gl.GetPointerv != nullptr &&
            gl.GenBuffers != nullptr &&
            gl.DeleteBuffers != nullptr &&
            gl.BindBuffer != nullptr &&
            gl.BindBufferBase != nullptr &&
            gl.BindBufferRange != nullptr &&
            gl.BufferData != nullptr &&
            gl.BufferSubData != nullptr &&
            gl.CopyBufferSubData != nullptr &&
            gl.MapBufferRange != nullptr &&
            gl.FlushMappedBufferRange != nullptr &&
            gl.UnmapBuffer != nullptr &&
            gl.IsBuffer != nullptr &&
            gl.GetBufferParameteriv != nullptr &&
            gl.GetBufferParameteri64v != nullptr &&
            gl.GetBufferPointerv != nullptr &&
            gl.GenVertexArrays != nullptr &&
            gl.DeleteVertexArrays != nullptr &&
            gl.BindVertexArray != nullptr &&
            gl.IsVertexArray != nullptr &&
            gl.EnableVertexAttribArray != nullptr &&
            gl.DisableVertexAttribArray != nullptr &&
            gl.VertexAttribPointer != nullptr &&
            gl.VertexAttribIPointer != nullptr &&
            gl.VertexAttribDivisor != nullptr &&
            gl.VertexAttrib1f != nullptr &&
            gl.VertexAttrib2f != nullptr &&
            gl.VertexAttrib3f != nullptr &&
            gl.VertexAttrib4f != nullptr &&
            gl.VertexAttrib1fv != nullptr &&
            gl.VertexAttrib2fv != nullptr &&
            gl.VertexAttrib3fv != nullptr &&
            gl.VertexAttrib4fv != nullptr &&
            gl.VertexAttribI4i != nullptr &&
            gl.VertexAttribI4ui != nullptr &&
            gl.VertexAttribI4iv != nullptr &&
            gl.VertexAttribI4uiv != nullptr &&
            gl.GetVertexAttribfv != nullptr &&
            gl.GetVertexAttribiv != nullptr &&
            gl.GetVertexAttribIiv != nullptr &&
            gl.GetVertexAttribIuiv != nullptr &&
            gl.GetVertexAttribPointerv != nullptr &&
            gl.VertexAttribFormat != nullptr &&
            gl.VertexAttribIFormat != nullptr &&
            gl.VertexAttribBinding != nullptr &&
            gl.BindVertexBuffer != nullptr &&
            gl.VertexBindingDivisor != nullptr &&
            gl.DrawArrays != nullptr &&
            gl.DrawArraysInstanced != nullptr &&
            gl.DrawArraysIndirect != nullptr &&
            gl.DrawElements != nullptr &&
            gl.DrawElementsInstanced != nullptr &&
            gl.DrawRangeElements != nullptr &&
            gl.DrawElementsBaseVertex != nullptr &&
            gl.DrawElementsInstancedBaseVertex != nullptr &&
            gl.DrawRangeElementsBaseVertex != nullptr &&
            gl.DrawElementsIndirect != nullptr &&
            gl.DrawBuffers != nullptr &&
            gl.ReadBuffer != nullptr &&
            gl.ReadPixels != nullptr &&
            gl.ReadnPixels != nullptr &&
            gl.Clear != nullptr &&
            gl.ClearColor != nullptr &&
            gl.ClearDepthf != nullptr &&
            gl.ClearStencil != nullptr &&
            gl.ClearBufferfv != nullptr &&
            gl.ClearBufferiv != nullptr &&
            gl.ClearBufferuiv != nullptr &&
            gl.ClearBufferfi != nullptr &&
            gl.CreateShader != nullptr &&
            gl.DeleteShader != nullptr &&
            gl.ShaderSource != nullptr &&
            gl.CompileShader != nullptr &&
            gl.ShaderBinary != nullptr &&
            gl.ReleaseShaderCompiler != nullptr &&
            gl.GetShaderiv != nullptr &&
            gl.GetShaderInfoLog != nullptr &&
            gl.GetShaderSource != nullptr &&
            gl.GetShaderPrecisionFormat != nullptr &&
            gl.IsShader != nullptr &&
            gl.CreateProgram != nullptr &&
            gl.DeleteProgram != nullptr &&
            gl.AttachShader != nullptr &&
            gl.DetachShader != nullptr &&
            gl.LinkProgram != nullptr &&
            gl.UseProgram != nullptr &&
            gl.ValidateProgram != nullptr &&
            gl.GetProgramiv != nullptr &&
            gl.GetProgramInfoLog != nullptr &&
            gl.IsProgram != nullptr &&
            gl.GetAttachedShaders != nullptr &&
            gl.BindAttribLocation != nullptr &&
            gl.GetAttribLocation != nullptr &&
            gl.GetActiveAttrib != nullptr &&
            gl.GetProgramBinary != nullptr &&
            gl.ProgramBinary != nullptr &&
            gl.ProgramParameteri != nullptr &&
            gl.GetFragDataLocation != nullptr &&
            gl.GetProgramInterfaceiv != nullptr &&
            gl.GetProgramResourceIndex != nullptr &&
            gl.GetProgramResourceName != nullptr &&
            gl.GetProgramResourceiv != nullptr &&
            gl.GetProgramResourceLocation != nullptr &&
            gl.GetUniformLocation != nullptr &&
            gl.GetActiveUniform != nullptr &&
            gl.GetActiveUniformsiv != nullptr &&
            gl.GetUniformIndices != nullptr &&
            gl.GetUniformBlockIndex != nullptr &&
            gl.GetActiveUniformBlockiv != nullptr &&
            gl.GetActiveUniformBlockName != nullptr &&
            gl.UniformBlockBinding != nullptr &&
            gl.Uniform1f != nullptr &&
            gl.Uniform2f != nullptr &&
            gl.Uniform3f != nullptr &&
            gl.Uniform4f != nullptr &&
            gl.Uniform1fv != nullptr &&
            gl.Uniform2fv != nullptr &&
            gl.Uniform3fv != nullptr &&
            gl.Uniform4fv != nullptr &&
            gl.Uniform1i != nullptr &&
            gl.Uniform2i != nullptr &&
            gl.Uniform3i != nullptr &&
            gl.Uniform4i != nullptr &&
            gl.Uniform1iv != nullptr &&
            gl.Uniform2iv != nullptr &&
            gl.Uniform3iv != nullptr &&
            gl.Uniform4iv != nullptr &&
            gl.Uniform1ui != nullptr &&
            gl.Uniform2ui != nullptr &&
            gl.Uniform3ui != nullptr &&
            gl.Uniform4ui != nullptr &&
            gl.Uniform1uiv != nullptr &&
            gl.Uniform2uiv != nullptr &&
            gl.Uniform3uiv != nullptr &&
            gl.Uniform4uiv != nullptr &&
            gl.UniformMatrix2fv != nullptr &&
            gl.UniformMatrix3fv != nullptr &&
            gl.UniformMatrix4fv != nullptr &&
            gl.UniformMatrix2x3fv != nullptr &&
            gl.UniformMatrix2x4fv != nullptr &&
            gl.UniformMatrix3x2fv != nullptr &&
            gl.UniformMatrix3x4fv != nullptr &&
            gl.UniformMatrix4x2fv != nullptr &&
            gl.UniformMatrix4x3fv != nullptr &&
            gl.GetUniformfv != nullptr &&
            gl.GetUniformiv != nullptr &&
            gl.GetUniformuiv != nullptr &&
            gl.GetnUniformfv != nullptr &&
            gl.GetnUniformiv != nullptr &&
            gl.GetnUniformuiv != nullptr &&
            gl.ProgramUniform1f != nullptr &&
            gl.ProgramUniform2f != nullptr &&
            gl.ProgramUniform3f != nullptr &&
            gl.ProgramUniform4f != nullptr &&
            gl.ProgramUniform1fv != nullptr &&
            gl.ProgramUniform2fv != nullptr &&
            gl.ProgramUniform3fv != nullptr &&
            gl.ProgramUniform4fv != nullptr &&
            gl.ProgramUniform1i != nullptr &&
            gl.ProgramUniform2i != nullptr &&
            gl.ProgramUniform3i != nullptr &&
            gl.ProgramUniform4i != nullptr &&
            gl.ProgramUniform1iv != nullptr &&
            gl.ProgramUniform2iv != nullptr &&
            gl.ProgramUniform3iv != nullptr &&
            gl.ProgramUniform4iv != nullptr &&
            gl.ProgramUniform1ui != nullptr &&
            gl.ProgramUniform2ui != nullptr &&
            gl.ProgramUniform3ui != nullptr &&
            gl.ProgramUniform4ui != nullptr &&
            gl.ProgramUniform1uiv != nullptr &&
            gl.ProgramUniform2uiv != nullptr &&
            gl.ProgramUniform3uiv != nullptr &&
            gl.ProgramUniform4uiv != nullptr &&
            gl.ProgramUniformMatrix2fv != nullptr &&
            gl.ProgramUniformMatrix3fv != nullptr &&
            gl.ProgramUniformMatrix4fv != nullptr &&
            gl.ProgramUniformMatrix2x3fv != nullptr &&
            gl.ProgramUniformMatrix2x4fv != nullptr &&
            gl.ProgramUniformMatrix3x2fv != nullptr &&
            gl.ProgramUniformMatrix3x4fv != nullptr &&
            gl.ProgramUniformMatrix4x2fv != nullptr &&
            gl.ProgramUniformMatrix4x3fv != nullptr &&
            gl.GenTextures != nullptr &&
            gl.DeleteTextures != nullptr &&
            gl.BindTexture != nullptr &&
            gl.ActiveTexture != nullptr &&
            gl.IsTexture != nullptr &&
            gl.TexImage2D != nullptr &&
            gl.TexImage3D != nullptr &&
            gl.TexSubImage2D != nullptr &&
            gl.TexSubImage3D != nullptr &&
            gl.TexStorage2D != nullptr &&
            gl.TexStorage3D != nullptr &&
            gl.TexStorage2DMultisample != nullptr &&
            gl.TexStorage3DMultisample != nullptr &&
            gl.CompressedTexImage2D != nullptr &&
            gl.CompressedTexImage3D != nullptr &&
            gl.CompressedTexSubImage2D != nullptr &&
            gl.CompressedTexSubImage3D != nullptr &&
            gl.CopyTexImage2D != nullptr &&
            gl.CopyTexSubImage2D != nullptr &&
            gl.CopyTexSubImage3D != nullptr &&
            gl.CopyImageSubData != nullptr &&
            gl.GenerateMipmap != nullptr &&
            gl.TexParameterf != nullptr &&
            gl.TexParameteri != nullptr &&
            gl.TexParameterfv != nullptr &&
            gl.TexParameteriv != nullptr &&
            gl.TexParameterIiv != nullptr &&
            gl.TexParameterIuiv != nullptr &&
            gl.GetTexParameterfv != nullptr &&
            gl.GetTexParameteriv != nullptr &&
            gl.GetTexParameterIiv != nullptr &&
            gl.GetTexParameterIuiv != nullptr &&
            gl.GetTexLevelParameteriv != nullptr &&
            gl.GetTexLevelParameterfv != nullptr &&
            gl.TexBuffer != nullptr &&
            gl.TexBufferRange != nullptr &&
            gl.GetMultisamplefv != nullptr &&
            gl.GetInternalformativ != nullptr &&
            gl.BindImageTexture != nullptr &&
            gl.GenSamplers != nullptr &&
            gl.DeleteSamplers != nullptr &&
            gl.BindSampler != nullptr &&
            gl.IsSampler != nullptr &&
            gl.SamplerParameterf != nullptr &&
            gl.SamplerParameteri != nullptr &&
            gl.SamplerParameterfv != nullptr &&
            gl.SamplerParameteriv != nullptr &&
            gl.SamplerParameterIiv != nullptr &&
            gl.SamplerParameterIuiv != nullptr &&
            gl.GetSamplerParameterfv != nullptr &&
            gl.GetSamplerParameteriv != nullptr &&
            gl.GetSamplerParameterIiv != nullptr &&
            gl.GetSamplerParameterIuiv != nullptr &&
            gl.GenFramebuffers != nullptr &&
            gl.DeleteFramebuffers != nullptr &&
            gl.BindFramebuffer != nullptr &&
            gl.IsFramebuffer != nullptr &&
            gl.CheckFramebufferStatus != nullptr &&
            gl.FramebufferTexture2D != nullptr &&
            gl.FramebufferTextureLayer != nullptr &&
            gl.FramebufferTexture != nullptr &&
            gl.FramebufferRenderbuffer != nullptr &&
            gl.FramebufferParameteri != nullptr &&
            gl.GetFramebufferParameteriv != nullptr &&
            gl.GetFramebufferAttachmentParameteriv != nullptr &&
            gl.BlitFramebuffer != nullptr &&
            gl.InvalidateFramebuffer != nullptr &&
            gl.InvalidateSubFramebuffer != nullptr &&
            gl.GenRenderbuffers != nullptr &&
            gl.DeleteRenderbuffers != nullptr &&
            gl.BindRenderbuffer != nullptr &&
            gl.IsRenderbuffer != nullptr &&
            gl.RenderbufferStorage != nullptr &&
            gl.RenderbufferStorageMultisample != nullptr &&
            gl.GetRenderbufferParameteriv != nullptr &&
            gl.GenTransformFeedbacks != nullptr &&
            gl.DeleteTransformFeedbacks != nullptr &&
            gl.BindTransformFeedback != nullptr &&
            gl.IsTransformFeedback != nullptr &&
            gl.BeginTransformFeedback != nullptr &&
            gl.EndTransformFeedback != nullptr &&
            gl.PauseTransformFeedback != nullptr &&
            gl.ResumeTransformFeedback != nullptr &&
            gl.TransformFeedbackVaryings != nullptr &&
            gl.GetTransformFeedbackVarying != nullptr &&
            gl.GenQueries != nullptr &&
            gl.DeleteQueries != nullptr &&
            gl.IsQuery != nullptr &&
            gl.BeginQuery != nullptr &&
            gl.EndQuery != nullptr &&
            gl.GetQueryiv != nullptr &&
            gl.GetQueryObjectuiv != nullptr &&
            gl.FenceSync != nullptr &&
            gl.DeleteSync != nullptr &&
            gl.IsSync != nullptr &&
            gl.ClientWaitSync != nullptr &&
            gl.WaitSync != nullptr &&
            gl.GetSynciv != nullptr &&
            gl.DispatchCompute != nullptr &&
            gl.DispatchComputeIndirect != nullptr &&
            gl.MemoryBarrier != nullptr &&
            gl.MemoryBarrierByRegion != nullptr &&
            gl.GenProgramPipelines != nullptr &&
            gl.DeleteProgramPipelines != nullptr &&
            gl.BindProgramPipeline != nullptr &&
            gl.IsProgramPipeline != nullptr &&
            gl.UseProgramStages != nullptr &&
            gl.ActiveShaderProgram != nullptr &&
            gl.CreateShaderProgramv != nullptr &&
            gl.ValidateProgramPipeline != nullptr &&
            gl.GetProgramPipelineiv != nullptr &&
            gl.GetProgramPipelineInfoLog != nullptr &&
            gl.PatchParameteri != nullptr &&
            gl.PrimitiveBoundingBox != nullptr &&
            gl.DebugMessageCallback != nullptr &&
            gl.DebugMessageControl != nullptr &&
            gl.DebugMessageInsert != nullptr &&
            gl.GetDebugMessageLog != nullptr &&
            gl.PushDebugGroup != nullptr &&
            gl.PopDebugGroup != nullptr &&
            gl.ObjectLabel != nullptr &&
            gl.ObjectPtrLabel != nullptr &&
            gl.GetObjectLabel != nullptr &&
            gl.GetObjectPtrLabel != nullptr &&
            gl.GetGraphicsResetStatus != nullptr;
    }
}

namespace metagl
{
    bool Initialize(GlGetProcAddressFn loader)
    {
        if (loader == nullptr) return false;

        // Hide the previous context before asking an external loader for a new
        // candidate. The candidate table below is published only after its
        // declared API/version has passed the complete mandatory-entry check.
        detail::g_gl.initialized = false;
        detail::g_function_availability.clear();
        detail::g_desktop_es_tier = detail::DesktopEsTier::None;
        detail::ResetContextAfterLoadFailure();
#ifdef METAGLDEBUG
        metagl::debug::set_get_error_fn(nullptr);
#endif

        detail::GlTable candidate{};
        auto& gl = candidate;

        // Bootstrap only what is needed to identify and validate the context.
        gl.GetString = detail::load<PFNGLGETSTRINGPROC>(
            loader, "glGetString");
        gl.GetIntegerv = detail::load<PFNGLGETINTEGERVPROC>(
            loader, "glGetIntegerv");
        gl.GetError = detail::load<PFNGLGETERRORPROC>(
            loader, "glGetError");

        if (!gl.GetString || !gl.GetIntegerv || !gl.GetError)
        {
            detail::g_function_availability.clear();
            return false;
        }

        const auto detected = detail::detect_version(gl);
        if (detected.level == detail::RequiredApiLevel::Invalid)
        {
            detail::g_function_availability.clear();
            return false;
        }

        gl.Enable = detail::load<PFNGLENABLEPROC>(loader, "glEnable");
        gl.Disable = detail::load<PFNGLDISABLEPROC>(loader, "glDisable");
        gl.Enablei = detail::load<PFNGLENABLEIPROC>(loader, "glEnablei");
        gl.Disablei = detail::load<PFNGLDISABLEIPROC>(loader, "glDisablei");
        gl.IsEnabled = detail::load<PFNGLISENABLEDPROC>(loader, "glIsEnabled");
        gl.IsEnabledi = detail::load<PFNGLISENABLEDIPROC>(loader, "glIsEnabledi");
        gl.BlendFunc = detail::load<PFNGLBLENDFUNCPROC>(loader, "glBlendFunc");
        gl.BlendFuncSeparate = detail::load<PFNGLBLENDFUNCSEPARATEPROC>(loader, "glBlendFuncSeparate");
        gl.BlendFunci = detail::load<PFNGLBLENDFUNCIPROC>(loader, "glBlendFunci");
        gl.BlendFuncSeparatei = detail::load<PFNGLBLENDFUNCSEPARATEIPROC>(loader, "glBlendFuncSeparatei");
        gl.BlendEquation = detail::load<PFNGLBLENDEQUATIONPROC>(loader, "glBlendEquation");
        gl.BlendEquationSeparate = detail::load<PFNGLBLENDEQUATIONSEPARATEPROC>(loader, "glBlendEquationSeparate");
        gl.BlendEquationi = detail::load<PFNGLBLENDEQUATIONIPROC>(loader, "glBlendEquationi");
        gl.BlendEquationSeparatei = detail::load<PFNGLBLENDEQUATIONSEPARATEIPROC>(loader, "glBlendEquationSeparatei");
        gl.BlendColor = detail::load<PFNGLBLENDCOLORPROC>(loader, "glBlendColor");
        gl.BlendBarrier = detail::load<PFNGLBLENDBARRIERPROC>(loader, "glBlendBarrier");
        gl.ColorMask = detail::load<PFNGLCOLORMASKPROC>(loader, "glColorMask");
        gl.ColorMaski = detail::load<PFNGLCOLORMASKIPROC>(loader, "glColorMaski");
        gl.DepthFunc = detail::load<PFNGLDEPTHFUNCPROC>(loader, "glDepthFunc");
        gl.DepthMask = detail::load<PFNGLDEPTHMASKPROC>(loader, "glDepthMask");
        gl.DepthRangef = detail::load<PFNGLDEPTHRANGEFPROC>(loader, "glDepthRangef");
        gl.DesktopDepthRange = gl.DepthRangef
            ? nullptr
            : detail::load<detail::GlTable::DesktopDepthRangeProc>(
                loader, "glDepthRange");
        gl.StencilFunc = detail::load<PFNGLSTENCILFUNCPROC>(loader, "glStencilFunc");
        gl.StencilFuncSeparate = detail::load<PFNGLSTENCILFUNCSEPARATEPROC>(loader, "glStencilFuncSeparate");
        gl.StencilOp = detail::load<PFNGLSTENCILOPPROC>(loader, "glStencilOp");
        gl.StencilOpSeparate = detail::load<PFNGLSTENCILOPSEPARATEPROC>(loader, "glStencilOpSeparate");
        gl.StencilMask = detail::load<PFNGLSTENCILMASKPROC>(loader, "glStencilMask");
        gl.StencilMaskSeparate = detail::load<PFNGLSTENCILMASKSEPARATEPROC>(loader, "glStencilMaskSeparate");
        gl.Scissor = detail::load<PFNGLSCISSORPROC>(loader, "glScissor");
        gl.Viewport = detail::load<PFNGLVIEWPORTPROC>(loader, "glViewport");
        gl.CullFace = detail::load<PFNGLCULLFACEPROC>(loader, "glCullFace");
        gl.FrontFace = detail::load<PFNGLFRONTFACEPROC>(loader, "glFrontFace");
        gl.LineWidth = detail::load<PFNGLLINEWIDTHPROC>(loader, "glLineWidth");
        gl.PolygonOffset = detail::load<PFNGLPOLYGONOFFSETPROC>(loader, "glPolygonOffset");
        gl.SampleCoverage = detail::load<PFNGLSAMPLECOVERAGEPROC>(loader, "glSampleCoverage");
        gl.SampleMaski = detail::load<PFNGLSAMPLEMASKIPROC>(loader, "glSampleMaski");
        gl.MinSampleShading = detail::load<PFNGLMINSAMPLESHADINGPROC>(loader, "glMinSampleShading");
        gl.Hint = detail::load<PFNGLHINTPROC>(loader, "glHint");
        gl.PixelStorei = detail::load<PFNGLPIXELSTOREIPROC>(loader, "glPixelStorei");
        gl.Finish = detail::load<PFNGLFINISHPROC>(loader, "glFinish");
        gl.Flush = detail::load<PFNGLFLUSHPROC>(loader, "glFlush");
        gl.GetBooleanv = detail::load<PFNGLGETBOOLEANVPROC>(loader, "glGetBooleanv");
        gl.GetFloatv = detail::load<PFNGLGETFLOATVPROC>(loader, "glGetFloatv");
        gl.GetInteger64v = detail::load<PFNGLGETINTEGER64VPROC>(loader, "glGetInteger64v");
        gl.GetIntegeri_v = detail::load<PFNGLGETINTEGERI_VPROC>(loader, "glGetIntegeri_v");
        gl.GetInteger64i_v = detail::load<PFNGLGETINTEGER64I_VPROC>(loader, "glGetInteger64i_v");
        gl.GetBooleani_v = detail::load<PFNGLGETBOOLEANI_VPROC>(loader, "glGetBooleani_v");
        gl.GetStringi = detail::load<PFNGLGETSTRINGIPROC>(loader, "glGetStringi");
        gl.GetPointerv = detail::load<PFNGLGETPOINTERVPROC>(loader, "glGetPointerv");
        gl.GenBuffers = detail::load<PFNGLGENBUFFERSPROC>(loader, "glGenBuffers");
        gl.DeleteBuffers = detail::load<PFNGLDELETEBUFFERSPROC>(loader, "glDeleteBuffers");
        gl.BindBuffer = detail::load<PFNGLBINDBUFFERPROC>(loader, "glBindBuffer");
        gl.BindBufferBase = detail::load<PFNGLBINDBUFFERBASEPROC>(loader, "glBindBufferBase");
        gl.BindBufferRange = detail::load<PFNGLBINDBUFFERRANGEPROC>(loader, "glBindBufferRange");
        gl.BufferData = detail::load<PFNGLBUFFERDATAPROC>(loader, "glBufferData");
        gl.BufferSubData = detail::load<PFNGLBUFFERSUBDATAPROC>(loader, "glBufferSubData");
        gl.CopyBufferSubData = detail::load<PFNGLCOPYBUFFERSUBDATAPROC>(loader, "glCopyBufferSubData");
        gl.MapBufferRange = detail::load<PFNGLMAPBUFFERRANGEPROC>(loader, "glMapBufferRange");
        gl.FlushMappedBufferRange = detail::load<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>(loader, "glFlushMappedBufferRange");
        gl.UnmapBuffer = detail::load<PFNGLUNMAPBUFFERPROC>(loader, "glUnmapBuffer");
        gl.IsBuffer = detail::load<PFNGLISBUFFERPROC>(loader, "glIsBuffer");
        gl.GetBufferParameteriv = detail::load<PFNGLGETBUFFERPARAMETERIVPROC>(loader, "glGetBufferParameteriv");
        gl.GetBufferParameteri64v = detail::load<PFNGLGETBUFFERPARAMETERI64VPROC>(loader, "glGetBufferParameteri64v");
        gl.GetBufferPointerv = detail::load<PFNGLGETBUFFERPOINTERVPROC>(loader, "glGetBufferPointerv");
        gl.GenVertexArrays = detail::load<PFNGLGENVERTEXARRAYSPROC>(loader, "glGenVertexArrays");
        gl.DeleteVertexArrays = detail::load<PFNGLDELETEVERTEXARRAYSPROC>(loader, "glDeleteVertexArrays");
        gl.BindVertexArray = detail::load<PFNGLBINDVERTEXARRAYPROC>(loader, "glBindVertexArray");
        gl.IsVertexArray = detail::load<PFNGLISVERTEXARRAYPROC>(loader, "glIsVertexArray");
        gl.EnableVertexAttribArray = detail::load<PFNGLENABLEVERTEXATTRIBARRAYPROC>(loader, "glEnableVertexAttribArray");
        gl.DisableVertexAttribArray = detail::load<PFNGLDISABLEVERTEXATTRIBARRAYPROC>(loader, "glDisableVertexAttribArray");
        gl.VertexAttribPointer = detail::load<PFNGLVERTEXATTRIBPOINTERPROC>(loader, "glVertexAttribPointer");
        gl.VertexAttribIPointer = detail::load<PFNGLVERTEXATTRIBIPOINTERPROC>(loader, "glVertexAttribIPointer");
        gl.VertexAttribDivisor = detail::load<PFNGLVERTEXATTRIBDIVISORPROC>(loader, "glVertexAttribDivisor");
        gl.VertexAttrib1f = detail::load<PFNGLVERTEXATTRIB1FPROC>(loader, "glVertexAttrib1f");
        gl.VertexAttrib2f = detail::load<PFNGLVERTEXATTRIB2FPROC>(loader, "glVertexAttrib2f");
        gl.VertexAttrib3f = detail::load<PFNGLVERTEXATTRIB3FPROC>(loader, "glVertexAttrib3f");
        gl.VertexAttrib4f = detail::load<PFNGLVERTEXATTRIB4FPROC>(loader, "glVertexAttrib4f");
        gl.VertexAttrib1fv = detail::load<PFNGLVERTEXATTRIB1FVPROC>(loader, "glVertexAttrib1fv");
        gl.VertexAttrib2fv = detail::load<PFNGLVERTEXATTRIB2FVPROC>(loader, "glVertexAttrib2fv");
        gl.VertexAttrib3fv = detail::load<PFNGLVERTEXATTRIB3FVPROC>(loader, "glVertexAttrib3fv");
        gl.VertexAttrib4fv = detail::load<PFNGLVERTEXATTRIB4FVPROC>(loader, "glVertexAttrib4fv");
        gl.VertexAttribI4i = detail::load<PFNGLVERTEXATTRIBI4IPROC>(loader, "glVertexAttribI4i");
        gl.VertexAttribI4ui = detail::load<PFNGLVERTEXATTRIBI4UIPROC>(loader, "glVertexAttribI4ui");
        gl.VertexAttribI4iv = detail::load<PFNGLVERTEXATTRIBI4IVPROC>(loader, "glVertexAttribI4iv");
        gl.VertexAttribI4uiv = detail::load<PFNGLVERTEXATTRIBI4UIVPROC>(loader, "glVertexAttribI4uiv");
        gl.GetVertexAttribfv = detail::load<PFNGLGETVERTEXATTRIBFVPROC>(loader, "glGetVertexAttribfv");
        gl.GetVertexAttribiv = detail::load<PFNGLGETVERTEXATTRIBIVPROC>(loader, "glGetVertexAttribiv");
        gl.GetVertexAttribIiv = detail::load<PFNGLGETVERTEXATTRIBIIVPROC>(loader, "glGetVertexAttribIiv");
        gl.GetVertexAttribIuiv = detail::load<PFNGLGETVERTEXATTRIBIUIVPROC>(loader, "glGetVertexAttribIuiv");
        gl.GetVertexAttribPointerv = detail::load<PFNGLGETVERTEXATTRIBPOINTERVPROC>(loader, "glGetVertexAttribPointerv");
        gl.VertexAttribFormat = detail::load<PFNGLVERTEXATTRIBFORMATPROC>(loader, "glVertexAttribFormat");
        gl.VertexAttribIFormat = detail::load<PFNGLVERTEXATTRIBIFORMATPROC>(loader, "glVertexAttribIFormat");
        gl.VertexAttribBinding = detail::load<PFNGLVERTEXATTRIBBINDINGPROC>(loader, "glVertexAttribBinding");
        gl.BindVertexBuffer = detail::load<PFNGLBINDVERTEXBUFFERPROC>(loader, "glBindVertexBuffer");
        gl.VertexBindingDivisor = detail::load<PFNGLVERTEXBINDINGDIVISORPROC>(loader, "glVertexBindingDivisor");
        gl.DrawArrays = detail::load<PFNGLDRAWARRAYSPROC>(loader, "glDrawArrays");
        gl.DrawArraysInstanced = detail::load<PFNGLDRAWARRAYSINSTANCEDPROC>(loader, "glDrawArraysInstanced");
        gl.DrawArraysIndirect = detail::load<PFNGLDRAWARRAYSINDIRECTPROC>(loader, "glDrawArraysIndirect");
        gl.DrawElements = detail::load<PFNGLDRAWELEMENTSPROC>(loader, "glDrawElements");
        gl.DrawElementsInstanced = detail::load<PFNGLDRAWELEMENTSINSTANCEDPROC>(loader, "glDrawElementsInstanced");
        gl.DrawRangeElements = detail::load<PFNGLDRAWRANGEELEMENTSPROC>(loader, "glDrawRangeElements");
        gl.DrawElementsBaseVertex = detail::load<PFNGLDRAWELEMENTSBASEVERTEXPROC>(loader, "glDrawElementsBaseVertex");
        gl.DrawElementsInstancedBaseVertex = detail::load<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC>(loader, "glDrawElementsInstancedBaseVertex");
        gl.DrawRangeElementsBaseVertex = detail::load<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>(loader, "glDrawRangeElementsBaseVertex");
        gl.DrawElementsIndirect = detail::load<PFNGLDRAWELEMENTSINDIRECTPROC>(loader, "glDrawElementsIndirect");
        gl.DrawBuffers = detail::load<PFNGLDRAWBUFFERSPROC>(loader, "glDrawBuffers");
        gl.ReadBuffer = detail::load<PFNGLREADBUFFERPROC>(loader, "glReadBuffer");
        gl.ReadPixels = detail::load<PFNGLREADPIXELSPROC>(loader, "glReadPixels");
        gl.ReadnPixels = detail::load<PFNGLREADNPIXELSPROC>(loader, "glReadnPixels");
        gl.Clear = detail::load<PFNGLCLEARPROC>(loader, "glClear");
        gl.ClearColor = detail::load<PFNGLCLEARCOLORPROC>(loader, "glClearColor");
        gl.ClearDepthf = detail::load<PFNGLCLEARDEPTHFPROC>(loader, "glClearDepthf");
        gl.DesktopClearDepth = gl.ClearDepthf
            ? nullptr
            : detail::load<detail::GlTable::DesktopClearDepthProc>(
                loader, "glClearDepth");
        gl.ClearStencil = detail::load<PFNGLCLEARSTENCILPROC>(loader, "glClearStencil");
        gl.ClearBufferfv = detail::load<PFNGLCLEARBUFFERFVPROC>(loader, "glClearBufferfv");
        gl.ClearBufferiv = detail::load<PFNGLCLEARBUFFERIVPROC>(loader, "glClearBufferiv");
        gl.ClearBufferuiv = detail::load<PFNGLCLEARBUFFERUIVPROC>(loader, "glClearBufferuiv");
        gl.ClearBufferfi = detail::load<PFNGLCLEARBUFFERFIPROC>(loader, "glClearBufferfi");
        gl.CreateShader = detail::load<PFNGLCREATESHADERPROC>(loader, "glCreateShader");
        gl.DeleteShader = detail::load<PFNGLDELETESHADERPROC>(loader, "glDeleteShader");
        gl.ShaderSource = detail::load<PFNGLSHADERSOURCEPROC>(loader, "glShaderSource");
        gl.CompileShader = detail::load<PFNGLCOMPILESHADERPROC>(loader, "glCompileShader");
        gl.ShaderBinary = detail::load<PFNGLSHADERBINARYPROC>(loader, "glShaderBinary");
        gl.ReleaseShaderCompiler = detail::load<PFNGLRELEASESHADERCOMPILERPROC>(loader, "glReleaseShaderCompiler");
        gl.GetShaderiv = detail::load<PFNGLGETSHADERIVPROC>(loader, "glGetShaderiv");
        gl.GetShaderInfoLog = detail::load<PFNGLGETSHADERINFOLOGPROC>(loader, "glGetShaderInfoLog");
        gl.GetShaderSource = detail::load<PFNGLGETSHADERSOURCEPROC>(loader, "glGetShaderSource");
        gl.GetShaderPrecisionFormat = detail::load<PFNGLGETSHADERPRECISIONFORMATPROC>(loader, "glGetShaderPrecisionFormat");
        gl.IsShader = detail::load<PFNGLISSHADERPROC>(loader, "glIsShader");
        gl.CreateProgram = detail::load<PFNGLCREATEPROGRAMPROC>(loader, "glCreateProgram");
        gl.DeleteProgram = detail::load<PFNGLDELETEPROGRAMPROC>(loader, "glDeleteProgram");
        gl.AttachShader = detail::load<PFNGLATTACHSHADERPROC>(loader, "glAttachShader");
        gl.DetachShader = detail::load<PFNGLDETACHSHADERPROC>(loader, "glDetachShader");
        gl.LinkProgram = detail::load<PFNGLLINKPROGRAMPROC>(loader, "glLinkProgram");
        gl.UseProgram = detail::load<PFNGLUSEPROGRAMPROC>(loader, "glUseProgram");
        gl.ValidateProgram = detail::load<PFNGLVALIDATEPROGRAMPROC>(loader, "glValidateProgram");
        gl.GetProgramiv = detail::load<PFNGLGETPROGRAMIVPROC>(loader, "glGetProgramiv");
        gl.GetProgramInfoLog = detail::load<PFNGLGETPROGRAMINFOLOGPROC>(loader, "glGetProgramInfoLog");
        gl.IsProgram = detail::load<PFNGLISPROGRAMPROC>(loader, "glIsProgram");
        gl.GetAttachedShaders = detail::load<PFNGLGETATTACHEDSHADERSPROC>(loader, "glGetAttachedShaders");
        gl.BindAttribLocation = detail::load<PFNGLBINDATTRIBLOCATIONPROC>(loader, "glBindAttribLocation");
        gl.GetAttribLocation = detail::load<PFNGLGETATTRIBLOCATIONPROC>(loader, "glGetAttribLocation");
        gl.GetActiveAttrib = detail::load<PFNGLGETACTIVEATTRIBPROC>(loader, "glGetActiveAttrib");
        gl.GetProgramBinary = detail::load<PFNGLGETPROGRAMBINARYPROC>(loader, "glGetProgramBinary");
        gl.ProgramBinary = detail::load<PFNGLPROGRAMBINARYPROC>(loader, "glProgramBinary");
        gl.ProgramParameteri = detail::load<PFNGLPROGRAMPARAMETERIPROC>(loader, "glProgramParameteri");
        gl.GetFragDataLocation = detail::load<PFNGLGETFRAGDATALOCATIONPROC>(loader, "glGetFragDataLocation");
        gl.GetProgramInterfaceiv = detail::load<PFNGLGETPROGRAMINTERFACEIVPROC>(loader, "glGetProgramInterfaceiv");
        gl.GetProgramResourceIndex = detail::load<PFNGLGETPROGRAMRESOURCEINDEXPROC>(loader, "glGetProgramResourceIndex");
        gl.GetProgramResourceName = detail::load<PFNGLGETPROGRAMRESOURCENAMEPROC>(loader, "glGetProgramResourceName");
        gl.GetProgramResourceiv = detail::load<PFNGLGETPROGRAMRESOURCEIVPROC>(loader, "glGetProgramResourceiv");
        gl.GetProgramResourceLocation = detail::load<PFNGLGETPROGRAMRESOURCELOCATIONPROC>(loader, "glGetProgramResourceLocation");
        gl.GetUniformLocation = detail::load<PFNGLGETUNIFORMLOCATIONPROC>(loader, "glGetUniformLocation");
        gl.GetActiveUniform = detail::load<PFNGLGETACTIVEUNIFORMPROC>(loader, "glGetActiveUniform");
        gl.GetActiveUniformsiv = detail::load<PFNGLGETACTIVEUNIFORMSIVPROC>(loader, "glGetActiveUniformsiv");
        gl.GetUniformIndices = detail::load<PFNGLGETUNIFORMINDICESPROC>(loader, "glGetUniformIndices");
        gl.GetUniformBlockIndex = detail::load<PFNGLGETUNIFORMBLOCKINDEXPROC>(loader, "glGetUniformBlockIndex");
        gl.GetActiveUniformBlockiv = detail::load<PFNGLGETACTIVEUNIFORMBLOCKIVPROC>(loader, "glGetActiveUniformBlockiv");
        gl.GetActiveUniformBlockName = detail::load<PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC>(loader, "glGetActiveUniformBlockName");
        gl.UniformBlockBinding = detail::load<PFNGLUNIFORMBLOCKBINDINGPROC>(loader, "glUniformBlockBinding");
        gl.Uniform1f = detail::load<PFNGLUNIFORM1FPROC>(loader, "glUniform1f");
        gl.Uniform2f = detail::load<PFNGLUNIFORM2FPROC>(loader, "glUniform2f");
        gl.Uniform3f = detail::load<PFNGLUNIFORM3FPROC>(loader, "glUniform3f");
        gl.Uniform4f = detail::load<PFNGLUNIFORM4FPROC>(loader, "glUniform4f");
        gl.Uniform1fv = detail::load<PFNGLUNIFORM1FVPROC>(loader, "glUniform1fv");
        gl.Uniform2fv = detail::load<PFNGLUNIFORM2FVPROC>(loader, "glUniform2fv");
        gl.Uniform3fv = detail::load<PFNGLUNIFORM3FVPROC>(loader, "glUniform3fv");
        gl.Uniform4fv = detail::load<PFNGLUNIFORM4FVPROC>(loader, "glUniform4fv");
        gl.Uniform1i = detail::load<PFNGLUNIFORM1IPROC>(loader, "glUniform1i");
        gl.Uniform2i = detail::load<PFNGLUNIFORM2IPROC>(loader, "glUniform2i");
        gl.Uniform3i = detail::load<PFNGLUNIFORM3IPROC>(loader, "glUniform3i");
        gl.Uniform4i = detail::load<PFNGLUNIFORM4IPROC>(loader, "glUniform4i");
        gl.Uniform1iv = detail::load<PFNGLUNIFORM1IVPROC>(loader, "glUniform1iv");
        gl.Uniform2iv = detail::load<PFNGLUNIFORM2IVPROC>(loader, "glUniform2iv");
        gl.Uniform3iv = detail::load<PFNGLUNIFORM3IVPROC>(loader, "glUniform3iv");
        gl.Uniform4iv = detail::load<PFNGLUNIFORM4IVPROC>(loader, "glUniform4iv");
        gl.Uniform1ui = detail::load<PFNGLUNIFORM1UIPROC>(loader, "glUniform1ui");
        gl.Uniform2ui = detail::load<PFNGLUNIFORM2UIPROC>(loader, "glUniform2ui");
        gl.Uniform3ui = detail::load<PFNGLUNIFORM3UIPROC>(loader, "glUniform3ui");
        gl.Uniform4ui = detail::load<PFNGLUNIFORM4UIPROC>(loader, "glUniform4ui");
        gl.Uniform1uiv = detail::load<PFNGLUNIFORM1UIVPROC>(loader, "glUniform1uiv");
        gl.Uniform2uiv = detail::load<PFNGLUNIFORM2UIVPROC>(loader, "glUniform2uiv");
        gl.Uniform3uiv = detail::load<PFNGLUNIFORM3UIVPROC>(loader, "glUniform3uiv");
        gl.Uniform4uiv = detail::load<PFNGLUNIFORM4UIVPROC>(loader, "glUniform4uiv");
        gl.UniformMatrix2fv = detail::load<PFNGLUNIFORMMATRIX2FVPROC>(loader, "glUniformMatrix2fv");
        gl.UniformMatrix3fv = detail::load<PFNGLUNIFORMMATRIX3FVPROC>(loader, "glUniformMatrix3fv");
        gl.UniformMatrix4fv = detail::load<PFNGLUNIFORMMATRIX4FVPROC>(loader, "glUniformMatrix4fv");
        gl.UniformMatrix2x3fv = detail::load<PFNGLUNIFORMMATRIX2X3FVPROC>(loader, "glUniformMatrix2x3fv");
        gl.UniformMatrix2x4fv = detail::load<PFNGLUNIFORMMATRIX2X4FVPROC>(loader, "glUniformMatrix2x4fv");
        gl.UniformMatrix3x2fv = detail::load<PFNGLUNIFORMMATRIX3X2FVPROC>(loader, "glUniformMatrix3x2fv");
        gl.UniformMatrix3x4fv = detail::load<PFNGLUNIFORMMATRIX3X4FVPROC>(loader, "glUniformMatrix3x4fv");
        gl.UniformMatrix4x2fv = detail::load<PFNGLUNIFORMMATRIX4X2FVPROC>(loader, "glUniformMatrix4x2fv");
        gl.UniformMatrix4x3fv = detail::load<PFNGLUNIFORMMATRIX4X3FVPROC>(loader, "glUniformMatrix4x3fv");
        gl.GetUniformfv = detail::load<PFNGLGETUNIFORMFVPROC>(loader, "glGetUniformfv");
        gl.GetUniformiv = detail::load<PFNGLGETUNIFORMIVPROC>(loader, "glGetUniformiv");
        gl.GetUniformuiv = detail::load<PFNGLGETUNIFORMUIVPROC>(loader, "glGetUniformuiv");
        gl.GetnUniformfv = detail::load<PFNGLGETNUNIFORMFVPROC>(loader, "glGetnUniformfv");
        gl.GetnUniformiv = detail::load<PFNGLGETNUNIFORMIVPROC>(loader, "glGetnUniformiv");
        gl.GetnUniformuiv = detail::load<PFNGLGETNUNIFORMUIVPROC>(loader, "glGetnUniformuiv");
        gl.ProgramUniform1f = detail::load<PFNGLPROGRAMUNIFORM1FPROC>(loader, "glProgramUniform1f");
        gl.ProgramUniform2f = detail::load<PFNGLPROGRAMUNIFORM2FPROC>(loader, "glProgramUniform2f");
        gl.ProgramUniform3f = detail::load<PFNGLPROGRAMUNIFORM3FPROC>(loader, "glProgramUniform3f");
        gl.ProgramUniform4f = detail::load<PFNGLPROGRAMUNIFORM4FPROC>(loader, "glProgramUniform4f");
        gl.ProgramUniform1fv = detail::load<PFNGLPROGRAMUNIFORM1FVPROC>(loader, "glProgramUniform1fv");
        gl.ProgramUniform2fv = detail::load<PFNGLPROGRAMUNIFORM2FVPROC>(loader, "glProgramUniform2fv");
        gl.ProgramUniform3fv = detail::load<PFNGLPROGRAMUNIFORM3FVPROC>(loader, "glProgramUniform3fv");
        gl.ProgramUniform4fv = detail::load<PFNGLPROGRAMUNIFORM4FVPROC>(loader, "glProgramUniform4fv");
        gl.ProgramUniform1i = detail::load<PFNGLPROGRAMUNIFORM1IPROC>(loader, "glProgramUniform1i");
        gl.ProgramUniform2i = detail::load<PFNGLPROGRAMUNIFORM2IPROC>(loader, "glProgramUniform2i");
        gl.ProgramUniform3i = detail::load<PFNGLPROGRAMUNIFORM3IPROC>(loader, "glProgramUniform3i");
        gl.ProgramUniform4i = detail::load<PFNGLPROGRAMUNIFORM4IPROC>(loader, "glProgramUniform4i");
        gl.ProgramUniform1iv = detail::load<PFNGLPROGRAMUNIFORM1IVPROC>(loader, "glProgramUniform1iv");
        gl.ProgramUniform2iv = detail::load<PFNGLPROGRAMUNIFORM2IVPROC>(loader, "glProgramUniform2iv");
        gl.ProgramUniform3iv = detail::load<PFNGLPROGRAMUNIFORM3IVPROC>(loader, "glProgramUniform3iv");
        gl.ProgramUniform4iv = detail::load<PFNGLPROGRAMUNIFORM4IVPROC>(loader, "glProgramUniform4iv");
        gl.ProgramUniform1ui = detail::load<PFNGLPROGRAMUNIFORM1UIPROC>(loader, "glProgramUniform1ui");
        gl.ProgramUniform2ui = detail::load<PFNGLPROGRAMUNIFORM2UIPROC>(loader, "glProgramUniform2ui");
        gl.ProgramUniform3ui = detail::load<PFNGLPROGRAMUNIFORM3UIPROC>(loader, "glProgramUniform3ui");
        gl.ProgramUniform4ui = detail::load<PFNGLPROGRAMUNIFORM4UIPROC>(loader, "glProgramUniform4ui");
        gl.ProgramUniform1uiv = detail::load<PFNGLPROGRAMUNIFORM1UIVPROC>(loader, "glProgramUniform1uiv");
        gl.ProgramUniform2uiv = detail::load<PFNGLPROGRAMUNIFORM2UIVPROC>(loader, "glProgramUniform2uiv");
        gl.ProgramUniform3uiv = detail::load<PFNGLPROGRAMUNIFORM3UIVPROC>(loader, "glProgramUniform3uiv");
        gl.ProgramUniform4uiv = detail::load<PFNGLPROGRAMUNIFORM4UIVPROC>(loader, "glProgramUniform4uiv");
        gl.ProgramUniformMatrix2fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX2FVPROC>(loader, "glProgramUniformMatrix2fv");
        gl.ProgramUniformMatrix3fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX3FVPROC>(loader, "glProgramUniformMatrix3fv");
        gl.ProgramUniformMatrix4fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX4FVPROC>(loader, "glProgramUniformMatrix4fv");
        gl.ProgramUniformMatrix2x3fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC>(loader, "glProgramUniformMatrix2x3fv");
        gl.ProgramUniformMatrix2x4fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC>(loader, "glProgramUniformMatrix2x4fv");
        gl.ProgramUniformMatrix3x2fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC>(loader, "glProgramUniformMatrix3x2fv");
        gl.ProgramUniformMatrix3x4fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC>(loader, "glProgramUniformMatrix3x4fv");
        gl.ProgramUniformMatrix4x2fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC>(loader, "glProgramUniformMatrix4x2fv");
        gl.ProgramUniformMatrix4x3fv = detail::load<PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC>(loader, "glProgramUniformMatrix4x3fv");
        gl.GenTextures = detail::load<PFNGLGENTEXTURESPROC>(loader, "glGenTextures");
        gl.DeleteTextures = detail::load<PFNGLDELETETEXTURESPROC>(loader, "glDeleteTextures");
        gl.BindTexture = detail::load<PFNGLBINDTEXTUREPROC>(loader, "glBindTexture");
        gl.ActiveTexture = detail::load<PFNGLACTIVETEXTUREPROC>(loader, "glActiveTexture");
        gl.IsTexture = detail::load<PFNGLISTEXTUREPROC>(loader, "glIsTexture");
        gl.TexImage2D = detail::load<PFNGLTEXIMAGE2DPROC>(loader, "glTexImage2D");
        gl.TexImage3D = detail::load<PFNGLTEXIMAGE3DPROC>(loader, "glTexImage3D");
        gl.TexSubImage2D = detail::load<PFNGLTEXSUBIMAGE2DPROC>(loader, "glTexSubImage2D");
        gl.TexSubImage3D = detail::load<PFNGLTEXSUBIMAGE3DPROC>(loader, "glTexSubImage3D");
        gl.TexStorage2D = detail::load<PFNGLTEXSTORAGE2DPROC>(loader, "glTexStorage2D");
        gl.TexStorage3D = detail::load<PFNGLTEXSTORAGE3DPROC>(loader, "glTexStorage3D");
        gl.TexStorage2DMultisample = detail::load<PFNGLTEXSTORAGE2DMULTISAMPLEPROC>(loader, "glTexStorage2DMultisample");
        gl.TexStorage3DMultisample = detail::load<PFNGLTEXSTORAGE3DMULTISAMPLEPROC>(loader, "glTexStorage3DMultisample");
        gl.CompressedTexImage2D = detail::load<PFNGLCOMPRESSEDTEXIMAGE2DPROC>(loader, "glCompressedTexImage2D");
        gl.CompressedTexImage3D = detail::load<PFNGLCOMPRESSEDTEXIMAGE3DPROC>(loader, "glCompressedTexImage3D");
        gl.CompressedTexSubImage2D = detail::load<PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC>(loader, "glCompressedTexSubImage2D");
        gl.CompressedTexSubImage3D = detail::load<PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC>(loader, "glCompressedTexSubImage3D");
        gl.CopyTexImage2D = detail::load<PFNGLCOPYTEXIMAGE2DPROC>(loader, "glCopyTexImage2D");
        gl.CopyTexSubImage2D = detail::load<PFNGLCOPYTEXSUBIMAGE2DPROC>(loader, "glCopyTexSubImage2D");
        gl.CopyTexSubImage3D = detail::load<PFNGLCOPYTEXSUBIMAGE3DPROC>(loader, "glCopyTexSubImage3D");
        gl.CopyImageSubData = detail::load<PFNGLCOPYIMAGESUBDATAPROC>(loader, "glCopyImageSubData");
        gl.GenerateMipmap = detail::load<PFNGLGENERATEMIPMAPPROC>(loader, "glGenerateMipmap");
        gl.TexParameterf = detail::load<PFNGLTEXPARAMETERFPROC>(loader, "glTexParameterf");
        gl.TexParameteri = detail::load<PFNGLTEXPARAMETERIPROC>(loader, "glTexParameteri");
        gl.TexParameterfv = detail::load<PFNGLTEXPARAMETERFVPROC>(loader, "glTexParameterfv");
        gl.TexParameteriv = detail::load<PFNGLTEXPARAMETERIVPROC>(loader, "glTexParameteriv");
        gl.TexParameterIiv = detail::load<PFNGLTEXPARAMETERIIVPROC>(loader, "glTexParameterIiv");
        gl.TexParameterIuiv = detail::load<PFNGLTEXPARAMETERIUIVPROC>(loader, "glTexParameterIuiv");
        gl.GetTexParameterfv = detail::load<PFNGLGETTEXPARAMETERFVPROC>(loader, "glGetTexParameterfv");
        gl.GetTexParameteriv = detail::load<PFNGLGETTEXPARAMETERIVPROC>(loader, "glGetTexParameteriv");
        gl.GetTexParameterIiv = detail::load<PFNGLGETTEXPARAMETERIIVPROC>(loader, "glGetTexParameterIiv");
        gl.GetTexParameterIuiv = detail::load<PFNGLGETTEXPARAMETERIUIVPROC>(loader, "glGetTexParameterIuiv");
        gl.GetTexLevelParameteriv = detail::load<PFNGLGETTEXLEVELPARAMETERIVPROC>(loader, "glGetTexLevelParameteriv");
        gl.GetTexLevelParameterfv = detail::load<PFNGLGETTEXLEVELPARAMETERFVPROC>(loader, "glGetTexLevelParameterfv");
        gl.TexBuffer = detail::load<PFNGLTEXBUFFERPROC>(loader, "glTexBuffer");
        gl.TexBufferRange = detail::load<PFNGLTEXBUFFERRANGEPROC>(loader, "glTexBufferRange");
        gl.GetMultisamplefv = detail::load<PFNGLGETMULTISAMPLEFVPROC>(loader, "glGetMultisamplefv");
        gl.GetInternalformativ = detail::load<PFNGLGETINTERNALFORMATIVPROC>(loader, "glGetInternalformativ");
        gl.BindImageTexture = detail::load<PFNGLBINDIMAGETEXTUREPROC>(loader, "glBindImageTexture");
        gl.GenSamplers = detail::load<PFNGLGENSAMPLERSPROC>(loader, "glGenSamplers");
        gl.DeleteSamplers = detail::load<PFNGLDELETESAMPLERSPROC>(loader, "glDeleteSamplers");
        gl.BindSampler = detail::load<PFNGLBINDSAMPLERPROC>(loader, "glBindSampler");
        gl.IsSampler = detail::load<PFNGLISSAMPLERPROC>(loader, "glIsSampler");
        gl.SamplerParameterf = detail::load<PFNGLSAMPLERPARAMETERFPROC>(loader, "glSamplerParameterf");
        gl.SamplerParameteri = detail::load<PFNGLSAMPLERPARAMETERIPROC>(loader, "glSamplerParameteri");
        gl.SamplerParameterfv = detail::load<PFNGLSAMPLERPARAMETERFVPROC>(loader, "glSamplerParameterfv");
        gl.SamplerParameteriv = detail::load<PFNGLSAMPLERPARAMETERIVPROC>(loader, "glSamplerParameteriv");
        gl.SamplerParameterIiv = detail::load<PFNGLSAMPLERPARAMETERIIVPROC>(loader, "glSamplerParameterIiv");
        gl.SamplerParameterIuiv = detail::load<PFNGLSAMPLERPARAMETERIUIVPROC>(loader, "glSamplerParameterIuiv");
        gl.GetSamplerParameterfv = detail::load<PFNGLGETSAMPLERPARAMETERFVPROC>(loader, "glGetSamplerParameterfv");
        gl.GetSamplerParameteriv = detail::load<PFNGLGETSAMPLERPARAMETERIVPROC>(loader, "glGetSamplerParameteriv");
        gl.GetSamplerParameterIiv = detail::load<PFNGLGETSAMPLERPARAMETERIIVPROC>(loader, "glGetSamplerParameterIiv");
        gl.GetSamplerParameterIuiv = detail::load<PFNGLGETSAMPLERPARAMETERIUIVPROC>(loader, "glGetSamplerParameterIuiv");
        gl.GenFramebuffers = detail::load<PFNGLGENFRAMEBUFFERSPROC>(loader, "glGenFramebuffers");
        gl.DeleteFramebuffers = detail::load<PFNGLDELETEFRAMEBUFFERSPROC>(loader, "glDeleteFramebuffers");
        gl.BindFramebuffer = detail::load<PFNGLBINDFRAMEBUFFERPROC>(loader, "glBindFramebuffer");
        gl.IsFramebuffer = detail::load<PFNGLISFRAMEBUFFERPROC>(loader, "glIsFramebuffer");
        gl.CheckFramebufferStatus = detail::load<PFNGLCHECKFRAMEBUFFERSTATUSPROC>(loader, "glCheckFramebufferStatus");
        gl.FramebufferTexture2D = detail::load<PFNGLFRAMEBUFFERTEXTURE2DPROC>(loader, "glFramebufferTexture2D");
        gl.FramebufferTextureLayer = detail::load<PFNGLFRAMEBUFFERTEXTURELAYERPROC>(loader, "glFramebufferTextureLayer");
        gl.FramebufferTexture = detail::load<PFNGLFRAMEBUFFERTEXTUREPROC>(loader, "glFramebufferTexture");
        gl.FramebufferRenderbuffer = detail::load<PFNGLFRAMEBUFFERRENDERBUFFERPROC>(loader, "glFramebufferRenderbuffer");
        gl.FramebufferParameteri = detail::load<PFNGLFRAMEBUFFERPARAMETERIPROC>(loader, "glFramebufferParameteri");
        gl.GetFramebufferParameteriv = detail::load<PFNGLGETFRAMEBUFFERPARAMETERIVPROC>(loader, "glGetFramebufferParameteriv");
        gl.GetFramebufferAttachmentParameteriv = detail::load<PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC>(loader, "glGetFramebufferAttachmentParameteriv");
        gl.BlitFramebuffer = detail::load<PFNGLBLITFRAMEBUFFERPROC>(loader, "glBlitFramebuffer");
        gl.InvalidateFramebuffer = detail::load<PFNGLINVALIDATEFRAMEBUFFERPROC>(loader, "glInvalidateFramebuffer");
        gl.InvalidateSubFramebuffer = detail::load<PFNGLINVALIDATESUBFRAMEBUFFERPROC>(loader, "glInvalidateSubFramebuffer");
        gl.GenRenderbuffers = detail::load<PFNGLGENRENDERBUFFERSPROC>(loader, "glGenRenderbuffers");
        gl.DeleteRenderbuffers = detail::load<PFNGLDELETERENDERBUFFERSPROC>(loader, "glDeleteRenderbuffers");
        gl.BindRenderbuffer = detail::load<PFNGLBINDRENDERBUFFERPROC>(loader, "glBindRenderbuffer");
        gl.IsRenderbuffer = detail::load<PFNGLISRENDERBUFFERPROC>(loader, "glIsRenderbuffer");
        gl.RenderbufferStorage = detail::load<PFNGLRENDERBUFFERSTORAGEPROC>(loader, "glRenderbufferStorage");
        gl.RenderbufferStorageMultisample = detail::load<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>(loader, "glRenderbufferStorageMultisample");
        gl.GetRenderbufferParameteriv = detail::load<PFNGLGETRENDERBUFFERPARAMETERIVPROC>(loader, "glGetRenderbufferParameteriv");
        gl.GenTransformFeedbacks = detail::load<PFNGLGENTRANSFORMFEEDBACKSPROC>(loader, "glGenTransformFeedbacks");
        gl.DeleteTransformFeedbacks = detail::load<PFNGLDELETETRANSFORMFEEDBACKSPROC>(loader, "glDeleteTransformFeedbacks");
        gl.BindTransformFeedback = detail::load<PFNGLBINDTRANSFORMFEEDBACKPROC>(loader, "glBindTransformFeedback");
        gl.IsTransformFeedback = detail::load<PFNGLISTRANSFORMFEEDBACKPROC>(loader, "glIsTransformFeedback");
        gl.BeginTransformFeedback = detail::load<PFNGLBEGINTRANSFORMFEEDBACKPROC>(loader, "glBeginTransformFeedback");
        gl.EndTransformFeedback = detail::load<PFNGLENDTRANSFORMFEEDBACKPROC>(loader, "glEndTransformFeedback");
        gl.PauseTransformFeedback = detail::load<PFNGLPAUSETRANSFORMFEEDBACKPROC>(loader, "glPauseTransformFeedback");
        gl.ResumeTransformFeedback = detail::load<PFNGLRESUMETRANSFORMFEEDBACKPROC>(loader, "glResumeTransformFeedback");
        gl.TransformFeedbackVaryings = detail::load<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>(loader, "glTransformFeedbackVaryings");
        gl.GetTransformFeedbackVarying = detail::load<PFNGLGETTRANSFORMFEEDBACKVARYINGPROC>(loader, "glGetTransformFeedbackVarying");
        gl.GenQueries = detail::load<PFNGLGENQUERIESPROC>(loader, "glGenQueries");
        gl.DeleteQueries = detail::load<PFNGLDELETEQUERIESPROC>(loader, "glDeleteQueries");
        gl.IsQuery = detail::load<PFNGLISQUERYPROC>(loader, "glIsQuery");
        gl.BeginQuery = detail::load<PFNGLBEGINQUERYPROC>(loader, "glBeginQuery");
        gl.EndQuery = detail::load<PFNGLENDQUERYPROC>(loader, "glEndQuery");
        gl.GetQueryiv = detail::load<PFNGLGETQUERYIVPROC>(loader, "glGetQueryiv");
        gl.GetQueryObjectuiv = detail::load<PFNGLGETQUERYOBJECTUIVPROC>(loader, "glGetQueryObjectuiv");
        gl.FenceSync = detail::load<PFNGLFENCESYNCPROC>(loader, "glFenceSync");
        gl.DeleteSync = detail::load<PFNGLDELETESYNCPROC>(loader, "glDeleteSync");
        gl.IsSync = detail::load<PFNGLISSYNCPROC>(loader, "glIsSync");
        gl.ClientWaitSync = detail::load<PFNGLCLIENTWAITSYNCPROC>(loader, "glClientWaitSync");
        gl.WaitSync = detail::load<PFNGLWAITSYNCPROC>(loader, "glWaitSync");
        gl.GetSynciv = detail::load<PFNGLGETSYNCIVPROC>(loader, "glGetSynciv");
        gl.DispatchCompute = detail::load<PFNGLDISPATCHCOMPUTEPROC>(loader, "glDispatchCompute");
        gl.DispatchComputeIndirect = detail::load<PFNGLDISPATCHCOMPUTEINDIRECTPROC>(loader, "glDispatchComputeIndirect");
        gl.MemoryBarrier = detail::load<PFNGLMEMORYBARRIERPROC>(loader, "glMemoryBarrier");
        gl.MemoryBarrierByRegion = detail::load<PFNGLMEMORYBARRIERBYREGIONPROC>(loader, "glMemoryBarrierByRegion");
        gl.GenProgramPipelines = detail::load<PFNGLGENPROGRAMPIPELINESPROC>(loader, "glGenProgramPipelines");
        gl.DeleteProgramPipelines = detail::load<PFNGLDELETEPROGRAMPIPELINESPROC>(loader, "glDeleteProgramPipelines");
        gl.BindProgramPipeline = detail::load<PFNGLBINDPROGRAMPIPELINEPROC>(loader, "glBindProgramPipeline");
        gl.IsProgramPipeline = detail::load<PFNGLISPROGRAMPIPELINEPROC>(loader, "glIsProgramPipeline");
        gl.UseProgramStages = detail::load<PFNGLUSEPROGRAMSTAGESPROC>(loader, "glUseProgramStages");
        gl.ActiveShaderProgram = detail::load<PFNGLACTIVESHADERPROGRAMPROC>(loader, "glActiveShaderProgram");
        gl.CreateShaderProgramv = detail::load<PFNGLCREATESHADERPROGRAMVPROC>(loader, "glCreateShaderProgramv");
        gl.ValidateProgramPipeline = detail::load<PFNGLVALIDATEPROGRAMPIPELINEPROC>(loader, "glValidateProgramPipeline");
        gl.GetProgramPipelineiv = detail::load<PFNGLGETPROGRAMPIPELINEIVPROC>(loader, "glGetProgramPipelineiv");
        gl.GetProgramPipelineInfoLog = detail::load<PFNGLGETPROGRAMPIPELINEINFOLOGPROC>(loader, "glGetProgramPipelineInfoLog");
        gl.PatchParameteri = detail::load<PFNGLPATCHPARAMETERIPROC>(loader, "glPatchParameteri");
        gl.PrimitiveBoundingBox = detail::load<PFNGLPRIMITIVEBOUNDINGBOXPROC>(loader, "glPrimitiveBoundingBox");
        gl.DebugMessageCallback = detail::load<PFNGLDEBUGMESSAGECALLBACKPROC>(loader, "glDebugMessageCallback");
        gl.DebugMessageControl = detail::load<PFNGLDEBUGMESSAGECONTROLPROC>(loader, "glDebugMessageControl");
        gl.DebugMessageInsert = detail::load<PFNGLDEBUGMESSAGEINSERTPROC>(loader, "glDebugMessageInsert");
        gl.GetDebugMessageLog = detail::load<PFNGLGETDEBUGMESSAGELOGPROC>(loader, "glGetDebugMessageLog");
        gl.PushDebugGroup = detail::load<PFNGLPUSHDEBUGGROUPPROC>(loader, "glPushDebugGroup");
        gl.PopDebugGroup = detail::load<PFNGLPOPDEBUGGROUPPROC>(loader, "glPopDebugGroup");
        gl.ObjectLabel = detail::load<PFNGLOBJECTLABELPROC>(loader, "glObjectLabel");
        gl.ObjectPtrLabel = detail::load<PFNGLOBJECTPTRLABELPROC>(loader, "glObjectPtrLabel");
        gl.GetObjectLabel = detail::load<PFNGLGETOBJECTLABELPROC>(loader, "glGetObjectLabel");
        gl.GetObjectPtrLabel = detail::load<PFNGLGETOBJECTPTRLABELPROC>(loader, "glGetObjectPtrLabel");
        gl.GetGraphicsResetStatus = detail::load<PFNGLGETGRAPHICSRESETSTATUSPROC>(loader, "glGetGraphicsResetStatus");

        gl.initialized = detail::required_version_loaded(gl, detected.level);
        if (!gl.initialized)
        {
            detail::g_function_availability.clear();
            return false;
        }

        // R76 — internal-only desktop ES-tier diagnostic (see
        // DesktopEsTier.hpp); never affects Initialize()'s success/failure.
        detail::g_desktop_es_tier =
            detected.level == detail::RequiredApiLevel::Desktop33
                ? detail::to_desktop_es_tier(detail::detect_desktop_es_tier(gl))
                : detail::DesktopEsTier::None;

        detail::g_gl = gl;
        try
        {
            // Detect capabilities and publish context state.
            detail::UpdateContextAfterLoad();
        }
        catch (...)
        {
            detail::g_gl.initialized = false;
            detail::g_function_availability.clear();
            detail::g_desktop_es_tier = detail::DesktopEsTier::None;
            detail::ResetContextAfterLoadFailure();
            throw;
        }

#ifdef METAGLDEBUG
        // Register raw GetError pointer so the debug logger can check for GL
        // errors after each call without going through the wrapper.
        metagl::debug::set_get_error_fn(
            reinterpret_cast<unsigned int(*)()>(detail::g_gl.GetError));
#endif

        return true;
    }

    bool IsInitialized() noexcept
    {
        return detail::g_gl.initialized;
    }

    bool IsFunctionAvailable(std::string_view name) noexcept
    {
        if (!detail::g_gl.initialized) return false;
        const auto it = detail::g_function_availability.find(name);
        if (it == detail::g_function_availability.end()) return false;
        return it->second;
    }

    bool AllFunctionsLoaded() noexcept
    {
        return detail::g_gl.initialized && detail::all_loaded(detail::g_gl);
    }

    namespace detail
    {
        // R76 — internal-only; see DesktopEsTier.hpp.
        DesktopEsTier GetDesktopEsTier() noexcept
        {
            return g_gl.initialized ? g_desktop_es_tier : DesktopEsTier::None;
        }
    }

    // #1
    void glEnable(Capability cap)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Enable != nullptr)) std::terminate();
        detail::g_gl.Enable(detail::to_gl_enum(cap));
        METAGL_DEBUG_LOG_VOID("glEnable", cap);
    }

    // #2
    void glDisable(Capability cap)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Disable != nullptr)) std::terminate();
        detail::g_gl.Disable(detail::to_gl_enum(cap));
        METAGL_DEBUG_LOG_VOID("glDisable", cap);
    }

    // #3
    void glEnablei(Capability target, GLuint index)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Enablei != nullptr)) std::terminate();
        detail::g_gl.Enablei(detail::to_gl_enum(target), index);
        METAGL_DEBUG_LOG_VOID("glEnablei", target, index);
    }

    // #4
    void glDisablei(Capability target, GLuint index)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Disablei != nullptr)) std::terminate();
        detail::g_gl.Disablei(detail::to_gl_enum(target), index);
        METAGL_DEBUG_LOG_VOID("glDisablei", target, index);
    }

    // #5
    bool glIsEnabled(Capability cap)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsEnabled != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsEnabled(detail::to_gl_enum(cap));
        METAGL_DEBUG_LOG("glIsEnabled", _r, cap);
        return _r;
    }

    // #6
    bool glIsEnabledi(Capability target, GLuint index)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsEnabledi != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsEnabledi(detail::to_gl_enum(target), index);
        METAGL_DEBUG_LOG("glIsEnabledi", _r, target, index);
        return _r;
    }

    // #7
    void glBlendFunc(BlendFactor sfactor, BlendFactor dfactor)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendFunc != nullptr)) std::terminate();
        detail::g_gl.BlendFunc(detail::to_gl_enum(sfactor), detail::to_gl_enum(dfactor));
        METAGL_DEBUG_LOG_VOID("glBlendFunc", sfactor, dfactor);
    }

    // #8
    void glBlendFuncSeparate(BlendFactor sfactorRGB, BlendFactor dfactorRGB, BlendFactor sfactorAlpha, BlendFactor dfactorAlpha)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendFuncSeparate != nullptr)) std::terminate();
        detail::g_gl.BlendFuncSeparate(detail::to_gl_enum(sfactorRGB), detail::to_gl_enum(dfactorRGB), detail::to_gl_enum(sfactorAlpha), detail::to_gl_enum(dfactorAlpha));
        METAGL_DEBUG_LOG_VOID("glBlendFuncSeparate", sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
    }

    // #9
    void glBlendFunci(GLuint buf, BlendFactor src, BlendFactor dst)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendFunci != nullptr)) std::terminate();
        detail::g_gl.BlendFunci(buf, detail::to_gl_enum(src), detail::to_gl_enum(dst));
        METAGL_DEBUG_LOG_VOID("glBlendFunci", buf, src, dst);
    }

    // #10
    void glBlendFuncSeparatei(GLuint buf, BlendFactor srcRGB, BlendFactor dstRGB, BlendFactor srcAlpha, BlendFactor dstAlpha)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendFuncSeparatei != nullptr)) std::terminate();
        detail::g_gl.BlendFuncSeparatei(buf, detail::to_gl_enum(srcRGB), detail::to_gl_enum(dstRGB), detail::to_gl_enum(srcAlpha), detail::to_gl_enum(dstAlpha));
        METAGL_DEBUG_LOG_VOID("glBlendFuncSeparatei", buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
    }

    // #11
    void glBlendEquation(BlendEquation mode)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendEquation != nullptr)) std::terminate();
        detail::g_gl.BlendEquation(detail::to_gl_enum(mode));
        METAGL_DEBUG_LOG_VOID("glBlendEquation", mode);
    }

    // #12
    void glBlendEquationSeparate(BlendEquation modeRGB, BlendEquation modeAlpha)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendEquationSeparate != nullptr)) std::terminate();
        detail::g_gl.BlendEquationSeparate(detail::to_gl_enum(modeRGB), detail::to_gl_enum(modeAlpha));
        METAGL_DEBUG_LOG_VOID("glBlendEquationSeparate", modeRGB, modeAlpha);
    }

    // #13
    void glBlendEquationi(GLuint buf, BlendEquation mode)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendEquationi != nullptr)) std::terminate();
        detail::g_gl.BlendEquationi(buf, detail::to_gl_enum(mode));
        METAGL_DEBUG_LOG_VOID("glBlendEquationi", buf, mode);
    }

    // #14
    void glBlendEquationSeparatei(GLuint buf, BlendEquation modeRGB, BlendEquation modeAlpha)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendEquationSeparatei != nullptr)) std::terminate();
        detail::g_gl.BlendEquationSeparatei(buf, detail::to_gl_enum(modeRGB), detail::to_gl_enum(modeAlpha));
        METAGL_DEBUG_LOG_VOID("glBlendEquationSeparatei", buf, modeRGB, modeAlpha);
    }

    // #15
    void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendColor != nullptr)) std::terminate();
        detail::g_gl.BlendColor(red, green, blue, alpha);
        METAGL_DEBUG_LOG_VOID("glBlendColor", red, green, blue, alpha);
    }

    // #16
    void glBlendBarrier(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlendBarrier != nullptr)) std::terminate();
        detail::g_gl.BlendBarrier();
        METAGL_DEBUG_LOG_VOID("glBlendBarrier");
    }

    // #17
    void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ColorMask != nullptr)) std::terminate();
        detail::g_gl.ColorMask(red, green, blue, alpha);
        METAGL_DEBUG_LOG_VOID("glColorMask", red, green, blue, alpha);
    }

    // #18
    void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ColorMaski != nullptr)) std::terminate();
        detail::g_gl.ColorMaski(index, r, g, b, a);
        METAGL_DEBUG_LOG_VOID("glColorMaski", index, r, g, b, a);
    }

    // #19
    void glDepthFunc(CompareFunc func)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DepthFunc != nullptr)) std::terminate();
        detail::g_gl.DepthFunc(detail::to_gl_enum(func));
        METAGL_DEBUG_LOG_VOID("glDepthFunc", func);
    }

    // #20
    void glDepthMask(GLboolean flag)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DepthMask != nullptr)) std::terminate();
        detail::g_gl.DepthMask(flag);
        METAGL_DEBUG_LOG_VOID("glDepthMask", flag);
    }

    // #21
    void glDepthRangef(GLfloat n, GLfloat f)
    {
        if (!(detail::g_gl.initialized
            && (detail::g_gl.DepthRangef != nullptr
                || detail::g_gl.DesktopDepthRange != nullptr))) std::terminate();
        if (detail::g_gl.DepthRangef)
            detail::g_gl.DepthRangef(n, f);
        else
            detail::g_gl.DesktopDepthRange(
                static_cast<double>(n), static_cast<double>(f));
        METAGL_DEBUG_LOG_VOID("glDepthRangef", n, f);
    }

    // #22
    void glStencilFunc(CompareFunc func, GLint ref, GLuint mask)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.StencilFunc != nullptr)) std::terminate();
        detail::g_gl.StencilFunc(detail::to_gl_enum(func), ref, mask);
        METAGL_DEBUG_LOG_VOID("glStencilFunc", func, ref, mask);
    }

    // #23
    void glStencilFuncSeparate(CullFace face, CompareFunc func, GLint ref, GLuint mask)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.StencilFuncSeparate != nullptr)) std::terminate();
        detail::g_gl.StencilFuncSeparate(detail::to_gl_enum(face), detail::to_gl_enum(func), ref, mask);
        METAGL_DEBUG_LOG_VOID("glStencilFuncSeparate", face, func, ref, mask);
    }

    // #24
    void glStencilOp(StencilOp fail, StencilOp zfail, StencilOp zpass)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.StencilOp != nullptr)) std::terminate();
        detail::g_gl.StencilOp(detail::to_gl_enum(fail), detail::to_gl_enum(zfail), detail::to_gl_enum(zpass));
        METAGL_DEBUG_LOG_VOID("glStencilOp", fail, zfail, zpass);
    }

    // #25
    void glStencilOpSeparate(CullFace face, StencilOp sfail, StencilOp dpfail, StencilOp dppass)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.StencilOpSeparate != nullptr)) std::terminate();
        detail::g_gl.StencilOpSeparate(detail::to_gl_enum(face), detail::to_gl_enum(sfail), detail::to_gl_enum(dpfail), detail::to_gl_enum(dppass));
        METAGL_DEBUG_LOG_VOID("glStencilOpSeparate", face, sfail, dpfail, dppass);
    }

    // #26
    void glStencilMask(GLuint mask)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.StencilMask != nullptr)) std::terminate();
        detail::g_gl.StencilMask(mask);
        METAGL_DEBUG_LOG_VOID("glStencilMask", mask);
    }

    // #27
    void glStencilMaskSeparate(CullFace face, GLuint mask)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.StencilMaskSeparate != nullptr)) std::terminate();
        detail::g_gl.StencilMaskSeparate(detail::to_gl_enum(face), mask);
        METAGL_DEBUG_LOG_VOID("glStencilMaskSeparate", face, mask);
    }

    // #28
    void glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Scissor != nullptr)) std::terminate();
        detail::g_gl.Scissor(x, y, width, height);
        METAGL_DEBUG_LOG_VOID("glScissor", x, y, width, height);
    }

    // #29
    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Viewport != nullptr)) std::terminate();
        detail::g_gl.Viewport(x, y, width, height);
        METAGL_DEBUG_LOG_VOID("glViewport", x, y, width, height);
    }

    // #30
    void glCullFace(CullFace mode)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CullFace != nullptr)) std::terminate();
        detail::g_gl.CullFace(detail::to_gl_enum(mode));
        METAGL_DEBUG_LOG_VOID("glCullFace", mode);
    }

    // #31
    void glFrontFace(FrontFace mode)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.FrontFace != nullptr)) std::terminate();
        detail::g_gl.FrontFace(detail::to_gl_enum(mode));
        METAGL_DEBUG_LOG_VOID("glFrontFace", mode);
    }

    // #32
    void glLineWidth(GLfloat width)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.LineWidth != nullptr)) std::terminate();
        detail::g_gl.LineWidth(width);
        METAGL_DEBUG_LOG_VOID("glLineWidth", width);
    }

    // #33
    void glPolygonOffset(GLfloat factor, GLfloat units)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.PolygonOffset != nullptr)) std::terminate();
        detail::g_gl.PolygonOffset(factor, units);
        METAGL_DEBUG_LOG_VOID("glPolygonOffset", factor, units);
    }

    // #34
    void glSampleCoverage(GLfloat value, GLboolean invert)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.SampleCoverage != nullptr)) std::terminate();
        detail::g_gl.SampleCoverage(value, invert);
        METAGL_DEBUG_LOG_VOID("glSampleCoverage", value, invert);
    }

    // #35
    void glSampleMaski(GLuint maskNumber, SampleMaskValue mask)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.SampleMaski != nullptr)) std::terminate();
        detail::g_gl.SampleMaski(maskNumber, static_cast<GLbitfield>(mask));
        METAGL_DEBUG_LOG_VOID("glSampleMaski", maskNumber, mask);
    }

    // #36
    void glMinSampleShading(GLfloat value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.MinSampleShading != nullptr)) std::terminate();
        detail::g_gl.MinSampleShading(value);
        METAGL_DEBUG_LOG_VOID("glMinSampleShading", value);
    }

    // #37
    void glHint(HintTarget target, HintMode mode)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Hint != nullptr)) std::terminate();
        detail::g_gl.Hint(detail::to_gl_enum(target), detail::to_gl_enum(mode));
        METAGL_DEBUG_LOG_VOID("glHint", target, mode);
    }

    // #38
    void glPixelStorei(PixelStoreParam pname, GLint param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.PixelStorei != nullptr)) std::terminate();
        detail::g_gl.PixelStorei(detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glPixelStorei", pname, param);
    }

    // #39
    void glFinish(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Finish != nullptr)) std::terminate();
        detail::g_gl.Finish();
        METAGL_DEBUG_LOG_VOID("glFinish");
    }

    // #40
    void glFlush(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Flush != nullptr)) std::terminate();
        detail::g_gl.Flush();
        METAGL_DEBUG_LOG_VOID("glFlush");
    }

    // #41
    ErrorCode glGetError(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetError != nullptr)) std::terminate();
        return static_cast<ErrorCode>(detail::g_gl.GetError());
    }

    // #42
    void glGetBooleanv(GetParameter pname, GLboolean * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetBooleanv != nullptr)) std::terminate();
        detail::g_gl.GetBooleanv(detail::to_gl_enum(pname), data);
        METAGL_DEBUG_LOG_VOID("glGetBooleanv", pname, data);
    }

    // #43
    void glGetIntegerv(GetParameter pname, GLint * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetIntegerv != nullptr)) std::terminate();
        detail::g_gl.GetIntegerv(detail::to_gl_enum(pname), data);
        METAGL_DEBUG_LOG_VOID("glGetIntegerv", pname, data);
    }

    // #44
    void glGetFloatv(GetParameter pname, GLfloat * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetFloatv != nullptr)) std::terminate();
        detail::g_gl.GetFloatv(detail::to_gl_enum(pname), data);
        METAGL_DEBUG_LOG_VOID("glGetFloatv", pname, data);
    }

    // #45
    void glGetInteger64v(GetParameter pname, GLint64 * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetInteger64v != nullptr)) std::terminate();
        detail::g_gl.GetInteger64v(detail::to_gl_enum(pname), data);
        METAGL_DEBUG_LOG_VOID("glGetInteger64v", pname, data);
    }

    // #46
    void glGetIntegeri_v(GetParameter target, GLuint index, GLint * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetIntegeri_v != nullptr)) std::terminate();
        detail::g_gl.GetIntegeri_v(detail::to_gl_enum(target), index, data);
        METAGL_DEBUG_LOG_VOID("glGetIntegeri_v", target, index, data);
    }

    // #47
    void glGetInteger64i_v(GetParameter target, GLuint index, GLint64 * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetInteger64i_v != nullptr)) std::terminate();
        detail::g_gl.GetInteger64i_v(detail::to_gl_enum(target), index, data);
        METAGL_DEBUG_LOG_VOID("glGetInteger64i_v", target, index, data);
    }

    // #48
    void glGetBooleani_v(GetParameter target, GLuint index, GLboolean * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetBooleani_v != nullptr)) std::terminate();
        detail::g_gl.GetBooleani_v(detail::to_gl_enum(target), index, data);
        METAGL_DEBUG_LOG_VOID("glGetBooleani_v", target, index, data);
    }

    // #49
    const GLubyte* glGetString(StringName name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetString != nullptr)) std::terminate();
        const auto _r = detail::g_gl.GetString(detail::to_gl_enum(name));
        METAGL_DEBUG_LOG("glGetString", _r, name);
        return _r;
    }

    // #50
    const GLubyte* glGetStringi(StringName name, GLuint index)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetStringi != nullptr)) std::terminate();
        const auto _r = detail::g_gl.GetStringi(detail::to_gl_enum(name), index);
        METAGL_DEBUG_LOG("glGetStringi", _r, name, index);
        return _r;
    }

    // #51
    void glGetPointerv(GetPointerParameter pname, void ** params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetPointerv != nullptr)) std::terminate();
        detail::g_gl.GetPointerv(detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetPointerv", pname, params);
    }

    // #52
    void glGenBuffers(GLsizei n, BufferId * buffers)
    {
        static_assert(sizeof(BufferId) == sizeof(GLuint), "BufferId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenBuffers != nullptr)) std::terminate();
        detail::g_gl.GenBuffers(n, reinterpret_cast<GLuint*>(buffers));
        METAGL_DEBUG_LOG_VOID("glGenBuffers", n, buffers);
    }

    // #53
    void glDeleteBuffers(GLsizei n, const BufferId * buffers)
    {
        static_assert(sizeof(BufferId) == sizeof(GLuint), "BufferId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteBuffers != nullptr)) std::terminate();
        detail::g_gl.DeleteBuffers(n, reinterpret_cast<const GLuint*>(buffers));
        METAGL_DEBUG_LOG_VOID("glDeleteBuffers", n, buffers);
    }

    // #54
    void glBindBuffer(BufferTarget target, BufferId buffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindBuffer != nullptr)) std::terminate();
        detail::g_gl.BindBuffer(detail::to_gl_enum(target), buffer.value);
        METAGL_DEBUG_LOG_VOID("glBindBuffer", target, buffer.value);
    }

    // #55
    void glBindBufferBase(BufferTarget target, GLuint index, BufferId buffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindBufferBase != nullptr)) std::terminate();
        detail::g_gl.BindBufferBase(detail::to_gl_enum(target), index, buffer.value);
        METAGL_DEBUG_LOG_VOID("glBindBufferBase", target, index, buffer.value);
    }

    // #56
    void glBindBufferRange(BufferTarget target, GLuint index, BufferId buffer, GLintptr offset, GLsizeiptr size)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindBufferRange != nullptr)) std::terminate();
        detail::g_gl.BindBufferRange(detail::to_gl_enum(target), index, buffer.value, offset, size);
        METAGL_DEBUG_LOG_VOID("glBindBufferRange", target, index, buffer.value, offset, size);
    }

    // #57
    void glBufferData(BufferTarget target, GLsizeiptr size, const void * data, BufferUsage usage)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BufferData != nullptr)) std::terminate();
        detail::g_gl.BufferData(detail::to_gl_enum(target), size, data, detail::to_gl_enum(usage));
        METAGL_DEBUG_LOG_VOID("glBufferData", target, size, data, usage);
    }

    // #58
    void glBufferSubData(BufferTarget target, GLintptr offset, GLsizeiptr size, const void * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BufferSubData != nullptr)) std::terminate();
        detail::g_gl.BufferSubData(detail::to_gl_enum(target), offset, size, data);
        METAGL_DEBUG_LOG_VOID("glBufferSubData", target, offset, size, data);
    }

    // #59
    void glCopyBufferSubData(BufferTarget readTarget, BufferTarget writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CopyBufferSubData != nullptr)) std::terminate();
        detail::g_gl.CopyBufferSubData(detail::to_gl_enum(readTarget), detail::to_gl_enum(writeTarget), readOffset, writeOffset, size);
        METAGL_DEBUG_LOG_VOID("glCopyBufferSubData", readTarget, writeTarget, readOffset, writeOffset, size);
    }

    // #60
    void* glMapBufferRange(BufferTarget target, GLintptr offset, GLsizeiptr length, MapBufferAccessMask access)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.MapBufferRange != nullptr)) std::terminate();
        void* const _r = detail::g_gl.MapBufferRange(
            detail::to_gl_enum(target), offset, length,
            detail::to_gl_bitfield(access));
        METAGL_DEBUG_LOG("glMapBufferRange", _r, target, offset, length, access);
        return _r;
    }

    // #61
    void glFlushMappedBufferRange(BufferTarget target, GLintptr offset, GLsizeiptr length)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.FlushMappedBufferRange != nullptr)) std::terminate();
        detail::g_gl.FlushMappedBufferRange(detail::to_gl_enum(target), offset, length);
        METAGL_DEBUG_LOG_VOID("glFlushMappedBufferRange", target, offset, length);
    }

    // #62
    GLboolean glUnmapBuffer(BufferTarget target)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UnmapBuffer != nullptr)) std::terminate();
        const auto _r = detail::g_gl.UnmapBuffer(detail::to_gl_enum(target));
        METAGL_DEBUG_LOG("glUnmapBuffer", _r, target);
        return _r;
    }

    // #63
    bool glIsBuffer(BufferId buffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsBuffer != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsBuffer(buffer.value);
        METAGL_DEBUG_LOG("glIsBuffer", _r, buffer.value);
        return _r;
    }

    // #64
    void glGetBufferParameteriv(BufferTarget target, BufferParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetBufferParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetBufferParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetBufferParameteriv", target, pname, params);
    }

    // #65
    void glGetBufferParameteri64v(BufferTarget target, BufferParameter pname, GLint64 * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetBufferParameteri64v != nullptr)) std::terminate();
        detail::g_gl.GetBufferParameteri64v(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetBufferParameteri64v", target, pname, params);
    }

    // #66
    void glGetBufferPointerv(BufferTarget target, BufferPointerParameter pname, void ** params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetBufferPointerv != nullptr)) std::terminate();
        detail::g_gl.GetBufferPointerv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetBufferPointerv", target, pname, params);
    }

    // #67
    void glGenVertexArrays(GLsizei n, VertexArrayId * arrays)
    {
        static_assert(sizeof(VertexArrayId) == sizeof(GLuint), "VertexArrayId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenVertexArrays != nullptr)) std::terminate();
        detail::g_gl.GenVertexArrays(n, reinterpret_cast<GLuint*>(arrays));
        METAGL_DEBUG_LOG_VOID("glGenVertexArrays", n, arrays);
    }

    // #68
    void glDeleteVertexArrays(GLsizei n, const VertexArrayId * arrays)
    {
        static_assert(sizeof(VertexArrayId) == sizeof(GLuint), "VertexArrayId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteVertexArrays != nullptr)) std::terminate();
        detail::g_gl.DeleteVertexArrays(n, reinterpret_cast<const GLuint*>(arrays));
        METAGL_DEBUG_LOG_VOID("glDeleteVertexArrays", n, arrays);
    }

    // #69
    void glBindVertexArray(VertexArrayId array)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindVertexArray != nullptr)) std::terminate();
        detail::g_gl.BindVertexArray(array.value);
        METAGL_DEBUG_LOG_VOID("glBindVertexArray", array.value);
    }

    // #70
    bool glIsVertexArray(VertexArrayId array)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsVertexArray != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsVertexArray(array.value);
        METAGL_DEBUG_LOG("glIsVertexArray", _r, array.value);
        return _r;
    }

    // #71
    void glEnableVertexAttribArray(AttribLocation index)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.EnableVertexAttribArray != nullptr)) std::terminate();
        detail::g_gl.EnableVertexAttribArray(index.value);
        METAGL_DEBUG_LOG_VOID("glEnableVertexAttribArray", index.value);
    }

    // #72
    void glDisableVertexAttribArray(AttribLocation index)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DisableVertexAttribArray != nullptr)) std::terminate();
        detail::g_gl.DisableVertexAttribArray(index.value);
        METAGL_DEBUG_LOG_VOID("glDisableVertexAttribArray", index.value);
    }

    // #73
    void glVertexAttribPointer(AttribLocation index, GLint size, DataType type, GLboolean normalized, GLsizei stride, const void * pointer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribPointer != nullptr)) std::terminate();
        detail::g_gl.VertexAttribPointer(index.value, size, detail::to_gl_enum(type), normalized, stride, pointer);
        METAGL_DEBUG_LOG_VOID("glVertexAttribPointer", index.value, size, type, normalized, stride, pointer);
    }

    // #74
    void glVertexAttribIPointer(AttribLocation index, GLint size, DataType type, GLsizei stride, const void * pointer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribIPointer != nullptr)) std::terminate();
        detail::g_gl.VertexAttribIPointer(index.value, size, detail::to_gl_enum(type), stride, pointer);
        METAGL_DEBUG_LOG_VOID("glVertexAttribIPointer", index.value, size, type, stride, pointer);
    }

    // #75
    void glVertexAttribDivisor(AttribLocation index, GLuint divisor)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribDivisor != nullptr)) std::terminate();
        detail::g_gl.VertexAttribDivisor(index.value, divisor);
        METAGL_DEBUG_LOG_VOID("glVertexAttribDivisor", index.value, divisor);
    }

    // #76
    void glVertexAttrib1f(AttribLocation index, GLfloat x)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttrib1f != nullptr)) std::terminate();
        detail::g_gl.VertexAttrib1f(index.value, x);
        METAGL_DEBUG_LOG_VOID("glVertexAttrib1f", index.value, x);
    }

    // #77
    void glVertexAttrib2f(AttribLocation index, GLfloat x, GLfloat y)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttrib2f != nullptr)) std::terminate();
        detail::g_gl.VertexAttrib2f(index.value, x, y);
        METAGL_DEBUG_LOG_VOID("glVertexAttrib2f", index.value, x, y);
    }

    // #78
    void glVertexAttrib3f(AttribLocation index, GLfloat x, GLfloat y, GLfloat z)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttrib3f != nullptr)) std::terminate();
        detail::g_gl.VertexAttrib3f(index.value, x, y, z);
        METAGL_DEBUG_LOG_VOID("glVertexAttrib3f", index.value, x, y, z);
    }

    // #79
    void glVertexAttrib4f(AttribLocation index, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttrib4f != nullptr)) std::terminate();
        detail::g_gl.VertexAttrib4f(index.value, x, y, z, w);
        METAGL_DEBUG_LOG_VOID("glVertexAttrib4f", index.value, x, y, z, w);
    }

    // #80
    void glVertexAttrib1fv(AttribLocation index, const GLfloat * v)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttrib1fv != nullptr)) std::terminate();
        detail::g_gl.VertexAttrib1fv(index.value, v);
        METAGL_DEBUG_LOG_VOID("glVertexAttrib1fv", index.value, v);
    }

    // #81
    void glVertexAttrib2fv(AttribLocation index, const GLfloat * v)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttrib2fv != nullptr)) std::terminate();
        detail::g_gl.VertexAttrib2fv(index.value, v);
        METAGL_DEBUG_LOG_VOID("glVertexAttrib2fv", index.value, v);
    }

    // #82
    void glVertexAttrib3fv(AttribLocation index, const GLfloat * v)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttrib3fv != nullptr)) std::terminate();
        detail::g_gl.VertexAttrib3fv(index.value, v);
        METAGL_DEBUG_LOG_VOID("glVertexAttrib3fv", index.value, v);
    }

    // #83
    void glVertexAttrib4fv(AttribLocation index, const GLfloat * v)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttrib4fv != nullptr)) std::terminate();
        detail::g_gl.VertexAttrib4fv(index.value, v);
        METAGL_DEBUG_LOG_VOID("glVertexAttrib4fv", index.value, v);
    }

    // #84
    void glVertexAttribI4i(AttribLocation index, GLint x, GLint y, GLint z, GLint w)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribI4i != nullptr)) std::terminate();
        detail::g_gl.VertexAttribI4i(index.value, x, y, z, w);
        METAGL_DEBUG_LOG_VOID("glVertexAttribI4i", index.value, x, y, z, w);
    }

    // #85
    void glVertexAttribI4ui(AttribLocation index, GLuint x, GLuint y, GLuint z, GLuint w)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribI4ui != nullptr)) std::terminate();
        detail::g_gl.VertexAttribI4ui(index.value, x, y, z, w);
        METAGL_DEBUG_LOG_VOID("glVertexAttribI4ui", index.value, x, y, z, w);
    }

    // #86
    void glVertexAttribI4iv(AttribLocation index, const GLint * v)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribI4iv != nullptr)) std::terminate();
        detail::g_gl.VertexAttribI4iv(index.value, v);
        METAGL_DEBUG_LOG_VOID("glVertexAttribI4iv", index.value, v);
    }

    // #87
    void glVertexAttribI4uiv(AttribLocation index, const GLuint * v)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribI4uiv != nullptr)) std::terminate();
        detail::g_gl.VertexAttribI4uiv(index.value, v);
        METAGL_DEBUG_LOG_VOID("glVertexAttribI4uiv", index.value, v);
    }

    // #88
    void glGetVertexAttribfv(AttribLocation index, VertexAttribParameter pname, GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetVertexAttribfv != nullptr)) std::terminate();
        detail::g_gl.GetVertexAttribfv(index.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetVertexAttribfv", index.value, pname, params);
    }

    // #89
    void glGetVertexAttribiv(AttribLocation index, VertexAttribParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetVertexAttribiv != nullptr)) std::terminate();
        detail::g_gl.GetVertexAttribiv(index.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetVertexAttribiv", index.value, pname, params);
    }

    // #90
    void glGetVertexAttribIiv(AttribLocation index, VertexAttribParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetVertexAttribIiv != nullptr)) std::terminate();
        detail::g_gl.GetVertexAttribIiv(index.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetVertexAttribIiv", index.value, pname, params);
    }

    // #91
    void glGetVertexAttribIuiv(AttribLocation index, VertexAttribParameter pname, GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetVertexAttribIuiv != nullptr)) std::terminate();
        detail::g_gl.GetVertexAttribIuiv(index.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetVertexAttribIuiv", index.value, pname, params);
    }

    // #92
    void glGetVertexAttribPointerv(AttribLocation index, VertexAttribParameter pname, void ** pointer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetVertexAttribPointerv != nullptr)) std::terminate();
        detail::g_gl.GetVertexAttribPointerv(index.value, detail::to_gl_enum(pname), pointer);
        METAGL_DEBUG_LOG_VOID("glGetVertexAttribPointerv", index.value, pname, pointer);
    }

    // #93
    void glVertexAttribFormat(AttribLocation attribindex, GLint size, DataType type, GLboolean normalized, GLuint relativeoffset)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribFormat != nullptr)) std::terminate();
        detail::g_gl.VertexAttribFormat(attribindex.value, size, detail::to_gl_enum(type), normalized, relativeoffset);
        METAGL_DEBUG_LOG_VOID("glVertexAttribFormat", attribindex.value, size, type, normalized, relativeoffset);
    }

    // #94
    void glVertexAttribIFormat(AttribLocation attribindex, GLint size, DataType type, GLuint relativeoffset)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribIFormat != nullptr)) std::terminate();
        detail::g_gl.VertexAttribIFormat(attribindex.value, size, detail::to_gl_enum(type), relativeoffset);
        METAGL_DEBUG_LOG_VOID("glVertexAttribIFormat", attribindex.value, size, type, relativeoffset);
    }

    // #95
    void glVertexAttribBinding(AttribLocation attribindex, GLuint bindingindex)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexAttribBinding != nullptr)) std::terminate();
        detail::g_gl.VertexAttribBinding(attribindex.value, bindingindex);
        METAGL_DEBUG_LOG_VOID("glVertexAttribBinding", attribindex.value, bindingindex);
    }

    // #96
    void glBindVertexBuffer(GLuint bindingindex, BufferId buffer, GLintptr offset, GLsizei stride)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindVertexBuffer != nullptr)) std::terminate();
        detail::g_gl.BindVertexBuffer(bindingindex, buffer.value, offset, stride);
        METAGL_DEBUG_LOG_VOID("glBindVertexBuffer", bindingindex, buffer.value, offset, stride);
    }

    // #97
    void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.VertexBindingDivisor != nullptr)) std::terminate();
        detail::g_gl.VertexBindingDivisor(bindingindex, divisor);
        METAGL_DEBUG_LOG_VOID("glVertexBindingDivisor", bindingindex, divisor);
    }

    // #98
    void glDrawArrays(PrimitiveType mode, GLint first, GLsizei count)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawArrays != nullptr)) std::terminate();
        detail::g_gl.DrawArrays(detail::to_gl_enum(mode), first, count);
        METAGL_DEBUG_LOG_VOID("glDrawArrays", mode, first, count);
    }

    // #99
    void glDrawArraysInstanced(PrimitiveType mode, GLint first, GLsizei count, GLsizei instancecount)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawArraysInstanced != nullptr)) std::terminate();
        detail::g_gl.DrawArraysInstanced(detail::to_gl_enum(mode), first, count, instancecount);
        METAGL_DEBUG_LOG_VOID("glDrawArraysInstanced", mode, first, count, instancecount);
    }

    // #100
    void glDrawArraysIndirect(PrimitiveType mode, const void * indirect)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawArraysIndirect != nullptr)) std::terminate();
        detail::g_gl.DrawArraysIndirect(detail::to_gl_enum(mode), indirect);
        METAGL_DEBUG_LOG_VOID("glDrawArraysIndirect", mode, indirect);
    }

    // #101
    void glDrawElements(PrimitiveType mode, GLsizei count, DataType type, const void * indices)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawElements != nullptr)) std::terminate();
        detail::g_gl.DrawElements(detail::to_gl_enum(mode), count, detail::to_gl_enum(type), indices);
        METAGL_DEBUG_LOG_VOID("glDrawElements", mode, count, type, indices);
    }

    // #102
    void glDrawElementsInstanced(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLsizei instancecount)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawElementsInstanced != nullptr)) std::terminate();
        detail::g_gl.DrawElementsInstanced(detail::to_gl_enum(mode), count, detail::to_gl_enum(type), indices, instancecount);
        METAGL_DEBUG_LOG_VOID("glDrawElementsInstanced", mode, count, type, indices, instancecount);
    }

    // #103
    void glDrawRangeElements(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, DataType type, const void * indices)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawRangeElements != nullptr)) std::terminate();
        detail::g_gl.DrawRangeElements(detail::to_gl_enum(mode), start, end, count, detail::to_gl_enum(type), indices);
        METAGL_DEBUG_LOG_VOID("glDrawRangeElements", mode, start, end, count, type, indices);
    }

    // #104
    void glDrawElementsBaseVertex(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLint basevertex)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawElementsBaseVertex != nullptr)) std::terminate();
        detail::g_gl.DrawElementsBaseVertex(detail::to_gl_enum(mode), count, detail::to_gl_enum(type), indices, basevertex);
        METAGL_DEBUG_LOG_VOID("glDrawElementsBaseVertex", mode, count, type, indices, basevertex);
    }

    // #105
    void glDrawElementsInstancedBaseVertex(PrimitiveType mode, GLsizei count, DataType type, const void * indices, GLsizei instancecount, GLint basevertex)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawElementsInstancedBaseVertex != nullptr)) std::terminate();
        detail::g_gl.DrawElementsInstancedBaseVertex(detail::to_gl_enum(mode), count, detail::to_gl_enum(type), indices, instancecount, basevertex);
        METAGL_DEBUG_LOG_VOID("glDrawElementsInstancedBaseVertex", mode, count, type, indices, instancecount, basevertex);
    }

    // #106
    void glDrawRangeElementsBaseVertex(PrimitiveType mode, GLuint start, GLuint end, GLsizei count, DataType type, const void * indices, GLint basevertex)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawRangeElementsBaseVertex != nullptr)) std::terminate();
        detail::g_gl.DrawRangeElementsBaseVertex(detail::to_gl_enum(mode), start, end, count, detail::to_gl_enum(type), indices, basevertex);
        METAGL_DEBUG_LOG_VOID("glDrawRangeElementsBaseVertex", mode, start, end, count, type, indices, basevertex);
    }

    // #107
    void glDrawElementsIndirect(PrimitiveType mode, DataType type, const void * indirect)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawElementsIndirect != nullptr)) std::terminate();
        detail::g_gl.DrawElementsIndirect(detail::to_gl_enum(mode), detail::to_gl_enum(type), indirect);
        METAGL_DEBUG_LOG_VOID("glDrawElementsIndirect", mode, type, indirect);
    }

    // #108
    void glDrawBuffers(GLsizei n, const DrawBuffer * bufs)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DrawBuffers != nullptr)) std::terminate();
        detail::g_gl.DrawBuffers(n, reinterpret_cast<const GLenum *>(bufs));
        METAGL_DEBUG_LOG_VOID("glDrawBuffers", n, bufs);
    }

    // #109
    void glReadBuffer(ReadBuffer src)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ReadBuffer != nullptr)) std::terminate();
        detail::g_gl.ReadBuffer(detail::to_gl_enum(src));
        METAGL_DEBUG_LOG_VOID("glReadBuffer", src);
    }

    // #110
    void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelFormat format, PixelType type, void * pixels)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ReadPixels != nullptr)) std::terminate();
        detail::g_gl.ReadPixels(x, y, width, height, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
        METAGL_DEBUG_LOG_VOID("glReadPixels", x, y, width, height, format, type, pixels);
    }

    // #111
    void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, PixelFormat format, PixelType type, GLsizei bufSize, void * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ReadnPixels != nullptr)) std::terminate();
        detail::g_gl.ReadnPixels(x, y, width, height, detail::to_gl_enum(format), detail::to_gl_enum(type), bufSize, data);
        METAGL_DEBUG_LOG_VOID("glReadnPixels", x, y, width, height, format, type, bufSize, data);
    }

    // #112
    void glClear(ClearBufferBit mask)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Clear != nullptr)) std::terminate();
        detail::g_gl.Clear(detail::to_gl_bitfield(mask));
        METAGL_DEBUG_LOG_VOID("glClear", mask);
    }

    // #113
    void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ClearColor != nullptr)) std::terminate();
        detail::g_gl.ClearColor(red, green, blue, alpha);
        METAGL_DEBUG_LOG_VOID("glClearColor", red, green, blue, alpha);
    }

    // #114
    void glClearDepthf(GLfloat d)
    {
        if (!(detail::g_gl.initialized
            && (detail::g_gl.ClearDepthf != nullptr
                || detail::g_gl.DesktopClearDepth != nullptr))) std::terminate();
        if (detail::g_gl.ClearDepthf)
            detail::g_gl.ClearDepthf(d);
        else
            detail::g_gl.DesktopClearDepth(static_cast<double>(d));
        METAGL_DEBUG_LOG_VOID("glClearDepthf", d);
    }

    // #115
    void glClearStencil(GLint s)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ClearStencil != nullptr)) std::terminate();
        detail::g_gl.ClearStencil(s);
        METAGL_DEBUG_LOG_VOID("glClearStencil", s);
    }

    // #116
    void glClearBufferfv(FloatClearBuffer buffer, GLint drawbuffer, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ClearBufferfv != nullptr)) std::terminate();
        detail::g_gl.ClearBufferfv(detail::to_gl_enum(buffer), drawbuffer, value);
        METAGL_DEBUG_LOG_VOID("glClearBufferfv", buffer, drawbuffer, value);
    }

    // #117
    void glClearBufferiv(SignedIntegerClearBuffer buffer, GLint drawbuffer, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ClearBufferiv != nullptr)) std::terminate();
        detail::g_gl.ClearBufferiv(detail::to_gl_enum(buffer), drawbuffer, value);
        METAGL_DEBUG_LOG_VOID("glClearBufferiv", buffer, drawbuffer, value);
    }

    // #118
    void glClearBufferuiv(UnsignedIntegerClearBuffer buffer, GLint drawbuffer, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ClearBufferuiv != nullptr)) std::terminate();
        detail::g_gl.ClearBufferuiv(detail::to_gl_enum(buffer), drawbuffer, value);
        METAGL_DEBUG_LOG_VOID("glClearBufferuiv", buffer, drawbuffer, value);
    }

    // #119
    void glClearBufferfi(GLfloat depth, GLint stencil)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ClearBufferfi != nullptr)) std::terminate();
        detail::g_gl.ClearBufferfi(GL_DEPTH_STENCIL, 0, depth, stencil);
        METAGL_DEBUG_LOG_VOID("glClearBufferfi", depth, stencil);
    }

    // #120
    ShaderId glCreateShader(ShaderType type)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CreateShader != nullptr)) std::terminate();
        const ShaderId _r{detail::g_gl.CreateShader(detail::to_gl_enum(type))};
        METAGL_DEBUG_LOG("glCreateShader", _r.value, type);
        return _r;
    }

    // #121
    void glDeleteShader(ShaderId shader)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteShader != nullptr)) std::terminate();
        detail::g_gl.DeleteShader(shader.value);
        METAGL_DEBUG_LOG_VOID("glDeleteShader", shader.value);
    }

    // #122
    void glShaderSource(ShaderId shader, GLsizei count, const GLchar *const* string, const GLint * length)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ShaderSource != nullptr)) std::terminate();
        detail::g_gl.ShaderSource(shader.value, count, string, length);
        METAGL_DEBUG_LOG_VOID("glShaderSource", shader.value, count, string, length);
    }

    // #123
    void glCompileShader(ShaderId shader)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CompileShader != nullptr)) std::terminate();
        detail::g_gl.CompileShader(shader.value);
        METAGL_DEBUG_LOG_VOID("glCompileShader", shader.value);
    }

    // #124
    void glShaderBinary(GLsizei count, const ShaderId * shaders, ShaderBinaryFormat binaryFormat, const void * binary, GLsizei length)
    {
        static_assert(sizeof(ShaderId) == sizeof(GLuint), "ShaderId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.ShaderBinary != nullptr)) std::terminate();
        detail::g_gl.ShaderBinary(count, reinterpret_cast<const GLuint*>(shaders), detail::to_gl_enum(binaryFormat), binary, length);
        METAGL_DEBUG_LOG_VOID("glShaderBinary", count, shaders, binaryFormat, binary, length);
    }

    // #125
    void glReleaseShaderCompiler(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ReleaseShaderCompiler != nullptr)) std::terminate();
        detail::g_gl.ReleaseShaderCompiler();
        METAGL_DEBUG_LOG_VOID("glReleaseShaderCompiler");
    }

    // #126
    void glGetShaderiv(ShaderId shader, ShaderParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetShaderiv != nullptr)) std::terminate();
        detail::g_gl.GetShaderiv(shader.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetShaderiv", shader.value, pname, params);
    }

    // #127
    void glGetShaderInfoLog(ShaderId shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetShaderInfoLog != nullptr)) std::terminate();
        detail::g_gl.GetShaderInfoLog(shader.value, bufSize, length, infoLog);
        METAGL_DEBUG_LOG_VOID("glGetShaderInfoLog", shader.value, bufSize, length, infoLog);
    }

    // #128
    void glGetShaderSource(ShaderId shader, GLsizei bufSize, GLsizei * length, GLchar * source)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetShaderSource != nullptr)) std::terminate();
        detail::g_gl.GetShaderSource(shader.value, bufSize, length, source);
        METAGL_DEBUG_LOG_VOID("glGetShaderSource", shader.value, bufSize, length, source);
    }

    // #129
    void glGetShaderPrecisionFormat(ShaderType shadertype, PrecisionType precisiontype, GLint * range, GLint * precision)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetShaderPrecisionFormat != nullptr)) std::terminate();
        detail::g_gl.GetShaderPrecisionFormat(detail::to_gl_enum(shadertype), detail::to_gl_enum(precisiontype), range, precision);
        METAGL_DEBUG_LOG_VOID("glGetShaderPrecisionFormat", shadertype, precisiontype, range, precision);
    }

    // #130
    bool glIsShader(ShaderId shader)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsShader != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsShader(shader.value);
        METAGL_DEBUG_LOG("glIsShader", _r, shader.value);
        return _r;
    }

    // #131
    ProgramId glCreateProgram(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CreateProgram != nullptr)) std::terminate();
        const ProgramId _r{detail::g_gl.CreateProgram()};
        METAGL_DEBUG_LOG("glCreateProgram", _r.value);
        return _r;
    }

    // #132
    void glDeleteProgram(ProgramId program)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteProgram != nullptr)) std::terminate();
        detail::g_gl.DeleteProgram(program.value);
        METAGL_DEBUG_LOG_VOID("glDeleteProgram", program.value);
    }

    // #133
    void glAttachShader(ProgramId program, ShaderId shader)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.AttachShader != nullptr)) std::terminate();
        detail::g_gl.AttachShader(program.value, shader.value);
        METAGL_DEBUG_LOG_VOID("glAttachShader", program.value, shader.value);
    }

    // #134
    void glDetachShader(ProgramId program, ShaderId shader)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DetachShader != nullptr)) std::terminate();
        detail::g_gl.DetachShader(program.value, shader.value);
        METAGL_DEBUG_LOG_VOID("glDetachShader", program.value, shader.value);
    }

    // #135
    void glLinkProgram(ProgramId program)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.LinkProgram != nullptr)) std::terminate();
        detail::g_gl.LinkProgram(program.value);
        METAGL_DEBUG_LOG_VOID("glLinkProgram", program.value);
    }

    // #136
    void glUseProgram(ProgramId program)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UseProgram != nullptr)) std::terminate();
        detail::g_gl.UseProgram(program.value);
        METAGL_DEBUG_LOG_VOID("glUseProgram", program.value);
    }

    // #137
    void glValidateProgram(ProgramId program)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ValidateProgram != nullptr)) std::terminate();
        detail::g_gl.ValidateProgram(program.value);
        METAGL_DEBUG_LOG_VOID("glValidateProgram", program.value);
    }

    // #138
    void glGetProgramiv(ProgramId program, ProgramParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramiv != nullptr)) std::terminate();
        detail::g_gl.GetProgramiv(program.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetProgramiv", program.value, pname, params);
    }

    // #139
    void glGetProgramInfoLog(ProgramId program, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramInfoLog != nullptr)) std::terminate();
        detail::g_gl.GetProgramInfoLog(program.value, bufSize, length, infoLog);
        METAGL_DEBUG_LOG_VOID("glGetProgramInfoLog", program.value, bufSize, length, infoLog);
    }

    // #140
    bool glIsProgram(ProgramId program)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsProgram != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsProgram(program.value);
        METAGL_DEBUG_LOG("glIsProgram", _r, program.value);
        return _r;
    }

    // #141
    void glGetAttachedShaders(ProgramId program, GLsizei maxCount, GLsizei * count, ShaderId * shaders)
    {
        static_assert(sizeof(ShaderId) == sizeof(GLuint), "ShaderId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GetAttachedShaders != nullptr)) std::terminate();
        detail::g_gl.GetAttachedShaders(program.value, maxCount, count, reinterpret_cast<GLuint*>(shaders));
        METAGL_DEBUG_LOG_VOID("glGetAttachedShaders", program.value, maxCount, count, shaders);
    }

    // #142
    void glBindAttribLocation(ProgramId program, AttribLocation index, const GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindAttribLocation != nullptr)) std::terminate();
        detail::g_gl.BindAttribLocation(program.value, index.value, name);
        METAGL_DEBUG_LOG_VOID("glBindAttribLocation", program.value, index.value, name);
    }

    // #143
    AttribLocation glGetAttribLocation(ProgramId program, const GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetAttribLocation != nullptr)) std::terminate();
        const AttribLocation _r{detail::g_gl.GetAttribLocation(program.value, name)};
        METAGL_DEBUG_LOG("glGetAttribLocation", _r.value, program.value, name);
        return _r;
    }

    // #144
    void glGetActiveAttrib(ProgramId program, ActiveAttribIndex index, GLsizei bufSize, GLsizei * length, GLint * size, UniformType * type, GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetActiveAttrib != nullptr)) std::terminate();
        detail::g_gl.GetActiveAttrib(program.value, index.value, bufSize, length, size, reinterpret_cast<GLenum *>(type), name);
        METAGL_DEBUG_LOG_VOID("glGetActiveAttrib", program.value, index.value, bufSize, length, size, type, name);
    }

    // #145
    void glGetProgramBinary(ProgramId program, GLsizei bufSize, GLsizei * length, ProgramBinaryFormat * binaryFormat, void * binary)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramBinary != nullptr)) std::terminate();
        detail::g_gl.GetProgramBinary(program.value, bufSize, length, reinterpret_cast<GLenum *>(binaryFormat), binary);
        METAGL_DEBUG_LOG_VOID("glGetProgramBinary", program.value, bufSize, length, binaryFormat, binary);
    }

    // #146
    void glProgramBinary(ProgramId program, ProgramBinaryFormat binaryFormat, const void * binary, GLsizei length)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramBinary != nullptr)) std::terminate();
        detail::g_gl.ProgramBinary(program.value, detail::to_gl_enum(binaryFormat), binary, length);
        METAGL_DEBUG_LOG_VOID("glProgramBinary", program.value, binaryFormat, binary, length);
    }

    // #147
    void glProgramParameteri(ProgramId program, ProgramParameter pname, GLint value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramParameteri != nullptr)) std::terminate();
        detail::g_gl.ProgramParameteri(program.value, detail::to_gl_enum(pname), value);
        METAGL_DEBUG_LOG_VOID("glProgramParameteri", program.value, pname, value);
    }

    // #148
    GLint glGetFragDataLocation(ProgramId program, const GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetFragDataLocation != nullptr)) std::terminate();
        const auto _r = detail::g_gl.GetFragDataLocation(program.value, name);
        METAGL_DEBUG_LOG("glGetFragDataLocation", _r, program.value, name);
        return _r;
    }

    // #149
    void glGetProgramInterfaceiv(ProgramId program, ProgramInterface programInterface, ProgramInterfaceParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramInterfaceiv != nullptr)) std::terminate();
        detail::g_gl.GetProgramInterfaceiv(program.value, detail::to_gl_enum(programInterface), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetProgramInterfaceiv", program.value, programInterface, pname, params);
    }

    // #150
    GLuint glGetProgramResourceIndex(ProgramId program, ProgramInterface programInterface, const GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramResourceIndex != nullptr)) std::terminate();
        const auto _r = detail::g_gl.GetProgramResourceIndex(program.value, detail::to_gl_enum(programInterface), name);
        METAGL_DEBUG_LOG("glGetProgramResourceIndex", _r, program.value, programInterface, name);
        return _r;
    }

    // #151
    void glGetProgramResourceName(ProgramId program, ProgramInterface programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramResourceName != nullptr)) std::terminate();
        detail::g_gl.GetProgramResourceName(program.value, detail::to_gl_enum(programInterface), index, bufSize, length, name);
        METAGL_DEBUG_LOG_VOID("glGetProgramResourceName", program.value, programInterface, index, bufSize, length, name);
    }

    // #152
    void glGetProgramResourceiv(ProgramId program, ProgramInterface programInterface, GLuint index, GLsizei propCount, const ProgramResourceProperty * props, GLsizei count, GLsizei * length, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramResourceiv != nullptr)) std::terminate();
        detail::g_gl.GetProgramResourceiv(program.value, detail::to_gl_enum(programInterface), index, propCount, reinterpret_cast<const GLenum *>(props), count, length, params);
        METAGL_DEBUG_LOG_VOID("glGetProgramResourceiv", program.value, programInterface, index, propCount, props, count, length, params);
    }

    // #153
    GLint glGetProgramResourceLocation(ProgramId program, ProgramInterface programInterface, const GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramResourceLocation != nullptr)) std::terminate();
        const auto _r = detail::g_gl.GetProgramResourceLocation(program.value, detail::to_gl_enum(programInterface), name);
        METAGL_DEBUG_LOG("glGetProgramResourceLocation", _r, program.value, programInterface, name);
        return _r;
    }

    // #154
    UniformLocation glGetUniformLocation(ProgramId program, const GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetUniformLocation != nullptr)) std::terminate();
        const UniformLocation _r{detail::g_gl.GetUniformLocation(program.value, name)};
        METAGL_DEBUG_LOG("glGetUniformLocation", _r.value, program.value, name);
        return _r;
    }

    // #155
    void glGetActiveUniform(ProgramId program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, UniformType * type, GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetActiveUniform != nullptr)) std::terminate();
        detail::g_gl.GetActiveUniform(program.value, index, bufSize, length, size, reinterpret_cast<GLenum *>(type), name);
        METAGL_DEBUG_LOG_VOID("glGetActiveUniform", program.value, index, bufSize, length, size, type, name);
    }

    // #156
    void glGetActiveUniformsiv(ProgramId program, GLsizei uniformCount, const GLuint * uniformIndices, UniformParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetActiveUniformsiv != nullptr)) std::terminate();
        detail::g_gl.GetActiveUniformsiv(program.value, uniformCount, uniformIndices, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetActiveUniformsiv", program.value, uniformCount, uniformIndices, pname, params);
    }

    // #157
    void glGetUniformIndices(ProgramId program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetUniformIndices != nullptr)) std::terminate();
        detail::g_gl.GetUniformIndices(program.value, uniformCount, uniformNames, uniformIndices);
        METAGL_DEBUG_LOG_VOID("glGetUniformIndices", program.value, uniformCount, uniformNames, uniformIndices);
    }

    // #158
    GLuint glGetUniformBlockIndex(ProgramId program, const GLchar * uniformBlockName)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetUniformBlockIndex != nullptr)) std::terminate();
        const auto _r = detail::g_gl.GetUniformBlockIndex(program.value, uniformBlockName);
        METAGL_DEBUG_LOG("glGetUniformBlockIndex", _r, program.value, uniformBlockName);
        return _r;
    }

    // #159
    void glGetActiveUniformBlockiv(ProgramId program, GLuint uniformBlockIndex, UniformBlockParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetActiveUniformBlockiv != nullptr)) std::terminate();
        detail::g_gl.GetActiveUniformBlockiv(program.value, uniformBlockIndex, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetActiveUniformBlockiv", program.value, uniformBlockIndex, pname, params);
    }

    // #160
    void glGetActiveUniformBlockName(ProgramId program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetActiveUniformBlockName != nullptr)) std::terminate();
        detail::g_gl.GetActiveUniformBlockName(program.value, uniformBlockIndex, bufSize, length, uniformBlockName);
        METAGL_DEBUG_LOG_VOID("glGetActiveUniformBlockName", program.value, uniformBlockIndex, bufSize, length, uniformBlockName);
    }

    // #161
    void glUniformBlockBinding(ProgramId program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformBlockBinding != nullptr)) std::terminate();
        detail::g_gl.UniformBlockBinding(program.value, uniformBlockIndex, uniformBlockBinding);
        METAGL_DEBUG_LOG_VOID("glUniformBlockBinding", program.value, uniformBlockIndex, uniformBlockBinding);
    }

    // #162
    void glUniform1f(UniformLocation location, GLfloat v0)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform1f != nullptr)) std::terminate();
        detail::g_gl.Uniform1f(location.value, v0);
        METAGL_DEBUG_LOG_VOID("glUniform1f", location.value, v0);
    }

    // #163
    void glUniform2f(UniformLocation location, GLfloat v0, GLfloat v1)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform2f != nullptr)) std::terminate();
        detail::g_gl.Uniform2f(location.value, v0, v1);
        METAGL_DEBUG_LOG_VOID("glUniform2f", location.value, v0, v1);
    }

    // #164
    void glUniform3f(UniformLocation location, GLfloat v0, GLfloat v1, GLfloat v2)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform3f != nullptr)) std::terminate();
        detail::g_gl.Uniform3f(location.value, v0, v1, v2);
        METAGL_DEBUG_LOG_VOID("glUniform3f", location.value, v0, v1, v2);
    }

    // #165
    void glUniform4f(UniformLocation location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform4f != nullptr)) std::terminate();
        detail::g_gl.Uniform4f(location.value, v0, v1, v2, v3);
        METAGL_DEBUG_LOG_VOID("glUniform4f", location.value, v0, v1, v2, v3);
    }

    // #166
    void glUniform1fv(UniformLocation location, GLsizei count, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform1fv != nullptr)) std::terminate();
        detail::g_gl.Uniform1fv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform1fv", location.value, count, value);
    }

    // #167
    void glUniform2fv(UniformLocation location, GLsizei count, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform2fv != nullptr)) std::terminate();
        detail::g_gl.Uniform2fv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform2fv", location.value, count, value);
    }

    // #168
    void glUniform3fv(UniformLocation location, GLsizei count, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform3fv != nullptr)) std::terminate();
        detail::g_gl.Uniform3fv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform3fv", location.value, count, value);
    }

    // #169
    void glUniform4fv(UniformLocation location, GLsizei count, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform4fv != nullptr)) std::terminate();
        detail::g_gl.Uniform4fv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform4fv", location.value, count, value);
    }

    // #170
    void glUniform1i(UniformLocation location, GLint v0)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform1i != nullptr)) std::terminate();
        detail::g_gl.Uniform1i(location.value, v0);
        METAGL_DEBUG_LOG_VOID("glUniform1i", location.value, v0);
    }

    // #171
    void glUniform2i(UniformLocation location, GLint v0, GLint v1)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform2i != nullptr)) std::terminate();
        detail::g_gl.Uniform2i(location.value, v0, v1);
        METAGL_DEBUG_LOG_VOID("glUniform2i", location.value, v0, v1);
    }

    // #172
    void glUniform3i(UniformLocation location, GLint v0, GLint v1, GLint v2)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform3i != nullptr)) std::terminate();
        detail::g_gl.Uniform3i(location.value, v0, v1, v2);
        METAGL_DEBUG_LOG_VOID("glUniform3i", location.value, v0, v1, v2);
    }

    // #173
    void glUniform4i(UniformLocation location, GLint v0, GLint v1, GLint v2, GLint v3)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform4i != nullptr)) std::terminate();
        detail::g_gl.Uniform4i(location.value, v0, v1, v2, v3);
        METAGL_DEBUG_LOG_VOID("glUniform4i", location.value, v0, v1, v2, v3);
    }

    // #174
    void glUniform1iv(UniformLocation location, GLsizei count, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform1iv != nullptr)) std::terminate();
        detail::g_gl.Uniform1iv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform1iv", location.value, count, value);
    }

    // #175
    void glUniform2iv(UniformLocation location, GLsizei count, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform2iv != nullptr)) std::terminate();
        detail::g_gl.Uniform2iv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform2iv", location.value, count, value);
    }

    // #176
    void glUniform3iv(UniformLocation location, GLsizei count, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform3iv != nullptr)) std::terminate();
        detail::g_gl.Uniform3iv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform3iv", location.value, count, value);
    }

    // #177
    void glUniform4iv(UniformLocation location, GLsizei count, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform4iv != nullptr)) std::terminate();
        detail::g_gl.Uniform4iv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform4iv", location.value, count, value);
    }

    // #178
    void glUniform1ui(UniformLocation location, GLuint v0)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform1ui != nullptr)) std::terminate();
        detail::g_gl.Uniform1ui(location.value, v0);
        METAGL_DEBUG_LOG_VOID("glUniform1ui", location.value, v0);
    }

    // #179
    void glUniform2ui(UniformLocation location, GLuint v0, GLuint v1)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform2ui != nullptr)) std::terminate();
        detail::g_gl.Uniform2ui(location.value, v0, v1);
        METAGL_DEBUG_LOG_VOID("glUniform2ui", location.value, v0, v1);
    }

    // #180
    void glUniform3ui(UniformLocation location, GLuint v0, GLuint v1, GLuint v2)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform3ui != nullptr)) std::terminate();
        detail::g_gl.Uniform3ui(location.value, v0, v1, v2);
        METAGL_DEBUG_LOG_VOID("glUniform3ui", location.value, v0, v1, v2);
    }

    // #181
    void glUniform4ui(UniformLocation location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform4ui != nullptr)) std::terminate();
        detail::g_gl.Uniform4ui(location.value, v0, v1, v2, v3);
        METAGL_DEBUG_LOG_VOID("glUniform4ui", location.value, v0, v1, v2, v3);
    }

    // #182
    void glUniform1uiv(UniformLocation location, GLsizei count, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform1uiv != nullptr)) std::terminate();
        detail::g_gl.Uniform1uiv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform1uiv", location.value, count, value);
    }

    // #183
    void glUniform2uiv(UniformLocation location, GLsizei count, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform2uiv != nullptr)) std::terminate();
        detail::g_gl.Uniform2uiv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform2uiv", location.value, count, value);
    }

    // #184
    void glUniform3uiv(UniformLocation location, GLsizei count, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform3uiv != nullptr)) std::terminate();
        detail::g_gl.Uniform3uiv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform3uiv", location.value, count, value);
    }

    // #185
    void glUniform4uiv(UniformLocation location, GLsizei count, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.Uniform4uiv != nullptr)) std::terminate();
        detail::g_gl.Uniform4uiv(location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glUniform4uiv", location.value, count, value);
    }

    // #186
    void glUniformMatrix2fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix2fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix2fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix2fv", location.value, count, transpose, value);
    }

    // #187
    void glUniformMatrix3fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix3fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix3fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix3fv", location.value, count, transpose, value);
    }

    // #188
    void glUniformMatrix4fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix4fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix4fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix4fv", location.value, count, transpose, value);
    }

    // #189
    void glUniformMatrix2x3fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix2x3fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix2x3fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix2x3fv", location.value, count, transpose, value);
    }

    // #190
    void glUniformMatrix2x4fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix2x4fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix2x4fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix2x4fv", location.value, count, transpose, value);
    }

    // #191
    void glUniformMatrix3x2fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix3x2fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix3x2fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix3x2fv", location.value, count, transpose, value);
    }

    // #192
    void glUniformMatrix3x4fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix3x4fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix3x4fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix3x4fv", location.value, count, transpose, value);
    }

    // #193
    void glUniformMatrix4x2fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix4x2fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix4x2fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix4x2fv", location.value, count, transpose, value);
    }

    // #194
    void glUniformMatrix4x3fv(UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UniformMatrix4x3fv != nullptr)) std::terminate();
        detail::g_gl.UniformMatrix4x3fv(location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glUniformMatrix4x3fv", location.value, count, transpose, value);
    }

    // #195
    void glGetUniformfv(ProgramId program, UniformLocation location, GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetUniformfv != nullptr)) std::terminate();
        detail::g_gl.GetUniformfv(program.value, location.value, params);
        METAGL_DEBUG_LOG_VOID("glGetUniformfv", program.value, location.value, params);
    }

    // #196
    void glGetUniformiv(ProgramId program, UniformLocation location, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetUniformiv != nullptr)) std::terminate();
        detail::g_gl.GetUniformiv(program.value, location.value, params);
        METAGL_DEBUG_LOG_VOID("glGetUniformiv", program.value, location.value, params);
    }

    // #197
    void glGetUniformuiv(ProgramId program, UniformLocation location, GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetUniformuiv != nullptr)) std::terminate();
        detail::g_gl.GetUniformuiv(program.value, location.value, params);
        METAGL_DEBUG_LOG_VOID("glGetUniformuiv", program.value, location.value, params);
    }

    // #198
    void glGetnUniformfv(ProgramId program, UniformLocation location, GLsizei bufSize, GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetnUniformfv != nullptr)) std::terminate();
        detail::g_gl.GetnUniformfv(program.value, location.value, bufSize, params);
        METAGL_DEBUG_LOG_VOID("glGetnUniformfv", program.value, location.value, bufSize, params);
    }

    // #199
    void glGetnUniformiv(ProgramId program, UniformLocation location, GLsizei bufSize, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetnUniformiv != nullptr)) std::terminate();
        detail::g_gl.GetnUniformiv(program.value, location.value, bufSize, params);
        METAGL_DEBUG_LOG_VOID("glGetnUniformiv", program.value, location.value, bufSize, params);
    }

    // #200
    void glGetnUniformuiv(ProgramId program, UniformLocation location, GLsizei bufSize, GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetnUniformuiv != nullptr)) std::terminate();
        detail::g_gl.GetnUniformuiv(program.value, location.value, bufSize, params);
        METAGL_DEBUG_LOG_VOID("glGetnUniformuiv", program.value, location.value, bufSize, params);
    }

    // #201
    void glProgramUniform1f(ProgramId program, UniformLocation location, GLfloat v0)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform1f != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform1f(program.value, location.value, v0);
        METAGL_DEBUG_LOG_VOID("glProgramUniform1f", program.value, location.value, v0);
    }

    // #202
    void glProgramUniform2f(ProgramId program, UniformLocation location, GLfloat v0, GLfloat v1)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform2f != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform2f(program.value, location.value, v0, v1);
        METAGL_DEBUG_LOG_VOID("glProgramUniform2f", program.value, location.value, v0, v1);
    }

    // #203
    void glProgramUniform3f(ProgramId program, UniformLocation location, GLfloat v0, GLfloat v1, GLfloat v2)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform3f != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform3f(program.value, location.value, v0, v1, v2);
        METAGL_DEBUG_LOG_VOID("glProgramUniform3f", program.value, location.value, v0, v1, v2);
    }

    // #204
    void glProgramUniform4f(ProgramId program, UniformLocation location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform4f != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform4f(program.value, location.value, v0, v1, v2, v3);
        METAGL_DEBUG_LOG_VOID("glProgramUniform4f", program.value, location.value, v0, v1, v2, v3);
    }

    // #205
    void glProgramUniform1fv(ProgramId program, UniformLocation location, GLsizei count, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform1fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform1fv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform1fv", program.value, location.value, count, value);
    }

    // #206
    void glProgramUniform2fv(ProgramId program, UniformLocation location, GLsizei count, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform2fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform2fv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform2fv", program.value, location.value, count, value);
    }

    // #207
    void glProgramUniform3fv(ProgramId program, UniformLocation location, GLsizei count, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform3fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform3fv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform3fv", program.value, location.value, count, value);
    }

    // #208
    void glProgramUniform4fv(ProgramId program, UniformLocation location, GLsizei count, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform4fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform4fv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform4fv", program.value, location.value, count, value);
    }

    // #209
    void glProgramUniform1i(ProgramId program, UniformLocation location, GLint v0)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform1i != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform1i(program.value, location.value, v0);
        METAGL_DEBUG_LOG_VOID("glProgramUniform1i", program.value, location.value, v0);
    }

    // #210
    void glProgramUniform2i(ProgramId program, UniformLocation location, GLint v0, GLint v1)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform2i != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform2i(program.value, location.value, v0, v1);
        METAGL_DEBUG_LOG_VOID("glProgramUniform2i", program.value, location.value, v0, v1);
    }

    // #211
    void glProgramUniform3i(ProgramId program, UniformLocation location, GLint v0, GLint v1, GLint v2)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform3i != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform3i(program.value, location.value, v0, v1, v2);
        METAGL_DEBUG_LOG_VOID("glProgramUniform3i", program.value, location.value, v0, v1, v2);
    }

    // #212
    void glProgramUniform4i(ProgramId program, UniformLocation location, GLint v0, GLint v1, GLint v2, GLint v3)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform4i != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform4i(program.value, location.value, v0, v1, v2, v3);
        METAGL_DEBUG_LOG_VOID("glProgramUniform4i", program.value, location.value, v0, v1, v2, v3);
    }

    // #213
    void glProgramUniform1iv(ProgramId program, UniformLocation location, GLsizei count, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform1iv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform1iv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform1iv", program.value, location.value, count, value);
    }

    // #214
    void glProgramUniform2iv(ProgramId program, UniformLocation location, GLsizei count, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform2iv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform2iv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform2iv", program.value, location.value, count, value);
    }

    // #215
    void glProgramUniform3iv(ProgramId program, UniformLocation location, GLsizei count, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform3iv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform3iv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform3iv", program.value, location.value, count, value);
    }

    // #216
    void glProgramUniform4iv(ProgramId program, UniformLocation location, GLsizei count, const GLint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform4iv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform4iv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform4iv", program.value, location.value, count, value);
    }

    // #217
    void glProgramUniform1ui(ProgramId program, UniformLocation location, GLuint v0)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform1ui != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform1ui(program.value, location.value, v0);
        METAGL_DEBUG_LOG_VOID("glProgramUniform1ui", program.value, location.value, v0);
    }

    // #218
    void glProgramUniform2ui(ProgramId program, UniformLocation location, GLuint v0, GLuint v1)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform2ui != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform2ui(program.value, location.value, v0, v1);
        METAGL_DEBUG_LOG_VOID("glProgramUniform2ui", program.value, location.value, v0, v1);
    }

    // #219
    void glProgramUniform3ui(ProgramId program, UniformLocation location, GLuint v0, GLuint v1, GLuint v2)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform3ui != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform3ui(program.value, location.value, v0, v1, v2);
        METAGL_DEBUG_LOG_VOID("glProgramUniform3ui", program.value, location.value, v0, v1, v2);
    }

    // #220
    void glProgramUniform4ui(ProgramId program, UniformLocation location, GLuint v0, GLuint v1, GLuint v2, GLuint v3)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform4ui != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform4ui(program.value, location.value, v0, v1, v2, v3);
        METAGL_DEBUG_LOG_VOID("glProgramUniform4ui", program.value, location.value, v0, v1, v2, v3);
    }

    // #221
    void glProgramUniform1uiv(ProgramId program, UniformLocation location, GLsizei count, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform1uiv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform1uiv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform1uiv", program.value, location.value, count, value);
    }

    // #222
    void glProgramUniform2uiv(ProgramId program, UniformLocation location, GLsizei count, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform2uiv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform2uiv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform2uiv", program.value, location.value, count, value);
    }

    // #223
    void glProgramUniform3uiv(ProgramId program, UniformLocation location, GLsizei count, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform3uiv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform3uiv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform3uiv", program.value, location.value, count, value);
    }

    // #224
    void glProgramUniform4uiv(ProgramId program, UniformLocation location, GLsizei count, const GLuint * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniform4uiv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniform4uiv(program.value, location.value, count, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniform4uiv", program.value, location.value, count, value);
    }

    // #225
    void glProgramUniformMatrix2fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix2fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix2fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix2fv", program.value, location.value, count, transpose, value);
    }

    // #226
    void glProgramUniformMatrix3fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix3fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix3fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix3fv", program.value, location.value, count, transpose, value);
    }

    // #227
    void glProgramUniformMatrix4fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix4fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix4fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix4fv", program.value, location.value, count, transpose, value);
    }

    // #228
    void glProgramUniformMatrix2x3fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix2x3fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix2x3fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix2x3fv", program.value, location.value, count, transpose, value);
    }

    // #229
    void glProgramUniformMatrix2x4fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix2x4fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix2x4fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix2x4fv", program.value, location.value, count, transpose, value);
    }

    // #230
    void glProgramUniformMatrix3x2fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix3x2fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix3x2fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix3x2fv", program.value, location.value, count, transpose, value);
    }

    // #231
    void glProgramUniformMatrix3x4fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix3x4fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix3x4fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix3x4fv", program.value, location.value, count, transpose, value);
    }

    // #232
    void glProgramUniformMatrix4x2fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix4x2fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix4x2fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix4x2fv", program.value, location.value, count, transpose, value);
    }

    // #233
    void glProgramUniformMatrix4x3fv(ProgramId program, UniformLocation location, GLsizei count, GLboolean transpose, const GLfloat * value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ProgramUniformMatrix4x3fv != nullptr)) std::terminate();
        detail::g_gl.ProgramUniformMatrix4x3fv(program.value, location.value, count, transpose, value);
        METAGL_DEBUG_LOG_VOID("glProgramUniformMatrix4x3fv", program.value, location.value, count, transpose, value);
    }

    // #234
    void glGenTextures(GLsizei n, TextureId * textures)
    {
        static_assert(sizeof(TextureId) == sizeof(GLuint), "TextureId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenTextures != nullptr)) std::terminate();
        detail::g_gl.GenTextures(n, reinterpret_cast<GLuint*>(textures));
        METAGL_DEBUG_LOG_VOID("glGenTextures", n, textures);
    }

    // #235
    void glDeleteTextures(GLsizei n, const TextureId * textures)
    {
        static_assert(sizeof(TextureId) == sizeof(GLuint), "TextureId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteTextures != nullptr)) std::terminate();
        detail::g_gl.DeleteTextures(n, reinterpret_cast<const GLuint*>(textures));
        METAGL_DEBUG_LOG_VOID("glDeleteTextures", n, textures);
    }

    // #236
    void glBindTexture(TextureTarget target, TextureId texture)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindTexture != nullptr)) std::terminate();
        detail::g_gl.BindTexture(detail::to_gl_enum(target), texture.value);
        METAGL_DEBUG_LOG_VOID("glBindTexture", target, texture.value);
    }

    // #237
    void glActiveTexture(TextureUnit texture)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ActiveTexture != nullptr)) std::terminate();
        detail::g_gl.ActiveTexture(detail::to_gl_enum(texture));
        METAGL_DEBUG_LOG_VOID("glActiveTexture", texture);
    }

    // #238
    bool glIsTexture(TextureId texture)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsTexture != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsTexture(texture.value);
        METAGL_DEBUG_LOG("glIsTexture", _r, texture.value);
        return _r;
    }

    // #239
    void glTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat, GLsizei width, GLsizei height, GLint border, PixelFormat format, PixelType type, const void * pixels)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexImage2D != nullptr)) std::terminate();
        detail::g_gl.TexImage2D(detail::to_gl_enum(target), level, static_cast<GLint>(detail::to_gl_enum(internalformat)), width, height, border, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
        METAGL_DEBUG_LOG_VOID("glTexImage2D", target, level, internalformat, width, height, border, format, type, pixels);
    }

    // #240
    void glTexImage3D(TextureTarget target, GLint level, InternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, PixelFormat format, PixelType type, const void * pixels)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexImage3D != nullptr)) std::terminate();
        detail::g_gl.TexImage3D(detail::to_gl_enum(target), level, static_cast<GLint>(detail::to_gl_enum(internalformat)), width, height, depth, border, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
        METAGL_DEBUG_LOG_VOID("glTexImage3D", target, level, internalformat, width, height, depth, border, format, type, pixels);
    }

    // #241
    void glTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, PixelFormat format, PixelType type, const void * pixels)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexSubImage2D != nullptr)) std::terminate();
        detail::g_gl.TexSubImage2D(detail::to_gl_enum(target), level, xoffset, yoffset, width, height, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
        METAGL_DEBUG_LOG_VOID("glTexSubImage2D", target, level, xoffset, yoffset, width, height, format, type, pixels);
    }

    // #242
    void glTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, PixelFormat format, PixelType type, const void * pixels)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexSubImage3D != nullptr)) std::terminate();
        detail::g_gl.TexSubImage3D(detail::to_gl_enum(target), level, xoffset, yoffset, zoffset, width, height, depth, detail::to_gl_enum(format), detail::to_gl_enum(type), pixels);
        METAGL_DEBUG_LOG_VOID("glTexSubImage3D", target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
    }

    // #243
    void glTexStorage2D(TextureTarget target, GLsizei levels, SizedInternalFormat internalformat, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexStorage2D != nullptr)) std::terminate();
        detail::g_gl.TexStorage2D(detail::to_gl_enum(target), levels, detail::to_gl_enum(internalformat), width, height);
        METAGL_DEBUG_LOG_VOID("glTexStorage2D", target, levels, internalformat, width, height);
    }

    void glTexStorage2D(TextureTarget target, GLsizei levels, CompressedInternalFormat internalformat, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexStorage2D != nullptr)) std::terminate();
        detail::g_gl.TexStorage2D(detail::to_gl_enum(target), levels, detail::to_gl_enum(internalformat), width, height);
        METAGL_DEBUG_LOG_VOID("glTexStorage2D", target, levels, internalformat, width, height);
    }

    // #244
    void glTexStorage3D(TextureTarget target, GLsizei levels, SizedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexStorage3D != nullptr)) std::terminate();
        detail::g_gl.TexStorage3D(detail::to_gl_enum(target), levels, detail::to_gl_enum(internalformat), width, height, depth);
        METAGL_DEBUG_LOG_VOID("glTexStorage3D", target, levels, internalformat, width, height, depth);
    }

    void glTexStorage3D(TextureTarget target, GLsizei levels, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexStorage3D != nullptr)) std::terminate();
        detail::g_gl.TexStorage3D(detail::to_gl_enum(target), levels, detail::to_gl_enum(internalformat), width, height, depth);
        METAGL_DEBUG_LOG_VOID("glTexStorage3D", target, levels, internalformat, width, height, depth);
    }

    // #245
    void glTexStorage2DMultisample(TextureTarget target, GLsizei samples, SizedInternalFormat internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexStorage2DMultisample != nullptr)) std::terminate();
        detail::g_gl.TexStorage2DMultisample(detail::to_gl_enum(target), samples, detail::to_gl_enum(internalformat), width, height, fixedsamplelocations);
        METAGL_DEBUG_LOG_VOID("glTexStorage2DMultisample", target, samples, internalformat, width, height, fixedsamplelocations);
    }

    // #246
    void glTexStorage3DMultisample(TextureTarget target, GLsizei samples, SizedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexStorage3DMultisample != nullptr)) std::terminate();
        detail::g_gl.TexStorage3DMultisample(detail::to_gl_enum(target), samples, detail::to_gl_enum(internalformat), width, height, depth, fixedsamplelocations);
        METAGL_DEBUG_LOG_VOID("glTexStorage3DMultisample", target, samples, internalformat, width, height, depth, fixedsamplelocations);
    }

    // #247
    void glCompressedTexImage2D(TextureTarget target, GLint level, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CompressedTexImage2D != nullptr)) std::terminate();
        detail::g_gl.CompressedTexImage2D(detail::to_gl_enum(target), level, detail::to_gl_enum(internalformat), width, height, border, imageSize, data);
        METAGL_DEBUG_LOG_VOID("glCompressedTexImage2D", target, level, internalformat, width, height, border, imageSize, data);
    }

    // #248
    void glCompressedTexImage3D(TextureTarget target, GLint level, CompressedInternalFormat internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CompressedTexImage3D != nullptr)) std::terminate();
        detail::g_gl.CompressedTexImage3D(detail::to_gl_enum(target), level, detail::to_gl_enum(internalformat), width, height, depth, border, imageSize, data);
        METAGL_DEBUG_LOG_VOID("glCompressedTexImage3D", target, level, internalformat, width, height, depth, border, imageSize, data);
    }

    // #249
    void glCompressedTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, CompressedInternalFormat format, GLsizei imageSize, const void * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CompressedTexSubImage2D != nullptr)) std::terminate();
        detail::g_gl.CompressedTexSubImage2D(detail::to_gl_enum(target), level, xoffset, yoffset, width, height, detail::to_gl_enum(format), imageSize, data);
        METAGL_DEBUG_LOG_VOID("glCompressedTexSubImage2D", target, level, xoffset, yoffset, width, height, format, imageSize, data);
    }

    // #250
    void glCompressedTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, CompressedInternalFormat format, GLsizei imageSize, const void * data)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CompressedTexSubImage3D != nullptr)) std::terminate();
        detail::g_gl.CompressedTexSubImage3D(detail::to_gl_enum(target), level, xoffset, yoffset, zoffset, width, height, depth, detail::to_gl_enum(format), imageSize, data);
        METAGL_DEBUG_LOG_VOID("glCompressedTexSubImage3D", target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
    }

    // #251
    void glCopyTexImage2D(TextureTarget target, GLint level, InternalFormat internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CopyTexImage2D != nullptr)) std::terminate();
        detail::g_gl.CopyTexImage2D(detail::to_gl_enum(target), level, detail::to_gl_enum(internalformat), x, y, width, height, border);
        METAGL_DEBUG_LOG_VOID("glCopyTexImage2D", target, level, internalformat, x, y, width, height, border);
    }

    // #252
    void glCopyTexSubImage2D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CopyTexSubImage2D != nullptr)) std::terminate();
        detail::g_gl.CopyTexSubImage2D(detail::to_gl_enum(target), level, xoffset, yoffset, x, y, width, height);
        METAGL_DEBUG_LOG_VOID("glCopyTexSubImage2D", target, level, xoffset, yoffset, x, y, width, height);
    }

    // #253
    void glCopyTexSubImage3D(TextureTarget target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CopyTexSubImage3D != nullptr)) std::terminate();
        detail::g_gl.CopyTexSubImage3D(detail::to_gl_enum(target), level, xoffset, yoffset, zoffset, x, y, width, height);
        METAGL_DEBUG_LOG_VOID("glCopyTexSubImage3D", target, level, xoffset, yoffset, zoffset, x, y, width, height);
    }

    // #254
    void glCopyImageSubData(GLuint srcName, TextureTarget srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, TextureTarget dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CopyImageSubData != nullptr)) std::terminate();
        detail::g_gl.CopyImageSubData(srcName, detail::to_gl_enum(srcTarget), srcLevel, srcX, srcY, srcZ, dstName, detail::to_gl_enum(dstTarget), dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
        METAGL_DEBUG_LOG_VOID("glCopyImageSubData", srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
    }

    void glCopyImageSubData(TextureId srcName, ImageCopyTextureTarget srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, TextureId dstName, ImageCopyTextureTarget dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth)
    {
        glCopyImageSubData(srcName.value, static_cast<TextureTarget>(detail::to_gl_enum(srcTarget)), srcLevel, srcX, srcY, srcZ, dstName.value, static_cast<TextureTarget>(detail::to_gl_enum(dstTarget)), dstLevel, dstX, dstY, dstZ, width, height, depth);
    }

    void glCopyImageSubData(TextureId srcName, ImageCopyTextureTarget srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, RenderbufferId dstName, GLint dstX, GLint dstY, GLsizei width, GLsizei height)
    {
        glCopyImageSubData(srcName.value, static_cast<TextureTarget>(detail::to_gl_enum(srcTarget)), srcLevel, srcX, srcY, srcZ, dstName.value, static_cast<TextureTarget>(GL_RENDERBUFFER), 0, dstX, dstY, 0, width, height, 1);
    }

    void glCopyImageSubData(RenderbufferId srcName, GLint srcX, GLint srcY, TextureId dstName, ImageCopyTextureTarget dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height)
    {
        glCopyImageSubData(srcName.value, static_cast<TextureTarget>(GL_RENDERBUFFER), 0, srcX, srcY, 0, dstName.value, static_cast<TextureTarget>(detail::to_gl_enum(dstTarget)), dstLevel, dstX, dstY, dstZ, width, height, 1);
    }

    void glCopyImageSubData(RenderbufferId srcName, GLint srcX, GLint srcY, RenderbufferId dstName, GLint dstX, GLint dstY, GLsizei width, GLsizei height)
    {
        glCopyImageSubData(srcName.value, static_cast<TextureTarget>(GL_RENDERBUFFER), 0, srcX, srcY, 0, dstName.value, static_cast<TextureTarget>(GL_RENDERBUFFER), 0, dstX, dstY, 0, width, height, 1);
    }

    // #255
    void glGenerateMipmap(TextureTarget target)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GenerateMipmap != nullptr)) std::terminate();
        detail::g_gl.GenerateMipmap(detail::to_gl_enum(target));
        METAGL_DEBUG_LOG_VOID("glGenerateMipmap", target);
    }

    // #256
    void glTexParameterf(TextureTarget target, TextureParameterSetter pname, GLfloat param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameterf != nullptr)) std::terminate();
        detail::g_gl.TexParameterf(detail::to_gl_enum(target), detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glTexParameterf", target, pname, param);
    }

    void glTexParameterf(TextureTarget target, TextureParameter pname, GLfloat param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameterf != nullptr)) std::terminate();
        detail::g_gl.TexParameterf(detail::to_gl_enum(target), detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glTexParameterf", target, pname, param);
    }

    // #257
    void glTexParameteri(TextureTarget target, TextureParameterSetter pname, GLint param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameteri != nullptr)) std::terminate();
        detail::g_gl.TexParameteri(detail::to_gl_enum(target), detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glTexParameteri", target, pname, param);
    }

    void glTexParameteri(TextureTarget target, TextureParameter pname, GLint param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameteri != nullptr)) std::terminate();
        detail::g_gl.TexParameteri(detail::to_gl_enum(target), detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glTexParameteri", target, pname, param);
    }

    // #258
    void glTexParameterfv(TextureTarget target, TextureParameterSetter pname, const GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameterfv != nullptr)) std::terminate();
        detail::g_gl.TexParameterfv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glTexParameterfv", target, pname, params);
    }

    void glTexParameterfv(TextureTarget target, TextureParameter pname, const GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameterfv != nullptr)) std::terminate();
        detail::g_gl.TexParameterfv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glTexParameterfv", target, pname, params);
    }

    // #259
    void glTexParameteriv(TextureTarget target, TextureParameterSetter pname, const GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameteriv != nullptr)) std::terminate();
        detail::g_gl.TexParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glTexParameteriv", target, pname, params);
    }

    void glTexParameteriv(TextureTarget target, TextureParameter pname, const GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameteriv != nullptr)) std::terminate();
        detail::g_gl.TexParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glTexParameteriv", target, pname, params);
    }

    // #260
    void glTexParameterIiv(TextureTarget target, TextureParameterSetter pname, const GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameterIiv != nullptr)) std::terminate();
        detail::g_gl.TexParameterIiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glTexParameterIiv", target, pname, params);
    }

    void glTexParameterIiv(TextureTarget target, TextureParameter pname, const GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameterIiv != nullptr)) std::terminate();
        detail::g_gl.TexParameterIiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glTexParameterIiv", target, pname, params);
    }

    // #261
    void glTexParameterIuiv(TextureTarget target, TextureParameterSetter pname, const GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameterIuiv != nullptr)) std::terminate();
        detail::g_gl.TexParameterIuiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glTexParameterIuiv", target, pname, params);
    }

    void glTexParameterIuiv(TextureTarget target, TextureParameter pname, const GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexParameterIuiv != nullptr)) std::terminate();
        detail::g_gl.TexParameterIuiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glTexParameterIuiv", target, pname, params);
    }

    // #262
    void glGetTexParameterfv(TextureTarget target, TextureParameterQuery pname, GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexParameterfv != nullptr)) std::terminate();
        detail::g_gl.GetTexParameterfv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexParameterfv", target, pname, params);
    }

    void glGetTexParameterfv(TextureTarget target, TextureParameter pname, GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexParameterfv != nullptr)) std::terminate();
        detail::g_gl.GetTexParameterfv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexParameterfv", target, pname, params);
    }

    // #263
    void glGetTexParameteriv(TextureTarget target, TextureParameterQuery pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetTexParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexParameteriv", target, pname, params);
    }

    void glGetTexParameteriv(TextureTarget target, TextureParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetTexParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexParameteriv", target, pname, params);
    }

    // #264
    void glGetTexParameterIiv(TextureTarget target, TextureParameterQuery pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexParameterIiv != nullptr)) std::terminate();
        detail::g_gl.GetTexParameterIiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexParameterIiv", target, pname, params);
    }

    void glGetTexParameterIiv(TextureTarget target, TextureParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexParameterIiv != nullptr)) std::terminate();
        detail::g_gl.GetTexParameterIiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexParameterIiv", target, pname, params);
    }

    // #265
    void glGetTexParameterIuiv(TextureTarget target, TextureParameterQuery pname, GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexParameterIuiv != nullptr)) std::terminate();
        detail::g_gl.GetTexParameterIuiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexParameterIuiv", target, pname, params);
    }

    void glGetTexParameterIuiv(TextureTarget target, TextureParameter pname, GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexParameterIuiv != nullptr)) std::terminate();
        detail::g_gl.GetTexParameterIuiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexParameterIuiv", target, pname, params);
    }

    // #266
    void glGetTexLevelParameteriv(TextureTarget target, GLint level, TextureLevelParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexLevelParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetTexLevelParameteriv(detail::to_gl_enum(target), level, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexLevelParameteriv", target, level, pname, params);
    }

    // #267
    void glGetTexLevelParameterfv(TextureTarget target, GLint level, TextureLevelParameter pname, GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTexLevelParameterfv != nullptr)) std::terminate();
        detail::g_gl.GetTexLevelParameterfv(detail::to_gl_enum(target), level, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetTexLevelParameterfv", target, level, pname, params);
    }

    // #268
    void glTexBuffer(TextureTarget target, InternalFormat internalformat, BufferId buffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexBuffer != nullptr)) std::terminate();
        detail::g_gl.TexBuffer(detail::to_gl_enum(target), detail::to_gl_enum(internalformat), buffer.value);
        METAGL_DEBUG_LOG_VOID("glTexBuffer", target, internalformat, buffer.value);
    }

    // #269
    void glTexBufferRange(TextureTarget target, InternalFormat internalformat, BufferId buffer, GLintptr offset, GLsizeiptr size)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TexBufferRange != nullptr)) std::terminate();
        detail::g_gl.TexBufferRange(detail::to_gl_enum(target), detail::to_gl_enum(internalformat), buffer.value, offset, size);
        METAGL_DEBUG_LOG_VOID("glTexBufferRange", target, internalformat, buffer.value, offset, size);
    }

    // #270
    void glGetMultisamplefv(MultisampleParameter pname, GLuint index, GLfloat * val)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetMultisamplefv != nullptr)) std::terminate();
        detail::g_gl.GetMultisamplefv(detail::to_gl_enum(pname), index, val);
        METAGL_DEBUG_LOG_VOID("glGetMultisamplefv", pname, index, val);
    }

    // #271
    void glGetInternalformativ(InternalFormatTarget target, InternalFormat internalformat, InternalFormatParameter pname, GLsizei count, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetInternalformativ != nullptr)) std::terminate();
        detail::g_gl.GetInternalformativ(detail::to_gl_enum(target), detail::to_gl_enum(internalformat), detail::to_gl_enum(pname), count, params);
        METAGL_DEBUG_LOG_VOID("glGetInternalformativ", target, internalformat, pname, count, params);
    }

    // #272
    void glBindImageTexture(ImageUnit unit, TextureId texture, GLint level, GLboolean layered, GLint layer, ImageAccess access, InternalFormat format)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindImageTexture != nullptr)) std::terminate();
        detail::g_gl.BindImageTexture(unit.value, texture.value, level, layered, layer, detail::to_gl_enum(access), detail::to_gl_enum(format));
        METAGL_DEBUG_LOG_VOID("glBindImageTexture", unit, texture.value, level, layered, layer, access, format);
    }

    // #273
    void glGenSamplers(GLsizei count, SamplerId * samplers)
    {
        static_assert(sizeof(SamplerId) == sizeof(GLuint), "SamplerId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenSamplers != nullptr)) std::terminate();
        detail::g_gl.GenSamplers(count, reinterpret_cast<GLuint*>(samplers));
        METAGL_DEBUG_LOG_VOID("glGenSamplers", count, samplers);
    }

    // #274
    void glDeleteSamplers(GLsizei count, const SamplerId * samplers)
    {
        static_assert(sizeof(SamplerId) == sizeof(GLuint), "SamplerId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteSamplers != nullptr)) std::terminate();
        detail::g_gl.DeleteSamplers(count, reinterpret_cast<const GLuint*>(samplers));
        METAGL_DEBUG_LOG_VOID("glDeleteSamplers", count, samplers);
    }

    // #275
    void glBindSampler(GLuint unit, SamplerId sampler)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindSampler != nullptr)) std::terminate();
        detail::g_gl.BindSampler(unit, sampler.value);
        METAGL_DEBUG_LOG_VOID("glBindSampler", unit, sampler.value);
    }

    // #276
    bool glIsSampler(SamplerId sampler)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsSampler != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsSampler(sampler.value);
        METAGL_DEBUG_LOG("glIsSampler", _r, sampler.value);
        return _r;
    }

    // #277
    void glSamplerParameterf(SamplerId sampler, SamplerParameter pname, GLfloat param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.SamplerParameterf != nullptr)) std::terminate();
        detail::g_gl.SamplerParameterf(sampler.value, detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glSamplerParameterf", sampler.value, pname, param);
    }

    // #278
    void glSamplerParameteri(SamplerId sampler, SamplerParameter pname, GLint param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.SamplerParameteri != nullptr)) std::terminate();
        detail::g_gl.SamplerParameteri(sampler.value, detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glSamplerParameteri", sampler.value, pname, param);
    }

    // #279
    void glSamplerParameterfv(SamplerId sampler, SamplerParameter pname, const GLfloat * param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.SamplerParameterfv != nullptr)) std::terminate();
        detail::g_gl.SamplerParameterfv(sampler.value, detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glSamplerParameterfv", sampler.value, pname, param);
    }

    // #280
    void glSamplerParameteriv(SamplerId sampler, SamplerParameter pname, const GLint * param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.SamplerParameteriv != nullptr)) std::terminate();
        detail::g_gl.SamplerParameteriv(sampler.value, detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glSamplerParameteriv", sampler.value, pname, param);
    }

    // #281
    void glSamplerParameterIiv(SamplerId sampler, SamplerParameter pname, const GLint * param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.SamplerParameterIiv != nullptr)) std::terminate();
        detail::g_gl.SamplerParameterIiv(sampler.value, detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glSamplerParameterIiv", sampler.value, pname, param);
    }

    // #282
    void glSamplerParameterIuiv(SamplerId sampler, SamplerParameter pname, const GLuint * param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.SamplerParameterIuiv != nullptr)) std::terminate();
        detail::g_gl.SamplerParameterIuiv(sampler.value, detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glSamplerParameterIuiv", sampler.value, pname, param);
    }

    // #283
    void glGetSamplerParameterfv(SamplerId sampler, SamplerParameter pname, GLfloat * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetSamplerParameterfv != nullptr)) std::terminate();
        detail::g_gl.GetSamplerParameterfv(sampler.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetSamplerParameterfv", sampler.value, pname, params);
    }

    // #284
    void glGetSamplerParameteriv(SamplerId sampler, SamplerParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetSamplerParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetSamplerParameteriv(sampler.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetSamplerParameteriv", sampler.value, pname, params);
    }

    // #285
    void glGetSamplerParameterIiv(SamplerId sampler, SamplerParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetSamplerParameterIiv != nullptr)) std::terminate();
        detail::g_gl.GetSamplerParameterIiv(sampler.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetSamplerParameterIiv", sampler.value, pname, params);
    }

    // #286
    void glGetSamplerParameterIuiv(SamplerId sampler, SamplerParameter pname, GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetSamplerParameterIuiv != nullptr)) std::terminate();
        detail::g_gl.GetSamplerParameterIuiv(sampler.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetSamplerParameterIuiv", sampler.value, pname, params);
    }

    // #287
    void glGenFramebuffers(GLsizei n, FramebufferId * framebuffers)
    {
        static_assert(sizeof(FramebufferId) == sizeof(GLuint), "FramebufferId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenFramebuffers != nullptr)) std::terminate();
        detail::g_gl.GenFramebuffers(n, reinterpret_cast<GLuint*>(framebuffers));
        METAGL_DEBUG_LOG_VOID("glGenFramebuffers", n, framebuffers);
    }

    // #288
    void glDeleteFramebuffers(GLsizei n, const FramebufferId * framebuffers)
    {
        static_assert(sizeof(FramebufferId) == sizeof(GLuint), "FramebufferId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteFramebuffers != nullptr)) std::terminate();
        detail::g_gl.DeleteFramebuffers(n, reinterpret_cast<const GLuint*>(framebuffers));
        METAGL_DEBUG_LOG_VOID("glDeleteFramebuffers", n, framebuffers);
    }

    // #289
    void glBindFramebuffer(FramebufferTarget target, FramebufferId framebuffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindFramebuffer != nullptr)) std::terminate();
        detail::g_gl.BindFramebuffer(detail::to_gl_enum(target), framebuffer.value);
        METAGL_DEBUG_LOG_VOID("glBindFramebuffer", target, framebuffer.value);
    }

    // #290
    bool glIsFramebuffer(FramebufferId framebuffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsFramebuffer != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsFramebuffer(framebuffer.value);
        METAGL_DEBUG_LOG("glIsFramebuffer", _r, framebuffer.value);
        return _r;
    }

    // #291
    FramebufferStatus glCheckFramebufferStatus(FramebufferTarget target)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CheckFramebufferStatus != nullptr)) std::terminate();
        const auto _r = static_cast<FramebufferStatus>(
            detail::g_gl.CheckFramebufferStatus(detail::to_gl_enum(target)));
        METAGL_DEBUG_LOG("glCheckFramebufferStatus", _r, target);
        return _r;
    }

    // #292
    void glFramebufferTexture2D(FramebufferTarget target, FramebufferAttachment attachment, TextureTarget textarget, TextureId texture, GLint level)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.FramebufferTexture2D != nullptr)) std::terminate();
        detail::g_gl.FramebufferTexture2D(detail::to_gl_enum(target), detail::to_gl_enum(attachment), detail::to_gl_enum(textarget), texture.value, level);
        METAGL_DEBUG_LOG_VOID("glFramebufferTexture2D", target, attachment, textarget, texture.value, level);
    }

    // #293
    void glFramebufferTextureLayer(FramebufferTarget target, FramebufferAttachment attachment, TextureId texture, GLint level, GLint layer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.FramebufferTextureLayer != nullptr)) std::terminate();
        detail::g_gl.FramebufferTextureLayer(detail::to_gl_enum(target), detail::to_gl_enum(attachment), texture.value, level, layer);
        METAGL_DEBUG_LOG_VOID("glFramebufferTextureLayer", target, attachment, texture.value, level, layer);
    }

    // #294
    void glFramebufferTexture(FramebufferTarget target, FramebufferAttachment attachment, TextureId texture, GLint level)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.FramebufferTexture != nullptr)) std::terminate();
        detail::g_gl.FramebufferTexture(detail::to_gl_enum(target), detail::to_gl_enum(attachment), texture.value, level);
        METAGL_DEBUG_LOG_VOID("glFramebufferTexture", target, attachment, texture.value, level);
    }

    // #295
    void glFramebufferRenderbuffer(FramebufferTarget target, FramebufferAttachment attachment, RenderbufferTarget renderbuffertarget, RenderbufferId renderbuffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.FramebufferRenderbuffer != nullptr)) std::terminate();
        detail::g_gl.FramebufferRenderbuffer(detail::to_gl_enum(target), detail::to_gl_enum(attachment), detail::to_gl_enum(renderbuffertarget), renderbuffer.value);
        METAGL_DEBUG_LOG_VOID("glFramebufferRenderbuffer", target, attachment, renderbuffertarget, renderbuffer.value);
    }

    // #296
    void glFramebufferParameteri(FramebufferTarget target, FramebufferDefaultParameter pname, GLint param)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.FramebufferParameteri != nullptr)) std::terminate();
        detail::g_gl.FramebufferParameteri(detail::to_gl_enum(target), detail::to_gl_enum(pname), param);
        METAGL_DEBUG_LOG_VOID("glFramebufferParameteri", target, pname, param);
    }

    // #297
    void glGetFramebufferParameteriv(FramebufferTarget target, FramebufferDefaultParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetFramebufferParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetFramebufferParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetFramebufferParameteriv", target, pname, params);
    }

    // #298
    void glGetFramebufferAttachmentParameteriv(FramebufferTarget target, FramebufferAttachment attachment, FramebufferAttachmentParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetFramebufferAttachmentParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetFramebufferAttachmentParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(attachment), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetFramebufferAttachmentParameteriv", target, attachment, pname, params);
    }

    void glGetFramebufferAttachmentParameteriv(FramebufferTarget target, DefaultFramebufferQueryAttachment attachment, FramebufferAttachmentParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetFramebufferAttachmentParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetFramebufferAttachmentParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(attachment), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetFramebufferAttachmentParameteriv", target, attachment, pname, params);
    }

    // #299
    void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, ClearBufferBit mask, BlitFilter filter)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BlitFramebuffer != nullptr)) std::terminate();
        detail::g_gl.BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, detail::to_gl_bitfield(mask), detail::to_gl_enum(filter));
        METAGL_DEBUG_LOG_VOID("glBlitFramebuffer", srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
    }

    // #300
    void glInvalidateFramebuffer(FramebufferTarget target, GLsizei numAttachments, const FramebufferAttachment * attachments)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.InvalidateFramebuffer != nullptr)) std::terminate();
        detail::g_gl.InvalidateFramebuffer(detail::to_gl_enum(target), numAttachments, reinterpret_cast<const GLenum *>(attachments));
        METAGL_DEBUG_LOG_VOID("glInvalidateFramebuffer", target, numAttachments, attachments);
    }

    void glInvalidateFramebuffer(FramebufferTarget target, GLsizei numAttachments, const DefaultFramebufferAttachment * attachments)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.InvalidateFramebuffer != nullptr)) std::terminate();
        detail::g_gl.InvalidateFramebuffer(detail::to_gl_enum(target), numAttachments, reinterpret_cast<const GLenum *>(attachments));
        METAGL_DEBUG_LOG_VOID("glInvalidateFramebuffer", target, numAttachments, attachments);
    }

    // #301
    void glInvalidateSubFramebuffer(FramebufferTarget target, GLsizei numAttachments, const FramebufferAttachment * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.InvalidateSubFramebuffer != nullptr)) std::terminate();
        detail::g_gl.InvalidateSubFramebuffer(detail::to_gl_enum(target), numAttachments, reinterpret_cast<const GLenum *>(attachments), x, y, width, height);
        METAGL_DEBUG_LOG_VOID("glInvalidateSubFramebuffer", target, numAttachments, attachments, x, y, width, height);
    }

    void glInvalidateSubFramebuffer(FramebufferTarget target, GLsizei numAttachments, const DefaultFramebufferAttachment * attachments, GLint x, GLint y, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.InvalidateSubFramebuffer != nullptr)) std::terminate();
        detail::g_gl.InvalidateSubFramebuffer(detail::to_gl_enum(target), numAttachments, reinterpret_cast<const GLenum *>(attachments), x, y, width, height);
        METAGL_DEBUG_LOG_VOID("glInvalidateSubFramebuffer", target, numAttachments, attachments, x, y, width, height);
    }

    // #302
    void glGenRenderbuffers(GLsizei n, RenderbufferId * renderbuffers)
    {
        static_assert(sizeof(RenderbufferId) == sizeof(GLuint), "RenderbufferId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenRenderbuffers != nullptr)) std::terminate();
        detail::g_gl.GenRenderbuffers(n, reinterpret_cast<GLuint*>(renderbuffers));
        METAGL_DEBUG_LOG_VOID("glGenRenderbuffers", n, renderbuffers);
    }

    // #303
    void glDeleteRenderbuffers(GLsizei n, const RenderbufferId * renderbuffers)
    {
        static_assert(sizeof(RenderbufferId) == sizeof(GLuint), "RenderbufferId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteRenderbuffers != nullptr)) std::terminate();
        detail::g_gl.DeleteRenderbuffers(n, reinterpret_cast<const GLuint*>(renderbuffers));
        METAGL_DEBUG_LOG_VOID("glDeleteRenderbuffers", n, renderbuffers);
    }

    // #304
    void glBindRenderbuffer(RenderbufferTarget target, RenderbufferId renderbuffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindRenderbuffer != nullptr)) std::terminate();
        detail::g_gl.BindRenderbuffer(detail::to_gl_enum(target), renderbuffer.value);
        METAGL_DEBUG_LOG_VOID("glBindRenderbuffer", target, renderbuffer.value);
    }

    // #305
    bool glIsRenderbuffer(RenderbufferId renderbuffer)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsRenderbuffer != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsRenderbuffer(renderbuffer.value);
        METAGL_DEBUG_LOG("glIsRenderbuffer", _r, renderbuffer.value);
        return _r;
    }

    // #306
    void glRenderbufferStorage(RenderbufferTarget target, InternalFormat internalformat, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.RenderbufferStorage != nullptr)) std::terminate();
        detail::g_gl.RenderbufferStorage(detail::to_gl_enum(target), detail::to_gl_enum(internalformat), width, height);
        METAGL_DEBUG_LOG_VOID("glRenderbufferStorage", target, internalformat, width, height);
    }

    // #307
    void glRenderbufferStorageMultisample(RenderbufferTarget target, GLsizei samples, InternalFormat internalformat, GLsizei width, GLsizei height)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.RenderbufferStorageMultisample != nullptr)) std::terminate();
        detail::g_gl.RenderbufferStorageMultisample(detail::to_gl_enum(target), samples, detail::to_gl_enum(internalformat), width, height);
        METAGL_DEBUG_LOG_VOID("glRenderbufferStorageMultisample", target, samples, internalformat, width, height);
    }

    // #308
    void glGetRenderbufferParameteriv(RenderbufferTarget target, RenderbufferParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetRenderbufferParameteriv != nullptr)) std::terminate();
        detail::g_gl.GetRenderbufferParameteriv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetRenderbufferParameteriv", target, pname, params);
    }

    // #309
    void glGenTransformFeedbacks(GLsizei n, TransformFeedbackId * ids)
    {
        static_assert(sizeof(TransformFeedbackId) == sizeof(GLuint), "TransformFeedbackId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenTransformFeedbacks != nullptr)) std::terminate();
        detail::g_gl.GenTransformFeedbacks(n, reinterpret_cast<GLuint*>(ids));
        METAGL_DEBUG_LOG_VOID("glGenTransformFeedbacks", n, ids);
    }

    // #310
    void glDeleteTransformFeedbacks(GLsizei n, const TransformFeedbackId * ids)
    {
        static_assert(sizeof(TransformFeedbackId) == sizeof(GLuint), "TransformFeedbackId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteTransformFeedbacks != nullptr)) std::terminate();
        detail::g_gl.DeleteTransformFeedbacks(n, reinterpret_cast<const GLuint*>(ids));
        METAGL_DEBUG_LOG_VOID("glDeleteTransformFeedbacks", n, ids);
    }

    // #311
    void glBindTransformFeedback(TransformFeedbackTarget target, TransformFeedbackId id)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindTransformFeedback != nullptr)) std::terminate();
        detail::g_gl.BindTransformFeedback(detail::to_gl_enum(target), id.value);
        METAGL_DEBUG_LOG_VOID("glBindTransformFeedback", target, id.value);
    }

    // #312
    bool glIsTransformFeedback(TransformFeedbackId id)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsTransformFeedback != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsTransformFeedback(id.value);
        METAGL_DEBUG_LOG("glIsTransformFeedback", _r, id.value);
        return _r;
    }

    // #313
    void glBeginTransformFeedback(PrimitiveType primitiveMode)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BeginTransformFeedback != nullptr)) std::terminate();
        detail::g_gl.BeginTransformFeedback(detail::to_gl_enum(primitiveMode));
        METAGL_DEBUG_LOG_VOID("glBeginTransformFeedback", primitiveMode);
    }

    // #314
    void glEndTransformFeedback(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.EndTransformFeedback != nullptr)) std::terminate();
        detail::g_gl.EndTransformFeedback();
        METAGL_DEBUG_LOG_VOID("glEndTransformFeedback");
    }

    // #315
    void glPauseTransformFeedback(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.PauseTransformFeedback != nullptr)) std::terminate();
        detail::g_gl.PauseTransformFeedback();
        METAGL_DEBUG_LOG_VOID("glPauseTransformFeedback");
    }

    // #316
    void glResumeTransformFeedback(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ResumeTransformFeedback != nullptr)) std::terminate();
        detail::g_gl.ResumeTransformFeedback();
        METAGL_DEBUG_LOG_VOID("glResumeTransformFeedback");
    }

    // #317
    void glTransformFeedbackVaryings(ProgramId program, GLsizei count, const GLchar *const* varyings, TransformFeedbackBufferMode bufferMode)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.TransformFeedbackVaryings != nullptr)) std::terminate();
        detail::g_gl.TransformFeedbackVaryings(program.value, count, varyings, detail::to_gl_enum(bufferMode));
        METAGL_DEBUG_LOG_VOID("glTransformFeedbackVaryings", program.value, count, varyings, bufferMode);
    }

    // #318
    void glGetTransformFeedbackVarying(ProgramId program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, UniformType * type, GLchar * name)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetTransformFeedbackVarying != nullptr)) std::terminate();
        detail::g_gl.GetTransformFeedbackVarying(program.value, index, bufSize, length, size, reinterpret_cast<GLenum *>(type), name);
        METAGL_DEBUG_LOG_VOID("glGetTransformFeedbackVarying", program.value, index, bufSize, length, size, type, name);
    }

    // #319
    void glGenQueries(GLsizei n, QueryId * ids)
    {
        static_assert(sizeof(QueryId) == sizeof(GLuint), "QueryId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenQueries != nullptr)) std::terminate();
        detail::g_gl.GenQueries(n, reinterpret_cast<GLuint*>(ids));
        METAGL_DEBUG_LOG_VOID("glGenQueries", n, ids);
    }

    // #320
    void glDeleteQueries(GLsizei n, const QueryId * ids)
    {
        static_assert(sizeof(QueryId) == sizeof(GLuint), "QueryId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteQueries != nullptr)) std::terminate();
        detail::g_gl.DeleteQueries(n, reinterpret_cast<const GLuint*>(ids));
        METAGL_DEBUG_LOG_VOID("glDeleteQueries", n, ids);
    }

    // #321
    bool glIsQuery(QueryId id)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsQuery != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsQuery(id.value);
        METAGL_DEBUG_LOG("glIsQuery", _r, id.value);
        return _r;
    }

    // #322
    void glBeginQuery(QueryTarget target, QueryId id)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BeginQuery != nullptr)) std::terminate();
        detail::g_gl.BeginQuery(detail::to_gl_enum(target), id.value);
        METAGL_DEBUG_LOG_VOID("glBeginQuery", target, id.value);
    }

    // #323
    void glEndQuery(QueryTarget target)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.EndQuery != nullptr)) std::terminate();
        detail::g_gl.EndQuery(detail::to_gl_enum(target));
        METAGL_DEBUG_LOG_VOID("glEndQuery", target);
    }

    // #324
    void glGetQueryiv(QueryTarget target, QueryParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetQueryiv != nullptr)) std::terminate();
        detail::g_gl.GetQueryiv(detail::to_gl_enum(target), detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetQueryiv", target, pname, params);
    }

    // #325
    void glGetQueryObjectuiv(QueryId id, QueryObjectParameter pname, GLuint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetQueryObjectuiv != nullptr)) std::terminate();
        detail::g_gl.GetQueryObjectuiv(id.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetQueryObjectuiv", id.value, pname, params);
    }

    // #326
    GLsync glFenceSync(SyncCondition condition, SyncFlag flags)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.FenceSync != nullptr)) std::terminate();
        const auto _r = detail::g_gl.FenceSync(detail::to_gl_enum(condition), detail::to_gl_bitfield(flags));
        METAGL_DEBUG_LOG("glFenceSync", _r, condition, flags);
        return _r;
    }

    // #327
    void glDeleteSync(GLsync sync)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteSync != nullptr)) std::terminate();
        detail::g_gl.DeleteSync(sync);
        METAGL_DEBUG_LOG_VOID("glDeleteSync", sync);
    }

    // #328
    bool glIsSync(GLsync sync)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsSync != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsSync(sync);
        METAGL_DEBUG_LOG("glIsSync", _r, sync);
        return _r;
    }

    // #329
    SyncWaitResult glClientWaitSync(GLsync sync, SyncFlushMask flags, GLuint64 timeout)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ClientWaitSync != nullptr)) std::terminate();
        const auto _r = static_cast<SyncWaitResult>(
            detail::g_gl.ClientWaitSync(
                sync, detail::to_gl_bitfield(flags), timeout));
        METAGL_DEBUG_LOG("glClientWaitSync", _r, sync, flags, timeout);
        return _r;
    }

    // #330
    void glWaitSync(GLsync sync, SyncFlag flags, GLuint64 timeout)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.WaitSync != nullptr)) std::terminate();
        detail::g_gl.WaitSync(sync, detail::to_gl_bitfield(flags), timeout);
        METAGL_DEBUG_LOG_VOID("glWaitSync", sync, flags, timeout);
    }

    // #331
    void glGetSynciv(GLsync sync, SyncParameter pname, GLsizei count, GLsizei * length, GLint * values)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetSynciv != nullptr)) std::terminate();
        detail::g_gl.GetSynciv(sync, detail::to_gl_enum(pname), count, length, values);
        METAGL_DEBUG_LOG_VOID("glGetSynciv", sync, pname, count, length, values);
    }

    // #332
    void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DispatchCompute != nullptr)) std::terminate();
        detail::g_gl.DispatchCompute(num_groups_x, num_groups_y, num_groups_z);
        METAGL_DEBUG_LOG_VOID("glDispatchCompute", num_groups_x, num_groups_y, num_groups_z);
    }

    // #333
    void glDispatchComputeIndirect(GLintptr indirect)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DispatchComputeIndirect != nullptr)) std::terminate();
        detail::g_gl.DispatchComputeIndirect(indirect);
        METAGL_DEBUG_LOG_VOID("glDispatchComputeIndirect", indirect);
    }

    // #334
    void glMemoryBarrier(MemoryBarrierMask barriers)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.MemoryBarrier != nullptr)) std::terminate();
        detail::g_gl.MemoryBarrier(detail::to_gl_bitfield(barriers));
        METAGL_DEBUG_LOG_VOID("glMemoryBarrier", barriers);
    }

    // #335
    void glMemoryBarrierByRegion(MemoryBarrierByRegionMask barriers)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.MemoryBarrierByRegion != nullptr)) std::terminate();
        detail::g_gl.MemoryBarrierByRegion(detail::to_gl_bitfield(barriers));
        METAGL_DEBUG_LOG_VOID("glMemoryBarrierByRegion", barriers);
    }

    // #336
    void glGenProgramPipelines(GLsizei n, ProgramPipelineId * pipelines)
    {
        static_assert(sizeof(ProgramPipelineId) == sizeof(GLuint), "ProgramPipelineId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.GenProgramPipelines != nullptr)) std::terminate();
        detail::g_gl.GenProgramPipelines(n, reinterpret_cast<GLuint*>(pipelines));
        METAGL_DEBUG_LOG_VOID("glGenProgramPipelines", n, pipelines);
    }

    // #337
    void glDeleteProgramPipelines(GLsizei n, const ProgramPipelineId * pipelines)
    {
        static_assert(sizeof(ProgramPipelineId) == sizeof(GLuint), "ProgramPipelineId must be layout-compatible with GLuint");
        if (!(detail::g_gl.initialized && detail::g_gl.DeleteProgramPipelines != nullptr)) std::terminate();
        detail::g_gl.DeleteProgramPipelines(n, reinterpret_cast<const GLuint*>(pipelines));
        METAGL_DEBUG_LOG_VOID("glDeleteProgramPipelines", n, pipelines);
    }

    // #338
    void glBindProgramPipeline(ProgramPipelineId pipeline)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.BindProgramPipeline != nullptr)) std::terminate();
        detail::g_gl.BindProgramPipeline(pipeline.value);
        METAGL_DEBUG_LOG_VOID("glBindProgramPipeline", pipeline.value);
    }

    // #339
    bool glIsProgramPipeline(ProgramPipelineId pipeline)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.IsProgramPipeline != nullptr)) std::terminate();
        const auto _r = detail::g_gl.IsProgramPipeline(pipeline.value);
        METAGL_DEBUG_LOG("glIsProgramPipeline", _r, pipeline.value);
        return _r;
    }

    // #340
    void glUseProgramStages(ProgramPipelineId pipeline, ShaderStageMask stages, ProgramId program)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.UseProgramStages != nullptr)) std::terminate();
        detail::g_gl.UseProgramStages(pipeline.value, detail::to_gl_bitfield(stages), program.value);
        METAGL_DEBUG_LOG_VOID("glUseProgramStages", pipeline.value, stages, program.value);
    }

    // #341
    void glActiveShaderProgram(ProgramPipelineId pipeline, ProgramId program)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ActiveShaderProgram != nullptr)) std::terminate();
        detail::g_gl.ActiveShaderProgram(pipeline.value, program.value);
        METAGL_DEBUG_LOG_VOID("glActiveShaderProgram", pipeline.value, program.value);
    }

    // #342
    ProgramId glCreateShaderProgramv(ShaderType type, GLsizei count, const GLchar *const* strings)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.CreateShaderProgramv != nullptr)) std::terminate();
        const ProgramId _r{detail::g_gl.CreateShaderProgramv(detail::to_gl_enum(type), count, strings)};
        METAGL_DEBUG_LOG("glCreateShaderProgramv", _r.value, type, count, strings);
        return _r;
    }

    // #343
    void glValidateProgramPipeline(ProgramPipelineId pipeline)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ValidateProgramPipeline != nullptr)) std::terminate();
        detail::g_gl.ValidateProgramPipeline(pipeline.value);
        METAGL_DEBUG_LOG_VOID("glValidateProgramPipeline", pipeline.value);
    }

    // #344
    void glGetProgramPipelineiv(ProgramPipelineId pipeline, ProgramPipelineParameter pname, GLint * params)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramPipelineiv != nullptr)) std::terminate();
        detail::g_gl.GetProgramPipelineiv(pipeline.value, detail::to_gl_enum(pname), params);
        METAGL_DEBUG_LOG_VOID("glGetProgramPipelineiv", pipeline.value, pname, params);
    }

    // #345
    void glGetProgramPipelineInfoLog(ProgramPipelineId pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetProgramPipelineInfoLog != nullptr)) std::terminate();
        detail::g_gl.GetProgramPipelineInfoLog(pipeline.value, bufSize, length, infoLog);
        METAGL_DEBUG_LOG_VOID("glGetProgramPipelineInfoLog", pipeline.value, bufSize, length, infoLog);
    }

    // #346
    void glPatchParameteri(TessellationParameter pname, GLint value)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.PatchParameteri != nullptr)) std::terminate();
        detail::g_gl.PatchParameteri(detail::to_gl_enum(pname), value);
        METAGL_DEBUG_LOG_VOID("glPatchParameteri", pname, value);
    }

    // #347
    void glPrimitiveBoundingBox(GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.PrimitiveBoundingBox != nullptr)) std::terminate();
        detail::g_gl.PrimitiveBoundingBox(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
        METAGL_DEBUG_LOG_VOID("glPrimitiveBoundingBox", minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
    }

    // #348
    void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DebugMessageCallback != nullptr)) std::terminate();
        detail::g_gl.DebugMessageCallback(callback, userParam);
        METAGL_DEBUG_LOG_VOID("glDebugMessageCallback", callback, userParam);
    }

    // #349
    void glDebugMessageControl(DebugSource source, DebugType type, DebugSeverity severity, GLsizei count, const GLuint * ids, GLboolean enabled)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DebugMessageControl != nullptr)) std::terminate();
        detail::g_gl.DebugMessageControl(detail::to_gl_enum(source), detail::to_gl_enum(type), detail::to_gl_enum(severity), count, ids, enabled);
        METAGL_DEBUG_LOG_VOID("glDebugMessageControl", source, type, severity, count, ids, enabled);
    }

    // #350
    void glDebugMessageInsert(DebugSource source, DebugType type, GLuint id, DebugSeverity severity, GLsizei length, const GLchar * buf)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.DebugMessageInsert != nullptr)) std::terminate();
        detail::g_gl.DebugMessageInsert(detail::to_gl_enum(source), detail::to_gl_enum(type), id, detail::to_gl_enum(severity), length, buf);
        METAGL_DEBUG_LOG_VOID("glDebugMessageInsert", source, type, id, severity, length, buf);
    }

    // #351
    GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, DebugSource * sources, DebugType * types, GLuint * ids, DebugSeverity * severities, GLsizei * lengths, GLchar * messageLog)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetDebugMessageLog != nullptr)) std::terminate();
        const auto _r = detail::g_gl.GetDebugMessageLog(count, bufSize, reinterpret_cast<GLenum *>(sources), reinterpret_cast<GLenum *>(types), ids, reinterpret_cast<GLenum *>(severities), lengths, messageLog);
        METAGL_DEBUG_LOG("glGetDebugMessageLog", _r, count, bufSize, sources, types, ids, severities, lengths, messageLog);
        return _r;
    }

    // #352
    void glPushDebugGroup(DebugSource source, GLuint id, GLsizei length, const GLchar * message)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.PushDebugGroup != nullptr)) std::terminate();
        detail::g_gl.PushDebugGroup(detail::to_gl_enum(source), id, length, message);
        METAGL_DEBUG_LOG_VOID("glPushDebugGroup", source, id, length, message);
    }

    // #353
    void glPopDebugGroup(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.PopDebugGroup != nullptr)) std::terminate();
        detail::g_gl.PopDebugGroup();
        METAGL_DEBUG_LOG_VOID("glPopDebugGroup");
    }

    // #354
    void glObjectLabel(DebugObjectLabel identifier, GLuint name, GLsizei length, const GLchar * label)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ObjectLabel != nullptr)) std::terminate();
        detail::g_gl.ObjectLabel(detail::to_gl_enum(identifier), name, length, label);
        METAGL_DEBUG_LOG_VOID("glObjectLabel", identifier, name, length, label);
    }

    // #355
    void glObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.ObjectPtrLabel != nullptr)) std::terminate();
        detail::g_gl.ObjectPtrLabel(ptr, length, label);
        METAGL_DEBUG_LOG_VOID("glObjectPtrLabel", ptr, length, label);
    }

    // #356
    void glGetObjectLabel(DebugObjectLabel identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetObjectLabel != nullptr)) std::terminate();
        detail::g_gl.GetObjectLabel(detail::to_gl_enum(identifier), name, bufSize, length, label);
        METAGL_DEBUG_LOG_VOID("glGetObjectLabel", identifier, name, bufSize, length, label);
    }

    // #357
    void glGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetObjectPtrLabel != nullptr)) std::terminate();
        detail::g_gl.GetObjectPtrLabel(ptr, bufSize, length, label);
        METAGL_DEBUG_LOG_VOID("glGetObjectPtrLabel", ptr, bufSize, length, label);
    }

    // #358
    GraphicsResetStatus glGetGraphicsResetStatus(void)
    {
        if (!(detail::g_gl.initialized && detail::g_gl.GetGraphicsResetStatus != nullptr)) std::terminate();
        const auto _r = static_cast<GraphicsResetStatus>(
            detail::g_gl.GetGraphicsResetStatus());
        METAGL_DEBUG_LOG("glGetGraphicsResetStatus", _r);
        return _r;
    }

}
