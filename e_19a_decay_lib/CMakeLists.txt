find_package(ROOT REQUIRED  COMPONENTS  Gui)



add_library(e_19a_decay_lib STATIC   src/particle.cc) 
target_include_directories(e_19a_decay_lib PUBLIC include/) 

target_link_libraries(e_19a_decay_lib  ${ROOT_LIBRARIES})
target_include_directories(e_19a_decay_lib PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_19a_decay_lib PROPERTY CXX_STANDARD 20)