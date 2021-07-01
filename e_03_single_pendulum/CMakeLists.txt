
find_package(ROOT REQUIRED  COMPONENTS  Gui)









add_executable(e_03_single_pendulum e_03_single_pendulum.cxx)
target_link_libraries(e_03_single_pendulum PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_03_single_pendulum PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_03_single_pendulum PROPERTY CXX_STANDARD 17)