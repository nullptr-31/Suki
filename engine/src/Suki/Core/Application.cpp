#include <Suki/Core/Application.h>
#include "Suki/Core/Logger.h"
#include "Suki/Core/Window.h"

namespace Suki
{

Application* Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecs& specs) : m_Specs(specs)
{
    s_Instance = this;
    SK_CORE_INFO("Application Created");

    m_Window = Window::Create(WindowSpecs(specs.Name));
    SK_CORE_INFO("Application Window Created");
}
Application::~Application()
{
    SK_CORE_INFO("Application Destroyed");
}

void Application::Close()
{
    SK_CORE_INFO("Application Closed");
    m_Running = false;
}

void Application::Run()
{
    SK_CORE_INFO("Application Running...");
    while(m_Running)
    {
        m_Window->OnUpdate();
    }
}

}  // namespace Suki
