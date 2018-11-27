#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <GL/glew.h>
#include "Array.cpp"
#define PI 3.14159265359f
namespace OpenGames::Oxel::Render::Models
{
	class Model
	{
	protected:
		GLuint vao;
		GLuint texture;
		Math::Array<GLuint> vbo;
		glm::mat4 model = glm::mat4(1.0f);
		glm::quat model_orientation_quaternion;
		glm::vec3 model_orientation = glm::vec3(1.0f, 0.0f, 0.0f);	//a point (direction) the model is looking at
																	//absolute orientation (zero-rotation-orientation) is always X:1 Y:0 Z:0
																	//probably need to make this a constant

		float model_orientation_angle = 0.0f;

		float model_scale_x = 1.0f;
		float model_scale_y = 1.0f;
		float model_scale_z = 1.0f;
	public:
		glm::vec3 position;
		Model(glm::vec3 position) : position(position)
		{
			model_orientation_quaternion = glm::angleAxis(glm::degrees(model_orientation_angle), model_orientation);
		}
		virtual ~Model()
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers((GLsizei)vbo.size(), &vbo[0]);
			delete &vbo;
		}
		virtual void draw() {}

		void setTexture(GLuint texture)
		{
			this->texture = texture;
		}
		virtual void addRotation(float ang, glm::vec3 axis)
		{
			model_orientation_quaternion = model_orientation_quaternion * glm::angleAxis(ang, axis);
			model_orientation_angle = acos(model_orientation_quaternion.w);
		}
		virtual void addRotation(float ang, glm::vec3 look_at, bool spec)
		{
			look_at = glm::normalize(look_at);
			model_orientation = look_at;

			float XY = glm::acos(glm::sqrt(model_orientation.x*model_orientation.x + model_orientation.z*model_orientation.z));
			float XZ = glm::acos(model_orientation.x)*glm::sign(model_orientation.z);

			addRotation(XY, glm::vec3(0.0f, 0.0f, 1.0f)); //rising on XY
			addRotation(XZ, glm::vec3(0.0f, 1.0f, 0.0f)); //rising on XZ
			addRotation(ang, model_orientation);
		}
		virtual void addRotation(float ang, float xy, float xz)
		{
			//look_at = glm::normalize(look_at);
			//model_orientation = look_at;
			model_orientation.x = glm::cos(xz)*glm::cos(xy);
			model_orientation.z = glm::sin(xz)*glm::cos(xy);
			model_orientation.y = glm::sin(xy);

			float XY = xy; // glm::acos(glm::sqrt(model_orientation.x*model_orientation.x + model_orientation.z*model_orientation.z));
			float XZ = xz; // glm::acos(model_orientation.x)*glm::sign(model_orientation.z);

			addRotation(XY, glm::vec3(0.0f, 0.0f, 1.0f)); //rising on XY
			addRotation(XZ, glm::vec3(0.0f, 1.0f, 0.0f)); //rising on XZ
			addRotation(ang, model_orientation);
		}
		virtual void scale(float x, float y, float z)
		{
			model_scale_x *= x;
			model_scale_y *= y;
			model_scale_z *= z;
		}
		virtual const glm::mat4 getModelMatrix()
		{		
			//auto Cmodel = model;

			/*std::cout << std::endl;
			std::cout << "-------------------------" << std::endl;
			std::cout << Cmodel[0][0] << " " << Cmodel[0][1] << " " << Cmodel[0][2] << " " << Cmodel[0][3] << std::endl;
			std::cout << Cmodel[1][0] << " " << Cmodel[1][1] << " " << Cmodel[1][2] << " " << Cmodel[1][3] << std::endl;
			std::cout << Cmodel[2][0] << " " << Cmodel[2][1] << " " << Cmodel[2][2] << " " << Cmodel[2][3] << std::endl;
			std::cout << Cmodel[3][0] << " " << Cmodel[3][1] << " " << Cmodel[3][2] << " " << Cmodel[3][3] << std::endl;
			std::cout << "-------------------------" << std::endl;
			std::cout << std::endl;*/

			auto rotation_matrix_model = glm::toMat4(model_orientation_quaternion);
			auto translation_matrix_model = glm::translate(model, position);
			auto scale_matrix_model = glm::mat4(1.0f);

			scale_matrix_model[0][0] = model_scale_x;
			scale_matrix_model[1][1] = model_scale_y;
			scale_matrix_model[2][2] = model_scale_z;

			/*std::cout << std::endl;
			std::cout << "-------------------------" << std::endl;
			std::cout << Cmodel[0][0] << " " << Cmodel[0][1] << " " << Cmodel[0][2] << " " << Cmodel[0][3] << std::endl;
			std::cout << Cmodel[1][0] << " " << Cmodel[1][1] << " " << Cmodel[1][2] << " " << Cmodel[1][3] << std::endl;
			std::cout << Cmodel[2][0] << " " << Cmodel[2][1] << " " << Cmodel[2][2] << " " << Cmodel[2][3] << std::endl;
			std::cout << Cmodel[3][0] << " " << Cmodel[3][1] << " " << Cmodel[3][2] << " " << Cmodel[3][3] << std::endl;
			std::cout << "-------------------------" << std::endl;
			std::cout << std::endl;*/

			//int c = 0;

			//std::cin >> c;
			return (translation_matrix_model * rotation_matrix_model * scale_matrix_model);
		}

		virtual inline GLuint getVao() { return vao; }
		virtual inline const Math::Array<GLuint>& getVbo() { return vbo; }
	};
	class DerivedModel
	{
	protected:
		Math::Array<Model*> models;
		glm::vec3 position;

	public:
		virtual glm::vec3 getPosition()
		{
			return position;
		}
		virtual inline void addModel(Model* m)
		{
			models.pushBack(m);
		}
		virtual inline int size()
		{
			return models.size();
		}
		virtual void draw(int index) {
			models[index]->draw();
		}
		virtual const glm::mat4 getModelMatrix(int index) {
			return models[index]->getModelMatrix();
		}
		virtual inline GLuint getVao(int index) {
			return models[index]->getVao();
		}
		virtual inline const Math::Array<GLuint>& getVbo(int index) {
			return models[index]->getVbo();
		}
	};
}