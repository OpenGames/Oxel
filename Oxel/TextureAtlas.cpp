#pragma once
#include <iostream>
#include <GL/glew.h>
#include "ContentPipe.cpp"

namespace OpenGames::Oxel::Render::Textures
{
	class Atlas
	{
	private:
		
	public:
		GLuint AtlasTexture;

		Atlas() {

		}
		void LoadAtlas(const char* filename)
		{
			AtlasTexture = ContentPipe::loadTexture(filename, GL_NEAREST);
		}

	};
}