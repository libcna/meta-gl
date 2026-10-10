# =====================================================================================
# meta-gl release identity -> the generated public header metagl/Version.hpp.
#
# The single source of truth is project(meta-gl VERSION ...) plus METAGL_VERSION_PRERELEASE in
# the root CMakeLists.txt; this file only renders that decision into a header. Nothing else in
# the tree may hard-code the number -- docs/releasing.md lists the hand-maintained copies
# (CHANGELOG.md, README.md) that a release bump must update by hand.
#
# CMAKE_CURRENT_BINARY_DIR, not CMAKE_BINARY_DIR: when meta-gl is consumed via
# add_subdirectory (as easy-gl does), CMAKE_BINARY_DIR is the *consumer's* build root, and the
# generated header belongs beside meta-gl's own generated Export.hpp.
# =====================================================================================

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/templates/Version.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/metagl/Version.hpp"
    @ONLY)
