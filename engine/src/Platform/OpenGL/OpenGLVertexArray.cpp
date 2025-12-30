#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>
#include "Suki/Renderer/Buffer.h"

namespace Suki
{

static GLenum ShaderDataTypeToOpenGLBaseType(EShaderDataType type)
{
    switch(type)
    {
        case EShaderDataType::Float:
            return GL_FLOAT;
        case EShaderDataType::Float2:
            return GL_FLOAT;
        case EShaderDataType::Float3:
            return GL_FLOAT;
        case EShaderDataType::Float4:
            return GL_FLOAT;
        case EShaderDataType::Mat3:
            return GL_FLOAT;
        case EShaderDataType::Mat4:
            return GL_FLOAT;
        case EShaderDataType::Int:
            return GL_INT;
        case EShaderDataType::Int2:
            return GL_INT;
        case EShaderDataType::Int3:
            return GL_INT;
        case EShaderDataType::Int4:
            return GL_INT;
        case EShaderDataType::Bool:
            return GL_BOOL;
    }
    return 0;
}

OpenGLVertexArray::OpenGLVertexArray()
{
    glCreateVertexArrays(1, &m_RendererID);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(
    const std::shared_ptr<VertexBuffer>& buffer)
{}

void OpenGLVertexArray::SetIndexBuffer(
    const std::shared_ptr<IndexBuffer>& buffer)
{
    glBindVertexArray(m_RendererID);
    buffer->Bind();

    m_IndexBuffer = buffer;
}

}  // namespace Suki
