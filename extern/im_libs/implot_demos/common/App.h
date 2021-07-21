#include "Fonts/Fonts.h"

#include "imgui.h"
#include "implot.h"

#include <string>
#include <map>
#include <functional>

struct GLFWwindow;

// Barebones Application Framework
struct App 
{
    // Constructor.
    App(int w, int h, std::string title, std::function<void()>&& fun);
    // Destructor.
     ~App();
    // Update, called once per frame.
    void update() { m_fun(); }
    // Runs the app.
    void run();

    ImVec4 ClearColor = ImVec4(0.15f, 0.16f, 0.21f, 1.00f);  // background clear color
    GLFWwindow* Window;                                      // GLFW window handle
    std::map<std::string,ImFont*> Fonts;                     // font map
    std::function<void()> m_fun;
};