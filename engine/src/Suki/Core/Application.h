#pragma once

#include <string>

namespace Suki
{

struct ApplicationSpecs
{
    std::string Name = "Suki Application";
    std::string Author = "ABDELBAKI Boukerche";
};

class Application
{
public:
    Application(const ApplicationSpecs& specs);
    ~Application();

    static Application& Get() { return *s_Instance; }
    const ApplicationSpecs GetSpecs() { return m_Specs; }

    void Run();

    void Close();

private:
    ApplicationSpecs m_Specs;
    bool m_Running = true;

private:
    static Application* s_Instance;
};

}  // namespace Suki
