
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_14_special_relativity_Twin_paradox e_14_special_relativity_Twin_paradox.cxx)
target_link_libraries(e_14_special_relativity_Twin_paradox PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_14_special_relativity_Twin_paradox PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_14_special_relativity_Twin_paradox PROPERTY CXX_STANDARD 20)

target_link_libraries(e_14_special_relativity_Twin_paradox PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
