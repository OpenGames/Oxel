#pragma once
#include "Model.cpp"
#include "ContentPipe.cpp"
namespace OpenGames::Oxel::Render::Models
{
	class Quad : public Model
	{
	private:
		GLfloat vertices[20] = {
			//Position
			-0.50f, -0.50f, 0.00f,
			-0.50f,  0.50f, 0.00f,
			 0.50f, -0.50f, 0.00f,
			 0.50f,  0.50f, 0.00f,

			 //UVs
			 0.0f, 0.5f, //12, 13
			 0.0f, 0.0f, //14, 15
			 0.5f, 0.5f, //16, 17
			 0.5f, 0.0f, //18, 19

			 //14 --> 20
		};
		
	public:
		Quad(glm::vec3 position = glm::vec3(0, 0, 0)) : Model(position)
		{
			GLuint vao, vbo;

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(sizeof(GLfloat) * 12));

			glBindVertexArray(0);

			this->vao = vao;
			this->vbo = vbo;
		}
		virtual void setUvRepeat(float x, float y) override final
		{
			vertices[12] *= x; vertices[13] *= y;
			vertices[14] *= x; vertices[15] *= y;
			vertices[16] *= x; vertices[17] *= y;
			vertices[18] *= x; vertices[19] *= y;


			GLuint vao, vbo;

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(sizeof(GLfloat) * 12));

			glBindVertexArray(0);

			this->vao = vao;
			this->vbo = vbo;
		}
		virtual void draw() override final
		{
			//ContentPipe::bindTexture(texture, 0);
			glBindVertexArray(vao);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			//ContentPipe::unbindTexture(0);
		}
	};
	class GreedyQuadBuilder
	{
	private:
		Quad* returnableQuad;
		char type;
		int width;
		int height;
	public:
		GreedyQuadBuilder(glm::vec3 position, char type)
		{
			returnableQuad = new Render::Models::Quad(position);
			this->type = type;
			if (type == 'z')
			{

			}
			else if (type == 'x')
			{
				this->returnableQuad->addRotation(0.0f, 0.0f, PI / 2);
			}
			else if (type == 'y')
			{
				this->returnableQuad->addRotation(PI / 2, 0.0f, 0.0f);
			}

			width = 1;
			height = 1;
		}
		void addRight()
		{
			width++;
		}
		void addLine()
		{
			height++;
		}
		Quad* build()
		{
			
			returnableQuad->scale(width, height, 1.0f);
			if (type == 'z')
			{
				returnableQuad->position.x += (float)(width - 1) / 2;
				returnableQuad->position.y += (float)(height - 1) / 2;
			}
			else if (type == 'x')
			{
				returnableQuad->position.z += (float)(width - 1) / 2;
				returnableQuad->position.y += (float)(height - 1) / 2;
			}
			else if (type == 'y')
			{
				returnableQuad->position.x += (float)(width - 1) / 2;
				returnableQuad->position.z += (float)(height - 1) / 2;
			}

			return returnableQuad;
		}

	};
}