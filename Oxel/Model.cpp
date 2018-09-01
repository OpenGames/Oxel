#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "Array.cpp"
namespace OpenGames::Oxel::Render::Models
{
	class Model
	{
	protected:
		glm::vec3 position;
		GLuint vao;
		Math::Array<GLuint> vbo;
	public:
		glm::mat4 model = glm::mat4(1.0f);
		virtual ~Model()
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers((GLsizei)vbo.size(), &vbo[0]);
			delete &vbo;
		}

		virtual void draw() {}

		virtual const GLfloat* getModelMatrixPointer()
		{	
			//std::cout << model[0][0] << " - " << model[0][1] << " - " << model[0][2] << " - " << model[0][3] << "\n";
			//std::cout << model[1][0] << " - " << model[1][1] << " - " << model[1][2] << " - " << model[1][3] << "\n";
			//std::cout << model[2][0] << " - " << model[2][1] << " - " << model[2][2] << " - " << model[2][3] << "\n";
			//std::cout << model[3][0] << " - " << model[3][1] << " - " << model[3][2] << " - " << model[3][3] << "\n\n\n\n";

			//model = glm::translate(model, glm::vec3(-0.5f));
			//model = glm::translate(model, position);
			return glm::value_ptr(model);
		}

		virtual inline GLuint getVao() { return vao; }
		virtual inline const Math::Array<GLuint>& getVbo() { return vbo; }
	};
}