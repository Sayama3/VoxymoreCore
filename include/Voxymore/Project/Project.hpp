//
// Created by Sayama on 26/10/2023.
//

#pragma once

#include "Voxymore/Core/FileSystem.hpp"
#include "Voxymore/Core/SmartPointers.hpp"
#include <string>
#include <filesystem>

namespace Voxymore::Core
{
	struct ProjectConfig {
		std::string name = "Untitled";

		std::filesystem::path assetDirectory = "Assets";
		std::filesystem::path cacheDirectory = "Cache";
		std::filesystem::path systemDirectory = "Systems";

		Path startScene;

		//TODO: Add script path once i've got scripting (i.e. C#/Lua/...).
	};

	class Project
	{
		friend class ProjectSerializer;
	public:
		Project();
		Project(ProjectConfig parameters);
		~Project();

		inline static std::filesystem::path GetAssetDirectory()
		{
			VXM_CORE_ASSERT(s_ActiveProject, "The Active Directory is not loaded yet.");
			return s_ActiveProject->GetAsset();
		}
		inline static std::filesystem::path GetCacheDirectory()
		{
			VXM_CORE_ASSERT(s_ActiveProject, "The Active Directory is not loaded yet.");
			return s_ActiveProject->GetCache();
		}
		inline static std::filesystem::path GetSystemsDirectory()
		{
			VXM_CORE_ASSERT(s_ActiveProject, "The Active Directory is not loaded yet.");
			return s_ActiveProject->GetSystems();
		}
		inline static const std::filesystem::path& GetProjectFilePath()
		{
			VXM_CORE_ASSERT(s_ActiveProject, "The Active Directory is not loaded yet.");
			return s_ActiveProject->GetFilePath();
		}

		inline static const ProjectConfig& GetConfig()
		{
			VXM_CORE_ASSERT(s_ActiveProject, "The Active Directory is not loaded yet.");
			return s_ActiveProject->m_Config;
		}

		static Ref<Project> New();
		static Ref<Project> Load(const std::filesystem::path&);
		static bool SaveActive(const std::filesystem::path& path = "");

	private:
		std::filesystem::path GetAsset() const;
		std::filesystem::path GetCache() const;
		std::filesystem::path GetSystems() const;
		const std::filesystem::path& GetFilePath() const;


	private:
		std::filesystem::path m_ProjectPath = "./Project.vxm";
		ProjectConfig m_Config;

		static Ref<Project> s_ActiveProject;
	};

} // namespace Voxymore::Core
