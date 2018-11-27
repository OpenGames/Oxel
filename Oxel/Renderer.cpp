#pragma once
#include <iostream>
#include <vector>
#include "Array.cpp"
#include "Model.cpp"
#include "Camera.cpp"
namespace OpenGames::Oxel::Render
{
	class Renderer
	{
		GLuint program;
	public:
		GLuint modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation;
		Render::Camera3D* camera;
		Math::Array<Models::Model*> gameModels;
		std::vector<Models::DerivedModel*> gameDModels;
		~Renderer()
		{
			for(int i = 0; i < gameModels.size(); ++i)
			{
				delete gameModels[i];
			}
		}
		GLuint getProgram()
		{
			return program;
		}
		void setCamera(Render::Camera3D *Camera)
		{
			camera = Camera;
		}
		void setShaderProgram(GLuint shaderProgram)
		{
			program = shaderProgram;
			glUseProgram(program);
			modelMatrixLocation = glGetUniformLocation(shaderProgram, "model");
			viewMatrixLocation = glGetUniformLocation(shaderProgram, "view");
			projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projection");
		}
		void render()
		{
			//glUseProgram(program);
			for(int i = 0; i < gameModels.size(); ++i)
			{
				glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, camera->getProjectionMatrixPointer());
				glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, camera->getViewMatrixPointer());
				glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameModels[i]->getModelMatrix()));

				gameModels[i]->draw();
			}
			for (int i = 0; i < gameDModels.size(); ++i)
			{
				glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, camera->getProjectionMatrixPointer());
				glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, camera->getViewMatrixPointer());
				for (int j = 0; j < gameDModels[i]->size(); j++)
				{
					glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameDModels[i]->getModelMatrix(j)));
					gameDModels[i]->draw(j);
				}			
			}
		}
	};
}