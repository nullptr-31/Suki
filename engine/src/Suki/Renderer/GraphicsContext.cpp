#include "Suki/Renderer/GraphicsContext.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Suki
{

std::unique_ptr<GraphicsContext> GraphicsContext::Create(void *window)
{
    return std::make_unique<OpenGLContext>(static_cast<GLFWwindow *>(window));
}

}  // namespace Suki
