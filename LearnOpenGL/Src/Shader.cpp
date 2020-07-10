#include "Shader.h"
#include <sstream>
#include <iostream>
#include<fstream>

Shader::Shader(const std::string& vertiexPath, const std::string& fragmentPath)
	:m_ShaderID(0)
{
	PraseShader(vertiexPath, fragmentPath);
	m_ShaderID = CreateShader();
}

Shader::~Shader()
{
	GLCALL(glDeleteProgram(m_ShaderID));
}

void Shader::PraseShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::ifstream vertexFile(vertexPath);
	std::ifstream fragmentFile(fragmentPath);
	try
	{
		if (!vertexFile.is_open() || !fragmentFile.is_open())
		{
			throw std::exception("shader file open failed!");
		}
		std::stringstream ss;
		ss << vertexFile.rdbuf();
		m_Source.VertexShaderSource = ss.str();
		ss.clear();
		ss.str("");
		ss << fragmentFile.rdbuf();
		m_Source.FragmentShaderSource = ss.str();
		//std::cout << "vertex:\n" << m_Source.VertexShaderSource << "\n frag:\n" << m_Source.FragmentShaderSource << std::endl;

		vertexFile.close();
		fragmentFile.close();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

unsigned int Shader::CreateShader()
{

	unsigned int program = glCreateProgram();
	/*GLenum e = glGetError();
	const unsigned char* error = gluErrorString(e);
	std::cout << error << std::endl;*/
	unsigned int vs = CompileShader(GL_VERTEX_SHADER,m_Source.VertexShaderSource);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,m_Source.FragmentShaderSource);
	GLCALL(glAttachShader(program, vs));
	GLCALL(glAttachShader(program, fs));
	GLCALL(glLinkProgram(program));
	GLCALL(glValidateProgram(program));
	GLCALL(glDeleteShader(vs));
	GLCALL(glDeleteShader(fs));

	return program;
}

void Shader::CreateGeometryShader(const std::string& path)
{
	std::ifstream File(path);
	std::string source;
	try
	{
		if (!File.is_open())
		{
			throw std::exception("shader file open failed!");
		}
		std::stringstream ss;
		ss << File.rdbuf();
		source = ss.str();

		File.close();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return;
	}

	unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, source);
	GLCALL(glAttachShader(m_ShaderID, gs));
	GLCALL(glLinkProgram(m_ShaderID));
	GLCALL(glDeleteShader(gs));
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& shaderSource)
{
	unsigned int id = glCreateShader(type);
	const char* source = shaderSource.c_str();
	GLCALL(glShaderSource(id, 1, &source, nullptr));
	GLCALL(glCompileShader(id));
	IsShaderCompiled(id);
	return id;
}

void Shader::IsShaderCompiled(unsigned int shader)
{
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout <<  message << std::endl;
	}
}

void Shader::Bind()
{
	GLCALL(glUseProgram(m_ShaderID));
}

void Shader::Unbind()
{
	GLCALL(glUseProgram(0));
}

void Shader::SetUniformMatrix4fv(const char* name, glm::mat4& mat, bool transpose)
{
	int location = glGetUniformLocation(m_ShaderID, name);
	ASSERT(location != -1);
	GLCALL(glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(mat)));
}

void Shader::SetUniform3fv(const char* name, float x, float y, float z)
{
	int location = glGetUniformLocation(m_ShaderID, name);
	const float val[] = { x, y, z };
	//ASSERT(location != -1);
	GLCALL(glUniform3fv(location, 1, &val[0]));
}

void Shader::SetUniform3fv(const char* name, const glm::vec3& val)
{
	SetUniform3fv(name, val.x, val.y, val.z);
}

void Shader::SetUniform1f(const char* name, float val)
{
	int location = glGetUniformLocation(m_ShaderID, name);
	ASSERT(location != -1);
	GLCALL(glUniform1f(location, val));
}

void Shader::SetUniform1i(const char* name, int val)
{
	int location = glGetUniformLocation(m_ShaderID, name);
	//ASSERT(location != -1);
	GLCALL(glUniform1i(location, val));
}
