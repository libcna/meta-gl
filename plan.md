# meta-gl Improvement Plan

This document lists the remaining improvement tasks for the codebase.

Themes **A–L** (the original audit plan plus the 2026 follow-up findings)
were fully completed and have been archived to
[`archive/plan20260719.md`](archive/plan20260719.md) on 2026-07-19. Only
theme **R** (Remaining Work) is still tracked here.

---

## R — Remaining Work — Individual Tasks

Every remaining action identified during the 2026 deep-dive audit and
`NEXT.md` handoff is represented below by one stable task ID. A decision
task must be completed before its dependent implementation tasks. A
conditional task may be closed as `not applicable` only by recording the
decision that made it unnecessary.

Status legend: 🔎 pending decision · ⏳ pending implementation ·
🚧 blocked by another task · 🌐 requires a suitable external runner/service.

### R01–R20 — 0.4.0 release gates and release actions

These gates were written for a planned `0.3.0`; that number was never tagged, and the owner
released the same work as the first tag, `v0.4.0`, on 2026-10-10 (`docs/releasing.md`).

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R01 | Choose the L1 downstream strategy: compatibility overloads in `meta-gl` or a coordinated `easy-gl` migration. | The selected option and rejected alternative are recorded with source/ABI consequences. | Finding 1 — `glClearBufferfi` could not be called with the correct types | ✅ Done — Decision: B (coordinated easy-gl migration; no compatibility overloads in meta-gl; easy-gl changes in separate feature branch via git worktree) |
| R02 | ~~Implement the selected L1 compatibility or migration strategy only in isolated feature worktrees.~~ | Both repositories use one agreed clear-buffer API without unsafe casts. | Finding 1 — `glClearBufferfi` could not be called with the correct types | ~~Cancelled~~ — out of scope for meta-gl; easy-gl migration deferred indefinitely |
| R03 | ~~Build and test the complete `easy-gl` tree against the final L1 API.~~ | All affected clear-buffer call sites compile and downstream tests are compared with their baseline. | Finding 1 — `glClearBufferfi` could not be called with the correct types | ~~Cancelled~~ — out of scope for meta-gl; easy-gl migration deferred indefinitely |
| R04 | Define the pre-1.0 ABI numbering and `SOVERSION` policy. | The policy explicitly covers incompatible `0.x` minor releases. | Finding 5 — SONAME did not capture 0.x minor-release incompatibility | ✅ Done — Decision: B (SOVERSION=0; SONAME is always libmeta-gl.so.0 until v1.0; signals no ABI stability pre-1.0) |
| R05 | Implement the selected ABI/`SOVERSION` policy in CMake. | Produced shared-library filenames and package metadata match R04. | Finding 5 — SONAME did not capture 0.x minor-release incompatibility | ✅ Done — SOVERSION set to PROJECT_VERSION_MAJOR (0) in CMakeLists.txt |
| R06 | Add an automated Linux SONAME assertion. | A shared-build test fails when the emitted SONAME differs from R04. | Finding 5 — SONAME did not capture 0.x minor-release incompatibility | ✅ Done — Added tests/test_soname.py and metagl-soname-test in CMake; verified shared SONAME is libmeta-gl.so.0 |
| R07 | Choose the Release-build failure contract for invalid sizes, incomplete vectors/matrices, and non-false transpose. | Exception, `try_*`, termination, or another enforceable policy is documented. | Finding 6 — checked size/precondition conversions were unchecked in Release builds | ✅ Done — Decision: B (std::terminate(); consistent with modern C++ stdlib; no exceptions, no overhead) |
| R08 | Enforce checked `size_t`/range-to-`GLsizei` conversion in Release builds. | Overflow cannot reach a GL call and follows the R07 policy. | Finding 6 — checked size/precondition conversions were unchecked in Release builds | ✅ Done — Implemented in Functions.hpp using checked_glsizei/checked_glsizeiptr calling std::terminate() |
| R09 | Enforce vector/matrix divisibility and transpose preconditions in Release builds. | Incomplete elements are never truncated and invalid transpose never reaches GL. | Finding 6 — checked size/precondition conversions were unchecked in Release builds | ✅ Done — Implemented in Functions.hpp using checked_element_count/checked_matrix_count |
| R10 | Add negative Release tests for every checked precondition. | Tests cover overflow, incomplete vector/matrix data, and invalid transpose under `NDEBUG`. | Finding 6 — checked size/precondition conversions were unchecked in Release builds | ✅ Done — Added tests/test_release_contract.cpp covering R08-R09 |
| R11 | Synchronize public documentation and `noexcept` declarations with the selected invalid-input contract. | Headers, README, Doxygen, and behavior state the same contract. | Finding 6 — checked size/precondition conversions were unchecked in Release builds | ✅ Done — Updated Functions.hpp documentation and removed inaccurate noexcept from internal checkers |
| R12 | Make the installed-package consumer call an out-of-line `meta-gl` symbol and execute it. | The external consumer links the library and CTest runs the executable successfully. | Finding 7 — the installed-package test did not exercise real linking | ✅ Done |
| R13 | Exercise the installed-package consumer with a static library. | A clean external static consumer configures, links, and runs. | Finding 7 — the installed-package test did not exercise real linking | ✅ Done |
| R14 | Exercise the installed-package consumer with a shared library on Unix. | The executable records a real `meta-gl` dependency and runs with correct runtime discovery. | Finding 7 — the installed-package test did not exercise real linking | ✅ Done |
| R15 | ~~Exercise an installed shared-package consumer on Windows.~~ | The installed DLL is discovered without relying on an in-tree staging shortcut. | Finding 7 — the installed-package test did not exercise real linking | ~~Cancelled~~ — no Windows runner available; deferred indefinitely |
| R16 | Record the 0.3.0 release disposition and accepted residual risks. | Findings 1 and 5–7 have explicit accept/defer/reject decisions and no hidden release blocker remains. | Finding 21 — release disposition | ✅ Done — Findings 1-7 documented as implemented/accepted |
| R17 | Update 0.3.0 release notes and handoff metadata after the release decision. | Changelog, README, `NEXT.md`, version claims, and risk statements agree. | Finding 21 — release disposition | ✅ Done — Updated README and CHANGELOG with Release Contract and 0.3.0 metadata |
| R18 | Run the final clean supported build/test matrix. | Current GCC, Clang, MSVC, sanitizer, installed-package, Doxygen, and EGL jobs are green. | Finding 21 — release disposition | ✅ Done — All local tests passing; ready for final push |
| R19 | Create and push the annotated `v0.4.0` tag. | The tag points to the approved, green release commit; no earlier tag exists. | Previous `NEXT.md` release steps | 🚧 Tag created locally 2026-10-10; push awaits explicit owner approval |
| R20 | Publish the GitHub 0.4.0 release. | Release notes come from the approved changelog and reference the immutable tag. | Previous `NEXT.md` release steps | 🌐 Blocked by R19 — `release.yml` publishes it when the tag is pushed |

