#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <stb_image.h>
#include "Input/Input.h"
#include "Types/PureEnums.h"
#include "Types/PureDefines.h"
#include "WindowingSystem/WindowHandler.h"
#include "Shader/Shader.h"
#include <glad/glad.h>


namespace Engine
{
	void RunPure(WindowHandler::WindowInfo& windowInfo);
	
	const unsigned int velocity = 8.0f;
	void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	
	/*static float g_lastXPos = (float)g_wI.m_ScrWidth / 2.0;
	static float g_lastYPos = (float)g_wI.m_ScrHeight / 2.0;
	static bool g_initMousePos = true;*/
	static WindowHandler::WindowInfo g_wI;
	static float g_windowCenterX = static_cast<float>(g_wI.m_ScrWidth) / 2;
	static float g_windowCenterY = static_cast<float>(g_wI.m_ScrHeight) / 2;

	static float g_deltaTime = 0.0f;
	static float g_lastFrame = 0.0f;
	


	namespace Graphics {
		const float m_YAW = -90.0f;
		const float m_PITCH = 0.0f;
		const float	m_SPEED = 5.0f;
		const float m_SENSETIVITY = 0.2f;
		const float m_ZOOM = 90.0f;
		struct Camera
		{

			glm::vec3 Position;
			glm::vec3 Front;
			glm::vec3 Up;
			glm::vec3 Right;
			glm::vec3 WorldUp;
			// euler angles
			float Yaw;
			float Pitch;

			float CameraSpeed;
			float MouseSensitivity;
			float Zoom;
			Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = m_YAW, float pitch = m_PITCH);
			Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);

			glm::mat4 GetViewMatrix();
			void UpdateCameraVectors();
			void UpdateCameraOrbit(GLFWwindow* glfwwindow);
			void ProcessCameraZoom(float yoffset);
	
			/*void UpdateCameraRotation(float x_offset, float y_offset, GLboolean constraintPitch);*/
			/*void UpdateCameraZooming(float y_Offset);*/
		}; 
		
		unsigned int LoadTexture(const char* path);
		void SetCubePositions(std::vector<glm::vec3>& cube_positions);
		void RenderCubes(const WindowHandler::WindowInfo& windowInfo, Camera* camera);
		void RenderModels(Camera* camera);
		void InitOpenGLAPI(GLFWwindow* window);
		void ProcessCam(Movement direction, Camera* cam, float changeInTime);
		
		void UpdateScreen();
		void InitAssets();
		
		void CleanUp(Camera* cam);
	}

	void GetInput(GLFWwindow* window);
}