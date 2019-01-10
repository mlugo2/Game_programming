//
// Created by marco on 1/9/19.
//

#ifndef GAME_PROGRAMMING_TEXTURE_H
#define GAME_PROGRAMMING_TEXTURE_H

#include <string>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

class Texture {
public:
    Texture();
    ~Texture();

    bool Load(const std::string& fileName);
    void Unload();

    void SetActive();

    int GetWidth() const { return mWidth; }
    int GetHeight() const { return mHeight; }

private:
    unsigned int mTextureID;
    int mWidth;
    int mHeight;
};


#endif //GAME_PROGRAMMING_TEXTURE_H
