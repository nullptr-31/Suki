#include "Suki/Renderer/RenderCommand.h"

namespace Suki
{

std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI =
    RendererAPI::Create();
}
