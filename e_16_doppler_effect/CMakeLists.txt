
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_16_doppler_effect e_16_doppler_effect.cxx)
target_link_libraries(e_16_doppler_effect PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_16_doppler_effect PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_16_doppler_effect PROPERTY CXX_STANDARD 20)

target_link_libraries(e_16_doppler_effect PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)

