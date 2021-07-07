
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_13_special_relativity_2 e_13_special_relativity_2.cxx)
target_link_libraries(e_13_special_relativity_2 PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_13_special_relativity_2 PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_13_special_relativity_2 PROPERTY CXX_STANDARD 20)

target_link_libraries(e_13_special_relativity_2 PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
