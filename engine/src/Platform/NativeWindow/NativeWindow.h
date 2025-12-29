#include <functional>
#include "GLFW/glfw3.h"
#include "Suki/Core/Window.h"
#include "Suki/Renderer/GraphicsContext.h"

namespace Suki
{

class NativeWindow : public Window
{
public:
    NativeWindow(const WindowSpecs& specs);
    virtual ~NativeWindow();

    void OnUpdate() override;

    uint32_t GetWidth() const override { return m_Data.Width; }
    uint32_t GetHeight() const override { return m_Data.Height; }

    void SetEventCallback(const std::function<void(Event&)>& callback) override
    {
        m_Data.EventCallback = callback;
    }

    void* GetNativeWindow() const override { return m_Window; }

private:
    virtual void Init(const WindowSpecs& specs);
    virtual void Shutdown();

private:
    GLFWwindow* m_Window;
    std::unique_ptr<GraphicsContext> m_Context;

    struct WindowData
    {
        std::string Title;
        uint32_t Width, Height;

        std::function<void(Event&)> EventCallback;
    };

    WindowData m_Data;
};

}  // namespace Suki
