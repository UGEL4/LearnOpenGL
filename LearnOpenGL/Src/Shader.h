#pragma once

#include <string>
#include "gl_inf.h"

enum class ShaderType
{
	VERTIEX_SHADER,
	FRAMGMENT_SHADER
};

struct ShaderSource
{
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();
	void PraseShader(const std::string& vertexPath, const std::string& fragmentPath);
	unsigned int CreateShader();
	void CreateGeometryShader(const std::string& path);
	unsigned int CompileShader(unsigned int type, const std::string& shaderSource);
	void IsShaderCompiled(unsigned int shader);
	void Bind();
	void Unbind();

	void SetUniformMatrix4fv(const char* name, glm::mat4& mat, bool transpose = false);
	void SetUniform3fv(const char* name, const glm::vec3& val);
	void SetUniform3fv(const char* name, float x, float y, float z);
	void SetUniform1f(const char* name, float val);
	void SetUniform1i(const char* name, int val);

	inline unsigned int GetShader() const { return m_ShaderID; }

private:
	ShaderSource m_Source;
	unsigned int m_ShaderID;
};