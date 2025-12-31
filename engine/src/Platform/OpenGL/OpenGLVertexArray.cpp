#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>
#include <cstdint>
#include "Suki/Core/Assert.h"
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
        default:
            return 0;
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
{
    SK_ASSERT_MSG(buffer->GetLayout().GetElemenets().size(),
                  "Vertex Buffer must have a valid layout");

    glBindVertexArray(m_RendererID);
    buffer->Bind();

    const BufferLayout& layout = buffer->GetLayout();
    for(const BufferElement& element : layout)
    {

        switch(element.Type)
        {
            case EShaderDataType::Float:
            case EShaderDataType::Float2:
            case EShaderDataType::Float3:
            case EShaderDataType::Float4: {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribPointer(
                    m_VertexBufferIndex, element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                    (const void*)element.Offset);
                m_VertexBufferIndex++;
                break;
            }
            case EShaderDataType::Int:
            case EShaderDataType::Int2:
            case EShaderDataType::Int3:
            case EShaderDataType::Int4:
            case EShaderDataType::Bool: {
                glEnableVertexAttribArray(m_VertexBufferIndex);
                glVertexAttribIPointer(
                    m_VertexBufferIndex, element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    layout.GetStride(), (const void*)element.Offset);
                m_VertexBufferIndex++;
                break;
            }
            case EShaderDataType::Mat3:
            case EShaderDataType::Mat4: {
                uint8_t count = element.GetComponentCount();

                for(uint8_t i = 0; i < count; i++)
                {
                    glEnableVertexAttribArray(m_VertexBufferIndex);
                    glVertexAttribPointer(
                        m_VertexBufferIndex, count,
                        ShaderDataTypeToOpenGLBaseType(element.Type),
                        element.Normalized ? GL_TRUE : GL_FALSE,
                        layout.GetStride(),
                        (const void*)(element.Offset +
                                      sizeof(float) * count * i));
                    glVertexAttribDivisor(m_VertexBufferIndex, 1);
                    m_VertexBufferIndex++;
                }
                break;
            }
            default:
                break;
        }
    }

    m_VertexBuffers.push_back(buffer);
}

void OpenGLVertexArray::SetIndexBuffer(
    const std::shared_ptr<IndexBuffer>& buffer)
{
    glBindVertexArray(m_RendererID);
    buffer->Bind();

    m_IndexBuffer = buffer;
}

}  // namespace Suki
