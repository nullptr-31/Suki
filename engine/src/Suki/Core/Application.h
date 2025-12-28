#pragma once

#include <memory>

#include <Suki/Core/Window.h>

namespace Suki
{

struct ApplicationSpecs
{
    std::string Name = "Suki Application";
    std::string Author = "Abdelbaki Boukerche";
};

class Application
{
public:
    Application(const ApplicationSpecs& specs);
    ~Application();

    static Application& Get() { return *s_Instance; }
    const ApplicationSpecs GetSpecs() const { return m_Specs; }

    Window& GetWindow() { return *m_Window; }

    void Run();
    void Close();

private:
    ApplicationSpecs m_Specs;
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;

private:
    static Application* s_Instance;
};

}  // namespace Suki
