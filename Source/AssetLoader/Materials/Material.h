#pragma  once

#include <map>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader/Shader.h"
#include "../Meshes/MeshPool.h"
#include <fstream>
#include <sstream>

namespace Engine
{
	namespace MaterialPool
	{
		struct Material
		{
			static std::vector<TexturePool::Texture> m_texturesLoaded;
			static std::vector<MeshPool::Mesh> m_meshes;
			void ProcessNode(aiNode* node, const aiScene* scene);
			MeshPool::Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
			void Draw(Shader& shader);
		};
	}
}