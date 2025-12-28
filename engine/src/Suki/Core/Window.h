#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace Suki
{

struct WindowSpecs
{
    WindowSpecs(const std::string& title = "Suki Engine", int width = 640,
                int height = 360)
        : Title(title), Width(width), Height(height)
    {}

    std::string Title;
    uint32_t Width;
    uint32_t Height;
};

class Window
{
public:
    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void* GetNativeWindow() const = 0;

    static std::unique_ptr<Window> Create(
        const WindowSpecs& specs = WindowSpecs());

private:
};

}  // namespace Suki
