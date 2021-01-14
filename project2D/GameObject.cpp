#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "atyp_Array.h"

void GameObject::tick(float deltaTime){
	if(!isActive)return;
	beforeUpdate(deltaTime);
	update(deltaTime);
	afterUpdate(deltaTime);
}

void GameObject::beforeUpdate(float dt){
	transform.updateGlobalTransform();
}

void GameObject::afterUpdate(float dt){
	for(int i = 0; i < transform.children.length; ++i){
		Transform* child = transform.children[i];
		child->gameObject.tick(dt);
	}
}

GameObject::GameObject() : transform(*this){
	id = -1;
	isActive = true;
}

GameObject::GameObject(Array<Component*> a_components) : transform(*this) {
	id = -1;
	
	components = a_components;
	isActive = true;
}

void GameObject::update(float dt){}

void GameObject::OnCollision(GameObject& other){
}

void GameObject::render(aie::Renderer2D& renderer){
	if(!isActive)return;
	beforeDraw(renderer);
	draw(renderer);
	afterDraw(renderer);
}

void GameObject::beforeDraw(aie::Renderer2D& renderer){
}

void GameObject::draw(aie::Renderer2D& renderer){
}

void GameObject::afterDraw(aie::Renderer2D& renderer){
	for (int i = 0; i < transform.children.length; ++i) {
		Transform* child = transform.children[i];
		child->gameObject.render(renderer);
	}
}


GameObject::~GameObject(){
	for (Component* c : components) {
		delete c;
	}

	for (int i = 0; i < transform.children.length; ++i) {
		Transform* child = transform.children[i];
		delete &(child->gameObject);
	}
}
