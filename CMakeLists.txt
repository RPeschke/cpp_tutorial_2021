cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(cpp_tutorial_2021)
include(${CMAKE_TOOLCHAIN_FILE})

add_subdirectory(e_01_hello_world)


add_subdirectory(e_02_hello_root)
#add_subdirectory(e_02a_hello_matplotlib)
add_subdirectory(e_03_single_pendulum)
add_subdirectory(e_04_phys_sim_header_library)
add_subdirectory(e_05_use_phys_sim)
add_subdirectory(e_06_catch2)