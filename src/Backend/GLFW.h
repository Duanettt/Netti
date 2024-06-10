#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

extern GLFWwindow* window;
extern int width;
extern int height;
extern const char* title;

namespace GLFW
{
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		bool InitializeWindow(const unsigned int& w, const unsigned int& h, const char* t);
		void ProcessInput();
		bool WindowIsOpen();

		void Terminate();
}