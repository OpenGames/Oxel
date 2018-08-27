#pragma once
#include "Array.cpp"
#include "Model.cpp"
namespace OpenGames::Oxel::Render
{
	class Renderer
	{
		GLuint program;
	public:
		GLuint modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation;
		Math::Array<Models::Model*> gameModels;
		~Renderer()
		{
			for(size_t i = 0; i < gameModels.size(); ++i)
			{
				delete gameModels[i];
			}
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
			glUseProgram(program);
			for(size_t i = 0; i < gameModels.size(); ++i)
			{
				glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, gameModels[i]->getModelMatrixPointer());
				gameModels[i]->draw();
			}
		}
	};
}