find_package(range-v3 CONFIG REQUIRED)



add_executable(e_08_function_templates_and_ranges e_08_function_templates_and_ranges.cxx)
set_property(TARGET e_08_function_templates_and_ranges PROPERTY CXX_STANDARD 20)
target_link_libraries(e_08_function_templates_and_ranges PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)