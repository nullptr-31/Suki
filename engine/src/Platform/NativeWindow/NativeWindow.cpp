#include "Platform/NativeWindow/NativeWindow.h"

#include "GLFW/glfw3.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Suki/Core/Assert.h"
#include "Suki/Core/Logger.h"
#include "Suki/Event/ApplicationEvent.h"
#include "Suki/Event/KeyEvent.h"
#include "Suki/Event/MouseEvent.h"

namespace Suki
{

static uint8_t s_GLFWWindowCount = 0;

NativeWindow::NativeWindow(const WindowSpecs& specs)
{
    Init(specs);
}

NativeWindow::~NativeWindow()
{
    Shutdown();
}

void NativeWindow::Init(const WindowSpecs& specs)
{
    m_Data.Title = specs.Title;
    m_Data.Width = specs.Width;
    m_Data.Height = specs.Height;

    SK_CORE_INFO("Initializing NativeWindow {0}", specs.Title);

    if(s_GLFWWindowCount == 0)
    {
        int result = glfwInit();
        SK_ASSERT_MSG(result, "Failed to inialize GLFW");
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height,
                                m_Data.Title.c_str(), NULL, NULL);
    s_GLFWWindowCount++;

    m_Context = GraphicsContext::Create(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);

    glfwSetWindowSizeCallback(
        m_Window,
        [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

    glfwSetWindowCloseCallback(
        m_Window,
        [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

    glfwSetKeyCallback(
        m_Window,
        [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, true);
                    data.EventCallback(event);
                    break;
                }
            }
        });

    glfwSetCharCallback(m_Window,
                        [](GLFWwindow* window, unsigned int keycode)
                        {
                            WindowData& data =
                                *(WindowData*)glfwGetWindowUserPointer(window);

                            KeyTypedEvent event(keycode);
                            data.EventCallback(event);
                        });

    glfwSetMouseButtonCallback(
        m_Window,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch(action)
            {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);

                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);

                    break;
                }
            }
        });

    glfwSetScrollCallback(
        m_Window,
        [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

    glfwSetCursorPosCallback(
        m_Window,
        [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
}

void NativeWindow::Shutdown()
{

    glfwDestroyWindow(m_Window);
    s_GLFWWindowCount--;

    if(s_GLFWWindowCount == 0)
    {
        glfwTerminate();
    }
}

void NativeWindow::OnUpdate()
{
    glfwPollEvents();

    m_Context->SwapBuffers();
}

}  // namespace Suki
