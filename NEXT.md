# NEXT.md — meta-gl follow-up audit handoff

Updated on 2026-07-19 for the isolated `feature/followup-audit` worktree.
The shared `develop` worktree remains unchanged at `d51fcd7`; the follow-up
changes described here are not committed or merged.

---

## 1. Project role

`meta-gl` is the low-level, procedural, type-safe C++23 layer over OpenGL,
OpenGL ES, and WebGL function pointers. It is designed to sit below `easy-gl`.

The dependency direction is:

```text
OpenGL / OpenGL ES / WebGL
              ↓
           meta-gl
              ↓
           easy-gl
```

`meta-gl` deliberately does not provide RAII resource ownership, engine
abstractions, or an object-oriented rendering API. Typed handles are lightweight
identifiers only; ownership belongs in `easy-gl`.

---

## 2. Release status

**0.4.0** (2026-10-10) is the first tagged release. The work prepared here as
`0.3.0` was never tagged, nor were the earlier milestones; it ships as `v0.4.0`.
`docs/releasing.md` explains the version mechanism and the release checklist.

- `project(meta-gl VERSION 0.4.0)` plus `METAGL_VERSION_PRERELEASE` drive the
  generated `metagl/Version.hpp`, the CMake package version and the library
  `VERSION` metadata; `SOVERSION` stays `0` (R04).
- `CHANGELOG.md` contains the dated `0.4.0` section above the untagged
  0.1.0–0.3.0 milestone entries.
- The original 113 plan tasks are complete.
- Follow-up findings L1–L4 are implemented and locally verified.
- `plan.md` reflects **166 completed tasks** and **26 remaining** (mostly long-term).
- **R01–R18 (Release Gates)** are resolved:
  - R01: Coordinated `easy-gl` migration is selected; `meta-gl` maintains strict types.
  - R04: ABI SOVERSION is set to `0` for the pre-1.0 phase.
  - R06: Automated Linux SONAME assertion verifies binary identity (libmeta-gl.so.0).
  - R07: Release contract for invalid inputs is `std::terminate()`.
  - R11: Contract documentation and `noexcept` sync for invalid inputs is complete.
  - R12–R14: Installed-package test now executes the consumer and verifies shared/static linkage on Unix.
  - R16: Findings 1–7 are accepted and implemented.
  - R17: Release notes and metadata are synchronized.
  - R18: Build/test matrix is green.
- **R44–R47 (ABI Surface)**: Explicit `METAGL_API` export macros, hidden visibility, and an automated Unix exported-symbol policy test are implemented.
- **R50–R59 (Thread Safety & Listeners)**: Thread-local global state, snapshot-based listener dispatch, and safe debug error formatting are implemented.
- **R72–R74 (Automation)**: GitHub Release workflow with checksums and automated changelog extraction is ready.
- The API verifier reports consistency across 358 wrappers and mandatory GLES sets.
- The current feature worktree passes all 5 tests (including new thread tests) on Linux (GCC/Clang) and local verification.

The annotated `v0.4.0` tag exists locally; push it (R19) only with the owner's
explicit approval — pushing it publishes the GitHub release through `release.yml` (R20).

---

## 3. Supported surface

- C++23, CMake 3.23 or newer.
- OpenGL ES 2.0 through 3.2 wrapper surface.
- Desktop OpenGL 3.3+ loading, including `glDepthRange` and `glClearDepth`
  adapters.
- WebGL/Emscripten loader and context-loss/context-restore integration.
- ANGLE detection through version, vendor, and renderer strings.
- 358 typed `metagl::gl*` wrappers.
- 99 enum classes and 15 lightweight handle/location/index types.
- **Thread-safe global state**: context tracking and function availability use `thread_local` (R50).
- **Explicit ABI control**: `METAGL_API` visibility macros for Windows DLLs and Unix shared objects (R44).
- `std::span` and range-size helpers with `std::terminate()` on Release failure (R07).
- Typed template dispatch for uniforms, vertex attributes, texture parameters,
  sampler parameters, and clear-buffer calls.
- Context status, generation tracking, capabilities, extension queries, and
  listener notifications with snapshot safety (R54).
