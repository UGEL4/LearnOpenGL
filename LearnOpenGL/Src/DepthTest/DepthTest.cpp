#include "DepthTest.h"
#include <time.h>
namespace DepthTest
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

			/*float vertices[] = {
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
			};*/
			float vertices[] = {
				// Back face
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
				0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
				-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
				// Front face
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
				0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
				0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
				-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
				// Left face
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
				-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
				-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
				// Right face
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
				0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
				0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
				0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
				// Bottom face
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
				0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
				0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
				-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
				-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
				// Top face
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
				0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
				0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
				-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
				-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left       
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


			//cube
			unsigned int vao;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			unsigned int vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			//顶点
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			//法线
			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			//uv
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

			Texture diffuseMap("res/texture/container2.png", "texture_diffuse", true);
			Texture specularMap("res/texture/container2_specular.png", "texture_specular", true);


			//model 模型变换矩阵
			glm::mat4 modelMat = glm::mat4(1.f);
			modelMat = glm::translate(modelMat, glm::vec3(0.f, 0.001f, 0.f));
			//modelMat = glm::rotate(modelMat,glm::radians(180.f), glm::vec3(0.f, 1.f, 0.f));
			//modelMat = glm::scale(modelMat, glm::vec3(0.1f, 0.1f, 0.1f));
			glm::mat4 viewMat = camera.GetViewMatrix();
			//proj 投影矩阵
			glm::mat4 projectMat = glm::mat4(1.f);
			projectMat = glm::perspective(glm::radians(90.f), (float)width / (float)height, 0.1f, 1000.f);

			Shader shader("Shaders/DepthTest/DepthTest.vs", "Shaders/DepthTest/DepthTest.fs");
			shader.Bind();
			shader.SetUniformMatrix4fv("modelMat", modelMat);
			shader.SetUniformMatrix4fv("viewMat", viewMat);
			shader.SetUniformMatrix4fv("projMat", projectMat);

			//定向光
			shader.SetUniform3fv("m_Light.direction", 0.f, 0.f, -3.f);
			shader.SetUniform3fv("m_Light.ambient", 0.1f, 0.1f, 0.1f);
			shader.SetUniform3fv("m_Light.diffuse", 0.1f, 0.1f, 0.1f);
			shader.SetUniform3fv("m_Light.specular", 1.f, 1.f, 1.f);
			//点光源
			shader.SetUniform3fv("m_PointLights[0].position", 0.f, 0.f, -3.f);
			shader.SetUniform3fv("m_PointLights[0].ambient", 1.f, 1.f, 1.f);
			shader.SetUniform3fv("m_PointLights[0].diffuse", 1.f, 1.f, 1.f);
			shader.SetUniform3fv("m_PointLights[0].specular", 1.f, 1.f, 1.f);
			shader.SetUniform1f("m_PointLights[0].constant", 1.f);
			shader.SetUniform1f("m_PointLights[0].linear", 0.09f);
			shader.SetUniform1f("m_PointLights[0].quadratic", 0.032f);
			//聚光灯
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
			//材质
			shader.SetUniform1i("m_Material.diffuse", 0);
			diffuseMap.Bind(0);
			shader.SetUniform1i("m_Material.specular", 1);
			specularMap.Bind(1);
			shader.SetUniform1f("m_Material.shininess", 64.f);
			
			shader.SetUniform3fv("viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
			shader.Unbind();

			float planeVertices[] = {
				// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
				4.f,	-1.f,	4.f,	2.f, 0.f,
				4.f,	-1.f,	-4.f,	2.f, 2.f,
				-4.f,	-1.f,	-4.f,	0.f, 2.f,
						 
				-4.f,	-1.f,	-4.f,	0.f, 2.f,
				-4.f,	-1.f,	4.f,	0.f, 0.f,
				4.f,	-1.f,	4.f,	2.f, 0.f
			};

			// plane VAO
			unsigned int planeVAO, planeVBO;
			glGenVertexArrays(1, &planeVAO);
			glGenBuffers(1, &planeVBO);
			glBindVertexArray(planeVAO);
			glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glBindVertexArray(0);

			Shader floorShader("Shaders/DepthTest/Floor.vs", "Shaders/DepthTest/Floor.fs");
			floorShader.Bind();
			floorShader.SetUniformMatrix4fv("modelMat", modelMat);
			floorShader.SetUniformMatrix4fv("viewMat", viewMat);
			floorShader.SetUniformMatrix4fv("projMat", projectMat);
			floorShader.SetUniform1i("m_Material.diffuse", 0);
			Texture floorDiffuseMap("res/texture/container2.png", "texture_diffuse", true);
			floorDiffuseMap.Bind(0);

			Shader singleColor("Shaders/DepthTest/SingleColor.vs", "Shaders/DepthTest/SingleColor.fs");
			singleColor.Bind();
			glm::mat4 model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(0.f, 0.001f, 0.f));
			model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
			singleColor.SetUniformMatrix4fv("modelMat", model);
			singleColor.SetUniformMatrix4fv("viewMat", viewMat);
			singleColor.SetUniformMatrix4fv("projMat", projectMat);

			//Texture floorTex("res/texture/")
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_STENCIL_TEST);		//模板测试
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			glEnable(GL_CULL_FACE);
			//glCullFace(GL_FRONT);
			//glFrontFace(GL_CCW);
			//clock_t start, end;
			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window))
			{
				float current_frame = static_cast<float>(glfwGetTime());
				deltaTime = current_frame - lastFrame;
				lastFrame = current_frame;
				/* Render here */
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

				//start = clock();

				glStencilMask(0x00);
				floorShader.Bind();
				viewMat = camera.GetViewMatrix();
				floorShader.SetUniformMatrix4fv("viewMat", viewMat);
				glBindVertexArray(planeVAO);
				floorShader.SetUniformMatrix4fv("modelMat", glm::mat4(1.f));
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
				floorShader.Unbind();

				//cube
				glStencilFunc(GL_ALWAYS, 1, 0xFF);
				glStencilMask(0xFF);
				shader.Bind();
				viewMat = camera.GetViewMatrix();
				shader.SetUniformMatrix4fv("viewMat", viewMat);
				shader.SetUniformMatrix4fv("modelMat", modelMat);
				shader.SetUniform3fv("m_SpolitLight.position", camera.GetCameraPos());
				shader.SetUniform3fv("m_SpolitLight.direction", camera.GetForward());
				shader.SetUniform3fv("viewPos", camera.GetCameraPos().x, camera.GetCameraPos().y, camera.GetCameraPos().z);
				glBindVertexArray(vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glm::mat4 m = glm::mat4(1.f);
				m = glm::translate(m, glm::vec3(0.f, 0.001f, 2.f));
				shader.SetUniformMatrix4fv("modelMat", m);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);
				shader.Unbind();

				glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
				glStencilMask(0x00);
				glDisable(GL_DEPTH_TEST);
				singleColor.Bind();
				singleColor.SetUniformMatrix4fv("viewMat", viewMat);
				model = glm::mat4(1.f);
				model = glm::translate(model, glm::vec3(0.f, 0.001f, 0.f));
				model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
				singleColor.SetUniformMatrix4fv("modelMat", model);
				glBindVertexArray(vao);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				model = glm::mat4(1.f);
				model = glm::translate(model, glm::vec3(0.f, 0.001f, 2.f));
				model = glm::scale(model, glm::vec3(1.05f, 1.05f, 1.05f));
				singleColor.SetUniformMatrix4fv("modelMat", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
				glBindVertexArray(0);

				glStencilMask(0xFF);
				glStencilFunc(GL_ALWAYS, 0, 0xFF);
				glEnable(GL_DEPTH_TEST);
				/* Swap front and back buffers */
				glfwSwapBuffers(window);

				//end = clock();
				//std::cout << (double)(end - start) / CLOCKS_PER_SEC << std::endl;

				/* Poll for and process events */
				glfwPollEvents();

				ProcessInput(window);
			}
			glDeleteVertexArrays(1, &vao);
			glDeleteVertexArrays(1, &planeVAO);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &planeVBO);
		}
		glfwTerminate();
	}
}