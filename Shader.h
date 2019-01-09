//
// Created by marco on 1/9/19.
//

#ifndef GAME_PROGRAMMING_SHADER_H
#define GAME_PROGRAMMING_SHADER_H


#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader();
    ~Shader();

    // Load the vertex/fragment shaders with the given names
    bool Load(const std::string& vertName,
            const std::string& fragName);
    void Unload();

    // Set this as the active shader program
    void SetActive();

private:
    // Tries to compile the specified shader
    bool CompileShader(const std::string& fileName,
                    GLenum shaderType, GLuint& outShader);
    // Test whether shader compiled successfully
    bool IsCompiled(GLuint shader);
    // Test whether vertex/fragment programs link
    bool IsValidProgram();
    // Store the shader object IDs
    GLuint mVertexShader;
    GLuint mFragShader;
    GLuint mShaderProgram;

};


#endif //GAME_PROGRAMMING_SHADER_H
