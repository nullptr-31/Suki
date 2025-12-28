#include "GLFW/glfw3.h"
#include "Suki/Core/Window.h"

namespace Suki
{

class NativeWindow : public Window
{
public:
    NativeWindow(const WindowSpecs& specs);
    virtual ~NativeWindow();

    void OnUpdate() override;

    uint32_t GetWidth() const override { return m_WindowSpecs.Width; }
    uint32_t GetHeight() const override { return m_WindowSpecs.Height; }

    void* GetNativeWindow() const override { return m_Window; }

private:
    virtual void Init(const WindowSpecs& specs);
    virtual void Shutdown();

private:
    GLFWwindow* m_Window;
    WindowSpecs m_WindowSpecs;
};

}  // namespace Suki
