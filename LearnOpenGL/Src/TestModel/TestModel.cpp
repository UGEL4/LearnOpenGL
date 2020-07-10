#include "TestModel.h"

namespace TestModel
{
	MyCamera camera(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 1.f, 0.f), 0.f);
	float deltaTime = 0.0f; // 当前帧与上一帧的时间差
	float lastFrame = 0.0f; // 上一帧的时间

	void ProcessInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveDirection::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveDirection::BACK, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveDirection::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveDirection::RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveDirection::UP, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveDirection::DOWN, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			camera.ProcessKeyboard(CameraMoveDirection::FOCUS, deltaTime);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			camera.IncSensitivity();
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			camera.DescSensitivity();

		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	void MousCallback(GLFWwindow* window, double x, double y)
	{
		camera.MouseInput(x, y);
	}

	bool InitOpenGl(GLFWwindow** window, const float width, const float height)
	{
		/* Initialize the library */
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		(*window) = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), "Hello World", NULL, NULL);
		if (!(*window))
		{
			glfwTerminate();
			return false;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(*window);


		glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(*window, MousCallback);
		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Error!" << "\n";
			return false;
		}

		std::cout << glGetString(GL_VERSION) << "\n";

		return true;
	}

	void Run()
	{
		GLFWwindow* window;
		float width = 1920.f;
		float height = 1080.f;
		if (InitOpenGl(&window, width, height))
		{
			//Model model("res/nanosuit/nanosuit.obj");
			//camera.SetMoveSpeed(5.f);
			Model model("res/so/ytryrt.obj");

			//model 模型变换矩阵
			glm::mat4 modelMat = glm::mat4(1.f);
			modelMat = glm::translate(modelMat, glm::vec3(0.f, 0.f, 0.f));
			//modelMat = glm::rotate(modelMat,glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
			modelMat = glm::scale(modelMat, glm::vec3(1.1f, 1.1f, 1.1f));

			glm::mat4 viewMat = camera.GetViewMatrix();

			//proj 投影矩阵
			glm::mat4 projectMat = glm::mat4(1.f);
			projectMat = glm::perspective(glm::radians(90.f), (float)width / (float)height, 0.1f, 1000.f);

			Shader modelShader("Shaders/NanosuitVertexShader.vs", "Shaders/NanosuitFragmentShader.fs");
			Shader geometryShader("Shaders/Normals.vs", "Shaders/Normals.fs");
			geometryShader.CreateGeometryShader("Shaders/Normals.gs");
			modelShader.CreateShader();
			modelShader.Bind();
			modelShader.SetUniform3fv("m_Light.direction", 0.f, 0.f, -10.f);
			modelShader.SetUniform3fv("lightPos", 0.f, 0.f, 3.f);
			modelShader.SetUniform3fv("m_Light.ambient", 0.2f, 0.2f, 0.2f);
			modelShader.SetUniform3fv("m_Light.diffuse", 0.5f, 0.5f, 0.5f);
			modelShader.SetUniform3fv("m_Light.specular", 1.f, 1.f, 1.f);
			modelShader.SetUniform1f("m_Material.shininess", 128.f);
			modelShader.SetUniformMatrix4fv("modelMat", modelMat);
			modelShader.SetUniformMatrix4fv("viewMat", viewMat);
			modelShader.SetUniformMatrix4fv("projMat", projectMat);

			modelShader.SetUniform3fv("m_PointLight.position", 0.f, 0.f, 3.f);
			modelShader.SetUniform3fv("m_PointLight.ambient", 0.2f, 0.2f, 0.2f);
			modelShader.SetUniform3fv("m_PointLight.diffuse", 1.f, 1.f, 1.f);
			modelShader.SetUniform3fv("m_PointLight.specular", 1.f, 1.f, 1.f);
			modelShader.SetUniform1f("m_PointLight.constant", 1.f);
			modelShader.SetUniform1f("m_PointLight.linear", 0.09f);
			modelShader.SetUniform1f("m_PointLight.quadratic", 0.032f);

			glEnable(GL_DEPTH_TEST);

			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window))
			{
				float current_frame = static_cast<float>(glfwGetTime());
				deltaTime = current_frame - lastFrame;
				lastFrame = current_frame;
				/* Render here */
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				modelShader.Bind();
				viewMat = camera.GetViewMatrix();
				modelShader.SetUniformMatrix4fv("viewMat", viewMat);
				modelShader.SetUniform3fv("viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
				//modelShader.SetUniform3fv("lightPos", camera.GteCameraPos().x, camera.GteCameraPos().y, camera.GteCameraPos().z);
				model.Draw(&modelShader);

				//法线视觉化
				//geometryShader.Bind();
				//geometryShader.SetUniformMatrix4fv("viewMat", viewMat);
				//geometryShader.SetUniformMatrix4fv("modelMat", modelMat);
				//geometryShader.SetUniformMatrix4fv("projection", projectMat);
				//model.Draw(&geometryShader);

				/* Swap front and back buffers */
				glfwSwapBuffers(window);

				/* Poll for and process events */
				glfwPollEvents();

				ProcessInput(window);
			}
		}

		glfwTerminate();
	}
}