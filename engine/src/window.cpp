#include "suki/window.h"

namespace SukiEngine
{

Window::Window() {}
Window::Window(std::string& title, int height, int width)
    : m_WindowTitle(title), m_WindowHeight(height), m_WindowWidth(width)
{}
Window::~Window() {}

}  // namespace SukiEngine
