#pragma once
#include <Gl/glew.h>
namespace OpenGames::Oxel::Render
{
	struct Vertex
	{
		GLfloat position[3];
		GLfloat uv[2];
	};
}