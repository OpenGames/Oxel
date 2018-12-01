#pragma once
#include "Chunk.cpp"

namespace OpenGames::Oxel::Game::GameWorld
{
	class WorldGenerator
	{
	private:
		GLuint texture;
		int chunkC = 0;
	public:
		WorldGenerator(GLuint Texture)
		{
			this->texture = Texture;
		}
		WorldGenerator()
		{

		}
		Chunk generateChunk(float x, float z)
		{
			Chunk chunk({ x , z }, texture);

			for (int y = 0; y < 16; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					for (int z = 0; z < 16; z++)
					{
						if (x == 8 && y == 8)
						{

						}
						else 
						{ 
							chunk.setBlock(x, y, z, *new Game::GameObjects::Block()); 
						}
					}
				}
			}
			return chunk;
		}
		std::vector<Chunk> generateChunks(glm::vec3 playerPos, int chunkRadius)
		{ 
			std::vector<Chunk> res;
			
			float x = glm::floor(playerPos.x / 16);
			float z = glm::floor(playerPos.z / 16);

			for (int i = 0; i < chunkRadius * chunkRadius; i++)
			{
				res.push_back(generateChunk(((i % chunkRadius) - (chunkRadius/2))*16 + x * 16 , ((i / chunkRadius) - (chunkRadius / 2)) * 16 + z * 16));
			}

			return res;
			res.clear();
		}
	};
}