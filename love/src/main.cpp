#include "Suki.h"
#include "Suki/Core/Logger.h"
#include "Suki/Core/Window.h"

int main()
{
    Suki::Logger::Init();

    Suki::ApplicationSpecs specs;
    Suki::Application* app = new Suki::Application(specs);

    app->Run();

    delete app;

    return 0;
}
