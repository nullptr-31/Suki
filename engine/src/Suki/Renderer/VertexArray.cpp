#include "Suki/Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Suki
{

std::shared_ptr<VertexArray> VertexArray::Create()
{
    return std::make_shared<OpenGLVertexArray>();
}

}  // namespace Suki
