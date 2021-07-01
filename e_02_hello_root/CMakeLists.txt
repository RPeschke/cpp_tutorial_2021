
find_package(ROOT REQUIRED)
message(${ROOT_LIBRARIES})
add_executable(e_02_hello_root e_02_hello_root.cxx)
target_link_libraries(e_02_hello_root PUBLIC ${ROOT_LIBRARIES})
target_include_directories(e_02_hello_root PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_02_hello_root PROPERTY CXX_STANDARD 17)