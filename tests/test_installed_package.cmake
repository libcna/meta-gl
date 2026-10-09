if(NOT DEFINED METAGL_SOURCE_DIR OR NOT DEFINED METAGL_BUILD_DIR)
    message(FATAL_ERROR "METAGL_SOURCE_DIR and METAGL_BUILD_DIR are required")
endif()

set(install_prefix "${METAGL_BUILD_DIR}/package-test/install")
set(consumer_build "${METAGL_BUILD_DIR}/package-test/consumer-build")

file(REMOVE_RECURSE "${METAGL_BUILD_DIR}/package-test")

set(install_command
    "${CMAKE_COMMAND}" --install "${METAGL_BUILD_DIR}" --prefix "${install_prefix}")
if(METAGL_TEST_CONFIG)
    list(APPEND install_command --config "${METAGL_TEST_CONFIG}")
endif()

execute_process(
    COMMAND ${install_command}
    RESULT_VARIABLE install_result
)
if(NOT install_result EQUAL 0)
    message(FATAL_ERROR "meta-gl installation failed: ${install_result}")
endif()

execute_process(
    COMMAND "${CMAKE_COMMAND}"
        -S "${METAGL_SOURCE_DIR}/tests/package-consumer"
        -B "${consumer_build}"
        "-DCMAKE_PREFIX_PATH=${install_prefix}"
    RESULT_VARIABLE configure_result
)
if(NOT configure_result EQUAL 0)
    message(FATAL_ERROR "Installed-package consumer configure failed: ${configure_result}")
endif()

set(build_command "${CMAKE_COMMAND}" --build "${consumer_build}")
if(METAGL_TEST_CONFIG)
    list(APPEND build_command --config "${METAGL_TEST_CONFIG}")
endif()

execute_process(
    COMMAND ${build_command}
    RESULT_VARIABLE build_result
)
if(NOT build_result EQUAL 0)
    message(FATAL_ERROR "Installed-package consumer build failed: ${build_result}")
endif()

# R12: Run the consumer executable to verify out-of-line symbol resolution.
if(METAGL_TEST_CONFIG)
    set(consumer_exe "${consumer_build}/${METAGL_TEST_CONFIG}/meta-gl-package-consumer")
else()
    set(consumer_exe "${consumer_build}/meta-gl-package-consumer")
endif()

# Also accept the executable without a config subdirectory (single-config generators on Unix).
if(NOT EXISTS "${consumer_exe}" AND EXISTS "${consumer_build}/meta-gl-package-consumer")
    set(consumer_exe "${consumer_build}/meta-gl-package-consumer")
endif()

# A shared meta-gl on Windows is the package's bin/meta-gl.dll, and Windows finds a DLL through
# PATH or the executable's own directory -- there is no rpath. Run without it, the consumer died
# with 0xc0000135 (DLL not found) on every shared Windows job (CNA plans/plan_apple_m4.md AM4-252).
if(CMAKE_HOST_WIN32)
    file(TO_NATIVE_PATH "${install_prefix}/bin" metagl_install_bin)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E env "PATH=${metagl_install_bin};$ENV{PATH}" "${consumer_exe}"
        RESULT_VARIABLE run_result
    )
else()
    execute_process(
        COMMAND "${consumer_exe}"
        RESULT_VARIABLE run_result
    )
endif()
if(NOT run_result EQUAL 0)
    message(FATAL_ERROR "Installed-package consumer executable failed with exit code: ${run_result}")
endif()

# R13: Re-run the consumer explicitly as a static-library consumer.
# This verifies that the installed CMake package works correctly when
# the downstream project forces BUILD_SHARED_LIBS=OFF (the default for
# meta-gl, but we make it explicit to guard against regressions).
set(consumer_build_static "${METAGL_BUILD_DIR}/package-test/consumer-build-static")

execute_process(
    COMMAND "${CMAKE_COMMAND}"
        -S "${METAGL_SOURCE_DIR}/tests/package-consumer"
        -B "${consumer_build_static}"
        "-DCMAKE_PREFIX_PATH=${install_prefix}"
        -DBUILD_SHARED_LIBS=OFF
    RESULT_VARIABLE configure_static_result
)
if(NOT configure_static_result EQUAL 0)
    message(FATAL_ERROR "Static-library consumer configure failed: ${configure_static_result}")
endif()

set(build_static_command "${CMAKE_COMMAND}" --build "${consumer_build_static}")
if(METAGL_TEST_CONFIG)
    list(APPEND build_static_command --config "${METAGL_TEST_CONFIG}")
endif()

execute_process(
    COMMAND ${build_static_command}
    RESULT_VARIABLE build_static_result
)
if(NOT build_static_result EQUAL 0)
    message(FATAL_ERROR "Static-library consumer build failed: ${build_static_result}")
endif()

# Locate and run the static-library consumer executable.
if(METAGL_TEST_CONFIG)
    set(consumer_static_exe "${consumer_build_static}/${METAGL_TEST_CONFIG}/meta-gl-package-consumer")
else()
    set(consumer_static_exe "${consumer_build_static}/meta-gl-package-consumer")
