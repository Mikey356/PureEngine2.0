#include <glfw3.h>
#include "keycodes.h"

namespace Input
{
	
	bool IsKeyDown(GLFWwindow* window, unsigned int key);
	void UpdateCameraRotation(GLFWwindow* window, float& yaw, float& pitch, bool constraintPitch, const float& mouseSensitivity);
	void SetMouseLastFrame(float lastX, float lastY);
	/*void ProcessMouseMovement(float xoffset, float yoffset, bool constraintpitch, float mouseSensitivity, float pitch, float yaw);
	void ProcessMouseScroll(float yOffset, float zoom);*/
}