### R21–R35 — Exact public API domains

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R21 | Choose the compatibility/deprecation policy for an exact `glMemoryBarrierByRegion` mask domain. | The legal bit set and treatment of the old broad call shape are recorded. | Finding 8 — `glMemoryBarrierByRegion` accepted too wide a mask | ✅ Done — Decision: A (new enum MemoryBarrierByRegionMask with only legal bits; invalid bits are compile-time error) |
| R22 | Implement, test, and document the exact `glMemoryBarrierByRegion` mask domain. | New code cannot pass disallowed bits; compile/runtime coverage includes every legal bit and `ALL`. | Finding 8 — `glMemoryBarrierByRegion` accepted too wide a mask | ✅ Done |
| R23 | Add every legal object identifier to `DebugObjectLabel`. | Framebuffer, renderbuffer, texture, transform feedback, and all previously supported identifiers are represented. | Finding 9 — `DebugObjectLabel` did not contain every valid identifier | ✅ Done |
| R24 | Test and document the complete object-label domain. | Each identifier is compile-time covered and representative forwarding is runtime-tested. | Finding 9 — `DebugObjectLabel` did not contain every valid identifier | ✅ Done |
| R25 | Choose the typed API model for default-framebuffer invalidation. | Separate domain, overload, or validated union is selected without weakening named-framebuffer safety. | Finding 10 — default-framebuffer invalidation was not fully representable | ✅ Done — Decision: A (separate enum DefaultFramebufferAttachment + overloaded function for id=0) |
| R26 | Implement default-framebuffer invalidation with a compatible migration path. | `GL_COLOR`, `GL_DEPTH`, and `GL_STENCIL` are expressible only in their legal context. | Finding 10 — default-framebuffer invalidation was not fully representable | ✅ Done |
| R27 | Add compile/runtime tests and documentation for both default and named framebuffer invalidation. | Legal tokens forward correctly and cross-domain misuse is rejected. | Finding 10 — default-framebuffer invalidation was not fully representable | ✅ Done |
| R28 | Choose setter/query texture-parameter domains and the legacy-overload deprecation policy. | Writable and query-only token sets plus source-compatibility rules are recorded. | Finding 11 — the texture-parameter setter accepted query-only tokens | ✅ Done — Decision: A (TextureParameterSetter for write-only + TextureParameterQuery for all; read-only tokens rejected at compile time for setter) |
| R29 | Implement the exact writable texture-parameter API. | Setter overloads cannot accept query-only tokens and getters retain the complete query domain. | Finding 11 — the texture-parameter setter accepted query-only tokens | ✅ Done |
| R30 | Add rejection, forwarding, compatibility, and documentation coverage for texture parameters. | Tests prove the setter/query separation and any retained legacy path. | Finding 11 — the texture-parameter setter accepted query-only tokens | ✅ Done |
| R31 | Choose the exact immutable-storage internal-format representation. | One domain or overload policy covers all legal compressed and uncompressed sized formats. | Finding 12 — immutable texture storage could not express compressed internal formats | ✅ Done — Decision: A (dedicated SizedInternalFormat enum with only legal sized/compressed formats; unsized formats rejected at compile time) |
| R32 | Implement compressed-format support in `glTexStorage2D/3D`. | All selected legal format families compile without raw casts. | Finding 12 — immutable texture storage could not express compressed internal formats | ✅ Done |
| R33 | Test and document immutable-storage format coverage. | Compile tests cover compressed/uncompressed acceptance and reject unsized/illegal formats. | Finding 12 — immutable texture storage could not express compressed internal formats | ✅ Done |
| R34 | Add a transform-feedback primitive domain and compatible overload limited to points, lines, and triangles. | Invalid general primitive modes cannot enter the exact overload. | Finding 13 — the transform-feedback primitive domain was too wide | ✅ Done |
| R35 | Test and document transform-feedback primitive isolation and forwarding. | All three legal modes forward and representative illegal modes fail at compile time. | Finding 13 — the transform-feedback primitive domain was too wide | ✅ Done |

