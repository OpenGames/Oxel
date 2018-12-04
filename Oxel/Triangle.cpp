#pragma once
#include "Model.cpp"
namespace OpenGames::Oxel::Render::Models
{
	class Triangle : public Model
	{
	public:
		Triangle(glm::vec3 position) : Model(position)
		{
			GLuint vao, vbo;

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			static const GLfloat vertices[15] = {
				//Position
				0.00f, 0.00f, 0.00f,
				0.00f, 1.00f, 0.00f,
				1.00f, 1.00f, 0.00f,
				 //UVs
				 1.0f,0.0f,
				 0.0f,1.0f,
				 1.0f,1.0f
			};

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(sizeof(GLfloat) * 9));

			glBindVertexArray(0);

			this->vao = vao;
			this->vbo = vbo;
		}
		virtual void draw() override final
		{
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	};
}