#include "Input.h"
namespace Input
{
	bool g_EnterMouse = true;
	float g_mouseLastFrameX;
	float g_mouseLastFrameY;
	double g_mouseOffsetX = 0;
	double g_mouseOffsetY = 0;
	double g_mouseX;
	double g_mouseY;
	double x, y;
	bool IsKeyDown(GLFWwindow* window, unsigned int key)
	{
		return glfwGetKey(window, key) == PURE_KEY_PRESS;
	}

	
	void SetMouseLastFrame(float lastX, float lastY)
	{
		 g_mouseLastFrameX = lastX;
		 g_mouseLastFrameY = lastY;
	}
	
	void UpdateCameraRotation(GLFWwindow* window, float& yaw, float& pitch, bool constraintPitch = true, const float& mouseSensitivity = 0.2f)
	{
		
		glfwGetCursorPos(window, &x, &y);		
		if (g_EnterMouse)
		{
			g_mouseLastFrameX = x;
			g_mouseLastFrameY = y;
			g_EnterMouse = false;
		}
		g_mouseX = x;
		g_mouseY = y;
		g_mouseOffsetX = x - g_mouseLastFrameX;
		g_mouseOffsetY = g_mouseLastFrameY - y;
		g_mouseLastFrameX = g_mouseX;
		g_mouseLastFrameY = g_mouseY;

		g_mouseOffsetX *= mouseSensitivity;
		g_mouseOffsetY *= mouseSensitivity;
		yaw += g_mouseOffsetX;
		pitch += g_mouseOffsetY;

		if (constraintPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}
	
		
	}
	
	

}