
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_21_QM_2_TunnelEffect e_21_QM_2_TunnelEffect.cxx)
target_link_libraries(e_21_QM_2_TunnelEffect  ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_21_QM_2_TunnelEffect PUBLIC ${ROOT_INCLUDE_DIRS})


set_property(TARGET e_21_QM_2_TunnelEffect PROPERTY CXX_STANDARD 20)
target_link_libraries(e_21_QM_2_TunnelEffect  range-v3 range-v3-meta range-v3::meta range-v3-concepts)
target_link_libraries(e_21_QM_2_TunnelEffect  app)

