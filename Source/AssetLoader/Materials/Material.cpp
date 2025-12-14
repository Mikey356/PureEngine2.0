
#include "Material.h"

namespace Engine
{
	namespace MaterialPool
	{
		void Material::ProcessNode(aiNode* node, const aiScene* scene)
		{
			for(unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				m_meshes.push_back(ProcessMesh(mesh, scene));
			}
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				ProcessNode(node->mChildren[i], scene);
			}
		}

		MeshPool::Mesh Material::ProcessMesh(aiMesh* mesh, const aiScene* scene)
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<TexturePool::Texture> textures;

			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				glm::vec3 vector;
				
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;

				if (mesh->HasNormals())
				{
					vector.x = mesh->mNormals[i].x;
					vector.y = mesh->mNormals[i].y;
					vector.z = mesh->mNormals[i].z;
				}

				if (mesh->mTextureCoords[0])
				{
					glm::vec2 vec;
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.m_TexCoords = vec;

					vector.x = mesh->mTangents[i].x;
					vector.y = mesh->mTangents[i].y;
					vector.z = mesh->mTangents[i].z;
					vertex.m_Tangent = vector;

					vector.x = mesh->mBitangents[i].x;
					vector.y = mesh->mBitangents[i].y;
					vector.z = mesh->mBitangents[i].z;
					vertex.m_Bitangent = vector;
				}
				else
					vertex.m_TexCoords = glm::vec2(0.0, 0.0);

				vertices.push_back(vertex);
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];

				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<TexturePool::Texture> diffuseMaps = TexturePool::LoadMaterialTextures(material, aiTextureType_DIFFUSE, TexturePool::g_TexType::Diffuse);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<TexturePool::Texture> ambientOcclusionMaps = TexturePool::LoadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION, TexturePool::g_TexType::AO);
			textures.insert(textures.end(), ambientOcclusionMaps.begin(), ambientOcclusionMaps.end());
			std::vector<TexturePool::Texture> baseColorMaps = TexturePool::LoadMaterialTextures(material, aiTextureType_BASE_COLOR, TexturePool::g_TexType::BaseColor);
			textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
			std::vector<TexturePool::Texture> albedoMaps = TexturePool::LoadMaterialTextures(material, aiTextureType_BASE_COLOR, TexturePool::g_TexType::Albedo);
			textures.insert(textures.end(), albedoMaps.begin(), albedoMaps.end());
			std::vector<TexturePool::Texture> specularMaps= TexturePool::LoadMaterialTextures(material, aiTextureType_SPECULAR, TexturePool::g_TexType::Specular);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			std::vector<TexturePool::Texture> emissiveMaps= TexturePool::LoadMaterialTextures(material, aiTextureType_EMISSIVE, TexturePool::g_TexType::Emissive);
			textures.insert(textures.end(), emissiveMaps.begin(), emissiveMaps.end());
			std::vector<TexturePool::Texture> metallicMaps = TexturePool::LoadMaterialTextures(material, aiTextureType_METALNESS, TexturePool::g_TexType::Metallic);
			textures.insert(textures.end(), metallicMaps.begin(), metallicMaps.end());
			std::vector<TexturePool::Texture> roughnessMaps = TexturePool::LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, TexturePool::g_TexType::Roughness);
			textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());
			std::vector<TexturePool::Texture> normalMaps = TexturePool::LoadMaterialTextures(material, aiTextureType_HEIGHT,  TexturePool::g_TexType::Normal);
			textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
			std::vector<TexturePool::Texture> heightMaps = TexturePool::LoadMaterialTextures(material, aiTextureType_AMBIENT, TexturePool::g_TexType::Height);
			textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
			
			return MeshPool::Mesh(vertices, indices);
		}

		void Material::Draw(Shader& shader)
		{
			unsigned int ambientOcclusionNr = 1;
			unsigned int diffuseNr = 1;
			unsigned int baseColorNr = 1;
			unsigned int albedoNr = baseColorNr;
			unsigned int specularNr = 1;
			unsigned int emissiveNr = 1;
			unsigned int metallicNr = 1;
			unsigned int roughnessNr = 1;
			unsigned int normalNr = 1;
			unsigned int heightNr = 1;

			for (unsigned int i = 0; i < m_texturesLoaded.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);

				std::string number;
				auto& type = m_texturesLoaded[i].m_type;
				switch (type)
				{
				case TexturePool::AO:
					number = std::to_string(ambientOcclusionNr++);
					break;
				case TexturePool::Diffuse:
					number = std::to_string(diffuseNr++);
					break;
				case TexturePool::Emissive:
					number = std::to_string(emissiveNr++);
					break;
				case TexturePool::BaseColor:
					number = std::to_string(baseColorNr++);
					break;
				case TexturePool::Albedo:
					number = std::to_string(albedoNr++);
					break;
				case TexturePool::Height:
					number = std::to_string(heightNr++);
					break;
				case TexturePool::Normal:
					number = std::to_string(normalNr++);
					break;
				case TexturePool::Metallic:
					number = std::to_string(metallicNr++);
					break;
				case TexturePool::Roughness:
					number = std::to_string(roughnessNr++);
					break;
				case TexturePool::Specular:
					number = std::to_string(specularNr++);
					break;
				default:
					std::cout << "ERROR::LINE::" << __LINE__ << "Undefined texture" << std::endl;
				}
				glUniform1i(glGetUniformLocation(shader.GetID(), (std::to_string(type) + number).c_str()), i);
				glBindTexture(GL_TEXTURE_2D, m_texturesLoaded[i].m_id);
			}
			glBindVertexArray(MeshPool::Mesh::m_VAO);
			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(MeshPool::Mesh::m_indices.size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			glActiveTexture(GL_TEXTURE0);
		}
	}
}