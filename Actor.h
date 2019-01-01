//
// Created by marco on 12/31/18.
//

#ifndef GAME_PROGRAMMING_ACTOR_H
#define GAME_PROGRAMMING_ACTOR_H


#include <vector>
#include "Math.h"

class Actor {
public:
    enum class State {
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game* game);
    virtual ~Actor();

    // Update function called from Game (not overridable)
    void Update(float deltaTime);
    // Updates all the components attached to the actor (n.o.)
    void UpdateComponents(float deltaTime);
    // Any actor-specific update code (n.o.)
    virtual void UpdateActor(float deltaTime);

    // Getters/setters
    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }
    float GetScale() const { return mScale; }
    void SetScale(const float scale) { mScale = scale; }
    float GetRotation() const { return mRotation; }
    void SetRotation(const float rotaion) { mRotation = rotaion; }

    State GetState() const { return mState; }
    void SetState(const State state) { mState = state; }

    // Add/remove components
    void AddComponent(class Component* component);
    void RemoveComponent(class Component *component);

private:

    // Actor's state
    State mState;

    // Transform
    Vector2 mPosition;
    float mScale;
    float mRotation;

    std::vector<class Component*> mComponents;
    class Game* mGame;
};


#endif //GAME_PROGRAMMING_ACTOR_H
