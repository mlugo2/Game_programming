//
// Created by marco on 12/31/18.
//

#include "Component.h"
#include "Actor.h"

Component::Component(class Actor *owner, int updateOrder)
        :mOwner(owner)
        ,mUpdateOrder(updateOrder)
{
    // Add to actor's vector of components
    mOwner->AddComponent(this);
}

Component::~Component() {
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {

}
