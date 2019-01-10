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
    const Vector3& GetPosition() const { return mPosition; }
    void SetPosition(const Vector3& pos) { mPosition = pos; }
    float GetScale() const { return mScale; }
    void SetScale(const float scale) { mScale = scale; }
    Quaternion GetRotation() const { return mRotation; }
    void SetRotation(const Quaternion rotation) { mRotation = rotation; }

    Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

    State GetState() const { return mState; }
    void SetState(const State state) { mState = state; }

    // Add/remove components
    void AddComponent(class Component* component);
    void RemoveComponent(class Component *component);

private:

    // Actor's state
    State mState;

    // Transform
    Vector3 mPosition;
    Quaternion mRotation;
    float mScale;

    std::vector<class Component*> mComponents;
    class Game* mGame;
};


#endif //GAME_PROGRAMMING_ACTOR_H
