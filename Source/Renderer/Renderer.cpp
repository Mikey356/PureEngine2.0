//#include "Renderer.h"
//
//Renderer::Renderer() : m_cam(glm::vec3(0.0f, 0.0f, 3.0f))
//{
//	glEnable(GL_DEPTH_TEST);
//	glGenVertexArrays(1, &m_VAO);
//	glGenBuffers(1, &m_VBO);
//	glBindVertexArray(m_VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//}
////	unsigned int m_VBO;
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
//
//const unsigned int& Renderer::GetVBO() const
//{
//	return m_VBO;
//}
//
//const unsigned int& Renderer::GetVAO() const
//{
//	return m_VAO;
//}
//
//void Renderer::SetVBO(unsigned int vbo)
//{
//	m_VBO = vbo;
//}
//
//
//void Renderer::SetVAO(unsigned int vao)
//{
//	m_VAO = vao;
//}
//
//void Renderer::SetTextures(unsigned int texture1, unsigned int texture2)
//{
//	m_texture1 = texture1;
//	m_texture2 = texture2;
//}
//Camera* Renderer::GetCamera()
//{
//	return &m_cam;
//}
//
//void Renderer::SetCubePositions(std::vector<glm::vec3>& cube_positions)
//{
//
//	std::vector<glm::vec3> cubePositions;
//	cubePositions.emplace_back( 0.0f, 0.0f, 0.0f);
//	cubePositions.emplace_back( 2.0f, 5.0f,-15.0f);
//	cubePositions.emplace_back(-1.5f,-2.2f,-2.5f);
//	cubePositions.emplace_back(-3.8f,-2.0f,-12.3f);
//	cubePositions.emplace_back( 2.4f,-0.4f,-3.5f);
//	cubePositions.emplace_back(-1.7f, 3.0f,-7.5f);
//	cubePositions.emplace_back( 1.3f,-2.0f,-2.5f);
//	cubePositions.emplace_back( 1.5f, 2.0f,-2.5f);
//	cubePositions.emplace_back( 1.5f, 0.2f,-1.5f);
//	cubePositions.emplace_back(-1.3f, 1.0f, -1.5f);
//	cube_positions = cubePositions;
//}			
//
//
//unsigned int Renderer::LoadTexture(const char* path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, numComponents;
//	unsigned char* data = stbi_load(path, &width, &height, &numComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (numComponents == 1)
//			format = GL_RED;
//		else if (numComponents == 3)
//			format = GL_RGB;
//		else if (numComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//	return textureID;
//}
//
//void Renderer::RenderCubes()
//{
//
//	float vertices[] = { 
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f };
//	std::vector<glm::vec3> cubePositionz;
//	SetCubePositions(cubePositionz);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//	Shader testShader;
//	testShader.Load("GL_Test.vert", "GL_Test.frag");
//	testShader.Use();
//	unsigned int texture1 = LoadTexture("Textures/container.jpg");
//	unsigned int texture2 = LoadTexture("Textures/awesomeface.png");
//	SetTextures(texture1, texture2);
//	testShader.SetInt("texture1", 0);
//	testShader.SetInt("texture2", 1);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, texture1);
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, texture2);
//
//	WindowHandler windowHandler;
//	testShader.Use();
//
//	glm::mat4 projection = glm::perspective(glm::radians(m_cam.Zoom), (float)windowHandler.GetWindowWidth() / (float)windowHandler.GetWindowHeight(), 0.1f, 100.0f);
//	testShader.SetMat4("projection", projection);
//
//	glm::mat4 view = m_cam.GetViewMatrix();
//	/*std::cout << glm::to_string(view) << std::endl;*/
//	testShader.SetMat4("view", view);
//	
//	
//	glBindVertexArray(m_VAO);
//	for (unsigned int i = 0; i < 10; i++)
//	{
//		glm::mat4 model = glm::mat4(1.0f);
//		model = glm::translate(model, cubePositionz[i]);
//		float angle = 20.0f * i;
//		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));
//		testShader.SetMat4("model", model);
//
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//	}
//}
//
//void Renderer::RenderScreen()
//{
//
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void Renderer::Update()
//{
//	RenderScreen();
//	RenderCubes();
//}
//
//Renderer::~Renderer()
//{
//	glDeleteBuffers(1, &m_VBO);
//	glDeleteVertexArrays(1, &m_VAO);
//}