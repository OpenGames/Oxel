#pragma once
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


		bool checkChLineZ(int x, int y, int z, int width, int blockID)				//		+-------> x
		{							
			if (x - width == 0) return false;										//		|
			bool result = true;														//		|
			for (int cw = x; cw > x - width; cw--)									//		|
			{																		//		V y
				
				//std::cout << "-----------------\nCCLZ DEBUG: \n-----------------\n";
				//std::cout << "\tcw:\t" << cw << "\n";
				//std::cout << "\tx:\t" << x << "\n";
				//std::cout << "\ty:\t" << y << "\n";
				//std::cout << "\tz:\t" << z << "\n";
				//std::cout << "\tw:\t" << width << "\n";
				//std::cout << "\tx-w:\t" << x - width << "\n";
				//std::cout << "\tBID:\t" << blockID << "\n";
				//std::cout << "\tres:\t" << result << "\n";
				//std::cout << "-----------------\nCCLZ DEBUG END\n-----------------\n\n";

				result = result && (chunk[cw][y][z].getID() == blockID);
			}
			return result;
		}																	
		bool checkChLineX(int z, int y, int x, int width, int blockID)				//		+-------> z
		{																			//		|
			bool result = true;														//		|
			for (int cw = z; cw > z - width; cw--)									//		|
			{																		//		V y
				/*std::cout << "-----------------\nCCLZ DEBUG: \n-----------------\n";
				std::cout << "\tcw:\t" << cw << "\n";
				std::cout << "\tx:\t" << x << "\n";
				std::cout << "\ty:\t" << y << "\n";
				std::cout << "\tz:\t" << z << "\n";
				std::cout << "\tw:\t" << width << "\n";
				std::cout << "\tx-w:\t" << x - width << "\n";
				std::cout << "\tBID:\t" << blockID << "\n";
				std::cout << "\tres:\t" << result << "\n";
				std::cout << "-----------------\nCCLZ DEBUG END\n-----------------\n\n";*/

				result &= chunk[x][y][cw].getID() == blockID;
			}
			return result;
		}
		bool checkChLineY(int x, int z, int y, int width, int blockID)				//		+-------> x
		{																			//		|
			bool result = true;														//		|
			for (int cw = x; cw > x - width; cw--)									//		|
			{																		//		V Z
				result &= chunk[cw][y][z].getID() == blockID;
			}
			return result;
		}
		bool checkMkLine(int x, int y, int width, std::vector<std::vector<bool>> freeMask)
		{
			bool result = true;								
			for (int cw = x; cw > x - width; cw--)									
			{																	
				result &= freeMask[cw][y];
			}
			return result;
		}

		//they has to be in same plane

		void QuadsToGreedyQuads()
		{
			
		}
	public:
		Chunk(glm::vec2 pos = glm::vec2(0,0))
		{
			std::vector<std::vector<std::vector<GameObjects::Block>>> initedChunk(size,
				std::vector<std::vector<GameObjects::Block>>(size,
					std::vector<GameObjects::Block>(size,
						*new GameObjects::Block(0))));

			this->pos = pos;
			//this->texture = texture;

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
		bool isUBlockSolid(int x, int y, int z)
		{
			if (y < 0)
				return false;
			else if (y >= size)
				return false;
			else
				return chunk[x][y - 1][z].getID() != GameObjects::Blocks::AIR;
		}



		Render::Models::DerivedModel* buildChunkModel()
		{
			Render::Models::DerivedModel* ChunkModel = new Render::Models::DerivedModel();
			glm::vec3 pos(this->pos.x, 0, this->pos.y);
			//for (int y = 0; y < size; y++)
			//{
			//	for (int x = 0; x < size; x++)
			//	{
			//		for (int z = 0; z < size; z++)
			//		{
			//			if (chunk[x][y][z].getID() == GameObjects::Blocks::AIR)
			//				continue;
			//			#pragma region Y
			//			if (y == 0) {
			//				continue;
			//				Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y - 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//				//face->setTexture(texture);
			//				face->addRotation(PI / 2, 0.0f, 0.0f);
			//				ChunkModel->addModel(face);
			//			}
			//			else
			//			{
			//				if (chunk[x][y - 1][z].getID() == GameObjects::Blocks::AIR)
			//				{
			//					Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y - 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//					//face->setTexture(texture);
			//					face->addRotation(PI / 2, 0.0f, 0.0f);
			//					ChunkModel->addModel(face);
			//					continue;
			//				}
			//			}
			//			if (y == 16) {
			//				continue;
			//				Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//				//face->setTexture(texture);
			//				face->addRotation(PI / 2, 0.0f, 0.0f);
			//				ChunkModel->addModel(face);
			//			}
			//			else
			//			{
			//				if (chunk[x][y + 1][z].getID() == GameObjects::Blocks::AIR)
			//				{
			//					Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0.5, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//					//face->setTexture(texture);
			//					face->addRotation(PI / 2, 0.0f, 0.0f);
			//					ChunkModel->addModel(face);
			//					continue;
			//				}
			//			}
			//			#pragma endregion
			//			#pragma region Z
			//			if (z == 0)
			//			{
			//				continue;
			//				Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z - 0.5) + glm::vec3(pos.x, 0, pos.y));
			//				//face->setTexture(texture);
			//				ChunkModel->addModel(face);
			//			}
			//			else
			//			{
			//				if (chunk[x][y][z - 1].getID() == GameObjects::Blocks::AIR)
			//				{
			//					Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z - 0.5) + glm::vec3(pos.x, 0, pos.y));
			//					//face->setTexture(texture);
			//					ChunkModel->addModel(face);
			//					continue;
			//				}
			//			}
			//			if (z == 15)
			//			{
			//				continue;
			//				Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z + 0.5f) + glm::vec3(pos.x, 0, pos.y));
			//				//face->setTexture(texture);
			//				ChunkModel->addModel(face);
			//			}
			//			else
			//			{
			//				if (chunk[x][y][z + 1].getID() == GameObjects::Blocks::AIR)
			//				{
			//					Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0, y + 0, z + 0.5) + glm::vec3(pos.x, 0, pos.y));
			//					//face->setTexture(texture);
			//					ChunkModel->addModel(face);
			//					continue;
			//				}
			//			}
			//			#pragma endregion						
			//			#pragma region X
			//			if (x == 0)
			//			{
			//				continue;
			//				Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + -0.5, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//				//face->setTexture(texture);
			//				face->addRotation(0.0f, 0.0f, PI / 2);
			//				ChunkModel->addModel(face);
			//			}
			//			else
			//			{
			//				if (chunk[x - 1][y][z].getID() == GameObjects::Blocks::AIR)
			//				{
			//					Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + -0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//					//face->setTexture(texture);
			//					face->addRotation(0.0f, 0.0f, PI / 2);
			//					ChunkModel->addModel(face);
			//					continue;
			//				}
			//			}
			//			if (x == 15)
			//			{
			//				continue;
			//				Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//				//face->setTexture(texture);
			//				face->addRotation(0.0f, 0.0f, PI / 2);
			//				ChunkModel->addModel(face);
			//			}
			//			else
			//			{
			//				if (chunk[x + 1][y][z].getID() == GameObjects::Blocks::AIR)
			//				{
			//					Render::Models::Model* face = new Render::Models::Quad(glm::vec3(x + 0.5f, y + 0, z + 0) + glm::vec3(pos.x, 0, pos.y));
			//					//face->setTexture(texture);
			//					face->addRotation(0.0f, 0.0f, PI / 2);
			//					ChunkModel->addModel(face);
			//					continue;
			//				}
			//			}
			//			#pragma endregion
			//		}
			//	}
			//}
			
			
			for (int z = 0; z < size; z++) //checking for Z planes
			{
				if (z == 0)
				{
					int x = 0;
					int y = 0;

					std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
					while (y < size)
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (freeMask[x][y] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cx = x;
							int cy = y;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x, y, z - 0.5) + pos, 'z');
							cw++; ch++;
							freeMask[cx][cy] = false;

							while (chunk[cx + 1][cy][z].getID() == currentGreedingBlock.getID() && freeMask[cx + 1][cy])
							{
								builder.addRight();
								cx++; cw++;
								freeMask[cx][cy] = false;

								if (cx == (size - 1))
									break;
							}
							while (checkChLineZ(cx, cy + 1, z, cw, currentGreedingBlock.getID()) && checkMkLine(cx, cy + 1, cw, freeMask))
							{
								builder.addLine();
								cy++; ch++;

								for (int ci = cx; ci > cx - cw; ci--)
								{
									freeMask[ci][cy] = false;
								}

								if (cy == (size - 1))
									break;
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							x = cx;
						}
						else
						{
							x++;
						}
						if (x >= (size - 1)) {
							x = 0;
							y++;
						}
					}
				}
				else if (z == size - 1)
				{
					int x = 0;
					int y = 0;

					std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
					while (y < size)
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (freeMask[x][y] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cx = x;
							int cy = y;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x, y, z + 0.5) + pos, 'z');
							cw++; ch++;
							freeMask[cx][cy] = false;

							while (chunk[cx + 1][cy][z].getID() == currentGreedingBlock.getID() && freeMask[cx + 1][cy])
							{
								builder.addRight();
								cx++; cw++;
								freeMask[cx][cy] = false;

								if (cx == (size - 1))
									break;
							}
							while (checkChLineZ(cx, cy + 1, z, cw, currentGreedingBlock.getID()) && checkMkLine(cx, cy + 1, cw, freeMask))
							{
								builder.addLine();
								cy++; ch++;

								for (int ci = cx; ci > cx - cw; ci--)
								{
									freeMask[ci][cy] = false;
								}

								if (cy == (size - 1))
									break;
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							x = cx;
						}
						else
						{
							x++;
						}
						if (x >= (size - 1)) {
							x = 0;
							y++;
						}
					}
				}
				else
				{
					int x = 0;
					int y = 0;

					std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
					while (y < size) //
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (chunk[x][y][z - 1].getID() == GameObjects::Blocks::AIR && freeMask[x][y] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cx = x;
							int cy = y;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x, y, z - 0.5) + pos, 'z');
							cw++; ch++;
							freeMask[cx][cy] = false;

							while ( chunk[cx + 1][cy][z].getID() == currentGreedingBlock.getID() && freeMask[cx + 1][cy])
							{
								builder.addRight();
								cx++; cw++;
								freeMask[cx][cy] = false;

								if (cx == (size - 1))
									break;
							}
							if (cy + 1 < size)
							{
								while (checkChLineZ(cx, cy + 1, z, cw, currentGreedingBlock.getID()) && checkMkLine(cx, cy + 1, cw, freeMask))
								{
									builder.addLine();
									cy++; ch++;

									for (int ci = cx; ci > cx - cw; ci--)
									{
										freeMask[ci][cy] = false;
									}

									if (cy == 15)
										break;
								}
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							x = cx;
						}
						else
						{
							x++;
						}
						if (x >= (size - 1)) {
							x = 0;
							y++;
						}
					}

					x = 0;
					y = 0;

					freeMask = std::vector<std::vector<bool>>(size, std::vector<bool>(size, true));
					while (y < size) //
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (chunk[x][y][z + 1].getID() == GameObjects::Blocks::AIR && freeMask[x][y] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cx = x;
							int cy = y;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x, y, z + 0.5) + pos, 'z');
							cw++; ch++;
							freeMask[cx][cy] = false;

							while (chunk[cx + 1][cy][z].getID() == currentGreedingBlock.getID() && freeMask[cx + 1][cy])
							{
								builder.addRight();
								cx++; cw++;
								freeMask[cx][cy] = false;

								if (cx == (size - 1))
									break;
							}
							if (cy + 1 < size)
							{
								while (checkChLineZ(cx, cy + 1, z, cw, currentGreedingBlock.getID()) && checkMkLine(cx, cy + 1, cw, freeMask))
								{
									builder.addLine();
									cy++; ch++;

									for (int ci = cx; ci > cx - cw; ci--)
									{
										freeMask[ci][cy] = false;
									}

									if (cy == 15)
										break;
								}
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							x = cx;
						}
						else
						{
							x++;
						}
						if (x >= (size - 1)) {
							x = 0;
							y++;
						}
					}
				}
			}
			for (int x = 0; x < size; x++) //checking for X planes
			{
				if (x == 0)
				{
					int z = 0;
					int y = 0;

					std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
					while (y < size)
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (freeMask[z][y] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cz = z;
							int cy = y;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x - 0.5, y, z) + pos, 'x');
							cw++; ch++;
							freeMask[cz][cy] = false;

							while (chunk[x][cy][cz + 1].getID() == currentGreedingBlock.getID() && freeMask[cz + 1][cy])
							{
								builder.addRight();
								cz++; cw++;
								freeMask[cz][cy] = false;

								if (cz == (size - 1))
									break;
							}
							if (cy + 1 < size)
							{
								while (checkChLineX(cz, cy + 1, x, cw, currentGreedingBlock.getID()) && checkMkLine(cz, cy + 1, cw, freeMask))
								{
									builder.addLine();
									cy++; ch++;

									for (int ci = cz; ci > cz - cw; ci--)
									{
										freeMask[ci][cy] = false;
									}

									if (cy == (size - 1))
										break;
								}
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							z = cz;
						}
						else
						{
							z++;
						}
						if (z >= (size - 1)) {
							z = 0;
							y++;
						}
					}
				}
				else if (x == size - 1)
				{
					int z = 0;
					int y = 0;

					std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
					while (y < size)
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (freeMask[z][y] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cz = z;
							int cy = y;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x + 0.5, y, z) + pos, 'x');
							cw++; ch++;
							freeMask[cz][cy] = false;

							while (chunk[x][cy][cz + 1].getID() == currentGreedingBlock.getID() && freeMask[cz + 1][cy])
							{
								builder.addRight();
								cz++; cw++;
								freeMask[cz][cy] = false;

								if (cz == (size - 1))
									break;
							}
							while (checkChLineX(cz, cy + 1, x, cw, currentGreedingBlock.getID()) && checkMkLine(cz, cy + 1, cw, freeMask))
							{
								builder.addLine();
								cy++; ch++;

								for (int ci = cz; ci > cz - cw; ci--)
								{
									freeMask[ci][cy] = false;
								}

								if (cy == (size - 1))
									break;
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							z = cz;
						}
						else
						{
							z++;
						}
						if (z >= (size - 1)) {
							z = 0;
							y++;
						}
					}
				}
				else
				{
					int z = 0;
					int y = 0;

					std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
					while (y < size)
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (chunk[x - 1][y][z].getID() == GameObjects::Blocks::AIR && freeMask[z][y] && currentGreedingBlock.getID() != GameObjects::AIR)
						{
							int cz = z;
							int cy = y;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x - 0.5, y, z) + pos, 'x');
							cw++; ch++;
							freeMask[cz][cy] = false;

							while (chunk[x - 1][cy][cz + 1].getID() == GameObjects::Blocks::AIR && chunk[x][cy][cz + 1].getID() == currentGreedingBlock.getID() && freeMask[cz + 1][cy])
							{
								builder.addRight();
								cz++; cw++;
								freeMask[cz][cy] = false;

								if (cz == (size - 1))
									break;
							}
							if (cy + 1 < size)
							{
								while (checkChLineX(cz, cy + 1, x - 1, cw, GameObjects::Blocks::AIR) && checkChLineX(cz, cy + 1, x, cw, currentGreedingBlock.getID()) && checkMkLine(cz, cy + 1, cw, freeMask))
								{
									builder.addLine();
									cy++; ch++;

									for (int ci = cz; ci > cz - cw; ci--)
									{
										freeMask[ci][cy] = false;
									}

									if (cy == (size - 1))
										break;
								}
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							z = cz;
						}
						else
						{
							z++;
						}
						if (z >= (size - 1)) {
							z = 0;
							y++;
						}
					}

					z = 0;
					y = 0;

					freeMask = std::vector<std::vector<bool>>(size, std::vector<bool>(size, true));
					while (y < size)
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (chunk[x + 1][y][z].getID() == GameObjects::Blocks::AIR &&freeMask[z][y] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cz = z;
							int cy = y;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x + 0.5, y, z) + pos, 'x');
							cw++; ch++;
							freeMask[cz][cy] = false;

							while (chunk[x + 1][cy][cz + 1].getID() == GameObjects::Blocks::AIR && chunk[x][cy][cz + 1].getID() == currentGreedingBlock.getID() && freeMask[cz + 1][cy])
							{
								builder.addRight();
								cz++; cw++;
								freeMask[cz][cy] = false;

								if (cz == (size - 1))
									break;
							}
							if (cy + 1 < size)
							{
								while (checkChLineX(cz, cy + 1, x + 1, cw, GameObjects::Blocks::AIR) && checkChLineX(cz, cy + 1, x, cw, currentGreedingBlock.getID()) && checkMkLine(cz, cy + 1, cw, freeMask))
								{
									builder.addLine();
									cy++; ch++;

									for (int ci = cz; ci > cz - cw; ci--)
									{
										freeMask[ci][cy] = false;
									}

									if (cy == (size - 1))
										break;
								}
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							z = cz;
						}
						else
						{
							z++;
						}
						if (z >= (size - 1)) {
							z = 0;
							y++;
						}
					}

				}
			}
			for (int y = 0; y < size; y++)
			{
				if (y == 0)
				{
					int x = 0;
					int z = 0;

					std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
					while (z < size)
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (freeMask[x][z] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cx = x;
							int cz = z;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x, y - 0.5, z) + pos, 'y');
							cw++; ch++;
							freeMask[cx][cz] = false;

							while (chunk[cx + 1][y][cz].getID() == currentGreedingBlock.getID() && freeMask[cx + 1][cz])
							{
								builder.addRight();
								cx++; cw++;
								freeMask[cx][cz] = false;

								if (cx == (size - 1))
									break;
							}
							if (cz + 1 < size)
							{
								while (checkChLineY(cx, cz + 1, y, cw, currentGreedingBlock.getID()) && checkMkLine(cx, cz + 1, cw, freeMask))
								{
									builder.addLine();
									cz++; ch++;

									for (int ci = cx; ci > cx - cw; ci--)
									{
										freeMask[ci][cz] = false;
									}

									if (cz == (size - 1))
										break;
								}
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							x = cx;
						}
						else
						{
							x++;
						}
						if (x >= (size - 1)) {
							x = 0;
							z++;
						}
					}
				}
				else if(y == (size - 1))
				{
					int x = 0;
					int z = 0;

					std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
					while (z < size)
					{
						GameObjects::Block currentGreedingBlock = chunk[x][y][z];

						if (freeMask[x][z] && currentGreedingBlock.getID() != GameObjects::AIR)
						{

							int cx = x;
							int cz = z;

							int cw = 0;
							int ch = 0;

							Render::Models::GreedyQuadBuilder builder(glm::vec3(x, y + 0.5, z) + pos, 'y');
							cw++; ch++;
							freeMask[cx][cz] = false;

							while (chunk[cx + 1][y][cz].getID() == currentGreedingBlock.getID() && freeMask[cx + 1][cz])
							{
								builder.addRight();
								cx++; cw++;
								freeMask[cx][cz] = false;

								if (cx == (size - 1))
									break;
							}
							if (cz + 1 < size)
							{
								while (checkChLineY(cx, cz + 1, y, cw, currentGreedingBlock.getID()) && checkMkLine(cx, cz + 1, cw, freeMask))
								{
									builder.addLine();
									cz++; ch++;

									for (int ci = cx; ci > cx - cw; ci--)
									{
										freeMask[ci][cz] = false;
									}

									if (cz == (size - 1))
										break;
								}
							}
							auto model = builder.build();
							model->setUvRepeat(cw, ch);
							ChunkModel->addModel(model);
							x = cx;
						}
						else
						{
							x++;
						}
						if (x >= (size - 1)) {
							x = 0;
							z++;
						}
					}
				}
				else
				{
				int x = 0;
				int z = 0;

				std::vector<std::vector<bool>> freeMask(size, std::vector<bool>(size, true));
				while (z < size)
				{
					GameObjects::Block currentGreedingBlock = chunk[x][y][z];

					if (chunk[x][y - 1][z].getID() == GameObjects::Blocks::AIR && freeMask[x][z] && currentGreedingBlock.getID() != GameObjects::AIR)
					{

						int cx = x;
						int cz = z;

						int cw = 0;
						int ch = 0;

						Render::Models::GreedyQuadBuilder builder(glm::vec3(x, y - 0.5, z) + pos, 'y');
						cw++; ch++;
						freeMask[cx][cz] = false;

						while (chunk[cx + 1][y - 1][cz].getID() == GameObjects::Blocks::AIR && chunk[cx + 1][y][cz].getID() == currentGreedingBlock.getID() && freeMask[cx + 1][cz])
						{
							builder.addRight();
							cx++; cw++;
							freeMask[cx][cz] = false;

							if (cx == (size - 1))
								break;
						}
						if (cz + 1 < size)
						{
							while (checkChLineY(cx, cz + 1, y - 1, cw, GameObjects::Blocks::AIR) && checkChLineY(cx, cz + 1, y, cw, currentGreedingBlock.getID()) && checkMkLine(cx, cz + 1, cw, freeMask))
							{
								builder.addLine();
								cz++; ch++;

								for (int ci = cx; ci > cx - cw; ci--)
								{
									freeMask[ci][cz] = false;
								}

								if (cz == (size - 1))
									break;
							}
						}
						auto model = builder.build();
						model->setUvRepeat(cw, ch);
						ChunkModel->addModel(model);
						x = cx;
					}
					else
					{
						x++;
					}
					if (x >= (size - 1)) {
						x = 0;
						z++;
					}
				}

				x = 0;
				z = 0;

				freeMask = std::vector<std::vector<bool>>(size, std::vector<bool>(size, true));
				while (z < size)
				{
					GameObjects::Block currentGreedingBlock = chunk[x][y][z];

					if (chunk[x][y + 1][z].getID() == GameObjects::Blocks::AIR && freeMask[x][z] && currentGreedingBlock.getID() != GameObjects::AIR)
					{

						int cx = x;
						int cz = z;

						int cw = 0;
						int ch = 0;

						Render::Models::GreedyQuadBuilder builder(glm::vec3(x, y + 0.5, z) + pos, 'y');
						cw++; ch++;
						freeMask[cx][cz] = false;

						while (chunk[cx + 1][y + 1][cz].getID() == GameObjects::Blocks::AIR && chunk[cx + 1][y][cz].getID() == currentGreedingBlock.getID() && freeMask[cx + 1][cz])
						{
							builder.addRight();
							cx++; cw++;
							freeMask[cx][cz] = false;

							if (cx == (size - 1))
								break;
						}
						if (cz + 1 < size)
						{
							while (checkChLineY(cx, cz + 1, y + 1, cw, GameObjects::Blocks::AIR) && checkChLineY(cx, cz + 1, y, cw, currentGreedingBlock.getID()) && checkMkLine(cx, cz + 1, cw, freeMask))
							{
								builder.addLine();
								cz++; ch++;

								for (int ci = cx; ci > cx - cw; ci--)
								{
									freeMask[ci][cz] = false;
								}

								if (cz == (size - 1))
									break;
							}
						}
						auto model = builder.build();
						model->setUvRepeat(cw, ch);
						ChunkModel->addModel(model);
						//ChunkModel->addModel(builder.build());
						x = cx;
					}
					else
					{
						x++;
					}
					if (x >= (size - 1)) {
						x = 0;
						z++;
					}
				}
				}
			}

			printf("small models: %d", ChunkModel->size());

			return ChunkModel;
		}
	};
}