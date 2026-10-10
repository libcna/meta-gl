cmake_minimum_required(VERSION 3.23)

project(meta-gl-package-consumer LANGUAGES CXX)

find_package(meta-gl CONFIG REQUIRED)

add_executable(meta-gl-package-consumer main.cpp)
target_link_libraries(meta-gl-package-consumer PRIVATE meta-gl::meta-gl)
target_compile_features(meta-gl-package-consumer PRIVATE cxx_std_23)
set_target_properties(meta-gl-package-consumer PROPERTIES CXX_EXTENSIONS NO)
# The installed metagl/Version.hpp must describe the same release as the installed
# meta-glConfigVersion.cmake that find_package() just accepted.
target_compile_definitions(meta-gl-package-consumer PRIVATE
    METAGL_PACKAGE_VERSION="${meta-gl_VERSION}")