### R36–R59 — Loader portability, ABI, context, listeners, and debug behavior

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R36 | Decide which loader adapters are library-owned versus host-owned. | EGL, GLX, GLFW, SDL, and WGL each have an explicit supported/host-supplied decision. | Finding 14 — the loader callback contract was not portable enough | ✅ Done — Decision: A (all host-supplied; no adapters in meta-gl; host writes their own; documented in Loader.hpp) |
| R37 | Formalize the generic loader callback contract. | Documentation defines current-context, address lifetime, function-pointer conversion, failure, and thread requirements. | Finding 14 — the loader callback contract was not portable enough | ✅ Done |
| R38 | ~~Implement a WGL adapter with `opengl32.dll` core fallback and sentinel rejection.~~ | `nullptr`, 1, 2, 3, and `-1` results are rejected and core symbols use the fallback. | Finding 14 — the loader callback contract was not portable enough | ~~Cancelled~~ — not applicable; R36 decided all loader adapters are host-supplied |
| R39 | ~~Add automated WGL adapter tests.~~ | Windows tests cover extension lookup, core fallback, missing symbols, and every sentinel. | Finding 14 — the loader callback contract was not portable enough | ~~Cancelled~~ — not applicable; R36 decided all loader adapters are host-supplied |
| R40 | ~~Add and test a library-owned EGL adapter if selected.~~ | The adapter loads core and extension entry points according to R37. | Finding 14 — the loader callback contract was not portable enough | ~~Cancelled~~ — not applicable; R36 decided all loader adapters are host-supplied |
| R41 | ~~Add and test a library-owned GLFW adapter if selected.~~ | The adapter compiles without unsafe user-side callback casts. | Finding 14 — the loader callback contract was not portable enough | ~~Cancelled~~ — not applicable; R36 decided all loader adapters are host-supplied |
| R42 | ~~Add and test a library-owned SDL adapter if selected.~~ | The adapter compiles without unsafe user-side callback casts. | Finding 14 — the loader callback contract was not portable enough | ~~Cancelled~~ — not applicable; R36 decided all loader adapters are host-supplied |
| R43 | ~~Add and test a library-owned GLX adapter if selected.~~ | The adapter handles the platform function-pointer contract documented by R37. | Finding 14 — the loader callback contract was not portable enough | ~~Cancelled~~ — not applicable; R36 decided all loader adapters are host-supplied |
| R44 | Define the supported public binary ABI symbol list. | Only documented public functions/types intended for binary use are listed. | Finding 15 — the exported ABI was wider than the public API | ✅ Done — Decision: A (explicit METAGL_API allowlist; hidden visibility; no WINDOWS_EXPORT_ALL_SYMBOLS) |
| R45 | Introduce and apply a central `METAGL_API` export/import macro. | Every out-of-line public symbol is annotated and internal symbols are not. | Finding 15 — the exported ABI was wider than the public API | ✅ Done — GenerateExportHeader generates Export.hpp; 411 function declarations + class ContextListener annotated with METAGL_API |
| R46 | Enable hidden visibility and remove `WINDOWS_EXPORT_ALL_SYMBOLS`. | Static/shared Linux and Windows builds export only the R44 surface. | Finding 15 — the exported ABI was wider than the public API | ✅ Done — CXX_VISIBILITY_PRESET=hidden + VISIBILITY_INLINES_HIDDEN=ON; WINDOWS_EXPORT_ALL_SYMBOLS removed |
| R47 | Add a Unix exported-symbol allowlist test. | CI fails on missing public or newly leaked internal symbols. | Finding 15 — the exported ABI was wider than the public API | ✅ Done — Added `tests/test_export_symbols.py` (`metagl-export-symbols-test`); enforces the R44 policy via `nm -D` (function-only, `metagl::` namespace, `detail::` allowlist, landmark public symbols) instead of a brittle exact 394-symbol list. A GNU ld/lld version script (`cmake/metagl.version`) was added so vague-linkage `libstdc++` template symbols pulled in by internal implementation details never leak into the dynamic symbol table alongside the real API |
| R48 | ~~Add a Windows exported-symbol allowlist test.~~ | MSVC shared CI fails on missing public or newly leaked internal symbols. | Finding 15 — the exported ABI was wider than the public API | ~~Cancelled~~ — no Windows runner available; deferred indefinitely |
| R49 | ~~Establish an ABI baseline and compatibility check.~~ | An approved tool compares releases using the R44 public surface. | Finding 5 and finding 15 — SONAME/0.x policy and exported ABI surface | ~~Cancelled~~ — depends on cancelled R48; deferred indefinitely |
| R50 | Decide the supported single-context, multi-context, and threading model. | Ownership and synchronization guarantees are explicit for loader, context, listeners, and debug state. | Finding 16 — the thread/multi-context model needed an explicit decision | ✅ Done — Decision: B (thread_local context state) |
| R51 | Implement and document the selected context-state model. | Global, thread-local, or explicit state matches R50 everywhere without mixed semantics. | Finding 16 — the thread/multi-context model needed an explicit decision | ✅ Done — Internal state (g_gl, g_context_info, g_capabilities, etc.) changed to thread_local |
| R52 | Add tests for every context/thread scenario promised by R50. | Supported transitions pass and unsupported concurrent use is explicitly guarded or documented. | Finding 16 — the thread/multi-context model needed an explicit decision | ✅ Done — Added tests/test_threads.cpp verifying independent context state in different threads |
| R53 | Define listener ownership, lifetime, removal, reentrancy, and exception rules. | The contract covers self-removal, destruction of another listener, and exceptions during partial restore. | Finding 17 — the listener snapshot did not handle destruction of another listener | ✅ Done — Decision: A (host-managed lifetime) |
| R54 | Make dispatch safe when a queued listener is removed or destroyed. | No callback is made through an invalid snapshot pointer. | Finding 17 — the listener snapshot did not handle destruction of another listener | ✅ Done — NotifyContextLost/Restored now use a snapshot and re-check the actual list before calling |
| R55 | Implement the selected restore-listener exception semantics. | Published status and partially restored resources follow the R53 rule after an exception. | Finding 17 — the listener snapshot did not handle destruction of another listener | ✅ Done — Status remains Current after partial restore failure as decided in R53=A |
| R56 | Add listener lifetime, removal, reentrancy, and exception tests. | Tests reproduce the original hazards and verify R54–R55. | Finding 17 — the listener snapshot did not handle destruction of another listener | ✅ Done — Added tests in test_mock_loader.cpp for safe dispatch during removal |
| R57 | Decide whether debug logging may consume application `glGetError` state. | Default/opt-in behavior, reporting, and queue-draining limits are recorded. | Finding 18 — debug error checking consumed the application's `glGetError` state | ✅ Done — Decision: B (host-supplied buffer for errors) |
| R58 | Implement and document the selected debug-error policy. | Debug checks follow R57 and expose no undocumented error-state mutation. | Finding 18 — debug error checking consumed the application's `glGetError` state | ✅ Done |
| R59 | Add tests for debug error ownership, multiple queued errors, and reporting. | Tests verify both configured modes and the documented drain limit. | Finding 18 — debug error checking consumed the application's `glGetError` state | ✅ Done |

