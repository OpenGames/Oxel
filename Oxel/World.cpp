#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "WorldGenerator.cpp"
#include "Chunk.cpp"

namespace OpenGames::Oxel::Game::GameWorld
{
	class World
	{
	private:
		//ChunkArr[xPos][zPos];

		Chunk XpZp[16][16]; // (0,0) includes here
		Chunk XpZn[16][16]; // (1, -1)
		Chunk XnZp[16][16]; // (-1, 1)
		Chunk XnZn[16][16]; // (-1, -1)

		WorldGenerator generator;

		int seed;

	public:
		World(int seed = 0) : seed(seed)
		{

		}
		void generate(glm::vec3 pos)
		{
			XpZp[0][0] = generator.generateChunk(0, 0);
		}
		Chunk getCurrentChunk(glm::vec3 pos)
		{
			float absZ = glm::abs(pos.z);
			float signZ = glm::sign(pos.z);
			float absX = glm::abs(pos.x);
			float signX = glm::sign(pos.x);
			if ((signZ > 0 && signX > 0) || (pos.z > -0.5f && pos.x > -0.5f))
			{
				printf("chunk at P-P ap: %i %i", (int)(absX / 16), (int)(absZ / 16));
				return XpZp[(int)(absX / 16)][(int)(absZ / 16)];
			}
			else if ((signZ < 0 && signX > 0) || (pos.x > -0.5f))
			{
				printf("chunk at P-N ap: %i %i", (int)(absX / 16), (int)(absZ / 16));
				return XpZn[(int)(absX / 16)][(int)(absZ / 16)];
			}
			else if (signZ < 0 && signX < 0)
			{
				printf("chunk at N-N ap: %i %i", (int)(absX / 16), (int)(absZ / 16));
				return XnZn[(int)(absX / 16)][(int)(absZ / 16)];
			}
			else
			{
				printf("chunk at N-P ap: %i %i", (int)(absX / 16), (int)(absZ / 16));
				return XnZp[(int)(absX / 16)][(int)(absZ / 16)];
			}
		}
		void DebugCC(glm::vec3 pos)
		{
				float absZ = glm::abs(pos.z);
				float signZ = glm::sign(pos.z);
				float absX = glm::abs(pos.x);
				float signX = glm::sign(pos.x);
				if ((signZ > 0 && signX > 0) || (pos.z > -0.5f && pos.x > -0.5f))
				{
					printf("chunk at P-P ap: %i %i", (int)(absX / 16), (int)(absZ / 16));
				}
				else if ((signZ < 0 && signX > 0) || (pos.x > -0.5f))
				{
					printf("chunk at P-N ap: %i %i", (int)(absX / 16), (int)(absZ / 16));
				}
				else if (signZ < 0 && signX < 0)
				{
					printf("chunk at N-N ap: %i %i", (int)(absX / 16), (int)(absZ / 16));
				}
				else
				{
					printf("chunk at N-P ap: %i %i", (int)(absX / 16), (int)(absZ / 16));
				}
		}
		std::vector<Render::Models::DerivedModel*> getChunksToRender(glm::vec3 pos, int radius)
		{
			std::vector<Render::Models::DerivedModel*> result;

			result.push_back(getCurrentChunk(pos).buildChunkModel());

			return result;
		}
		static bool isBottomBlockSolid(float x, float y, float z, Chunk ZAWARUDO)
		{
			return ZAWARUDO.getBlock((int)x % 16, (int)floorf(y) - 1, (int)z % 16).getID() != GameObjects::Blocks::AIR;
		}
		static bool isBottomBlockSolid(glm::vec3 pos, Chunk ZAWARUDO)
		{
			return ZAWARUDO.getBlock((int)pos.x % 16, (int)floorf(pos.y) - 1, (int)pos.z % 16).getID() != GameObjects::Blocks::AIR;
		}
	};

}