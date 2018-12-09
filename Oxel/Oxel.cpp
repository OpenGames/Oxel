#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ContentPipe.cpp"
#include "Triangle.cpp"
#include "Quad.cpp"
#include "Renderer.cpp"
#include "Camera.cpp"
#include "ShaderLoader.cpp"
#include "DerivedList.cpp"
#include "Player.cpp"
#include "World.cpp"

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

		Game::Player player;

		Render::Renderer renderer;
		Render::Camera3D* camera;

		Game::GameWorld::Chunk Chunk;
		Game::GameWorld::World ZAWARUDO;

		GLuint posrx, posry;

		int multiplyer = 1;
		float rx = 1, ry = 1;

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
						player.move(0, 0.04f * multiplyer);
						break;
					case GLFW_KEY_A:
						player.move(-0.04f * multiplyer, 0);
						break;
					case GLFW_KEY_S:
						player.move(0, -0.04f * multiplyer);
						break;
					case GLFW_KEY_D:
						player.move(0.04f * multiplyer, 0);
						break;
					case GLFW_KEY_DELETE:
						renderer.gameDModels.clear();
						break;
					case GLFW_KEY_INSERT:
						UpdateChunks(1);
						//renderer.gameDModels[0]->addRotation(-PI / 1280, 0, 0);
						break;
					case GLFW_KEY_UP:
						ry += 0.04f;
						break;
					case GLFW_KEY_DOWN:
						ry -= 0.04f;
						//glUniform1f(posry, ry);
						break;
					case GLFW_KEY_LEFT:
						rx -= 0.04f;
						//glUniform1f(posrx, rx);
						break;
					case GLFW_KEY_RIGHT:
						rx += 0.04f;
						//glUniform1f(posrx, rx);
						break;
					case GLFW_KEY_SPACE:
						player.jump();
						break;
					case GLFW_KEY_F12:
						multiplyer = 10;
						break;
					case GLFW_KEY_F11:
						multiplyer = 1;
						break;
					case GLFW_KEY_F10:
						player.changeCreative();
						break;
					case 341: //ctrl
						//camera.position.y -= 0.04f * multiplyer;
						break;
					case 340: //shift
						//multiplyer = 10;
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
			player.Look(deltaY / (HEIGHT / 2), deltaX / (WIDTH / 2));
		}

		Game::GameWorld::WorldGenerator generator;
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
			glEnable(GL_DEPTH_TEST);

			player = *new Game::Player({ 0.0f, 20.0f, 0.0f });
			player.setScreen(WIDTH, HEIGHT);

			renderer.setShaderProgram(Render::ShaderLoader::createProgram(Render::ShaderLoader::compileShader(GL_VERTEX_SHADER, "Core.vert"), Render::ShaderLoader::compileShader(GL_FRAGMENT_SHADER, "Core.frag")));
			posrx = glGetUniformLocation(renderer.getProgram(), "rx");
			posry = glGetUniformLocation(renderer.getProgram(), "ry");
			renderer.setCamera(player.getCameraInstance());

			GLuint missing = ContentPipe::loadTexture("Contents/missing.png", GL_NEAREST);
			ContentPipe::bindTexture(missing, 0);
			ZAWARUDO = *new Game::GameWorld::World(missing);
			ZAWARUDO.generate(player.getPosition());

			//UpdateChunks(1);
			//auto quad = new Render::Models::Quad({ 0.0f,0.0f,0.0f });
			//quad->scale(2.0f, 2.0f, 1.0f);

			

			double time = glfwGetTime();

			auto chunkModels = ZAWARUDO.getChunksToRender(player.getPosition(), 4);
			printf("\n~~~~~\nchunk build elapsed: %fms\n~~~~~\n", glfwGetTime() - time);
			printf("chunkModels size: %i", chunkModels.size());
			for (Render::Models::DerivedModel* chunkModel : chunkModels)
			{
				
				renderer.gameDModels.push_back(chunkModel);
			}
			

			glUniformMatrix4fv(renderer.projectionMatrixLocation, 1, GL_FALSE, player.getProjectionMatrixPointer());
			glUniformMatrix4fv(renderer.viewMatrixLocation, 1, GL_FALSE, player.getViewMatrixPointer());
		}
		void UpdateChunks(int r)
		{
			//renderer.gameDModels.clear();

			//std::vector<Game::GameWorld::Chunk> chunk = generator.generateChunks(player.getPosition(), r);

			//ZAWARUDO = generator.generateChunk(0, 0);

			//double time = glfwGetTime();
			//auto chunkModel = ZAWARUDO.buildChunkModel();
			//printf("\n~~~~~\nchunk build elapsed: %fms\n~~~~~\n", glfwGetTime() - time);

			//renderer.gameDModels.push_back(chunkModel);
			
		}
		double fps;
		double time;
		void render()
		{
			time = glfwGetTime();

			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0.698f, 0.99f, 0.99f, 1.0f);
			glUniform1f(posrx, rx);
			glUniform1f(posry, ry);
			
			renderer.render();

			glfwSwapBuffers(window);

			fps = 1.0 / (glfwGetTime() - time);
			time = glfwGetTime();
		}
		void update()
		{
			//this->player.setGroundState(fa);
			this->player.update(TICK_RATE);
			
			keyHandler();
			glfwSetWindowTitle(window, ("FPS: " + std::to_string(fps) + " CK: " + std::to_string(renderer.gameDModels.size()) + " RX: " + std::to_string(rx)).c_str());
			std::cout << player.getPosition().x << "    \t" << player.getPosition().y << "    \t" << player.getPosition().z << "    \t" << player.getCameraInstance()->angleFromX << "    \t" << player.getCameraInstance()->angleFromY << std::endl;
			//std::cout << camera.position.x << "\t" << camera.position.y << "\t" << camera.position.z << "\t" << camera.orientation.x << "\t" << camera.orientation.y << "\t" << camera.orientation.z << "\t" << std::endl;
		}
		inline int windowShouldClose() { return glfwWindowShouldClose(window); }
	};
}
