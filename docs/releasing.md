# Releasing meta-gl

*Current as of 0.4.0 (2026-10-10).*

meta-gl follows [Semantic Versioning 2.0.0](https://semver.org/spec/v2.0.0.html). A release is
an annotated git tag plus a `CHANGELOG.md` entry — there is no separate release branch, and
nothing is published to a package registry. Pushing a `vMAJOR.MINOR.PATCH` tag starts
`.github/workflows/release.yml`, which builds and tests the Linux static, Linux shared and
Windows shared packages, validates each archive with `tests/package-consumer`, and publishes a
public GitHub release whose notes are the tag's `CHANGELOG.md` section.

## Where the version lives

The version is decided in exactly **one** place:

```cmake
# CMakeLists.txt (repository root)
project(meta-gl VERSION 0.4.0 ...)
set(METAGL_VERSION_PRERELEASE "")   # e.g. "beta.1"; empty on a final release
```

`project(VERSION …)` accepts numeric components only, so the pre-release identifier sits beside
it and the two are joined into `METAGL_VERSION_STRING` (`0.4.0`, or `0.5.0-beta.1`).
`METAGL_VERSION_PRERELEASE` is deliberately a normal variable and not a cache entry: a cached
copy would keep an existing build directory reporting the previous release after a bump.

Everything else derives from that:

| Consumer | How it gets the version |
|---|---|
| C++ code | `#include <metagl/Version.hpp>` (also pulled in by `metagl.hpp`) → `metagl::GetVersionString()`, `METAGL_VERSION_MAJOR`, … |
| `find_package(meta-gl)` consumers | `meta-glConfigVersion.cmake` → `meta-gl_VERSION` (numeric components only) |
| The shared library | `VERSION` property → `libmeta-gl.so.0.4.0` |
| Doxygen | `PROJECT_NUMBER` in `cmake/Doxyfile.in` is `@METAGL_VERSION_STRING@` |
| The configure banner | `-- meta-gl: version <x.y.z>` |

`metagl/Version.hpp` is **generated** by `cmake/Version.cmake` from
`cmake/templates/Version.hpp.in` into `<build>/include/metagl/Version.hpp`, beside the generated
`Export.hpp`, and is installed through the same `generated_headers` file set. Never edit the
generated file, and never hard-code the version anywhere else. `tests/test_version.cpp` and the
installed-package consumer check that the header, CMake and the package version file agree; they
name no concrete release, so a bump never edits them.

Two copies are maintained by hand and must be updated as part of a bump:

- `CHANGELOG.md` — the release entry and its link definitions at the bottom.
- `README.md` — the *Version* section and the `find_package(meta-gl <MAJOR.MINOR> …)` example.

## Numbers that are *not* the product version

- **`SOVERSION`** is `0` for the whole pre-1.0 phase (plan R04), so the SONAME stays
  `libmeta-gl.so.0` across `0.x` releases; `tests/test_soname.py` pins it. It signals that there
  is no ABI stability before 1.0, not which release you hold.
- **The OpenGL / OpenGL ES version** of a live context (`GetContextInfo().major/minor`,
  `GetCapabilities()`) is a property of the driver, reported at runtime.
- **`"version": 6`** in `CMakePresets.json` is the presets schema version.

## History of the number

`0.1.0`, `0.2.0` and `0.3.0` were recorded in `project()` and `CHANGELOG.md` as development
milestones, but none of them was ever tagged or published. `v0.4.0` is the first tag; the
milestone entries stay in `CHANGELOG.md` because they document the breaking changes made along
the way.

## Pre-1.0 policy

While the major version is 0, a minor bump may change the public API, and the package version
file uses `SameMinorVersion` compatibility: `find_package(meta-gl 0.4)` accepts any `0.4.z` and
nothing else. Pre-release identifiers are `alpha.N` → `beta.N` → `rc.N`, ordered as SemVer
orders them. The release workflow is triggered only by final `vMAJOR.MINOR.PATCH` tags; a
pre-release tag is a git tag only.

## Downstream consumers

easy-gl consumes this repository as a **sibling checkout** with `add_subdirectory(../meta-gl)`,
and CNA consumes easy-gl the same way, so a downstream build takes whatever revision the
`meta-gl` checkout happens to be on. A downstream release entry can name a meta-gl tag instead of
a raw commit hash; tagging here is therefore worth doing before a downstream release, not after.

## Cutting a release

1. **Choose the version.** Edit `project(meta-gl VERSION …)` and/or `METAGL_VERSION_PRERELEASE`
   in the root `CMakeLists.txt`.
2. **Write the changelog entry.** Move what is under `## [Unreleased]` into a new
   `## [x.y.z] — YYYY-MM-DD` section in `CHANGELOG.md` and add the link definitions at the bottom
   of the file. The release workflow publishes exactly that section as the GitHub release notes.
3. **Update `README.md`** — the *Version* section and the `find_package` example.
4. **Record the build environment** in that entry. The library's only build dependency, the
   Khronos GLES headers, is vendored in `third_party/Khronos`, so the tag selects it; the EGL
   implementation used by the optional GPU smoke test is a system package:

   ```bash
   printf '%s\n' "$(lsb_release -ds)" "$(g++ --version | head -1)" \
       "$(cmake --version | head -1)" \
       "Mesa EGL $(dpkg-query -W -f='${Version}' libegl-mesa0)"
   ```
5. **Build and test** in the existing `build/` directory (the build rules in the parent
   `CLAUDE.md` — shared ccache, no new build directories), with the configuration the release
   workflow uses:

   ```bash
   export CCACHE_DIR=/rv/cnaccache CCACHE_BASEDIR=/rv
   cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON \
       -DMETAGL_BUILD_TESTS=ON -DMETAGL_BUILD_EXAMPLES=ON -DMETAGL_BUILD_GPU_TESTS=ON \
       -DMETAGL_BUILD_DOCS=ON \
       -DCMAKE_CXX_COMPILER_LAUNCHER=ccache -DCMAKE_C_COMPILER_LAUNCHER=ccache
   cmake --build build --parallel
   ctest --test-dir build --output-on-failure --timeout 180
   cmake --build build --target metagl-docs
   ```

   The configure banner prints `-- meta-gl: version <x.y.z>` — check it matches. The build must
   be warning-free and every test must pass.
6. **Commit** the version-bearing files by explicit name (`CMakeLists.txt`, `CHANGELOG.md`,
   `README.md`), never `git add -A`.
7. **Tag** with a `v` prefix and an annotated tag:

   ```bash
   git tag -a v0.4.0 -m "meta-gl 0.4.0"
   ```

   The tag string carries the `v`; `METAGL_VERSION_STRING` never does.
8. **Push only when the project owner asks**, and push the tag explicitly. Pushing the tag
   publishes a public GitHub release through `release.yml`:

   ```bash
   git push origin develop
   git push origin v0.4.0
   ```
9. **Open the next cycle** by adding an empty `## [Unreleased]` section back to `CHANGELOG.md`
   if step 2 consumed it.
