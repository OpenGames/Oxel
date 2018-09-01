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
		GLuint vao;
		Math::Array<GLuint> vbo;
		glm::mat4 model = glm::mat4(1.0f);
	public:
		glm::vec3 position;
		Model(glm::vec3 position) : position(position)
		{
		}
		virtual ~Model()
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers((GLsizei)vbo.size(), &vbo[0]);
			delete &vbo;
		}

		virtual void draw() {}

		virtual const GLfloat* getModelMatrixPointer()
		{	
			model = glm::translate(model, glm::vec3(-0.5f));
			//model = glm::translate(model, position);
			return glm::value_ptr(model);
		}

		virtual inline GLuint getVao() { return vao; }
		virtual inline const Math::Array<GLuint>& getVbo() { return vbo; }
	};
}