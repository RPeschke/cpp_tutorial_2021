
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_20_QM_1_Schroedinger_equation e_20_QM_1_Schroedinger_equation.cxx)
target_link_libraries(e_20_QM_1_Schroedinger_equation  ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_20_QM_1_Schroedinger_equation PUBLIC ${ROOT_INCLUDE_DIRS})


set_property(TARGET e_20_QM_1_Schroedinger_equation PROPERTY CXX_STANDARD 20)
target_link_libraries(e_20_QM_1_Schroedinger_equation  range-v3 range-v3-meta range-v3::meta range-v3-concepts)
target_link_libraries(e_20_QM_1_Schroedinger_equation  app)

