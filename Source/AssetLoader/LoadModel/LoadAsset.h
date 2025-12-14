#pragma once
#include "../Materials/Material.h"

namespace Engine
{
	namespace LoadAsset
	{
		struct Asset
		{
			static std::string m_directory;
			static MaterialPool::Material* m_material;
			bool m_gammaCorrection;
			Asset() = default;
			Asset(const std::string& path, bool gamma = false);
			~Asset();
		};
		void LoadModel(const std::string& path);
		void Draw(Shader& shader);
	}
}