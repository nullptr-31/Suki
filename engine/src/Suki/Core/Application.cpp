#include "Suki/Core/Application.h"
#include "Suki/Core/Logger.h"

namespace Suki
{
Application* Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecs& specs) : m_Specs(specs)
{
    s_Instance = this;
    SK_CORE_INFO("Application Created");
}

Application::~Application()
{
    SK_CORE_INFO("Application Destroyed");
}

void Application::Run()
{
    SK_CORE_INFO("Application Running...");

    while(m_Running)
    {}
}

void Application::Close()
{
    SK_CORE_INFO("Application Closed");
}

}  // namespace Suki
