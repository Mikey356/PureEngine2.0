#include "LoadAsset.h"

namespace Engine
{
	namespace LoadAsset
	{
		Asset::Asset(const std::string& path, bool gamma) : m_gammaCorrection(gamma)
		{
			LoadModel(path);
		}
		Asset::~Asset()
		{
			if (!m_material)
			{
				delete m_material;
			}
		}
		void LoadModel(const std::string& path)
		{
			Assimp::Importer import;
			const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "ERROR::ASSIMP::IMPORT" << import.GetErrorString() << std::endl;
				return;
			}
			Asset::m_directory = path.substr(0, path.find_last_of('/'));

			Asset::m_material->ProcessNode(scene->mRootNode, scene);
		}

		void Draw(Shader& shader)
		{
			for (auto& mesh : Asset::m_material->m_meshes)
				Asset::m_material->m_meshes;
		}
	}
}