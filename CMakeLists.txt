cmake_minimum_required(VERSION 3.23)

project(meta-gl
    VERSION 0.4.1
    DESCRIPTION "Low-level type-safe C++ wrapper over OpenGL function pointers"
    LANGUAGES CXX)

# --- Release identity (docs/releasing.md) --------------------------------------------------
# project(VERSION) accepts numeric components only, so the Semantic Versioning pre-release
# identifier lives beside it and is joined back on here. Deliberately a normal variable and not
# a cache entry: the version identifies the release, it is not a per-build knob, and a cached
# copy would keep an already-configured build directory reporting the previous release after a
# bump. METAGL_VERSION_STRING is the single spelling the rest of the build reads -- the
# generated metagl/Version.hpp, the Doxygen PROJECT_NUMBER, the configure banner. Do not
# re-derive it elsewhere.
set(METAGL_VERSION_PRERELEASE "")
if(METAGL_VERSION_PRERELEASE)
    set(METAGL_VERSION_STRING "${PROJECT_VERSION}-${METAGL_VERSION_PRERELEASE}")
else()
    set(METAGL_VERSION_STRING "${PROJECT_VERSION}")
endif()
message(STATUS "meta-gl: version ${METAGL_VERSION_STRING}")
include(cmake/Version.cmake)

# Keep conventional BUILD_SHARED_LIBS behavior without forcing a cache option
# into parent projects that consume meta-gl via add_subdirectory().
if(PROJECT_IS_TOP_LEVEL AND NOT DEFINED BUILD_SHARED_LIBS)
    option(BUILD_SHARED_LIBS "Build libraries as shared libraries" OFF)
endif()

# Backward-compatible aliases for the pre-0.3 standalone option names.
if(PROJECT_IS_TOP_LEVEL AND DEFINED SANITIZE AND NOT DEFINED METAGL_SANITIZE)
    set(METAGL_SANITIZE "${SANITIZE}")
endif()
if(PROJECT_IS_TOP_LEVEL AND DEFINED BUILD_TESTING AND NOT DEFINED METAGL_BUILD_TESTS)
    set(METAGL_BUILD_TESTS "${BUILD_TESTING}")
endif()
if(PROJECT_IS_TOP_LEVEL AND DEFINED BUILD_EXAMPLES AND NOT DEFINED METAGL_BUILD_EXAMPLES)
    set(METAGL_BUILD_EXAMPLES "${BUILD_EXAMPLES}")
endif()

option(METAGL_SANITIZE "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
option(METAGL_BUILD_TESTS "Build the meta-gl test suite" OFF)
option(METAGL_BUILD_GPU_TESTS "Build EGL tests that require a real GL implementation" OFF)
option(METAGL_BUILD_EXAMPLES "Build the meta-gl examples" OFF)
option(METAGL_BUILD_DOCS "Build Doxygen API documentation" OFF)
option(METAGL_ENABLE_DEBUG_LOGGING "Compile per-call GL debug logging into meta-gl" OFF)
option(METAGL_DEBUG_IMMEDIATE "Flush debug logging after every GL call" OFF)

add_library(meta-gl)
add_library(meta-gl::meta-gl ALIAS meta-gl)

set_target_properties(meta-gl PROPERTIES
    CXX_EXTENSIONS NO
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON)

include(GenerateExportHeader)
generate_export_header(meta-gl
    EXPORT_MACRO_NAME   METAGL_API
    EXPORT_FILE_NAME    include/metagl/Export.hpp
    BASE_NAME           METAGL
)

# R44-R47: on ELF (Unix, non-Apple) shared builds, enforce the public export
# policy at link time with a version script, so that vague-linkage libstdc++
# template symbols (e.g. from the internal std::unordered_map cache in
# Functions.cpp) never leak into the dynamic symbol table alongside the
# metagl:: public API. See cmake/metagl.version and
# tests/test_export_symbols.py.
if(UNIX AND NOT APPLE)
    set(METAGL_VERSION_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/cmake/metagl.version")
    target_link_options(meta-gl PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:LINKER:--version-script=${METAGL_VERSION_SCRIPT}>
    )
    set_target_properties(meta-gl PROPERTIES LINK_DEPENDS "${METAGL_VERSION_SCRIPT}")
endif()

target_compile_features(meta-gl PUBLIC cxx_std_23)

target_sources(meta-gl
    PRIVATE
        src/Functions.cpp
        src/Context.cpp
        src/Debug.cpp
)

target_sources(meta-gl
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES
        include/metagl/metagl.hpp
        include/metagl/Types.hpp
        include/metagl/Enums.hpp
        include/metagl/Functions.hpp
        include/metagl/Loader.hpp
        include/metagl/Context.hpp
        include/metagl/Capabilities.hpp
        include/metagl/ContextEvents.hpp
        include/metagl/Emscripten.hpp
        include/metagl/Debug.hpp
        include/metagl/EnumNames.hpp
        include/metagl/DesktopEsTier.hpp
)

target_sources(meta-gl
    PUBLIC
    FILE_SET generated_headers
    TYPE HEADERS
    BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}/include"
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/include/metagl/Export.hpp"
        "${CMAKE_CURRENT_BINARY_DIR}/include/metagl/Version.hpp"
)

target_include_directories(meta-gl
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/third_party/Khronos>
        $<INSTALL_INTERFACE:include>
)

function(metagl_apply_warnings target_name)
    target_compile_options(${target_name} PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive- /Zc:preprocessor>
    )
endfunction()

function(metagl_stage_runtime target_name)
    if(WIN32 AND BUILD_SHARED_LIBS)
        add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:meta-gl>"
                "$<TARGET_FILE_DIR:${target_name}>"
            COMMENT "Staging the meta-gl runtime beside ${target_name}"
            VERBATIM
        )
    endif()
endfunction()

metagl_apply_warnings(meta-gl)

if(METAGL_ENABLE_DEBUG_LOGGING OR METAGL_DEBUG_IMMEDIATE)
    target_compile_definitions(meta-gl PRIVATE METAGLDEBUG)
endif()
if(METAGL_DEBUG_IMMEDIATE)
    target_compile_definitions(meta-gl PRIVATE METAGLDEBUG_IMMEDIATE)
endif()

if(METAGL_SANITIZE)
    target_compile_options(meta-gl PUBLIC
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-fsanitize=address,undefined -fno-omit-frame-pointer>
    )
    target_link_options(meta-gl PUBLIC
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-fsanitize=address,undefined>
    )
endif()

if(METAGL_BUILD_GPU_TESTS AND NOT METAGL_BUILD_TESTS)
    message(FATAL_ERROR "METAGL_BUILD_GPU_TESTS requires METAGL_BUILD_TESTS=ON")
endif()

if(METAGL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(METAGL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(METAGL_BUILD_DOCS)
    find_package(Doxygen REQUIRED)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        @ONLY
    )
    add_custom_target(metagl-docs
        COMMAND Doxygen::doxygen "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating meta-gl API documentation"
        VERBATIM
    )
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS meta-gl
        EXPORT meta-gl-targets
        FILE_SET HEADERS           DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILE_SET generated_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY
        third_party/Khronos/GLES2
        third_party/Khronos/GLES3
        third_party/Khronos/KHR
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES
        LICENSE
        third_party/Khronos/LICENSE-MIT.txt
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/meta-gl
)

install(EXPORT meta-gl-targets
        FILE meta-glTargets.cmake
        NAMESPACE meta-gl::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meta-gl
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/meta-glConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meta-gl
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMinorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/meta-glConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/meta-gl
)
