
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_09_tomography_with_filter e_09_tomography_with_filter.cxx)
target_link_libraries(e_09_tomography_with_filter PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_09_tomography_with_filter PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_09_tomography_with_filter PROPERTY CXX_STANDARD 17)

target_link_libraries(e_09_tomography_with_filter PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)