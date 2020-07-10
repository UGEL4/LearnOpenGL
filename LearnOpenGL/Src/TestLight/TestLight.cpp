#include "TestLight.h"

namespace TestLight
{
	MyCamera camera(glm::vec3(0.f, 0.f, 3.f), glm::vec3(0.f, 1.f, 0.f), 0.f);
	float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
	float lastFrame = 0.0f; // ��һ֡��ʱ��

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
		camera.SetMoveSpeed(3.f);
		GLFWwindow* window;
		float width = 1920.f;
		float height = 1080.f;
		if (InitOpenGl(&window, width, height))
		{

			float vertices[] = {
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f
			};

			glm::vec3 cube_positions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
			};

			//floor
			float planeVertices[] = {
				// positions            // normals         // texcoords
				 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
				-10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
				-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

				 10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
				-10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
				 10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
			};
			// plane VAO
			unsigned int planeVAO, planeVBO;
			glGenVertexArrays(1, &planeVAO);
			glGenBuffers(1, &planeVBO);
			glBindVertexArray(planeVAO);
			glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glBindVertexArray(0);
			Shader blinnPhone("Shaders/AdvancedLight/BlinnPhone.vs", "Shaders/AdvancedLight/BlinnPhone.fs");
			Texture floorTexture("res/texture/floor.jpg", "texture_diffuse", 1);
			blinnPhone.Bind();
			blinnPhone.SetUniform1i("floorTexture", 4);
			floorTexture.Bind(4);

			//cube
			unsigned int VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			unsigned int vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//����
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			//����
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			//uv
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

			Texture diffuseMap("res/texture/container2.png", "texture_diffuse", true);
			Texture specularMap("res/texture/container2_specular.png", "texture_specular", true);

			//model ģ�ͱ任����
			glm::mat4 modelMat = glm::mat4(1.f);
			modelMat = glm::translate(modelMat, glm::vec3(0.f, 0.f, 0.f));
			//modelMat = glm::rotate(modelMat,glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
			//modelMat = glm::scale(modelMat, glm::vec3(0.1f, 0.1f, 0.1f));
			glm::mat4 viewMat = camera.GetViewMatrix();
			//proj ͶӰ����
			glm::mat4 projectMat = glm::mat4(1.f);
			projectMat = glm::perspective(glm::radians(90.f), (float)width / (float)height, 0.1f, 1000.f);

			Shader shader("Shaders/BaseVertexShader.vs", "Shaders/BaseFragmentShader.fs");
			shader.Bind();
			shader.SetUniformMatrix4fv("modelMat", modelMat);
			shader.SetUniformMatrix4fv("viewMat", viewMat);
			shader.SetUniformMatrix4fv("projMat", projectMat);

			//�����
			shader.SetUniform3fv("m_Light.direction", 0.f, 0.f, -3.f);
			shader.SetUniform3fv("m_Light.ambient", 0.1f, 0.1f, 0.1f);
			shader.SetUniform3fv("m_Light.diffuse", 0.1f, 0.1f, 0.1f);
			shader.SetUniform3fv("m_Light.specular", 1.f, 1.f, 1.f);
			//���Դ
			shader.SetUniform3fv("m_PointLights[0].position", 0.f, 0.f, -3.f);
			shader.SetUniform3fv("m_PointLights[0].ambient", 1.f, 1.f, 1.f);
			shader.SetUniform3fv("m_PointLights[0].diffuse", 1.f, 1.f, 1.f);
			shader.SetUniform3fv("m_PointLights[0].specular", 1.f, 1.f, 1.f);
			shader.SetUniform1f("m_PointLights[0].constant", 1.f);
			shader.SetUniform1f("m_PointLights[0].linear", 0.09f);
			shader.SetUniform1f("m_PointLights[0].quadratic", 0.032f);
			//�۹��
			shader.SetUniform3fv("m_SpolitLight.position", camera.GetCameraPos());
			shader.SetUniform3fv("m_SpolitLight.direction", camera.GetForward());
			shader.SetUniform1f("m_SpolitLight.cutOff", glm::cos(glm::radians(5.5f)));
			shader.SetUniform1f("m_SpolitLight.outerCutOff", glm::cos(glm::radians(7.5f)));
			shader.SetUniform3fv("m_SpolitLight.ambient", 0.1f, 0.1f, 0.1f);
			shader.SetUniform3fv("m_SpolitLight.diffuse", 1.f, 1.f, 1.f);
			shader.SetUniform3fv("m_SpolitLight.specular", 1.f, 1.f, 1.f);
			shader.SetUniform1f("m_SpolitLight.constant", 1.f);
			shader.SetUniform1f("m_SpolitLight.linear", 0.09f);
			shader.SetUniform1f("m_SpolitLight.quadratic", 0.032f);
			//����
			shader.SetUniform1i("m_Material.diffuse", 0);
			diffuseMap.Bind(0);
			shader.SetUniform1i("m_Material.specular", 1);
			specularMap.Bind(1);
			shader.SetUniform1f("m_Material.shininess", 64.f);
			
			shader.SetUniform3fv("viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
			shader.Unbind();

			glEnable(GL_DEPTH_TEST);

			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window))
			{
				float current_frame = static_cast<float>(glfwGetTime());
				deltaTime = current_frame - lastFrame;
				lastFrame = current_frame;
				/* Render here */
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//plan
				blinnPhone.Bind();
				floorTexture.Bind(4);
				blinnPhone.SetUniform1i("floorTexture", 4);
				blinnPhone.SetUniformMatrix4fv("projection", projectMat);
				viewMat = camera.GetViewMatrix();
				blinnPhone.SetUniformMatrix4fv("view", viewMat);
				blinnPhone.SetUniform3fv("viewPos", camera.GetCameraPos());
				blinnPhone.SetUniform3fv("lightPos", 8.f, 0.f, 0.f);
				glBindVertexArray(planeVAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);

				//cube
				shader.Bind();
				viewMat = camera.GetViewMatrix();
				shader.SetUniformMatrix4fv("viewMat", viewMat);
				shader.SetUniform3fv("m_SpolitLight.position", camera.GetCameraPos());
				shader.SetUniform3fv("m_SpolitLight.direction", camera.GetForward());
				shader.SetUniform3fv("viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
				glBindVertexArray(VAO);
				for (int i = 0; i < 10; i++)
				{
					glm::mat4 model = glm::mat4(1.0f);
					modelMat = glm::translate(modelMat, cube_positions[i]);
					float angle = 20.0f * i;
					shader.SetUniformMatrix4fv("modelMat", modelMat);
					modelMat = glm::mat4(1.f);
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
				shader.Unbind();

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