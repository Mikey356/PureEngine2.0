#include <iostream>
#include "WindowingSystem/WindowHandler.h"
#include "GraphicsDebugger/Debug.h"
#include "Engine/Engine.h"

auto w_Info = new WindowHandler::WindowInfo;

int main()
{

	GLFWwindow* window = w_Info->CreateWindow("PureEngine", nullptr, nullptr);

	TextBasedDebugger::EnableDebugger();
	Engine::Graphics::InitOpenGLAPI(window);
	Engine::Graphics::InitAssets();
	
	while (!glfwWindowShouldClose(window))
	{
		Engine::RunPure(*w_Info);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}
	
	glfwDestroyWindow(window);
	delete w_Info;
	glfwTerminate();
	return 0;
}