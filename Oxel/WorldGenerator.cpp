#pragma once
#include "Chunk.cpp"

namespace OpenGames::Oxel::Game::GameWorld
{
	class WorldGenerator
	{
	private:
		GLuint texture;
	public:
		WorldGenerator(GLuint Texture)
		{
			this->texture = Texture;
		}
		Chunk generateChunk()
		{
			Chunk chunk({ 0.0, 0.0 }, texture);

			for (int y = 0; y < 10; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					for (int z = 0; z < 16; z++)
					{
						chunk.setBlock(x, y, z, *new Game::GameObjects::Block());
					}
				}
			}

			return chunk;
		}
	};
}