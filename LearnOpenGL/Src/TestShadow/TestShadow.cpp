#include "TestShadow.h"

namespace TestShadow
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
		camera.SetMoveSpeed(3.f);
		GLFWwindow* window;
		float width = 1920.f;
		float height = 1080.f;
		if (InitOpenGl(&window, width, height))
		{

			float vertices[] = {
				// back face
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
				 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
				// front face
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
				 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
				-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				// left face
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				// right face
				 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
				 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
				// bottom face
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
				 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				// top face
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
				 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
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
				 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
				-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
				-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

				 25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
				-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
				 25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
			};


			unsigned int depthMapFBO;
			glGenFramebuffers(1, &depthMapFBO);
			const unsigned int S_WIDTH = 1024, S_HEIGHT = 1024;
			unsigned int depthMap;
			glGenTextures(1, &depthMap);
			glBindTexture(GL_TEXTURE_2D, depthMap);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, S_WIDTH, S_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
			glReadBuffer(GL_NONE);
			glDrawBuffer(GL_NONE);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			//quad
			float quadVertices[] = {
				// positions        // texture Coords
				-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			unsigned int quadVAO;
			unsigned int quadVBO;
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

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
			Texture floorTexture("res/texture/floor.jpg", "texture_diffuse", 1);
			//floorTexture.Bind(4);

			//cube
			unsigned int VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			unsigned int vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//顶点
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			//法线
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			//uv
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

			Texture diffuseMap("res/texture/container2.png", "texture_diffuse", true);

			//model 模型变换矩阵
			glm::mat4 modelMat = glm::mat4(1.f);
			modelMat = glm::translate(modelMat, glm::vec3(0.f, 0.f, 0.f));
			//modelMat = glm::rotate(modelMat,glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
			//modelMat = glm::scale(modelMat, glm::vec3(0.1f, 0.1f, 0.1f));
			glm::mat4 viewMat = camera.GetViewMatrix();
			//proj 投影矩阵
			glm::mat4 projectMat = glm::mat4(1.f);
			projectMat = glm::perspective(glm::radians(90.f), (float)width / (float)height, 0.1f, 100.f);


			glm::vec3 lightPos(0.f, 4.0f, -2.f);

			Shader shader("Shaders/ShadowTest/shadow_mapping.vs", "Shaders/ShadowTest/shadow_mapping.fs");
			//shader.Bind();

			//定向光
			//shader.SetUniform3fv("m_Light.direction", 0.f, 0.f, -3.f);
			//shader.SetUniform3fv("m_Light.ambient", 0.1f, 0.1f, 0.1f);
			//shader.SetUniform3fv("m_Light.diffuse", 0.1f, 0.1f, 0.1f);
			//shader.SetUniform3fv("m_Light.specular", 1.f, 1.f, 1.f);
			//点光源
			//shader.SetUniform3fv("m_PointLights[0].position", 0.f, 0.f, -3.f);
			//shader.SetUniform3fv("m_PointLights[0].ambient", 1.f, 1.f, 1.f);
			//shader.SetUniform3fv("m_PointLights[0].diffuse", 1.f, 1.f, 1.f);
			//shader.SetUniform3fv("m_PointLights[0].specular", 1.f, 1.f, 1.f);
			//shader.SetUniform1f("m_PointLights[0].constant", 1.f);
			//shader.SetUniform1f("m_PointLights[0].linear", 0.09f);
			//shader.SetUniform1f("m_PointLights[0].quadratic", 0.032f);
			//聚光灯
			//shader.SetUniform3fv("m_SpolitLight.position", camera.GetCameraPos());
			//shader.SetUniform3fv("m_SpolitLight.direction", camera.GetForward());
			//shader.SetUniform1f("m_SpolitLight.cutOff", glm::cos(glm::radians(5.5f)));
			//shader.SetUniform1f("m_SpolitLight.outerCutOff", glm::cos(glm::radians(7.5f)));
			//shader.SetUniform3fv("m_SpolitLight.ambient", 0.1f, 0.1f, 0.1f);
			//shader.SetUniform3fv("m_SpolitLight.diffuse", 1.f, 1.f, 1.f);
			//shader.SetUniform3fv("m_SpolitLight.specular", 1.f, 1.f, 1.f);
			//shader.SetUniform1f("m_SpolitLight.constant", 1.f);
			//shader.SetUniform1f("m_SpolitLight.linear", 0.09f);
			//shader.SetUniform1f("m_SpolitLight.quadratic", 0.032f);
			//材质

			//shader.SetUniform1i("diffuseTexture", 0);
			//diffuseMap.Bind(0);
			//shader.Unbind();

			Shader simpleDepthShader("Shaders/ShadowTest/shadow_mapping_depth.vs", "Shaders/ShadowTest/shadow_mapping_depth.fs");
			Shader debugDepthQuad("Shaders/ShadowTest/debug_quad.vs", "Shaders/ShadowTest/debug_quad.fs");

			glEnable(GL_DEPTH_TEST);

			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window))
			{
				float current_frame = static_cast<float>(glfwGetTime());
				deltaTime = current_frame - lastFrame;
				lastFrame = current_frame;
				/* Render here */
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//渲染深度贴图
				glm::mat4 lightProjection, lightView;
				glm::mat4 lightSpaceMatrix;
				float near_plane = 1.0f, far_plane = 7.5f;
				lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
				lightView = glm::lookAt(lightPos, glm::vec3(0.0f,0.f,0.f), glm::vec3(0.0, 1.0, 0.0));
				lightSpaceMatrix = lightProjection * lightView;
				// render scene from light's point of view
				simpleDepthShader.Bind();
				simpleDepthShader.SetUniformMatrix4fv("lightSpaceMatrix", lightSpaceMatrix);

				glViewport(0, 0, S_WIDTH, S_HEIGHT);
				glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
				glClear(GL_DEPTH_BUFFER_BIT);
				//plan
				glm::mat4 model = glm::mat4(1.0f);
				simpleDepthShader.SetUniformMatrix4fv("model", model);
				glBindVertexArray(planeVAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
				//cube
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
				model = glm::scale(model, glm::vec3(0.5f));
				simpleDepthShader.SetUniformMatrix4fv("model", model);
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				simpleDepthShader.Unbind();

				// reset viewport
				glViewport(0, 0, width, height);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//渲染场景
				//plan
				shader.Bind();
				shader.SetUniform1i("diffuseTexture", 0);
				floorTexture.Bind(0);
				shader.SetUniform1i("shadowMap", 1);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, depthMap);
				shader.SetUniformMatrix4fv("projection", projectMat);
				viewMat = camera.GetViewMatrix();
				shader.SetUniformMatrix4fv("view", viewMat);
				model = glm::mat4(1.0f);
				shader.SetUniformMatrix4fv("model", model);
				shader.SetUniformMatrix4fv("lightSpaceMatrix", lightSpaceMatrix);
				float z = camera.GetForward().z;
				shader.SetUniform3fv("viewPos", camera.GetCameraPos());
				shader.SetUniform3fv("lightPos", lightPos);
				glBindVertexArray(planeVAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);

				//cube
				shader.SetUniform1i("diffuseTexture", 2);
				diffuseMap.Bind(2);
				shader.SetUniform1i("shadowMap", 3);
				glActiveTexture(GL_TEXTURE3);
				glBindTexture(GL_TEXTURE_2D, depthMap);
				shader.SetUniformMatrix4fv("projection", projectMat);
				viewMat = camera.GetViewMatrix();
				shader.SetUniformMatrix4fv("view", viewMat);
				model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
				model = glm::scale(model, glm::vec3(0.5f));
				shader.SetUniformMatrix4fv("model", model);
				shader.SetUniformMatrix4fv("lightSpaceMatrix", lightSpaceMatrix);
				z = camera.GetForward().z;
				shader.SetUniform3fv("viewPos", camera.GetCameraPos());
				shader.SetUniform3fv("lightPos", lightPos);
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
				shader.Unbind();

				//渲染阴影
				//debugDepthQuad.Bind();
				////debugDepthQuad.SetUniform1f("near_plane", near_plane);
				////debugDepthQuad.SetUniform1f("far_plane", far_plane);
				//debugDepthQuad.SetUniform1i("depthMap", 0);
				//glActiveTexture(GL_TEXTURE0);
				//glBindTexture(GL_TEXTURE_2D, depthMap);
				//glBindVertexArray(quadVAO);
				//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
				//glBindVertexArray(0);

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