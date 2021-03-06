//
// Created by marco on 1/9/19.
//

#include <fstream>
#include <sstream>
#include <SDL_log.h>
#include "Shader.h"

bool Shader::CompileShader(const std::string &fileName,
                           GLenum shaderType,
                           GLuint &outShader) {
    // Open file
    std::ifstream shaderFile(fileName);

    if (shaderFile.is_open()) {
        // Read all the text into a string
        std::stringstream sstream;
        sstream << shaderFile.rdbuf();
        std::string contents = sstream.str();
        const char* contentsChar = contents.c_str();

        // Create a shader of the specified type
        outShader = glCreateShader(shaderType);

        // Set the source characters and try to compile
        glShaderSource(outShader, 1, &(contentsChar), nullptr);
        glCompileShader(outShader);

        if (!IsCompiled(outShader)) {
            SDL_Log("Failed to compile shader %s", fileName.c_str());
            return false;
        }
    }
    else {
        SDL_Log("Shader file not found: %s", fileName.c_str());
        return false;
    }
    return true;
}

bool Shader::IsCompiled(GLuint shader) {
    GLint status;

    // Query the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL Compile Failed:\n%s", buffer);
        return false;
    }
    return true;
}

bool Shader::IsValidProgram() {
    GLint status;

    // Query the program status
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
        SDL_Log("GLSL Program Failed:\n%s", buffer);
        return false;
    }
    return true;
}

bool Shader::Load(const std::string &vertName,
                  const std::string &fragName) {
    // Compile vertex and fragment shaders
    if (!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader)||
            !CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader)) {
        return false;
    }

    // Now create a shader program that
    // links together the vertex/frag shaders
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, mVertexShader);
    glAttachShader(mShaderProgram, mFragShader);
    glLinkProgram(mShaderProgram);

    // Verify that the program linked successfully
    if (!IsValidProgram()) {
        return false;
    }
    return true;
}

void Shader::SetActive() {
    glUseProgram(mShaderProgram);
}

void Shader::Unload() {
    glDeleteProgram(mShaderProgram);
    glDeleteShader(mVertexShader);
    glDeleteShader(mFragShader);
}