
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_19_Muon_decay e_19_Muon_decay.cxx)
target_link_libraries(e_19_Muon_decay PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_19_Muon_decay PUBLIC ${ROOT_INCLUDE_DIRS})

target_link_library(e_19_Muon_decay e_19a_decay_lib) 

set_property(TARGET e_19_Muon_decay PROPERTY CXX_STANDARD 20)
target_link_libraries(e_19_Muon_decay PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)
target_link_libraries(e_19_Muon_decay PRIVATE app)