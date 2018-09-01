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
				glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, gameModels[i]->getModelMatrixPointer());

				//std::cout << "LEL" << SomePosLoc;

				gameModels[i]->draw();
			}
		}
	};
}