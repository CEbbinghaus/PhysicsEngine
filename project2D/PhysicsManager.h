#pragma once
#include "Master.h"
#include "atyp_Array.h"
#include "Rigidbody.h"

class PhysicsManager : public Manager{
	Array<Rigidbody*> rigidbodies;
public:
	static float gravity;
	static PhysicsManager* Instance;

	void RegisterRigidBody(Rigidbody*);
	void RemoveRigidbody(Rigidbody*);

	void update(float);
	void draw(aie::Renderer2D&);

	PhysicsManager();
	virtual ~PhysicsManager() override;
};

