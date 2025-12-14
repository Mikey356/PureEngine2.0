#include "TexturePool.h"
#include <iostream>
namespace Engine
{
	namespace TexturePool
	{
		
		std::string g_directory;
		std::vector<Texture> g_texturesLoaded;
		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, g_TexType typeName)
		{
			std::vector<Texture> textures;
			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);
				bool isLoaded = false;
				for (auto& texture : g_texturesLoaded)
				{
					if (strcmp(texture.m_path.data(), str.C_Str()) == 0)
					{
						textures.push_back(texture);
						isLoaded = true;
						break;
					}
				}
				if (!isLoaded)
				{
					Texture texture;
					texture.m_id = Texture::TextureFromFile(str.C_Str(), g_directory, false);
					texture.m_type = typeName;
					texture.m_path = str.C_Str();
					textures.push_back(texture);
				}
			}
			return textures;
		}
		unsigned int Texture::TextureFromFile(const char* path, const std::string& directory, bool gamma = false)
		{
			std::string filename = std::string(path);
			filename = directory + '/' + filename;

			unsigned int textureID;
			glGenTextures(1, &textureID);

			int width, height, numChannels;
			unsigned char* data = stbi_load(filename.c_str(), &width, &height, &numChannels, 0);
			if (data)
			{
				GLenum format;
				if (numChannels == 1)
					format = GL_RED;
				else if (numChannels == 3)
					format = GL_RGB;
				else if (numChannels == 4)
					format = GL_RGBA;

				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_image_free(data);
			}
			else
			{
				std::cout << "Texture failed to load at: " << path << std::endl;
				stbi_image_free(data);
			}
			return textureID;
		}
		
	}
}