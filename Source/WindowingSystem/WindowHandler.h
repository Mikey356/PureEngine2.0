#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>

namespace WindowHandler {
	struct WindowInfo
	{
		GLFWwindow* m_window;
		unsigned int m_ScrWidth;
		unsigned int m_ScrHeight;
		GLFWwindow* CreateWindow(const char* t, GLFWmonitor* monitor, GLFWwindow* share);

		WindowInfo();
		~WindowInfo();
	};
}