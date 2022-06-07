#include "le3_shader.h"
#include "le3_print.h"

LE3Shader::LE3Shader() : m_program(0)
{

}

void LE3Shader::CompileShader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    GLuint vertexShader = CreateShader(vertexShaderPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = CreateShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    // Check if linking succeeded
    GLint status;
    glGetProgramiv(m_program, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        char infoLog[SHADER_ERROR_BUFFER_SIZE];
        glGetProgramInfoLog(m_program, SHADER_ERROR_BUFFER_SIZE, nullptr, infoLog);
        #ifndef NDEBUG
        PrintTitle("Shader Linking Error");
        std::cout << "An error occuured while linking shader." << std::endl;
        std::cout << "The following message was returned:" << std::endl;
        std::cout << infoLog << std::endl;
        #endif
    }

    // Mark shaders for deletion
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint LE3Shader::CreateShader(std::string filePath, GLenum type)
{
    if (!std::filesystem::exists(filePath))
    {
        #ifndef NDEBUG
        PrintTitle("Shader Compile Error");
        std::cout << "File does not exists:\t" << filePath << std::endl;
        #endif
        return 0;
    }
    std::string shaderSourceString = LE3Shader::ReadShaderFile(filePath);
    const char* shaderSource = shaderSourceString.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // Check if compiling succeeded
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char infoLog[SHADER_ERROR_BUFFER_SIZE];
        glGetShaderInfoLog(shader, SHADER_ERROR_BUFFER_SIZE, nullptr, infoLog);
        #ifndef NDEBUG
        PrintTitle("Shader Compile Error");
        std::cout << "An error occuured while compiling shader:\t" << filePath << std::endl;
        std::cout << "The following message was returned:" << std::endl;
        std::cout << infoLog << std::endl;
        #endif
    }

    return shader;
}

std::string LE3Shader::ReadShaderFile(std::string filePath)
{
    std::ifstream ifs(filePath);
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    return buffer.str();
}

void LE3Shader::Use()
{
    glUseProgram(m_program);
}

void LE3Shader::Delete()
{
    glDeleteProgram(m_program);
}

GLint LE3Shader::GetUniformLocation(std::string uniformName)
{
    // If this a new uniform, ask the shader program and update internaly
    if (m_uniformLocation.find(uniformName) == m_uniformLocation.end())
    {
        GLint loc = glGetUniformLocation(m_program, uniformName.c_str());
        m_uniformLocation[uniformName] = loc;
    }
    return m_uniformLocation[uniformName];
}

void LE3Shader::Uniform(std::string uniformName, glm::vec4 v)
{
    GLint loc = GetUniformLocation(uniformName);
    glUniform4f(loc, v.x, v.y, v.z, v.w);
}

void LE3Shader::Uniform(std::string uniformName, glm::mat4 m)
{
    GLint loc = GetUniformLocation(uniformName);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}