#pragma once
#include <iostream>
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
		Math::Array<Models::DerivedModel*> gameDModels;
		~Renderer()
		{
			for(size_t i = 0; i < gameModels.size(); ++i)
			{
				delete gameModels[i];
			}
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
			for(size_t i = 0; i < gameModels.size(); ++i)
			{
				glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, camera->getProjectionMatrixPointer());
				glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, camera->getViewMatrixPointer());
				glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameModels[i]->getModelMatrix()));

				gameModels[i]->draw();
			}
			for (size_t i = 0; i < gameDModels.size(); ++i)
			{
				glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, camera->getProjectionMatrixPointer());
				glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, camera->getViewMatrixPointer());
				for (size_t j = 0; j < gameDModels[i]->size(); j++)
				{
					if (j == 0)
					{
						if (camera->position.x  < gameDModels[i]->getPosition().x - 0.5)
						{
							glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameDModels[i]->getModelMatrix(j)));
							gameDModels[i]->draw(j);
						}
					}
					if (j == 1)
					{
						if (camera->position.x  > gameDModels[i]->getPosition().x + 0.5)
						{
							glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameDModels[i]->getModelMatrix(j)));
							gameDModels[i]->draw(j);
						}
					}
					if (j == 2)
					{
						if (camera->position.y  < gameDModels[i]->getPosition().y - 0.5)
						{
							glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameDModels[i]->getModelMatrix(j)));
							gameDModels[i]->draw(j);
						}
					}
					if (j == 3)
					{
						if (camera->position.y > gameDModels[i]->getPosition().y + 0.5)
						{
							glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameDModels[i]->getModelMatrix(j)));
							gameDModels[i]->draw(j);
						}
					}
					if (j == 4)
					{
						if (camera->position.z  < gameDModels[i]->getPosition().z - 0.5)
						{
							glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameDModels[i]->getModelMatrix(j)));
							gameDModels[i]->draw(j);
						}
					}
					if (j == 5)
					{
						if (camera->position.z  > gameDModels[i]->getPosition().z + 0.5)
						{
							glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(gameDModels[i]->getModelMatrix(j)));
							gameDModels[i]->draw(j);
						}
					}
				}
				
			}
		}
	};
}