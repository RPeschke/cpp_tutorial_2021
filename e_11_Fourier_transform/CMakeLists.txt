
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_11_Fourier_transform e_11_Fourier_transform.cxx)
target_link_libraries(e_11_Fourier_transform PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_11_Fourier_transform PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_11_Fourier_transform PROPERTY CXX_STANDARD 20)

target_link_libraries(e_11_Fourier_transform PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)