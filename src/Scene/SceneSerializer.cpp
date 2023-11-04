//
// Created by ianpo on 29/08/2023.
//

#include "Voxymore/Scene/SceneSerializer.hpp"
#include "Voxymore/Scene/Entity.hpp"
#include "Voxymore/Scene/Components.hpp"
#include "Voxymore/Core/Core.hpp"
#include "Voxymore/Core/YamlHelper.hpp"
#include "Voxymore/Scene/CustomComponent.hpp"

namespace Voxymore::Core
{

	SceneSerializer::SceneSerializer(const Ref<Scene> &scene) : m_Scene(scene)
	{
	}
	SceneSerializer::~SceneSerializer()
	{
	}

	bool SceneSerializer::Serialize(const std::string &filePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << KEYVAL("Scene", "Scene Name"); // TODO: add a name to the scenes.
		out << KEYVAL("Entities", YAML::BeginSeq);


		for (entt::entity id : m_Scene->m_Registry.storage<entt::entity>())
		{
			Entity entity(id, m_Scene.get());
			if(!entity) continue;
			SerializeEntity(out, entity);
		}
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fileOut(filePath);
		fileOut << out.c_str();

		return true;
	}

	bool SceneSerializer::Deserialize(const std::string &filePath)
	{
		std::ifstream ifstream(filePath);
		std::stringstream  stringstream;
		stringstream << ifstream.rdbuf();

		YAML::Node data = YAML::Load(stringstream.str());
		if(!data["Scene"])
		{
			return false;
		}

		std::string sceneName = data["Scene"].as<std::string>();
		auto entities = data["Entities"];
		if(entities)
		{
			for (YAML::Node yamlEntity : entities)
			{
				auto id = yamlEntity["Entity"];
				uint64_t uuid = id.as<uint64_t>();

				std::string name;
				auto tagComponent = yamlEntity["TagComponent"];
				if(tagComponent)
				{
					name = tagComponent["Tag"].as<std::string>();
				}
				VXM_CORE_TRACE("Deserialize Entity with name: {0} and id: {1}", name, uuid);

				Entity entity = m_Scene->CreateEntity(name);


				auto transformComponent = yamlEntity["TransformComponent"];
				if(transformComponent)
				{
					auto& tc = entity.GetComponent<TransformComponent>();
					tc.SetPosition(transformComponent["Position"].as<glm::vec3>());
					tc.SetScale(transformComponent["Scale"].as<glm::vec3>());
					auto rotation = transformComponent["Rotation"].as<glm::quat>() ;
					auto eulerRotation = transformComponent["EulerRotation"].as<glm::vec3>() ;
					if(rotation != glm::quat(eulerRotation))
					{
						tc.SetRotation(rotation);
					}
					else
					{
						tc.SetEulerRotation(eulerRotation);
					}

				}

				auto cameraComponent = yamlEntity["CameraComponent"];
				if(cameraComponent)
				{
					auto& cc = entity.AddComponent<CameraComponent>();

					cc.Primary = cameraComponent["Primary"].as<bool>();
					cc.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();

					auto camera = cameraComponent["Camera"];
					auto aspectRatio = camera["AspectRatio"].as<float>();
					cc.Camera.SetAspectRatio(aspectRatio);

					auto orthographicSize = camera["OrthographicSize"].as<float>();
					auto orthographicNear = camera["OrthographicNear"].as<float>();
					auto orthographicFar = camera["OrthographicFar"].as<float>();
					cc.Camera.SetOrthographic(orthographicSize, orthographicNear, orthographicFar);

					auto perspectiveVerticalFOV = camera["PerspectiveVerticalFOV"].as<float>();
					auto perspectiveNear = camera["PerspectiveNear"].as<float>();
					auto perspectiveFar = camera["PerspectiveFar"].as<float>();
					cc.Camera.SetPerspective(perspectiveVerticalFOV, perspectiveNear, perspectiveFar);

					cc.Camera.SwitchToOrthographic(camera["IsOrthographic"].as<bool>());
				}

				for (const ComponentChecker& cc : ComponentManager::GetComponents())
				{
					YAML::Node yamlcc = yamlEntity[cc.ComponentName];
					if(yamlcc)
					{
						cc.AddComponent(entity);
						cc.DeserializeComponent(yamlcc, entity);
					}
				}
			}
		}
		return true;
	}

	bool SceneSerializer::SerializeRuntime(const std::string &filePath)
	{
		return false;
	}
	bool SceneSerializer::DeserializeRuntime(const std::string &filePath)
	{
		VXM_CORE_ASSERT(false, "Function DeserializeRuntime not implemented yet.");
		return false;
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter &out, Entity entity)
	{
		out << YAML::BeginMap; // Entity

		out << KEYVAL("Entity", "123456789"); //TODO: set entity ID;

		if(entity.HasComponent<TagComponent>())
		{
			out << KEY("TagComponent");
			out << YAML::BeginMap; // TagComponent

			auto& component = entity.GetComponent<TagComponent>();
			out << KEYVAL("Tag", component.Tag);

			out << YAML::EndMap; // TagComponent
		}

		if(entity.HasComponent<TransformComponent>())
		{
			out << KEY("TransformComponent");
			out << YAML::BeginMap; // TransformComponent

			auto& component = entity.GetComponent<TransformComponent>();
			out << KEYVAL("Position", component.GetPosition());
			out << KEYVAL("Rotation", component.GetRotation());
			out << KEYVAL("EulerRotation", component.GetEulerRotation());
			out << KEYVAL("Scale", component.GetScale());

			out << YAML::EndMap; // TransformComponent
		}

		if(entity.HasComponent<CameraComponent>())
		{
			out << KEY("CameraComponent");
			out << YAML::BeginMap; // CameraComponent

			auto& component = entity.GetComponent<CameraComponent>();
			out << KEYVAL("Primary", component.Primary);
			out << KEYVAL("FixedAspectRatio", component.FixedAspectRatio);

			out << KEY("Camera");
			out << YAML::BeginMap; // Camera
			out << KEYVAL("IsOrthographic", component.Camera.IsOrthographic());
			out << KEYVAL("AspectRatio", component.Camera.GetAspectRatio());

			out << KEYVAL("OrthographicSize", component.Camera.GetOrthographicSize());
			out << KEYVAL("OrthographicNear", component.Camera.GetOrthographicNear());
			out << KEYVAL("OrthographicFar", component.Camera.GetOrthographicFar());

			out << KEYVAL("PerspectiveVerticalFOV", component.Camera.GetPerspectiveVerticalFOV());
			out << KEYVAL("PerspectiveNear", component.Camera.GetPerspectiveNear());
			out << KEYVAL("PerspectiveFar", component.Camera.GetPerspectiveFar());
			out << YAML::EndMap; // Camera

			out << YAML::EndMap; // CameraComponent
		}

		//TODO: serialize the NativeScriptComponent.
		//TODO: serialize the MeshComponent.

		for (const ComponentChecker& cc : ComponentManager::GetComponents())
		{
			if(cc.HasComponent(entity))
			{
				out << KEYVAL(cc.ComponentName, YAML::BeginMap);
				cc.SerializeComponent(out, entity);
				out << YAML::EndMap;
			}
		}

		out << YAML::EndMap; // Entity
	}
} // namespace Voxymore::Core
