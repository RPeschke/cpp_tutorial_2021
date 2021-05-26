
find_package(ROOT REQUIRED)

add_library(e_04_phys_sim_header_library INTERFACE) 
target_include_directories(e_04_phys_sim_header_library INTERFACE ./) 

target_link_libraries(e_04_phys_sim_header_library INTERFACE ${ROOT_LIBRARIES})
target_include_directories(e_04_phys_sim_header_library INTERFACE ${ROOT_INCLUDE_DIRS})