- Safe error formatting with `FormatGlError` into host-supplied buffers (R58).
- Static or shared builds, CMake package export, installed Khronos headers, and
  Doxygen generation.

---

## 4. Tests and CI

CTest currently defines nine tests:

1. `metagl-compile-tests` — concepts, enum domains, bitfields, template
   dispatch, handle isolation, and enum-name coverage.
2. `metagl-mock-loader-test` — loading, version-tier validation, failure
   recovery, context lifecycle/listeners (snapshot-safe), extensions, and debug flush.
3. `metagl-release-contract-tests` — verification of enforced `std::terminate()`
   for invalid sizes, incomplete ranges, and invalid transpose (R10).
4. `metagl-thread-tests` — verification of independent `thread_local` context
   states in concurrent threads (R51).
5. `metagl-soname-test` — automated Linux SONAME assertion ensuring ABI
   consistency with the R04 policy (R06).
6. `metagl-desktop-tier-test` — desktop OpenGL ES-tier boundary coverage at
   3.3/4.1/4.3, with and without `GL_ARB_ES3_1/3_2_compatibility` (R76–R78).
7. `metagl-export-symbols-test` — Linux exported dynamic-symbol policy check
   (`nm -D`: function-only, `metagl::` namespace, `detail::` allowlist,
   landmark public symbols) enforcing the R44 ABI surface (R47).
8. `metagl-api-consistency-test` — declaration, definition, loader-name, and
   exact GLES mandatory-function consistency.
9. `metagl-installed-package-test` — install plus an external consumer build
   verifying static/shared linkage and runtime execution (R12–R14).

GitHub Actions runs:

- Linux GCC static;
- Linux Clang shared;
- Windows MSVC shared;
- Linux Clang ASan and UBSan;
- **Release Automation**: Automated tag-triggered build, checksum, and GitHub Release (R72).

The Windows build stages the shared `meta-gl` runtime beside in-tree tests and
examples, so their executables can find the DLL.

Useful local verification:

```bash
cmake -S . -B build/release-check -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=ON \
  -DMETAGL_BUILD_TESTS=ON \
  -DMETAGL_BUILD_EXAMPLES=ON \
  -DMETAGL_BUILD_GPU_TESTS=ON
cmake --build build/release-check --parallel
ctest --test-dir build/release-check --output-on-failure

python3 tools/verify_api.py

cmake -S . -B build/docs -G Ninja -DMETAGL_BUILD_DOCS=ON
cmake --build build/docs --target metagl-docs
```

---

## 5. Compatibility with easy-gl

The original comprehensive audit was compiled against the complete `easy-gl`
source tree and did not create a new failure. The newer L1 follow-up change is
different: current `easy-gl` uses the removed broad `ClearBuffer` type and the
old four-argument `glClearBufferfi` call shape.

The feature worktree must therefore not be merged into shared `develop` until
R01–R03 select and verify either:

- compatible `meta-gl` overloads; or
- a coordinated `easy-gl` migration in its own feature worktree.

Other deliberate source/API corrections in the candidate include:

- `AttribLocation` has signed storage and represents `-1` correctly;
- invalid enum-domain values were removed;
- clear-buffer domains are split by value type and `glClearBufferfi` supplies
  its fixed target/draw-buffer arguments;
- stricter enum types reject previously accepted invalid calls; range helpers
  diagnose invalid input in Debug while R07–R11 define the Release contract.

Compatibility overloads are retained where they are valid, including the
legacy draw-index, active-attribute, and raw `glCopyImageSubData` call forms.

---

## 6. Known limitations

- L1 downstream compatibility is unresolved (R01–R03); migration of `easy-gl` is required.
- Pre-1.0 ABI/SONAME policy is set to SOVERSION 0 (R04).
- Checked size, element-count, matrix-count, and transpose preconditions use `std::terminate()` in Release (R07).
- Emscripten code and presets are present, but context loss/restore has not yet
  been exercised by an automated test in a real browser/WebGL runtime (R66).
- The real-GPU CI smoke test currently covers Linux EGL/Mesa only. Native WGL,
  GLX, ANGLE, macOS, and vendor drivers are not runtime-tested in CI
  (R67–R71).
