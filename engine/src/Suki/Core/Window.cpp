#include "Suki/Core/Window.h"
#include "Platform/NativeWindow/NativeWindow.h"

namespace Suki
{

std::unique_ptr<Window> Window::Create(const WindowSpecs& specs)
{
    return std::make_unique<NativeWindow>(specs);
}

}  // namespace Suki
