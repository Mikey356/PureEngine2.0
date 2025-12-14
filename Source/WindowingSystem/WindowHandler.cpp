#include "WindowHandler.h"
#include "PureDefines.h"

WindowHandler::WindowInfo::WindowInfo()  : m_ScrHeight(1440), m_ScrWidth(2560)
{
	
	glfwInit();
	glfwWindowHint(PURE_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(PURE_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(PURE_OPENGL_PROFILE, PURE_OPENGL_CORE_PROFILE);
	glfwWindowHint(PURE_OPENGL_DEBUG_CONTEXT, true);
	
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

GLFWwindow* WindowHandler::WindowInfo::CreateWindow(const char* t, GLFWmonitor* monitor, GLFWwindow* share)
{

	m_window= glfwCreateWindow(m_ScrWidth, m_ScrHeight, t, monitor, share);
	if (m_window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return m_window;
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

WindowHandler::WindowInfo::~WindowInfo()
{
	if (!m_window)
	{
		delete m_window;
	}
	
}