//
// Created by marco on 12/30/18.
//

#include <algorithm>
#include "Game.h"
#include "Actor.h"

Game::Game() {
    mWindow = nullptr;
    mIsRunning = true;

    // Pong specific
    mPaddlePos.x = 15.0f;
    mPaddlePos.y = 500.0f;

    mBallPos.x = 500.0f;
    mBallPos.y = 500.0f;

    mTicksCount = 0;

    mBallVel.x = -200.0f;
    mBallVel.y = -235.0f;
}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    // If non-zero, initialization failed
    if (sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    // Use the core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    // Specify version 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Request a color buffer with 8-bits per RGBA channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // Force OpenGL to use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    // We have succeeded, let's created a window
    mWindow = SDL_CreateWindow(
            "Game Programming in C++",
            100,
            100,
            1024,
            768,
            SDL_WINDOW_OPENGL
            );

    // Let's see if the window was created..
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mContext = SDL_GL_CreateContext(mWindow);

    // Initialize GLEW
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        SDL_Log("Failed to initialize GLEW.");
        return false;
    }

    // On some platforms, GLEW will emit a benign error code
    // so clear it.
    glGetError();

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    LoadData();

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
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;
    mPaddleDir = 0;

    // While there are still events in the queue
    while (SDL_PollEvent(&event)) {
        // Handle different event types here
        switch (event.type) {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                break;
        }
    }

    // Get state of keyboard
    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    // If escape is pressed, also end loop
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

    // Handle left paddle controls
    if (state[SDL_SCANCODE_W]) {
        mPaddleDir += -1;
    }

    if (state[SDL_SCANCODE_S]) {
        mPaddleDir += 1;
    }
}

void Game::UpdateGame() {

    // Frame limiting
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount+16));

    // Delta time is the difference in ticks form last
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount)/1000.0f;

    // Update tick count for next frame
    mTicksCount = SDL_GetTicks();

    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    // Update all actors
    mUpdatingActors = true;

    for (auto actor : mActors) {
        actor->Update(deltaTime);
    }

    mUpdatingActors = false;

    // Move any pending actors to mActors
    for (auto pending : mPendingActors) {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    // Add any dead actors to a temp vector
    std::vector<Actor*>deadActors;
    for (auto actor : mActors) {
        if (actor->GetState() == Actor::State::EDead) {
            deadActors.emplace_back(actor);
        }
    }

    // Delete dead actors (which removes them from mActors)
    for (auto actor : deadActors) {
        delete actor;
    }

}

void Game::GenerateOutput() {

    // Set the clear color to gray
    glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // todo Draw game scene here..

    // Swap the buffers, which also displays the scene
    SDL_GL_SwapWindow(mWindow);
}

void Game::LoadData() {

}

void Game::UnloadData() {

}

void Game::AddActor(Actor *actor) {
    // If updating actors, need to add to pending
    if (mUpdatingActors) {
        mPendingActors.emplace_back(actor);
    }
    else {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor *actor) {
    // Is it pending actors?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);

    if (iter != mPendingActors.end()) {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end()-1);
        mPendingActors.pop_back();
    }

    // Is it in actors?
    iter = std::find(mActors.begin(), mActors.end(), actor);

    if (iter != mActors.end()) {
        std::iter_swap(iter, mActors.end()-1);
        mActors.pop_back();
    }

}