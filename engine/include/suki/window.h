#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

namespace SukiEngine
{

class Window
{
   public:
    Window();
    Window(std::string& title, int height, int width);

    ~Window();

   private:
    std::string m_WindowTitle = "Window";
    int m_WindowHeight = 480;
    int m_WindowWidth = 640;

    GLFWwindow* m_Window = nullptr;
};

}  // namespace SukiEngine

#endif  // WINDOW_H
