#pragma once

#include <iostream>

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

    void Close();

private:
    bool m_Running = true;
    ApplicationSpecs m_Specs;
    static Application* s_Instance;
};

}  // namespace Suki
