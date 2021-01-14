#pragma once
#include "atyp_Array.h"
#include "Renderer2D.h"
#include "Transform.h"
#include <type_traits>

class Component;

class GameObject{
	friend class Master;
	friend class ColliderManager;

	void tick(float);
	Array<Component*> components;


protected:
	virtual void beforeUpdate(float);
	virtual void update(float dt);
	virtual void afterUpdate(float);


	void render(aie::Renderer2D&);
	void beforeDraw(aie::Renderer2D&);
	virtual void draw(aie::Renderer2D& renderer);
	void afterDraw(aie::Renderer2D&);

	virtual void OnCollision(GameObject& other);

public:
	char id;
	bool isActive;

	Transform transform;

	GameObject();
	GameObject(Array<Component*>);

	template<typename T, typename = std::enable_if<std::is_base_of<Component, T>::value, T>::type>
	T* GetComponent(){
		for(Component* component : components){
			if(component->GetType() == T::GetStaticType()){
				return (T*)component;
			}
		}
		return nullptr;
	}

	virtual ~GameObject();
};

