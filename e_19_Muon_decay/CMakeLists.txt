
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_19_Muon_decay e_19_Muon_decay.cxx)
target_link_libraries(e_19_Muon_decay  ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_19_Muon_decay PUBLIC ${ROOT_INCLUDE_DIRS})


set_property(TARGET e_19_Muon_decay PROPERTY CXX_STANDARD 20)
target_link_libraries(e_19_Muon_decay  range-v3 range-v3-meta range-v3::meta range-v3-concepts)
target_link_libraries(e_19_Muon_decay  app)

target_link_libraries(e_19_Muon_decay   e_19a_decay_lib) 