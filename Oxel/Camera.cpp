#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#define PI 3.14159265359f
namespace OpenGames::Oxel::Render
{
	class Camera3D
	{
	private:
		float aspectRatio;
	public:
		glm::vec3 position = glm::vec3(0.0f, 0.0f, -2.0f);// -0.418867
		glm::vec3 orientation = glm::vec3(0.0f, 0.0f, 0.0f);
		float angleFromX = 7.86158f;
		float angleFromY = .0f;
		float sensivity = 1.0f;
		float fov = 90.0f;

		Camera3D(uint16_t width, uint16_t height) : aspectRatio((float)width / height) {}

		//yaw: up/down
		//pitch: left/right
		inline void addRotation(float yaw, float pitch)
		{
			angleFromX += pitch * PI * sensivity;
			if(angleFromY + yaw * PI * sensivity * 2 < PI / 2 && angleFromY + yaw * PI * sensivity * 2 > -PI / 2)
				angleFromY += yaw * PI * sensivity;
			orientation.x = glm::cos(angleFromX) * glm::cos(angleFromY);
			orientation.z = glm::sin(angleFromX) * glm::cos(angleFromY);
			orientation.y = glm::sin(angleFromY);

		}
		inline void move(float side, float straight)
		{
			position.x += straight * glm::cos(angleFromX) + side * glm::cos(angleFromX + PI / 2);
			position.z += straight * glm::sin(angleFromX) + side * glm::sin(angleFromX + PI / 2);
			//position.y += straight * glm::cos(angleFromY);
		}
		inline const GLfloat* getViewMatrixPointer()
		{
			return glm::value_ptr(glm::lookAt(position, orientation + position, glm::vec3(0.0f, 1.0f, 0.0f)));
		}
		inline const GLfloat* getProjectionMatrixPointer()
		{
			return glm::value_ptr(glm::perspective(glm::radians(fov), 640.0f / 480, 0.0001f, 1000.0f));
		}
	};
}