- For an initialized current context, `AllFunctionsLoaded()` answers whether
  every tracked loader slot is non-null; it returns false after context loss
  and cannot prove that a mock or driver implementation behaves correctly.
- The mechanical API surface is still hand-maintained (R60–R65).
- Buffered Windows debug logging must be flushed explicitly with
  `metagl::FlushDebugLog()` before DLL teardown, or built with
  `METAGL_DEBUG_IMMEDIATE=ON`; its long-term shutdown policy is R75.
- Desktop OpenGL 3.3+ ES-tier equivalence is an internal-only diagnostic
  (`metagl::detail::GetDesktopEsTier()`, R76–R78); it never affects
  `Capabilities` or `Initialize()`'s success/failure, by design.

R47 (exported-symbol policy test) is complete; R19 (pushing the `v0.4.0` tag) is the final approval step for the release.

---

## 7. Execution order

`plan.md` is the single task backlog; do not create additional implicit TODO
lists in this document.

1. The release gates R01–R18 are resolved; 0.4.0 is tagged locally.
2. Only after a green approved release commit, perform R19–R20 (tag and GitHub
   release). Never move or recreate a pushed release tag.
3. Review the exact API-domain work R21–R35 for the next compatible feature
   release.
4. Resolve platform, ABI, context, listener, and debug contracts in R36–R59.
5. Treat generation and broader runtime coverage R60–R71 as staged long-term
   work.
6. Release automation is tracked explicitly by R72–R74; the remaining Windows
   debug-shutdown decision/test is R75.
7. The desktop OpenGL ES-tier equivalence detection R76–R78 is complete as an
   internal-only refinement of `Initialize()` validation.

---

## 8. Architectural invariants

1. `meta-gl` must never depend on `easy-gl`.
2. Handle types do not own resources and must stay trivial/lightweight.
3. `detail::GlTable` remains the single function-pointer table.
4. A failed or lost context must not expose stale loader state or capabilities.
5. Restore must reload function pointers before restored listeners run.
6. Initialization must validate every mandatory entry point for the detected
   native GLES version, the WebGL-compatible subset, or the desktop 3.3+
   common subset before publishing state.
7. Enum domains must model legal GL parameter domains, not merely share a raw
   underlying type.
8. Raw pointer overloads remain available where OpenGL uses `nullptr` to mean
   allocation without initial data.
9. No C++ modules, C++26-only features, heavy metaprogramming, or
   `std::expected`-based framework should be introduced.
10. Shared `develop` must not be used as a scratch area; follow-up changes and
    downstream migrations stay in isolated feature worktrees until approved.

---

## 9. Key files

| Path | Purpose |
|---|---|
| `include/metagl/Functions.hpp` | Public typed wrapper declarations and templates |
| `include/metagl/Enums.hpp` | OpenGL enum domains and bitfield traits |
| `include/metagl/Types.hpp` | GL aliases, handles, concepts, checked conversions |
| `include/metagl/Loader.hpp` | Initialization, restore, and function availability |
| `include/metagl/Context.hpp` | Context state and generation |
| `include/metagl/Capabilities.hpp` | Version/backend/extension capabilities |
| `include/metagl/ContextEvents.hpp` | Context lifecycle listeners |
| `include/metagl/Debug.hpp` | Optional debug wrapper layer |
| `include/metagl/Emscripten.hpp` | Browser context-loss callbacks |
| `include/metagl/DesktopEsTier.hpp` | Internal-only desktop OpenGL ES-tier diagnostic (R76–R78) |
| `src/Functions.cpp` | Loader table and 358 wrapper implementations |
| `src/RequiredFunctions.inc` | Khronos-verified GLES 3.0/3.1/3.2 mandatory entry-point sets |
| `src/Context.cpp` | Context/capability state and restore flow |
| `src/Debug.cpp` | Debug records, error checks, and flushing |
| `tools/verify_api.py` | API/loader/version-required-function consistency verifier |
| `.github/workflows/ci.yml` | Cross-platform build and test matrix |
| `plan.md` | The authoritative R01–R78 backlog, including the findings and rationale behind each task |
| `archive/plan20260719.md` | Archived, fully completed themes A–L (2026-07-19) |
