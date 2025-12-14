#include <glm/glm.hpp>

#ifndef  MAX_BONE_INFLUENCE
#define MAX_BONE_INFLUENCE 4
#endif 


namespace Engine {
	struct Vertex
	{
		glm::vec3 m_Position;
		glm::vec3 m_Normal;
		glm::vec2 m_TexCoords;
		glm::vec3 m_Tangent;
		glm::vec3 m_Bitangent;

		GLint m_BoneIDs[MAX_BONE_INFLUENCE];
		GLfloat m_Weights[MAX_BONE_INFLUENCE];
	};
}

