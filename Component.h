//
// Created by marco on 12/31/18.
//

#ifndef GAME_PROGRAMMING_COMPONENT_H
#define GAME_PROGRAMMING_COMPONENT_H

#include <cstdint>

class Component {
public:
    // Constructor
    // (the lower the update order, the earlier the component updates)
    Component (class Actor* owner, int updateOrder = 100);
    // Destructor
    virtual ~Component();
    // Update this component by delta time
    virtual void Update(float deltaTime);
    // Process input for this component
    virtual void ProcessInput(const uint8_t* keystate) {}
    // Called when world transform changes
    virtual void OnUpdateWorldTransform() {}

    int GetUpdateOrder() const { return mUpdateOrder; }

protected:
    // Owning actor
    class Actor* mOwner;
    // Update order of component
    int mUpdateOrder;
};

#endif //GAME_PROGRAMMING_COMPONENT_H
