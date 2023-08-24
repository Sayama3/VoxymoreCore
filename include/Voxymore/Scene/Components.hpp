//
// Created by ianpo on 24/08/2023.
//

#pragma once

#include "Voxymore/Core/Math.hpp"
#include "Voxymore/Core/SmartPointers.hpp"
#include "Voxymore/Scene/SceneCamera.hpp"
#include "Voxymore/Renderer/Material.hpp"
#include "Voxymore/Renderer/VertexArray.hpp"

namespace Voxymore::Core
{
	struct TransformComponent
	{
		glm::vec3 Position = glm::vec3(0.0f);
		glm::quat Rotation = glm::identity<glm::quat>();
		glm::vec3 Scale = glm::vec3(1.0f);

		inline TransformComponent() = default;
		inline TransformComponent(const TransformComponent&) = default;
		inline TransformComponent(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale) : Position(position), Rotation(rotation), Scale(scale) {}

		inline glm::mat4 GetTransform() const
		{
			// Not using Math::TRS because I don't have to pass reference this way so it should therefore be faster... I think... Need to be verified.
			VXM_PROFILE_FUNCTION();
			glm::mat4 trs(1.0f);
			trs = glm::translate(trs, Position); // Translation Matrix
			trs = trs * glm::toMat4(Rotation); // Rotation Matrix
			trs = glm::scale(trs, Scale); // Scale Matrix
			return trs; // Translation * Rotation * Scale => TRS Matrix.
		}
	};

	struct MeshComponent
	{
		Ref<Voxymore::Core::Material> Material;
		Ref<VertexArray> Mesh;

		inline MeshComponent() = default;
		inline MeshComponent(const MeshComponent&) = default;
		inline MeshComponent(const Ref<Voxymore::Core::Material>& material,const Ref<VertexArray>& vertexArray) : Material(material), Mesh(vertexArray) {}
	};

	struct TagComponent
	{
		std::string Tag;

		inline TagComponent() = default;
		inline TagComponent(const TagComponent&) = default;
		inline TagComponent(const std::string& tag) : Tag(tag) {}
	};

	struct CameraComponent
	{
		Voxymore::Core::SceneCamera Camera;
		// TODO: Moving primary camera logic on Scene.
		bool Primary = true;
		bool FixedAspectRation = false;

		inline CameraComponent() = default;
		inline CameraComponent(const CameraComponent&) = default;

		/**
		 * Orthographic Camera Constructor.
		 * @param width
		 * @param height
		 * @param size
		 * @param nearClip
		 * @param farClip
		 */
		inline CameraComponent(uint32_t width, uint32_t height, float size, float nearClip, float farClip) : Camera(width, height, size, nearClip, farClip) {}
		/**
		 * Perspective Camera Constructor.
		 * @param fov
		 * @param nearClip
		 * @param farClip
		 * @param width
		 * @param height
		 */
		inline CameraComponent(float fov, float nearClip, float farClip, uint32_t width, uint32_t height) : Camera(fov, nearClip, farClip, width, height) {}
		inline CameraComponent(const Voxymore::Core::SceneCamera& camera) : Camera(camera) {}

	};
}