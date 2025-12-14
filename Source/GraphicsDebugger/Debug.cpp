#include <iostream>
#include "Debug.h"
bool g_enable = false;
GLenum TextBasedDebugger::glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)
 



 void APIENTRY TextBasedDebugger::glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
 {
	 // ignore non-significant error/warning codes
	 GLint major, minor;
	 glGetIntegerv(GL_MAJOR_VERSION, &major);
	 glGetIntegerv(GL_MINOR_VERSION, &minor);
	 const GLubyte* vendor = glGetString(GL_VENDOR);
	 const GLubyte* renderer = glGetString(GL_RENDERER);
	 if (!g_enable) {
		 std::cout << "\nGPU: " << renderer << "\n";
		 std::cout << "GL version: " << major << "." << minor << "\n\n";
		 g_enable = true;
	 }
	 if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	 std::cout << "----------------" << std::endl;
	 std::cout << "Debug message (" << id << "): " << message << std::endl;

	 switch (source)
	 {
	 case GL_DEBUG_SOURCE_API:		std::cout << "Source: API"; break;
	 case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cout << "Source: Window System"; break;
	 case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	 case GL_DEBUG_SOURCE_THIRD_PARTY: std::cout << "Source: Third Party"; break;
	 case GL_DEBUG_SOURCE_APPLICATION: std::cout << "Source: Application"; break;
	 case GL_DEBUG_SOURCE_OTHER:	std::cout << "Source: Other"; break;
	 }std::cout << std::endl;

	 switch (type)
	 {
	 case GL_DEBUG_TYPE_ERROR:				std::cout << "Type: Error"; break;
	 case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behavior"; break;
	 case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behavior"; break;
	 case GL_DEBUG_TYPE_PORTABILITY:		    std::cout << "Type: PORTABILITY"; break;
	 case GL_DEBUG_TYPE_PERFORMANCE:			std::cout << "Type: PERFORMANCE"; break;
	 case GL_DEBUG_TYPE_MARKER:				std::cout << "Type: MARKER"; break;
	 case GL_DEBUG_TYPE_PUSH_GROUP:			std::cout << "Type: PUSH_GROUP"; break;
	 case GL_DEBUG_TYPE_POP_GROUP:			std::cout << "Type: POP_GROUP"; break;
	 case GL_DEBUG_TYPE_OTHER:				std::cout << "Type: OTHER"; break;
	 }std::cout << std::endl;


	 switch (severity)
	 {
	 case GL_DEBUG_SEVERITY_HIGH:		 std::cout << "Severity: high"; break;
	 case GL_DEBUG_SEVERITY_MEDIUM:		 std::cout << "Severity: medium"; break;
	 case GL_DEBUG_SEVERITY_LOW:			 std::cout << "Severity: low"; break;
	 case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	 }std::cout << std::endl;
	 std::cout << std::endl;
 }

 int TextBasedDebugger::EnableDebugger()
 {

	 if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	 {
		 std::cout << "Failed to initialize GLAD" << std::endl;
		 return -1;
	 }
	 int flags;  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

	 auto debugOutput = TextBasedDebugger::glDebugOutput;
	 if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	 {
		 glEnable(GL_DEBUG_OUTPUT);
		 glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
		 glDebugMessageCallback(debugOutput, nullptr);
		 glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	 } 
 }