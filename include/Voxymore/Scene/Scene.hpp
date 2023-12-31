//
// Created by ianpo on 24/08/2023.
//

#pragma once

#include "Voxymore/Core/UUID.hpp"
#include "Voxymore/Core/SmartPointers.hpp"
#include "Voxymore/Core/TimeStep.hpp"
#include "Voxymore/Renderer/EditorCamera.hpp"
#include "Voxymore/Core/Core.hpp"
#include <entt/entt.hpp>
#include <unordered_set>

// TODO: find a better way?
namespace Voxymore::Editor {
	class SceneHierarchyPanel;
}

namespace Voxymore::Core
{
	class SceneSerializer;
	class Entity;
	class GameplaySystem;

	class Scene
	{
	private:
		friend class Voxymore::Editor::SceneHierarchyPanel;
		friend class Entity;
		friend class SceneSerializer;
		friend class GameplaySystem;
	public:
		Scene();
		Scene(std::string name);
		Scene(UUID id);
		Scene(UUID id, std::string name);
		Scene(Ref<Scene> scene);
		~Scene();

		Entity CreateEntity();
		Entity CreateEntity(const std::string& name);
		Entity CreateEntity(UUID id, const std::string& name);
		Entity CreateEntity(UUID id);

		Entity GetEntity(UUID id);

		void DestroyEntity(Entity entity);

		void StartScene();
		void StopScene();
		inline bool IsStarted() const {return m_Started;}

		void OnUpdateEditor(TimeStep ts, EditorCamera& camera);
		void OnUpdateRuntime(TimeStep ts);
		void SetViewportSize(uint32_t width, uint32_t height);

		inline const std::string& GetName() const {return m_Name;}
		inline void SetName(const std::string& name) {m_Name = name;}
		inline UUID GetID() const {return m_ID;}
	private:
		template<typename T>
		inline void OnComponentAdded(entt::entity entity, T& component) {}
		template<typename T>
		inline void OnEmptyComponentAdded(entt::entity entity) {}
		void InitScene();
		void OnCreateIDComponent(entt::entity);
		void OnDestroyIDComponent(entt::entity);
	public:
		// Helper:
		Entity GetPrimaryCameraEntity();
	private:
		UUID m_ID;
		std::string m_Name;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		entt::registry m_Registry;
		std::unordered_set<std::string> m_StartedSystem;
		std::unordered_map<UUID, Entity> m_Entities;
		bool m_Started = false;
	public:
		inline entt::registry& GetRegistry() { return m_Registry; }
		inline const entt::registry& GetRegistry() const { return m_Registry; }
	};

} // Voxymore
// Core
