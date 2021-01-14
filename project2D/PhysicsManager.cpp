#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::Instance = nullptr;
float PhysicsManager::gravity = 9.8;

void PhysicsManager::RegisterRigidBody(Rigidbody* col){
	rigidbodies.push(col);
}

void PhysicsManager::RemoveRigidbody(Rigidbody* col){
	rigidbodies.remove(col);
}

void PhysicsManager::update(float deltaTime){
	for(int i = 0; i < rigidbodies.length; ++i){
		Rigidbody* r = rigidbodies[i];
		if(r->useGravity)
			r->velocity -= (Vector2::up() * gravity);
			
		r->getParent().transform.Position += r->velocity * deltaTime;
	}
}

void PhysicsManager::draw(aie::Renderer2D& renderer){}

PhysicsManager::PhysicsManager(){
	if(Instance)throw "There is Already a Instance of the Collision Manager";
	Instance = this;
}


PhysicsManager::~PhysicsManager(){
	printf("Destroying Physics Manager");
	Instance = nullptr;
}
