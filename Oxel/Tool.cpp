#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace OpenGames::Oxel::Game::GameObjects
{
	class Tool
	{
	private:
		int AtlasX;
		int AtlasY;

	protected:
		long id;

	public:
		float hardness;
		float lightness;
		bool gravityAffected;
		bool collisionAffected;
		bool isStackable;
		int maxStack;
	};
}