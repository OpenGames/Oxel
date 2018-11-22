#pragma once
#include "Model.cpp"
#include "ContentPipe.cpp"
namespace OpenGames::Oxel::Render::Models
{
	class Quad : public Model
	{
	public:
		Quad(glm::vec3 position) : Model(position)
		{
			GLuint vao, vbo;

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			static const GLfloat vertices[20] = {
				//Position
				-0.50f, -0.50f, 0.00f,
				-0.50f,  0.50f, 0.00f,
				 0.50f, -0.50f, 0.00f,
				 0.50f,  0.50f, 0.00f,
				 //UVs
				  0.0f, 0.0f,
				  0.0f, 1.0f,
				  1.0f, 0.0f,
				  1.0f, 1.0f

				 //14 --> 20
			};

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(sizeof(GLfloat) * 12));

			glBindVertexArray(0);

			this->vao = vao;
			this->vbo.pushBack(vbo);
		}

		virtual void draw() override final
		{
			ContentPipe::bindTexture(texture, 0);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			ContentPipe::unbindTexture(0);
		}
	};
}