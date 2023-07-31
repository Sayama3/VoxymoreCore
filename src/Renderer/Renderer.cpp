//
// Created by ianpo on 20/07/2023.
//

#include "Voxymore/Renderer/Renderer.hpp"
#include "Voxymore/Logger.hpp"
#include "Voxymore/OpenGL/OpenGLShader.hpp"

namespace Voxymore::Core {
	const Camera* Renderer::s_Camera = nullptr;

    void Renderer::Init() {
        RenderCommand::Init();
    }

    void Renderer::BeginScene(const Camera& camera) {
		s_Camera = &camera;
    }

    void Renderer::EndScene() {
		s_Camera = nullptr;
    }

    void Renderer::Submit(Ref<Shader>& shader, const Ref<VertexArray> &vertexArray, const glm::mat4& transform) {
		if(s_Camera == nullptr) {
			VXM_CORE_ERROR("No valid camera set, begin the scene with a camera before submitting meshes.");
			return;
		}
		shader->Bind();
        //TODO: Set the view projection matrix once per frame not once per model drawn.
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ViewProjectionMatrix", s_Camera->GetViewProjectionMatrix());
        std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0,0,width,height);
    }
} // Core