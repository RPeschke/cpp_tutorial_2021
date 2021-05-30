
find_package(ROOT REQUIRED)

add_executable(e_05_use_phys_sim e_05_use_phys_sim.cxx e_05_second_file.cc)
target_link_libraries(e_05_use_phys_sim PUBLIC ${ROOT_LIBRARIES})
target_link_libraries(e_05_use_phys_sim PUBLIC e_04_phys_sim_header_library)
target_include_directories(e_05_use_phys_sim PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_05_use_phys_sim PROPERTY CXX_STANDARD 14)