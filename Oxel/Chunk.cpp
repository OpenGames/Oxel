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

	public:
		Chunk(glm::vec2 pos, GLuint texture)
		{
			std::vector<std::vector<std::vector<GameObjects::Block>>> initedChunk(16, 
				std::vector<std::vector<GameObjects::Block>>(256, 
					std::vector<GameObjects::Block>(16, 
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

			for (int y = 0; y < 256; y++)
			{
				for (int x = 0; x < 16; x++)
				{
					for (int z = 0; z < 16; z++)
					{
						if (chunk[x][y][z].getID() == GameObjects::Blocks::AIR)
							continue;
						#pragma region Y
						if (y == 0) {
							Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y - 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
							face->setTexture(texture);
							face->addRotation(PI / 2, 0.0f, 0.0f);
							ChunkModel->addModel(face);
						}
						else
						{
							if (chunk[x][y - 1][z].getID() == GameObjects::Blocks::AIR)
							{
								Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y - 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
								face->setTexture(texture);
								face->addRotation(PI / 2, 0.0f, 0.0f);
								ChunkModel->addModel(face);
							}
						}
						if (y == 255) {
							Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
							face->setTexture(texture);
							face->addRotation(PI / 2, 0.0f, 0.0f);
							ChunkModel->addModel(face);
						}
						else
						{
							if (chunk[x][y + 1][z].getID() == GameObjects::Blocks::AIR)
							{
								Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
								face->setTexture(texture);
								face->addRotation(PI / 2, 0.0f, 0.0f);
								ChunkModel->addModel(face);
							}
						}
						#pragma endregion
						#pragma region Z
						if (z == 0)
						{
							Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z - 0.5) + glm::vec3(pos.x, 0, pos.y));
							face->setTexture(texture);
							ChunkModel->addModel(face);
						}
						else
						{
							if (chunk[x][y][z - 1].getID() == GameObjects::Blocks::AIR)
							{
								Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z - 0.5) + glm::vec3(pos.x, 0, pos.y));
								face->setTexture(texture);
								ChunkModel->addModel(face);
							}
						}
						if (z == 15)
						{
							Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z + 0.5f) + glm::vec3(pos.x, 0, pos.y));
							face->setTexture(texture);
							ChunkModel->addModel(face);
						}
						else
						{
							if (chunk[x][y][z + 1].getID() == GameObjects::Blocks::AIR)
							{
								Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z + 0.5) + glm::vec3(pos.x, 0, pos.y));
								face->setTexture(texture);
								ChunkModel->addModel(face);
							}
						}
						#pragma endregion						
						#pragma region X
						if (x == 0)
						{
							Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + -0.5, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
							face->setTexture(texture);
							face->addRotation(0.0f, 0.0f, PI / 2);
							ChunkModel->addModel(face);
						}
						else
						{
							if (chunk[x - 1][y][z].getID() == GameObjects::Blocks::AIR)
							{
								Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + -0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
								face->setTexture(texture);
								face->addRotation(0.0f, 0.0f, PI / 2);
								ChunkModel->addModel(face);
							}
						}
						if (x == 15)
						{
							Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
							face->setTexture(texture);
							face->addRotation(0.0f, 0.0f, PI / 2);
							ChunkModel->addModel(face);
						}
						else
						{
							if (chunk[x + 1][y][z].getID() == GameObjects::Blocks::AIR)
							{
								Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
								face->setTexture(texture);
								face->addRotation(0.0f, 0.0f, PI / 2);
								ChunkModel->addModel(face);
							}
						}
						#pragma endregion
					}
				}
			}

			return ChunkModel;
		}
	};
}