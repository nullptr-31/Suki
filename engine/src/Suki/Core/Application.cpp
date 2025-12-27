#include <Suki/Core/Application.h>

namespace Suki
{

Application* Application::s_Instance = nullptr;

Application::Application(const ApplicationSpecs& specs) : m_Specs(specs)
{
    s_Instance = this;
}
Application::~Application() {}

void Application::Close()
{
    m_Running = false;
}

}  // namespace Suki
