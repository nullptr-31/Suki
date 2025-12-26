#include <iostream>

#include "suki/engine.h"

int main()
{
    SukiEngine::Engine engine;
    std::cout << "Version: " << engine.version() << std::endl;

    return 0;
}
