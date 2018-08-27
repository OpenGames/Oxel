#pragma once
#include <fstream>
#include <GL/glew.h>
namespace OpenGames::Oxel::Render
{
	class ShaderLoader
	{
		static GLchar* readFile(const char* filename) {
			std::ifstream file(filename);
			std::string code((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
			size_t codeLength = code.length() + 1;
			GLchar* buffer = new GLchar[codeLength];
			strcpy_s(buffer, codeLength, code.c_str());
			return buffer;
		}
		static GLuint makeShader(GLuint shaderId, GLchar* shaderSource)
		{
			glShaderSource(shaderId, 1, &shaderSource, NULL);
			glCompileShader(shaderId);
			GLint compilationResult = 0;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationResult);
			if(compilationResult == GL_FALSE)
			{
				GLchar infoLog[1024];
				glGetShaderInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
				printf(infoLog);
			}
			return shaderId;
		}
	public:
		static GLuint compileShader(GLenum shaderType, const char* fileName)
		{
			return makeShader(glCreateShader(shaderType), readFile(fileName));
		}
		static GLuint createProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
		{
			GLuint shaderProgramId = glCreateProgram();
			glAttachShader(shaderProgramId, vertexShaderId);
			glAttachShader(shaderProgramId, fragmentShaderId);
			glLinkProgram(shaderProgramId);
			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);
			return shaderProgramId;
		}
	};
}