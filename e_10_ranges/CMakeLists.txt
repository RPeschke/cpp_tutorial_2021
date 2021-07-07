
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_10_ranges e_10_ranges.cxx)
target_link_libraries(e_10_ranges PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_10_ranges PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_10_ranges PROPERTY CXX_STANDARD 20)

target_link_libraries(e_10_ranges PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
