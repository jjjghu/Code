#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>;

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Shader
{
private:
	std::string LoadShaderSrc(const char* path)
	{
		try
		{
			std::ifstream shaderFile;
			std::stringstream shaderStream;
			std::string shaderCode;
			shaderFile.open(path);
			if (shaderFile.is_open())
			{
				shaderStream << shaderFile.rdbuf();
				shaderCode = shaderStream.str();
			}
			return shaderCode;
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		return "";
	}
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath)
	{

		int success;
		char infoLog[512];

		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vShaderSrc = LoadShaderSrc(vertexPath);
		std::string fShaderSrc = LoadShaderSrc(fragmentPath);
		
		const GLchar* vShaderCode = vShaderSrc.c_str();
		const GLchar* fShaderCode = fShaderSrc.c_str();


		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}


		// create program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}
	void use()
	{
		glUseProgram(ID);
	}
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	~Shader()
	{
		glDeleteProgram(ID);
	}
};
#endif