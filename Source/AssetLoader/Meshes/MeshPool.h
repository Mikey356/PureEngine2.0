#pragma once

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

#include "../TextureP/TexturePool.h"
#include "Vertex.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#ifndef  MAX_BONE_INFLUENCE
#define MAX_BONE_INFLUENCE 4

#endif 
#ifndef BUFFERS
#define BUFFERS
unsigned int VBO, VAO, EBO;
#endif


namespace Engine
{
	namespace MeshPool
	{

		struct Mesh
		{
			std::vector<Vertex> m_vertices;
			static std::vector<unsigned int> m_indices;
		
			inline static unsigned int m_VBO;
			inline static unsigned int m_EBO;
			inline static unsigned int m_VAO;
			Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);


			void GenMesh();
		};
	
	};
}