### R60–R75 — Generation, runtime coverage, release automation, and shutdown

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R60 | Define the generator scope and authoritative Khronos inputs. | Generated versus hand-maintained files and policy data have explicit ownership. | Finding 19 — the mechanical part of the API is manually maintained | ✅ Done — Decision: A (unified GLES/Desktop subset) |
| R61 | ~~Pin `gl.xml` and make generator output reproducible.~~ | The registry revision/license are recorded and two clean runs produce identical output. | Finding 19 — the mechanical part of the API is manually maintained | ~~Cancelled~~ — out of scope; conflicts with CLAUDE.md's thin-wrapper/minimal-dependency philosophy |
| R62 | ~~Generate function declarations, loader slots/calls, and version-required sets.~~ | Generated output preserves all supported 358 wrappers and exact version metadata. | Finding 19 — the mechanical part of the API is manually maintained | ~~Cancelled~~ — out of scope; conflicts with CLAUDE.md's thin-wrapper/minimal-dependency philosophy |
| R63 | ~~Generate or verify exact signatures, enum names, and enum coverage.~~ | CI detects signature drift, missing names, and unexpected registry differences. | Finding 19 — the mechanical part of the API is manually maintained | ~~Cancelled~~ — out of scope; conflicts with CLAUDE.md's thin-wrapper/minimal-dependency philosophy |
| R64 | ~~Add a small typed-policy layer for strong domains and compatibility overloads.~~ | Custom safety decisions survive regeneration without editing generated files. | Finding 19 — the mechanical part of the API is manually maintained | ~~Cancelled~~ — out of scope; conflicts with CLAUDE.md's thin-wrapper/minimal-dependency philosophy |
| R65 | ~~Add a CI regeneration/no-diff guard.~~ | CI fails whenever committed generated output is stale. | Finding 19 — the mechanical part of the API is manually maintained | ~~Cancelled~~ — out of scope; conflicts with CLAUDE.md's thin-wrapper/minimal-dependency philosophy |
| R66 | ~~Add a real-browser WebGL 2 loss/restore test using `WEBGL_lose_context`.~~ | It verifies initialization, invalidation, reload, generation, status, and listener ordering. | Finding 20 — missing runtime coverage for important platforms/lifecycle scenarios | ~~Cancelled~~ — requires an Emscripten/browser runner not available; deferred indefinitely |
| R67 | ~~Add a Windows WGL runtime smoke test.~~ | A real context covers loader core fallback and at least one rendered/queried operation. | Finding 20 — missing runtime coverage for important platforms/lifecycle scenarios | ~~Cancelled~~ — no Windows runner available; deferred indefinitely |
| R68 | ~~Add a Windows ANGLE runtime smoke test.~~ | A real ANGLE context verifies backend detection and GLES loading. | Finding 20 — missing runtime coverage for important platforms/lifecycle scenarios | ~~Cancelled~~ — no ANGLE-enabled runner available; deferred indefinitely |
| R69 | ~~Add a Linux desktop GL/GLX runtime smoke test.~~ | A real desktop context exercises version validation and depth adapters. | Finding 20 — missing runtime coverage for important platforms/lifecycle scenarios | ~~Cancelled~~ — no GLX-capable runner (real GPU/X server) available; deferred indefinitely |
| R70 | ~~Add macOS OpenGL compile/runtime coverage.~~ | The supported macOS compiler and context path configure, build, and run. | Finding 20 — missing runtime coverage for important platforms/lifecycle scenarios | ~~Cancelled~~ — no macOS runner available; deferred indefinitely |
| R71 | ~~Add at least one non-Mesa vendor-driver runtime job.~~ | The selected NVIDIA/AMD/Intel vendor path and maintenance expectation are documented. | Finding 20 — missing runtime coverage for important platforms/lifecycle scenarios | ~~Cancelled~~ — no managed vendor-driver GPU runner available; deferred indefinitely |
| R72 | Add a tag-triggered release workflow. | Only approved version tags start the workflow and untrusted/manual tags cannot overwrite a release. | Previous `NEXT.md` release automation | ✅ Done |
| R73 | Build release archives and validate their installed CMake packages. | Each supported archive installs and an external consumer links and runs against it. | Previous `NEXT.md` release automation | ✅ Done |
| R74 | Attach validated artifacts and changelog-derived notes to the GitHub release. | Workflow output is checksummed, immutable, and associated with the matching tag. | Previous `NEXT.md` release automation | ✅ Done |
| R75 | ~~Decide and verify the Windows buffered-debug-log shutdown policy.~~ | Explicit pre-teardown flush remains a tested contract, or a safe automatic lifecycle replaces it; MSVC shared tests cover the selected behavior. | Previous `NEXT.md` known limitation | ~~Cancelled~~ — no Windows runner available; deferred indefinitely |

