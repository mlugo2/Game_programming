//
// Created by marco on 12/30/18.
//

#include "Game.h"

Game::Game() {
    mWindow = nullptr;
    mIsRunning = true;
}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    // If non-zero, initialization failed
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // We have succeeded, let's created a window
    mWindow = SDL_CreateWindow(
            "Game Programming in C++",
            100,
            100,
            1024,
            768,
            0
            );

    // Let's see if the window was created..
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    // Ok ok, we got a window, now we need to render inside it
    mRenderer = SDL_CreateRenderer(
            mWindow,    // Window to create renderer for
            -1,         // Usually -1
            SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
            );

    // Let's check this too!
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    // Let the game begin :)
    return true;
}

void Game::RunLoop() {
    while(mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown() {
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;

    // While there are still events in the queue
    while (SDL_PollEvent(&event)) {
        // Handle different event types here
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }

    // Get state of keyboard
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
}

void Game::UpdateGame() {}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(
            mRenderer,
            0,  // R
            0,  // G
            255,    // B
            255     // A
            );
    SDL_RenderClear(mRenderer);

    // Draw game scene here..

    SDL_RenderPresent(mRenderer);
}