
find_package(ROOT REQUIRED  COMPONENTS  Gui)


find_package(range-v3 CONFIG REQUIRED)






add_executable(e_17_implot e_17_implot.cxx)
target_link_libraries(e_17_implot PUBLIC ${ROOT_LIBRARIES} ROOT::Gui)
target_include_directories(e_17_implot PUBLIC ${ROOT_INCLUDE_DIRS})
set_property(TARGET e_17_implot PROPERTY CXX_STANDARD 20)

target_link_libraries(e_17_implot PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)



    target_link_libraries(e_17_implot PRIVATE app)