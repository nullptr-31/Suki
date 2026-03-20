#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace Suki
{

struct WindowSpecs
{
    WindowSpecs(const std::string& title = "Suki", uint32_t width = 640,
                uint32_t height = 360)
        : Title(title), Width(width), Height(height)
    {}

    std::string Title;
    uint32_t Width, Height;
};

class Window
{
public:
    virtual ~Window() = default;

    static std::unique_ptr<Window> Create(
        const WindowSpecs& specs = WindowSpecs());

    virtual void OnUpdate() = 0;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void* GetNativeWindow() const = 0;
};

}  // namespace Suki
