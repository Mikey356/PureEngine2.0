#include "AssetLoader/LoadModel/LoadAsset.h"

// Always select the dedicated GPU
extern "C"
{
	_declspec(dllexport) unsigned long NvOptimusEnablement = 1;
	_declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
namespace Engine
{


	void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	
	LoadAsset::Asset* g_house = nullptr;
	Shader* g_houseShader = nullptr;
	Shader* g_cubeShader = nullptr;
	GLuint g_VBO, g_VAO;
	
	namespace Graphics
	{

		Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), CameraSpeed(m_SPEED), MouseSensitivity(m_SENSETIVITY), Zoom(m_ZOOM)
		{
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;
			UpdateCameraVectors();
		}

		Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
		{
			Position = glm::vec3(pos_x, pos_y, pos_z);
			WorldUp = glm::vec3(up_x, up_y, up_z);
			Yaw = yaw;
			Pitch = pitch;
			UpdateCameraVectors();
		}

		glm::mat4 Camera::GetViewMatrix()
		{
			return glm::lookAt(Position, Position + Front, Up);
		}

		void Camera::UpdateCameraVectors()
		{
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			Front = glm::normalize(front);
			Right = glm::normalize(glm::cross(Front, WorldUp));
			Up = glm::normalize(glm::cross(Right, Front));
		}

		void Camera::UpdateCameraOrbit(GLFWwindow* glfwwindow)
		{
			Input::UpdateCameraRotation(glfwwindow, Yaw, Pitch, true, MouseSensitivity);
			UpdateCameraVectors();
		}
		void Camera::ProcessCameraZoom(float yoffset)
		{
			Zoom -= (float)yoffset;
			if (Zoom < 1.0f)
				Zoom = 1.0f;
			if (Zoom > 90.0f)
				Zoom = 90.0f;

		}
		void InitOpenGLAPI(GLFWwindow* window) {
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
			}
			glEnable(GL_DEPTH_TEST);
			glGenVertexArrays(1, &g_VAO);
			glGenBuffers(1, &g_VBO);
			glBindVertexArray(g_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
			glfwSetScrollCallback(window, Engine::MouseScrollCallback);
			Input::SetMouseLastFrame(g_windowCenterX, g_windowCenterY);
		}
		void InitAssets()
		{
			LoadAsset::Asset* g_house = new LoadAsset::Asset("Assets/House/House/House.obj");
			g_houseShader = new Shader();
			g_houseShader->Load("GL_Test.vert", "GL_Test.frag");
			g_cubeShader = new Shader();
			g_cubeShader->Load("GL_Cube.vert", "GL_Cube.frag");
		}
		void SetCubePositions(std::vector<glm::vec3>& cube_positions)
		{
			std::vector<glm::vec3> cubePositions;
			cubePositions.emplace_back(0.0f, 0.0f, 0.0f);
			cubePositions.emplace_back(2.0f, 5.0f, -15.0f);
			cubePositions.emplace_back(-1.5f, -2.2f, -2.5f);
			cubePositions.emplace_back(-3.8f, -2.0f, -12.3f);
			cubePositions.emplace_back(2.4f, -0.4f, -3.5f);
			cubePositions.emplace_back(-1.7f, 3.0f, -7.5f);
			cubePositions.emplace_back(1.3f, -2.0f, -2.5f);
			cubePositions.emplace_back(1.5f, 2.0f, -2.5f);
			cubePositions.emplace_back(1.5f, 0.2f, -1.5f);
			cubePositions.emplace_back(-1.3f, 1.0f, -1.5f);
			cube_positions = cubePositions;
		}

		unsigned int LoadTexture(const char* path)
		{
			unsigned int textureID;
			glGenTextures(1, &textureID);

			int width, height, numComponents;
			unsigned char* data = stbi_load(path, &width, &height, &numComponents, 0);
			if (data)
			{
				GLenum format;
				if (numComponents == 1)
					format = GL_RED;
				else if (numComponents == 3)
					format = GL_RGB;
				else if (numComponents == 4)
					format = GL_RGBA;

				glBindTexture(GL_TEXTURE_2D, textureID);
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_image_free(data);
			}
			else
			{
				std::cout << "Texture failed to load at path: " << path << std::endl;
				stbi_image_free(data);
			}
			return textureID;
		}
		void RenderCubes(const WindowHandler::WindowInfo& windowInfo, Camera* camera)
		{

			float vertices[] =
			{
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
			};
			std::vector<glm::vec3> cubePositionz;
			SetCubePositions(cubePositionz);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			
			g_cubeShader->Use();
			unsigned int texture1 = LoadTexture("Textures/container.jpg");
			unsigned int texture2 = LoadTexture("Textures/awesomeface.png");
			g_cubeShader->SetInt("texture1", 0);
			g_cubeShader->SetInt("texture2", 1);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);
			g_cubeShader->Use();

			glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)windowInfo.m_ScrWidth / (float)windowInfo.m_ScrHeight, NEAR_PLANE, FAR_PLANE);
			g_cubeShader->SetMat4("projection", projection);

			glm::mat4 view = camera->GetViewMatrix();
			g_cubeShader->SetMat4("view", view);

			glBindVertexArray(g_VAO);
			for (auto& position : cubePositionz)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, position);
				float angle = 20.0f * position.length();
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
				g_cubeShader->SetMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
		void UpdateScreen()
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		void CleanUp(Camera* cam)
		{
			if (!g_VAO)
			{
				glDeleteVertexArrays(1, &g_VAO);
			}
			if (!g_VBO)
			{
				glDeleteBuffers(1, &g_VBO);
			}
			if (!cam)
			{
				delete cam;
			}
			if (!g_houseShader)
			{
				delete g_houseShader;
			}
			if (!g_cubeShader)
			{
				delete g_cubeShader;
			}
			if (!g_house)
			{
				delete g_house;
			}
		}

		void ProcessCam(Movement movement, Camera* cam, float changeInTime)
		{
			float velocity = cam->CameraSpeed * changeInTime;

			if (movement == FORWARD)
			{
				cam->Position += cam->Front * velocity;
			}
			if (movement == BACKWARD)
			{
				cam->Position -= cam->Front * velocity;
			}
			if (movement == RIGHT)
			{
				cam->Position += cam->Right * velocity;
			}
			if (movement == LEFT)
			{
				cam->Position -= cam->Right * velocity;
			}

		}

		void RenderModels(Camera* camera)
		{
			
			g_houseShader->Use();
			glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)g_wI.m_ScrWidth / (float)g_wI.m_ScrHeight, NEAR_PLANE, FAR_PLANE);
			glm::mat4 view = camera->GetViewMatrix();
			g_houseShader->SetMat4("projection", projection);
			g_houseShader->SetMat4("view", view);
			glm::mat4 modelMat = glm::mat4(1.0f);
			modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, 0.0f));
			modelMat = glm::scale(modelMat, glm::vec3(0.04f, 0.04f, 0.04f));
			g_houseShader->SetMat4("model", modelMat);
		
		}

	}

	Graphics::Camera* m_Cam = new Graphics::Camera(glm::vec3(0.0, 0.0, 3.0));
	

	void GetInput(GLFWwindow* window)
	{
		if (Input::IsKeyDown(window, PURE_KEY_W))
		{
			ProcessCam(FORWARD, m_Cam, g_deltaTime);
		}
		if (Input::IsKeyDown(window, PURE_KEY_A))
		{
			ProcessCam(LEFT, m_Cam, g_deltaTime);
		}
		if (Input::IsKeyDown(window, PURE_KEY_S))
		{
			ProcessCam(BACKWARD, m_Cam, g_deltaTime);
		}
		if (Input::IsKeyDown(window, PURE_KEY_D))
		{
			ProcessCam(RIGHT, m_Cam, g_deltaTime);
		}

		if (Input::IsKeyDown(window, PURE_KEY_UP))
		{
			ProcessCam(FORWARD, m_Cam, g_deltaTime);
		}
		if (Input::IsKeyDown(window, PURE_KEY_LEFT))
		{
			ProcessCam(LEFT, m_Cam, g_deltaTime);
		}
		if (Input::IsKeyDown(window, PURE_KEY_DOWN))
		{
			ProcessCam(BACKWARD, m_Cam, g_deltaTime);
		}
		if (Input::IsKeyDown(window, PURE_KEY_RIGHT))
		{
			ProcessCam(RIGHT, m_Cam, g_deltaTime);
		}
		if (Input::IsKeyDown(window, PURE_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwWindowShouldClose(window))
		{
			CleanUp(m_Cam);
		}
	}
	void RunPure(WindowHandler::WindowInfo& windowInfo)
	{

		float thisFrame = static_cast<float>(glfwGetTime());
		g_deltaTime = thisFrame - g_lastFrame;
		g_lastFrame = thisFrame;
		Graphics::UpdateScreen();
		RenderModels(m_Cam);
		GetInput(windowInfo.m_window);
		m_Cam->UpdateCameraOrbit(windowInfo.m_window);
	}

	void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		m_Cam->ProcessCameraZoom(static_cast<float>(yOffset));
		
	}
}