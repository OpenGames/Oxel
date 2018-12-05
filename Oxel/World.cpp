#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Chunk.cpp"

namespace OpenGames::Oxel::Game::GameWorld
{
	class World
	{
	private:
		std::vector<Chunk> XpZp; // (0,0) includes here
		std::vector<Chunk> XpZn; // (1, -1)
		std::vector<Chunk> XnZp; // (-1, 1)
		std::vector<Chunk> XnZn; // (-1, -1)

		int seed;

	public:
		World(int seed) : seed(seed)
		{
		}
		Chunk getCurrentChunk(glm::vec3 pos)
		{

		}
		std::vector<Render::Models::DerivedModel*> getChunksToRender(glm::vec3 pos, int radius)
		{

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