endif()

# Also accept the executable without a config subdirectory (single-config generators on Unix).
if(NOT EXISTS "${consumer_static_exe}" AND EXISTS "${consumer_build_static}/meta-gl-package-consumer")
    set(consumer_static_exe "${consumer_build_static}/meta-gl-package-consumer")
endif()

execute_process(
    COMMAND "${consumer_static_exe}"
    RESULT_VARIABLE run_static_result
)
if(NOT run_static_result EQUAL 0)
    message(FATAL_ERROR "Static-library consumer executable failed with exit code: ${run_static_result}")
endif()

# R14: Exercise the installed-package consumer with a shared library on Unix.
# We re-install meta-gl as a shared library into a separate prefix, then
# configure, build, and run an external consumer against it.  This verifies
# that the installed CMake package correctly propagates the SONAME dependency
# and that the consumer executable can resolve the library at runtime via
# LD_LIBRARY_PATH pointing at the installed lib directory.
#
# This sub-test is skipped on non-Unix platforms (Windows uses a different
# runtime-discovery mechanism and is covered by R15/R75).
if(NOT CMAKE_HOST_WIN32)
    set(install_shared_prefix "${METAGL_BUILD_DIR}/package-test/install-shared")
    set(consumer_build_shared "${METAGL_BUILD_DIR}/package-test/consumer-build-shared")

    # Re-install with BUILD_SHARED_LIBS=ON into a dedicated prefix.
    # We need a dedicated build directory so the shared variant does not
    # overwrite the static install used by R12/R13.
    set(shared_build_dir "${METAGL_BUILD_DIR}/package-test/meta-gl-shared-build")

    execute_process(
        COMMAND "${CMAKE_COMMAND}"
            -S "${METAGL_SOURCE_DIR}"
            -B "${shared_build_dir}"
            -DCMAKE_BUILD_TYPE=Release
            -DBUILD_SHARED_LIBS=ON
            -DMETAGL_BUILD_TESTS=OFF
        RESULT_VARIABLE configure_shared_metagl_result
    )
    if(NOT configure_shared_metagl_result EQUAL 0)
        message(FATAL_ERROR "Shared meta-gl configure failed: ${configure_shared_metagl_result}")
    endif()

    execute_process(
        COMMAND "${CMAKE_COMMAND}" --build "${shared_build_dir}" --config Release
        RESULT_VARIABLE build_shared_metagl_result
    )
    if(NOT build_shared_metagl_result EQUAL 0)
        message(FATAL_ERROR "Shared meta-gl build failed: ${build_shared_metagl_result}")
    endif()

    execute_process(
        COMMAND "${CMAKE_COMMAND}" --install "${shared_build_dir}" --config Release
                                  --prefix "${install_shared_prefix}"
        RESULT_VARIABLE install_shared_result
    )
    if(NOT install_shared_result EQUAL 0)
        message(FATAL_ERROR "Shared meta-gl install failed: ${install_shared_result}")
    endif()

    # Configure and build the external consumer against the shared install.
    execute_process(
        COMMAND "${CMAKE_COMMAND}"
            -S "${METAGL_SOURCE_DIR}/tests/package-consumer"
            -B "${consumer_build_shared}"
            "-DCMAKE_PREFIX_PATH=${install_shared_prefix}"
            -DBUILD_SHARED_LIBS=ON
        RESULT_VARIABLE configure_shared_result
    )
    if(NOT configure_shared_result EQUAL 0)
        message(FATAL_ERROR "Shared-library consumer configure failed: ${configure_shared_result}")
    endif()

    execute_process(
        COMMAND "${CMAKE_COMMAND}" --build "${consumer_build_shared}" --config Release
        RESULT_VARIABLE build_shared_result
    )
    if(NOT build_shared_result EQUAL 0)
        message(FATAL_ERROR "Shared-library consumer build failed: ${build_shared_result}")
    endif()

    # Locate the consumer executable.
    set(consumer_shared_exe "${consumer_build_shared}/meta-gl-package-consumer")

    # Run the consumer with LD_LIBRARY_PATH pointing at the installed lib
    # directory so the dynamic linker finds the shared meta-gl library.
    set(shared_lib_dir "${install_shared_prefix}/lib")
    execute_process(
        COMMAND "${consumer_shared_exe}"
        RESULT_VARIABLE run_shared_result
        COMMAND_ECHO STDOUT
        # Prepend the installed lib directory to the search path.
        WORKING_DIRECTORY "${consumer_build_shared}"
    )
    # If the plain run failed, retry with LD_LIBRARY_PATH set explicitly.
    if(NOT run_shared_result EQUAL 0)
        execute_process(
            COMMAND "${CMAKE_COMMAND}" -E env
                    "LD_LIBRARY_PATH=${shared_lib_dir}"
                    "${consumer_shared_exe}"
            RESULT_VARIABLE run_shared_result
        )
    endif()
    if(NOT run_shared_result EQUAL 0)
        message(FATAL_ERROR "Shared-library consumer executable failed with exit code: ${run_shared_result}")
    endif()
endif() # NOT CMAKE_HOST_WIN32
