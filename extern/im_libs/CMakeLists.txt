

# FETCH CONTENT LIBS
include(FetchContent) 
# set(FETCHCONTENT_FULLY_DISCONNECTED ON)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw) 
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(iir GIT_REPOSITORY https://github.com/berndporr/iir1) 
FetchContent_MakeAvailable(iir)





set(IMGUI_HEADERS
    imgui/imconfig.h
    imgui/imgui_internal.h
    imgui/imgui.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h    
    imgui/examples/libs/gl3w/GL/gl3w.h
    imgui/examples/libs/gl3w/GL/glcorearb.h
    imgui/backends/imgui_impl_glfw.h
    imgui/backends/imgui_impl_opengl3.h
    imgui/misc/cpp/imgui_stdlib.h
)

set(IMGUI_SRC
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/examples/libs/gl3w/GL/gl3w.c
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/misc/cpp/imgui_stdlib.cpp
)

find_package(OpenGL REQUIRED)

add_library(imgui ${IMGUI_HEADERS} ${IMGUI_SRC})
target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
target_compile_definitions(imgui PRIVATE IMGUI_DLL_EXPORT)
include_directories(
  imgui/ 
  imgui/examples 
  imgui/examples/libs/gl3w 
  imgui/backends 
  imgui/misc/cpp
)



set(IMPLOT_HEADERS 
    implot/implot.h 
    implot/implot_internal.h
    )
    
set(IMPLOT_SRC     
    implot/implot.cpp 
    implot/implot_items.cpp 
    implot/implot_demo.cpp
    )

add_library(implot ${IMPLOT_HEADERS} ${IMPLOT_SRC})
target_link_libraries(implot PUBLIC imgui)
target_compile_definitions(implot PUBLIC IMPLOT_DEBUG IMPLOT_DLL_EXPORT)


add_library(app 
  implot_demos/common/App.h
  implot_demos/common/App.cpp
  implot_demos/common/Fonts/Fonts.h
  implot_demos/common/Fonts/FontAwesome5.cpp
  implot_demos/common/Fonts/RobotoRegular.cpp
  implot_demos/common/Fonts/RobotoBold.cpp
  implot_demos/common/Fonts/RobotoItalic.cpp
  implot_demos/common/Fonts/RobotoMonoRegular.cpp
  implot_demos/common/Fonts/RobotoMonoBold.cpp
  implot_demos/common/Fonts/RobotoMonoItalic.cpp
)
target_include_directories(app PUBLIC implot_demos/common)
target_include_directories(app PUBLIC implot)
target_link_libraries(app implot)