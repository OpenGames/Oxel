#pragma once
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
		virtual ~Model()
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers((GLsizei)vbo.size(), &vbo[0]);
			delete &vbo;
		}

		virtual void draw() {}

		virtual const GLfloat* getModelMatrixPointer()
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-0.5f));
			model = glm::translate(model, position);
			return glm::value_ptr(model);
		}

		virtual inline GLuint getVao() { return vao; }
		virtual inline const Math::Array<GLuint>& getVbo() { return vbo; }
	};
}