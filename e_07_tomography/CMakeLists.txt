
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_07_tomography e_07_tomography.cxx)
target_link_libraries(e_07_tomography PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_07_tomography PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_07_tomography PROPERTY CXX_STANDARD 17)

target_link_libraries(e_07_tomography PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)