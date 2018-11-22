#pragma once
#include <vector>
#include "Model.cpp"
#include "Quad.cpp"
namespace OpenGames::Oxel::Render::Models
{
	class Block : public DerivedModel
	{
	public:
		Block(glm::vec3 position, GLuint texture)// : Model(position)
		{
			this->position = position;

			this->addModel(new Render::Models::Quad((glm::vec3(-0.5f,  0.0f,  0.0f) + position)));
			this->addModel(new Render::Models::Quad((glm::vec3( 0.5f,  0.0f,  0.0f) + position)));
			this->addModel(new Render::Models::Quad((glm::vec3( 0.0f, -0.5f,  0.0f) + position)));
			this->addModel(new Render::Models::Quad((glm::vec3( 0.0f,  0.5f,  0.0f) + position)));
			this->addModel(new Render::Models::Quad((glm::vec3( 0.0f,  0.0f, -0.5f) + position)));
			this->addModel(new Render::Models::Quad((glm::vec3( 0.0f,  0.0f,  0.5f) + position)));

			models[0]->setTexture(texture);
			models[1]->setTexture(texture);
			models[2]->setTexture(texture);
			models[3]->setTexture(texture);
			models[4]->setTexture(texture);
			models[5]->setTexture(texture);

			models[0]->addRotation(0.0f, 0.0f, PI/2);
			models[1]->addRotation(0.0f, 0.0f, PI/2);
			models[2]->addRotation(PI/2, 0.0f, 0.0f);
			models[3]->addRotation(PI/2, 0.0f, 0.0f);
		}
	};
}