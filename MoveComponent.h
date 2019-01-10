//
// Created by marco on 1/9/19.
//

#ifndef GAME_PROGRAMMING_MOVECOMPONENT_H
#define GAME_PROGRAMMING_MOVECOMPONENT_H

#include "Component.h"

class MoveComponent : public Component {
public:
    // Lower update order to update first
    MoveComponent(class Actor* owner, int updateOrder = 10);
    void Update(float deltaTime) override;

    float GetAngularSpeed() const { return mAngularSpeed; }
    float GetForwardSpeed() const { return mForwardSpeed; }
    void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
    void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

private:
    float mAngularSpeed;
    float mForwardSpeed;
};


#endif //GAME_PROGRAMMING_MOVECOMPONENT_H
