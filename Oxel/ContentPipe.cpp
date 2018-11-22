#pragma once
#include <vector>
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
namespace OpenGames
{
	class ContentPipe
	{
	private:
		static const uint16_t ATLAS_SIZE = 512;
		static const uint16_t textureSize = 32;
	public:
		static GLuint loadTexture(const char* fileName, GLint filtering)
		{
			GLuint textureId;
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
			int width, height;
			unsigned char* data = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			SOIL_free_image_data(data);
			return textureId;
		}
		static void deleteTexture(GLuint textureId)
		{
			glDeleteTextures(1, &textureId);
		}
		static void bindTexture(GLuint textureId, unsigned int textureUnit)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, textureId);
		}
		static void unbindTexture(unsigned int textureUnit)
		{
			glActiveTexture(GL_TEXTURE0 + textureUnit);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		static std::vector<GLfloat> getTexture(glm::vec2 position)
		{
			static const GLfloat TEXTURES_PER_ROW = (GLfloat)ATLAS_SIZE / (GLfloat)textureSize;
			static const GLfloat TEXTURE_SIZE = 1.0f / TEXTURES_PER_ROW;
			static const GLfloat PIXEL_SIZE = 1.0f / (float)ATLAS_SIZE;

			GLfloat xMin = (position.x * TEXTURE_SIZE) + 0.5f * PIXEL_SIZE - PIXEL_SIZE / 2;
			GLfloat yMin = (position.y * TEXTURE_SIZE) + 0.5f * PIXEL_SIZE - PIXEL_SIZE / 2;

			GLfloat xMax = (xMin + TEXTURE_SIZE) - 0.5f * PIXEL_SIZE + PIXEL_SIZE / 2;
			GLfloat yMax = (yMin + TEXTURE_SIZE) - 0.5f * PIXEL_SIZE + PIXEL_SIZE / 2;

			std::vector<GLfloat> uv = {
				xMax, yMin,
				xMin, yMin,
				xMax, yMax,
				xMin, yMax,

				xMin, yMin,
				xMin, yMax,
				xMax, yMin,
				xMax, yMax,

				xMax, yMin,
				xMin, yMin,
				xMax, yMax,
				xMin, yMax,

				xMax, yMax,
				xMax, yMin,
				xMin, yMax,
				xMin, yMin,

				xMax, yMin,
				xMin, yMin,
				xMax, yMax,
				xMin, yMax,

				xMin, yMin,
				xMin, yMax,
				xMax, yMin,
				xMax, yMax
			};

			return uv;
		}
	};
}