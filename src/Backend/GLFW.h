#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Renderer/Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

extern GLFWwindow* window;
extern int width;
extern int height;
extern const char* title;


namespace GLFW
{

		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		bool InitializeWindow(const unsigned int& w, const unsigned int& h, const char* t);
		void ProcessInput(Camera& camera, float& deltaTime);
		void ProcessInput(float mixValue);
		bool WindowIsOpen();

		void Terminate();
}