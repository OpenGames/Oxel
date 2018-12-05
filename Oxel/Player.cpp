#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Camera.cpp"
#define PI 3.14159265359f

namespace OpenGames::Oxel::Game
{
	class Player
	{
	private:
		float ar;
		OpenGames::Oxel::Render::Camera3D camera;
		glm::vec3 pos;

		float verticalSpeed = -5.0f;
		bool isOnTheGround = false;

		bool creative = false;
	public:
		Player(glm::vec3 pos = glm::vec3(0, 0, 0))
		{
			this->pos = pos;
			camera.setPosition(pos);
		}
		void setScreen(uint16_t w, uint16_t h)
		{
			camera = Render::Camera3D(w, h);
			camera.setPosition(pos);
		}
		void setFov(float fov)
		{
			camera.setFov(fov);
		}
		Render::Camera3D* getCameraInstance()
		{
			return &this->camera;
		}
		inline const GLfloat* getViewMatrixPointer()
		{
			return camera.getViewMatrixPointer();
		}
		inline const GLfloat* getProjectionMatrixPointer()
		{
			return camera.getProjectionMatrixPointer();
		}
		glm::vec3 getPosition()
		{
			return pos;
		}
		glm::vec3 getOrientation()
		{
			return camera.orientation;
		}
		void changeCreative()
		{
			creative = !creative;
		}
		inline void Look(float yaw, float pitch)
		{
			camera.addRotation(yaw, pitch);
		}
		inline void move(float side, float straight)
		{
			if (creative)
			{
				pos.x += straight * glm::cos(camera.angleFromX) * glm::cos(camera.angleFromY) + side * glm::cos(camera.angleFromX + PI / 2); //str*cos(Y) if flyng
				pos.z += straight * glm::sin(camera.angleFromX) * glm::cos(camera.angleFromY) + side * glm::sin(camera.angleFromX + PI / 2); //str*cos(Y) if flyng
				pos.y += straight * glm::sin(camera.angleFromY);
			}
			else
			{
				pos.x += straight * glm::cos(camera.angleFromX) + side * glm::cos(camera.angleFromX + PI / 2); //str*cos(Y) if flyng
				pos.z += straight * glm::sin(camera.angleFromX) + side * glm::sin(camera.angleFromX + PI / 2); //str*cos(Y) if flyng
				//position.y += straight * glm::sin(camera.angleFromY);
			}

		}
		inline void jump()
		{
			if (verticalSpeed >= -0.1f && verticalSpeed <= 0.1f)
			{
				verticalSpeed += 5.0f;
			}
		}
		inline void setGroundState(bool state)
		{
			isOnTheGround = state;
		}
		inline void update(float time)
		{
			if (!isOnTheGround)
			{

				//pos.y += (verticalSpeed * time);

				//if (verticalSpeed >= -5.0f)
				//	verticalSpeed -= 0.4f * time;
			}
			else {
				verticalSpeed = 0;
			}

			camera.setPosition(pos);
		}
	};
}