//
// Created by marco on 12/30/18.
//

#ifndef GAME_PROGRAMMING_GAME_H
#define GAME_PROGRAMMING_GAME_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include "Math.h"
#include "Actor.h"

class Game {

public:
    Game();

    // Initialize the game
    bool Initialize();
    // Runs the game loop until the game is over
    void RunLoop();
    // Shutdown the game
    void Shutdown();

    void AddActor(Actor *actor);
    void RemoveActor(Actor *actor);

private:

    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    // Window created by SDL
    SDL_Window* mWindow;

    // SDL GLContext
    SDL_GLContext mContext;

    Uint32 mTicksCount;


    // Game should continue to run
    bool mIsRunning;
    bool mUpdatingActors;

    // Actors
    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;

    // Pong specific
    Vector2 mPaddlePos;
    Vector2 mBallPos;
    Sint32 mPaddleDir;
    Vector2 mBallVel;
};


#endif //GAME_PROGRAMMING_GAME_H
