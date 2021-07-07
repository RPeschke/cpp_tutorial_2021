cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(cpp_tutorial_2021)


add_compile_definitions(__CPP20__)



if(DEFINED ENV{vcpkg_cmake_toolchain})
    message( "vcpkg_cmake_toolchain = $ENV{vcpkg_cmake_toolchain}")
    include($ENV{vcpkg_cmake_toolchain})
else()
    message( "Evirement Variable  'vcpkg_cmake_toolchain' Not found. Please provide the envirment variable poini ")
endif()

include_directories("extern/TGSignals")
include_directories("extern/group_helpers")

add_subdirectory(e_01_hello_world)


add_subdirectory(e_02_hello_root)
#add_subdirectory(e_02a_hello_matplotlib)
add_subdirectory(e_03_single_pendulum)
add_subdirectory(e_04_phys_sim_header_library)
add_subdirectory(e_05_use_phys_sim)
#add_subdirectory(e_06_catch2)
add_subdirectory(e_07_tomography)

add_subdirectory(e_08_function_templates_and_ranges)
add_subdirectory(e_09_tomography_with_filter)
add_subdirectory(e_10_ranges)
add_subdirectory(e_11_Fourier_transform)
#add_subdirectory(e_12_special_relativity)
add_subdirectory(e_13_special_relativity_2)