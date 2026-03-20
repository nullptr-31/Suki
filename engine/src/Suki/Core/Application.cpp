#include "Suki/Core/Application.h"
#include "Suki/Core/Logger.h"

namespace Suki
{
Application* Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecs& specs) : m_Specs(specs)
{
    s_Instance = this;
    SK_CORE_TRACE("Application Created");

    m_Window = Window::Create(WindowSpecs(specs.Name));
    SK_CORE_TRACE("Application Window {0} Created", specs.Name);
}

Application::~Application()
{
    SK_CORE_TRACE("Application Destroyed");
}

void Application::Run()
{
    SK_CORE_TRACE("Application Running...");

    while(m_Running)
    {
        m_Window->OnUpdate();
    }
}

void Application::Close()
{
    SK_CORE_TRACE("Application Closed");
    m_Running = false;
}

}  // namespace Suki
