//#pragma once
//#include <glad/glad.h>
//#include "WindowingSystem/WindowHandler.h"
//#include "Types/PureDefines.h"
//#include "Shader/Shader.h"
//#include "Camera/Camera.h"
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/string_cast.hpp>
//#include <stb_image.h>
//#include <vector>
//#include <iostream>
//
//class Renderer
//{
//private:
//	unsigned int m_VBO;
//	unsigned int m_VAO;
//	unsigned int m_texture1;
//	unsigned int m_texture2;
//	Camera m_cam;
//	unsigned int LoadTexture(const char* path);
//    void RenderScreen();
//	void SetCubePositions(std::vector<glm::vec3>& cube_positions);
//	void RenderCubes();
//public:
//	const unsigned int& GetVBO() const;
//	const unsigned int& GetVAO() const;
//    Camera* GetCamera();
//	void SetTextures(unsigned int texture1, unsigned int texture2);
//	void SetVBO(unsigned int vbo);
//	void SetVAO(unsigned int vao);
//    void Update();
//	Renderer();
//	~Renderer();
//};