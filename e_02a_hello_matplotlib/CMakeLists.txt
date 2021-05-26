
find_path(MATPLOTLIB_CPP_INCLUDE_DIRS "matplotlibcpp.h")
message(${MATPLOTLIB_CPP_INCLUDE_DIRS})
#find_path(SYSTEM_INCLUDE_DIR zlib.h)
message(${CMAKE_TOOLCHAIN_FILE})
#find_package(matplotlib_cpp)
find_package(PythonLibs REQUIRED COMPONENTS Development)
message(${PYTHON_INCLUDE_DIRS})

find_package(Python REQUIRED COMPONENTS Development)
message(${Python_SITEARCH})

add_executable(e_02a_hello_matplotlib e_02a_hello_matplotlib.cxx)
target_link_libraries(e_02a_hello_matplotlib ${PYTHON_LIBRARIES})
set_property(TARGET e_02a_hello_matplotlib PROPERTY CXX_STANDARD 20)
target_include_directories(e_02a_hello_matplotlib PUBLIC ${PYTHON_INCLUDE_DIRS})
message("${PYTHON_INCLUDE_DIRS}/../lib/site-packages/numpy/core/include")

target_include_directories(e_02a_hello_matplotlib PRIVATE ${MATPLOTLIB_CPP_INCLUDE_DIRS})
target_include_directories(e_02a_hello_matplotlib PRIVATE "${PYTHON_INCLUDE_DIRS}/../lib/site-packages/numpy/core/include")
#target_include_directories(main PRIVATE /mnt/c/Users/Richa/Documents/github/vcpkg/installed/x86-windows/include)



