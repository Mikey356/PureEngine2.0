#pragma once
#include "Engine/Engine.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace Engine
{
	namespace TexturePool
	{
		enum g_TexType
		{
			AO,
			BaseColor,
			Albedo,
			Diffuse,
			Height,
			Metallic,
			Normal,
			Roughness,
			Emissive,
			Specular
		};
		

		struct Texture 
		{
			unsigned int m_id;
			g_TexType m_type;
			std::string m_path;
			static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);
			Texture() = default;
			Texture(std::vector<Texture>& textures);
		};
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, g_TexType typeName);
			
	}
}