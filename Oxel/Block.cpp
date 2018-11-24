#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>
#include "ContentPipe.cpp"
#include "Array.cpp"

namespace OpenGames::Oxel::Game::GameObjects
{
	class Block
	{
	private:
		int AtlasX;
		int AtlasY;



	protected:
		int id;

	public:
		float hardness;
		float lightness;
		bool gravityAffected;
		bool collisionAffected;
		bool isStackable;
		int maxStack;

		Block(int id = -1)
		{
			this->id = id;
		}
		virtual long getID()
		{
			return id;
		}
	};
	class BlockManager
	{
	public:
		BlockManager()
		{
		}

		Block GetBlock(int id)
		{
			return *blocks[id];
		}

	private:
		Math::Array<Block*> blocks;
	};

	enum Blocks
	{
		MISSING = -1,
		AIR
	}; 
}