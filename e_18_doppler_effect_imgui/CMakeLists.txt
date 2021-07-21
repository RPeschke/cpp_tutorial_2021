
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_18_doppler_effect_imgui e_18_doppler_effect_imgui.cxx)
target_link_libraries(e_18_doppler_effect_imgui PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_18_doppler_effect_imgui PUBLIC ${ROOT_INCLUDE_DIRS})


set_property(TARGET e_18_doppler_effect_imgui PROPERTY CXX_STANDARD 20)
target_link_libraries(e_18_doppler_effect_imgui PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
target_link_libraries(e_18_doppler_effect_imgui PRIVATE app)