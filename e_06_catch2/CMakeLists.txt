add_executable(e_06_catch2 e_06_catch2.cxx )

find_package(Catch2 CONFIG REQUIRED)
target_link_libraries(e_06_catch2 PRIVATE Catch2::Catch2)