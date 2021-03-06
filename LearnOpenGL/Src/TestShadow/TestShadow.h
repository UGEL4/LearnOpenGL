#pragma once

#define GLEW_STATIC
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../MyCamera.h"
#include "../Shader.h"
#include "../gl_inf.h"
#include "../Texture.h"
#include <vector>

namespace TestShadow
{
	void ProcessInput(GLFWwindow* window);
	void MousCallback(GLFWwindow* window, double x, double y);
	bool InitOpenGl(GLFWwindow** window, const float width, const float height);

	void Run();

	void PointShadow();
}
