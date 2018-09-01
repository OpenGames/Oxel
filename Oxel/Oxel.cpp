#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Triangle.cpp"
#include "Quad.cpp"
#include "Renderer.cpp"
#include "Camera.cpp"
#include "ShaderLoader.cpp"
namespace OpenGames::Oxel
{
	class Oxel
	{
	public:
		const uint16_t WIDTH = 800, HEIGHT = 600;
		const char* title = "Oxel";
		const double TICK_RATE = 1.0 / 128;
		GLFWwindow* window;
	private:
		const float HALF_WIDTH = WIDTH / 2.0f, HALF_HEIGHT = HEIGHT / 2.0f;
		bool keys[1024];

		Render::Renderer renderer;
		Render::Camera3D camera = Render::Camera3D(WIDTH, HEIGHT);

		GLuint programId;

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			keys[key] = action;
		}
		void keyHandler()
		{
			for(short i = 0; i < 348; i++)
			{
				if(keys[i])
				{
					switch(i)
					{
					case GLFW_KEY_ESCAPE:
						glfwSetWindowShouldClose(window, true);
						break;
					case GLFW_KEY_W:
						camera.move(0, 0.04f);
						break;
					case GLFW_KEY_A:
						camera.move(-0.04f, 0);
						break;
					case GLFW_KEY_S:
						camera.move(0, -0.04f);
						break;
					case GLFW_KEY_D:
						camera.move(0.04f, 0);
						break;
					case GLFW_KEY_SPACE:
						camera.position.y += 0.04f;
						break;
					case 341:
						camera.position.y -= 0.04f;
						break;
					case 340:
						camera.position.y -= 0.04f;
						break;
					}
				}
			}
		}
		void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			float deltaX = -(HALF_WIDTH - (float)xpos);
			float deltaY = (HALF_HEIGHT - (float)ypos);
			glfwSetCursorPos(window, HALF_WIDTH, HALF_HEIGHT);
			camera.addRotation(deltaY / (HEIGHT / 2), deltaX / (WIDTH / 2));
		}
	public:
		void init()
		{
			glfwInit();

			glfwWindowHint(GLFW_SAMPLES, 0);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

			window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);
			glfwMakeContextCurrent(window);

			glfwSetCursorPos(window, HALF_WIDTH, HALF_HEIGHT);
			glfwSetWindowUserPointer(window, this);
			glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
				static_cast<Oxel*>(glfwGetWindowUserPointer(window))->keyCallback(window, key, scancode, action, mods);
			});
			glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
				static_cast<Oxel*>(glfwGetWindowUserPointer(window))->cursorPositionCallback(window, xpos, ypos);
			});

			glewExperimental = GL_TRUE;
			glewInit();

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			/*
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			*/
			glEnable(GL_DEPTH_TEST);

			renderer.setShaderProgram(Render::ShaderLoader::createProgram(Render::ShaderLoader::compileShader(GL_VERTEX_SHADER, "Core.vert"), Render::ShaderLoader::compileShader(GL_FRAGMENT_SHADER, "Core.frag")));
			renderer.setCamera(&camera);

			Render::Models::Quad* object = new Render::Models::Quad();
			renderer.gameModels.pushBack(object);

			glUniformMatrix4fv(renderer.projectionMatrixLocation, 1, GL_FALSE, camera.getProjectionMatrixPointer());
			glUniformMatrix4fv(renderer.viewMatrixLocation, 1, GL_FALSE, camera.getViewMatrixPointer());
		}
		void render()
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			renderer.render();

			glfwSwapBuffers(window);
		}
		void update()
		{
			keyHandler();
			std::cout << camera.position.x << "\t" << camera.position.y << "\t" << camera.position.z << "\t" << camera.angleFromX << "\t" << camera.angleFromY << std::endl;
			//std::cout << camera.position.x << "\t" << camera.position.y << "\t" << camera.position.z << "\t" << camera.orientation.x << "\t" << camera.orientation.y << "\t" << camera.orientation.z << "\t" << std::endl;
		}
		inline int windowShouldClose() { return glfwWindowShouldClose(window); }
	};
}