#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Array.cpp"
#include "Model.cpp"
#include "Quad.cpp"
#include "Block.cpp"

namespace OpenGames::Oxel::Game::GameWorld
{
	class Chunk
	{
	private:
		std::vector<std::vector<std::vector<GameObjects::Block>>> chunk;
		glm::vec2 pos;
		GLuint texture;

		int size = 16;

	public:
		Chunk(glm::vec2 pos, GLuint texture)
		{
			std::vector<std::vector<std::vector<GameObjects::Block>>> initedChunk(size,
				std::vector<std::vector<GameObjects::Block>>(size,
					std::vector<GameObjects::Block>(size,
						*new GameObjects::Block(0))));

			this->pos = pos;
			this->texture = texture;

			chunk = initedChunk;
		}
		void setBlock(int x, int y, int z, GameObjects::Block block)
		{
			chunk[x][y][z] = block;
		}
		GameObjects::Block getBlock(int x, int y, int z)
		{
			return chunk[x][y][z];
		}
		Render::Models::DerivedModel* buildChunkModel()
		{
			Render::Models::DerivedModel* ChunkModel = new Render::Models::DerivedModel();

			//for (int y = 0; y < 256; y++)
			//{
			//	for (int x = 0; x < 16; x++)
			//	{
			//		for (int z = 0; z < 16; z++)
			//		{
			//			//if (chunk[x][y][z].getID() == GameObjects::Blocks::AIR)
			//			//	continue;
			//			//#pragma region Y
			//			//if (y == 0) {
			//			//	continue;
			//			//	Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y - 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//			//	//face->setTexture(texture);
			//			//	face->addRotation(PI / 2, 0.0f, 0.0f);
			//			//	ChunkModel->addModel(face);
			//			//}
			//			//else
			//			//{
			//			//	if (chunk[x][y - 1][z].getID() == GameObjects::Blocks::AIR)
			//			//	{
			//			//		Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y - 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//			//		//face->setTexture(texture);
			//			//		face->addRotation(PI / 2, 0.0f, 0.0f);
			//			//		ChunkModel->addModel(face);
			//			//		continue;
			//			//	}
			//			//}
			//			//if (y == 255) {
			//			//	continue;
			//			//	Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//			//	//face->setTexture(texture);
			//			//	face->addRotation(PI / 2, 0.0f, 0.0f);
			//			//	ChunkModel->addModel(face);
			//			//}
			//			//else
			//			//{
			//			//	if (chunk[x][y + 1][z].getID() == GameObjects::Blocks::AIR)
			//			//	{
			//			//		Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//			//		//face->setTexture(texture);
			//			//		face->addRotation(PI / 2, 0.0f, 0.0f);
			//			//		ChunkModel->addModel(face);
			//			//		continue;
			//			//	}
			//			//}
			//			//#pragma endregion
			//			//#pragma region Z
			//			//if (z == 0)
			//			//{
			//			//	continue;
			//			//	Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z - 0.5) + glm::vec3(pos.x, 0, pos.y));
			//			//	//face->setTexture(texture);
			//			//	ChunkModel->addModel(face);
			//			//}
			//			//else
			//			//{
			//			//	if (chunk[x][y][z - 1].getID() == GameObjects::Blocks::AIR)
			//			//	{
			//			//		Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z - 0.5) + glm::vec3(pos.x, 0, pos.y));
			//			//		//face->setTexture(texture);
			//			//		ChunkModel->addModel(face);
			//			//		continue;
			//			//	}
			//			//}
			//			//if (z == 15)
			//			//{
			//			//	continue;
			//			//	Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z + 0.5f) + glm::vec3(pos.x, 0, pos.y));
			//			//	//face->setTexture(texture);
			//			//	ChunkModel->addModel(face);
			//			//}
			//			//else
			//			//{
			//			//	if (chunk[x][y][z + 1].getID() == GameObjects::Blocks::AIR)
			//			//	{
			//			//		Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z + 0.5) + glm::vec3(pos.x, 0, pos.y));
			//			//		//face->setTexture(texture);
			//			//		ChunkModel->addModel(face);
			//			//		continue;
			//			//	}
			//			//}
			//			//#pragma endregion						
			//			//#pragma region X
			//			//if (x == 0)
			//			//{
			//			//	continue;
			//			//	Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + -0.5, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//			//	//face->setTexture(texture);
			//			//	face->addRotation(0.0f, 0.0f, PI / 2);
			//			//	ChunkModel->addModel(face);
			//			//}
			//			//else
			//			//{
			//			//	if (chunk[x - 1][y][z].getID() == GameObjects::Blocks::AIR)
			//			//	{
			//			//		Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + -0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//			//		//face->setTexture(texture);
			//			//		face->addRotation(0.0f, 0.0f, PI / 2);
			//			//		ChunkModel->addModel(face);
			//			//		continue;
			//			//	}
			//			//}
			//			//if (x == 15)
			//			//{
			//			//	continue;
			//			//	Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//			//	//face->setTexture(texture);
			//			//	face->addRotation(0.0f, 0.0f, PI / 2);
			//			//	ChunkModel->addModel(face);
			//			//}
			//			//else
			//			//{
			//			//	if (chunk[x + 1][y][z].getID() == GameObjects::Blocks::AIR)
			//			//	{
			//			//		Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//			//		//face->setTexture(texture);
			//			//		face->addRotation(0.0f, 0.0f, PI / 2);
			//			//		ChunkModel->addModel(face);
			//			//		continue;
			//			//	}
			//			//}
			//			//#pragma endregion
			//		}
			//	}
			//}

			for (int z = 0; z < size; z++) //checking for Z plane
			{
				for (int x = 0; x < size; x++)
				{
					for (int y = 0; y < size; y++)
					{
						GameObjects::Block CurrentCheckingBlock = chunk[x][y][z];


					}
				}
			}

			return ChunkModel;
		}
	};
}