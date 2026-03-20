#include "Platform/NativeWindow/NativeWindow.h"
#include "GLFW/glfw3.h"
#include "Suki/Core/Assert.h"
#include "Suki/Core/Logger.h"

namespace Suki
{

static uint8_t s_GLFWWindowCount = 0;

NativeWindow::NativeWindow(const WindowSpecs &specs)
{
    Init(specs);
}

NativeWindow::~NativeWindow()
{
    Shutdown();
}

void NativeWindow::Init(const WindowSpecs &specs)
{
    m_Data.Title = specs.Title;
    m_Data.Width = specs.Width;
    m_Data.Height = specs.Height;

    SK_CORE_TRACE("Initializing NativeWindow {0}", specs.Title);

    if(s_GLFWWindowCount == 0)
    {
        int result = glfwInit();
        SK_ASSERT_MSG(result, "Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height,
                                m_Data.Title.c_str(), NULL, NULL);
    s_GLFWWindowCount++;
    m_Context = GraphicsContext::Create(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
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
