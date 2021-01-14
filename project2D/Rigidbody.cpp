#include "Rigidbody.h"
#include "PhysicsManager.h"

Symbol Rigidbody::type = Symbol("Rigidbody");

Rigidbody::Rigidbody(GameObject& parent, Vector2 initialVelocity, bool useGravity): Component(parent), useGravity(useGravity){
    if(PhysicsManager::Instance != nullptr)
        PhysicsManager::Instance->RegisterRigidBody(this);
    velocity = initialVelocity;
    mass = 1;
    elasticity = 1;
}

Rigidbody::~Rigidbody(){
    if(PhysicsManager::Instance != nullptr)
        PhysicsManager::Instance->RemoveRigidbody(this);
}