#include <Suki/Core/Application.h>
#include "Suki/Core/Logger.h"
#include "Suki/Core/Window.h"
#include "Suki/Event/ApplicationEvent.h"

namespace Suki
{

Application* Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecs& specs) : m_Specs(specs)
{
    s_Instance = this;
    SK_CORE_INFO("Application Created");

    m_Window = Window::Create(WindowSpecs(specs.Name));
    m_Window->SetEventCallback([this](Event& e) { this->OnEvent(e); });
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

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>(
        [this](WindowCloseEvent& event) { return this->OnWindowClose(event); });
    dispatcher.Dispatch<WindowResizeEvent>(
        [this](WindowResizeEvent& event)
        { return this->OnWindowResize(event); });
}

void Application::Run()
{
    SK_CORE_INFO("Application Running...");
    while(m_Running)
    {
        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent& event)
{
    m_Running = false;
    return true;
}

bool Application::OnWindowResize(WindowResizeEvent& event)
{
    if(event.GetWidth() == 0 || event.GetHeight() == 0)
    {
        // m_Minimized = true;
        return false;
    }

    // m_Minimized = false;
    // Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
}

}  // namespace Suki