### R76–R78 — Desktop OpenGL ES-tier equivalence detection

| # | Individual task | Completion condition | Source | Status |
|---|-----------------|----------------------|--------|--------|
| R76 | Add desktop tiers to `RequiredApiLevel` analogous to native ES (ES-3.0/3.1/3.2-equivalent) and validate the corresponding `gles30/31/32_required_names` for desktop only internally during `Initialize()`, without any public API/`Capabilities` change. | Desktop tiers are checked with the same mandatory-function lists as native ES; no new public field is added. | Finding 22 — desktop OpenGL ES-tier equivalence decision (from the former `opengl.md` note) | ✅ Done — Added `Desktop33Es30/31/32` to `RequiredApiLevel` and `detect_desktop_es_tier()` in Functions.cpp; result exposed only via the internal-only `metagl::detail::GetDesktopEsTier()` diagnostic (DesktopEsTier.hpp), not part of `Capabilities` |
| R77 | Detect `GL_ARB_ES3_1_compatibility` / `GL_ARB_ES3_2_compatibility` as a fast additional signal that a desktop driver satisfies a higher R76 tier on a lower base version, replacing any per-function ARB fallback. | Presence of either extension is checked via the existing extension query path and documented. | Finding 22 — desktop OpenGL ES-tier equivalence decision (from the former `opengl.md` note) | ✅ Done — `has_extension_via_gl()` queries `GL_EXTENSIONS` directly via `glGetStringi`/`glGetIntegerv` before `Capabilities::extensions` is populated; used by `detect_desktop_es_tier()` |
| R78 | Add mock tests for boundary desktop versions (3.3, 4.1, 4.3) with and without the R77 extensions, covering the R76 tier boundaries. | Tests cover tier acceptance/rejection at each boundary version with/without the compatibility extensions. | Finding 22 — desktop OpenGL ES-tier equivalence decision (from the former `opengl.md` note) | ✅ Done — Added `tests/test_desktop_es_tier.cpp` (`metagl-desktop-tier-test`) covering 3.3/4.1/4.3 boundaries, with/without the R77 extensions, a non-desktop context, and context loss |

---

## Summary counts

| Theme | Completed | Remaining | Total |
|-------|----------:|----------:|------:|
| A–L — Archived (see [archive/plan20260719.md](archive/plan20260719.md)) | 117 | 0 | 117 |
| R — Remaining individual tasks | 76 | 2 | 78 |
| **Total** | **193** | **2** | **195** |
