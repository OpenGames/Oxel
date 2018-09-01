#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#define PI 3.1415f
namespace OpenGames::Oxel::Render
{
	class Camera3D
	{
	private:
		float aspectRatio;
	public:
		glm::vec3 position = glm::vec3(1.0f, 1.0f, 1.0f);// -0.418867
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, 0.0f);
		float angleFromX = 1.97126f;
		float angleFromY = -0.418867f;
		float sensivity = 1.0f;
		float fov = 90.0f;

		Camera3D(uint16_t width, uint16_t height) : aspectRatio((float)width / height) {}

		//yaw: up/down
		//pitch: left/right
		inline void addRotation(float yaw, float pitch)
		{
			angleFromX += pitch * PI * sensivity;
			if(angleFromY + yaw * PI * sensivity <= PI / 2 && angleFromY + yaw * PI * sensivity >= -PI / 2)
				angleFromY += yaw * PI * sensivity;
			float radiusFromY = cos(angleFromY);
			orientation.x = cos(angleFromX) * radiusFromY;
			orientation.z = sin(angleFromX) * radiusFromY;
			orientation.y = sin(angleFromY);

		}
		inline void move(float side, float straight)
		{
			position.x += straight * cos(angleFromX) + side * cos(angleFromX + PI / 2);
			position.z += straight * sin(angleFromX) + side * sin(angleFromX + PI / 2);
		}
		inline glm::vec2 getSomePos()
		{
			return glm::vec2(position.x, position.y);
		}
		inline const GLfloat* getViewMatrixPointer()
		{
			return glm::value_ptr(glm::lookAt(position, orientation + position, glm::vec3(0.0f, 1.0f, 0.0f)));
		}
		inline const GLfloat* getProjectionMatrixPointer()
		{
			return glm::value_ptr(glm::perspective(glm::radians(fov), 640.0f / 480, 0.0001f, 1000.0f));
		}
		inline const glm::highp_mat4 getViewMatrixPointerC()
		{
			return glm::lookAt(position, orientation + position, glm::vec3(0.0f, 1.0f, 0.0f));
		}
		inline const glm::highp_mat4 getProjectionMatrixPointerC()
		{
			return glm::perspective(glm::radians(fov), aspectRatio, 0.0001f, 1000.0f);
		}
	};
}