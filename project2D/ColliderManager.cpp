#include "ColliderManager.h"
#include "ColliderFunctions.h"
#include "Rigidbody.h"

const collideFunc ColliderManager::collisionFunctions[] = {CircleCircle, CircleBox, CircleLine,
											  CircleBox,    BoxBox,    BoxLine,
											  CircleLine,   BoxLine,   LineLine};

ColliderManager* ColliderManager::Instance = nullptr;

void ColliderManager::RegisterCollider(Collider* col){
	colliders.push(col);
}

void ColliderManager::RemoveCollider(Collider* col){
	colliders.remove(col);
}

void ColliderManager::draw(aie::Renderer2D& renderer){
	if(!debug)return;
	renderer.SetRenderColour(0.0f, 0.5f, 0.2f, 0.3f);
	for (Collider* c : colliders) {
		Vector2 finalPos = c->GetWorldPosition();

		if(c->GetColliderType() == ColliderType::circle)
			renderer.DrawCircle(finalPos.x, finalPos.y, ((CircleCollider*)c)->radius);

		else if(c->GetColliderType() == ColliderType::box)
			renderer.DrawBox(finalPos.x, finalPos.y, ((BoxCollider*)c)->GetWidth(), ((BoxCollider*)c)->GetHeight());
		
		else if(c->GetColliderType() == ColliderType::line){
			LineCollider* l = (LineCollider*)c;
			Vector2 direction = l->GetVector() * 1000;
			renderer.DrawLine(finalPos.x - direction.x, finalPos.y - direction.y, finalPos.x + direction.x, finalPos.y + direction.y);
		}
	}
	renderer.SetRenderColour(1.0f, 1.0f, 1.0f);
}

void ColliderManager::update(float deltaTime){
	Array<std::tuple<GameObject*, GameObject*>> needUpdate;

	for(int i = 0; i < colliders.length; ++i){
		for(int j = i + 1; j < colliders.length; ++j){

			Collider* a = colliders[i];
			Collider* b = colliders[j];

			if(&a->getParent() == &b->getParent())continue;
			if(!(a->layerMask & b->layerMask))continue;

			Colission col;

			if(Collide(a, b, col)){
				GameObject& gma = a->getParent();
				GameObject& gmb = b->getParent();

				needUpdate.push({&gma, &gmb});
				// a->getParent().OnCollision(b->getParent());
				// b->getParent().OnCollision(a->getParent());

				Vector2 penetration = col.normal * col.depth;

				Rigidbody* rba = gma.GetComponent<Rigidbody>();
				Rigidbody* rbb = gmb.GetComponent<Rigidbody>();

				if(rba && rbb){

					Vector2 relativeVelocity = rba->velocity - rbb->velocity;

					if(relativeVelocity.magnitude() == 0)
						relativeVelocity = Vector2::one();
				
					float just = 
						Vector2::dot( -(1 + (rba->elasticity * rbb->elasticity)) * (relativeVelocity), col.normal)
							/
						Vector2::dot(col.normal, col.normal * ((1 / rba->mass) + (1 / rbb->mass)));

					if(isnan(just)){
						printf("Value was Nan");
					}
					gma.transform.Position -= penetration / 2;
					gmb.transform.Position += penetration / 2;

					rba->ApplyForce(col.normal * just);
					rbb->ApplyForce(col.normal * -just);
				}else{
					if(rba){
						gma.transform.Position += penetration;
					}else{
						gmb.transform.Position += penetration;
					}
				}
			}
		}
	}

	for(std::tuple<GameObject*, GameObject*>& tuple : needUpdate){
		GameObject* a = std::get<0>(tuple);
		GameObject* b = std::get<1>(tuple);

		a->OnCollision(*b);
		b->OnCollision(*a);
	}
}

bool ColliderManager::Collide(Collider * a, Collider * b, Colission& out){
	if(a == b)return false;

	char aType = (char)a->GetColliderType();
	char bType = (char)b->GetColliderType();

	if((char)aType == -1 || (char)bType == -1)
		throw "Cannot Use Undefined Type";

	int index = aType * (char)ColliderType::size + bType;
	collideFunc function = collisionFunctions[index];
	if(function == nullptr)return false;

	if(aType < bType)
		return function(out, a, b);
	else{
		bool v = function(out, b, a);
		out.normal = -out.normal;
		return v;
	}
}

ColliderManager::ColliderManager(){
	if(Instance)throw "There is Already a Instance of the Collision Manager";
	Instance = this;
	debug = false;
}


ColliderManager::~ColliderManager(){
	printf("Destroying Collider Manager");
	Instance = nullptr;
}
