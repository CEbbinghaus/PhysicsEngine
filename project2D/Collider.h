#pragma once
#include <atyp_Vector2.h>
#include "GameObject.h"
#include "Component.h"

using uint = unsigned int;

enum class ColliderType: char{
	circle,
	box,
	line,
	size
};

struct Layer{
	uint mask = 1;
  public:
    static Layer default;
	static Layer one;
	static Layer two;
	static Layer three;
	static Layer four;
	static Layer five;

	Layer(uint mask): mask(mask){}

	Layer operator |(const Layer& other) const{
		return {other.mask | mask};
	}

	Layer operator &(const Layer& other) const{
		return {other.mask & mask};
	}
	
	Layer operator ^(const Layer& other) const{
		return {other.mask ^ mask};
	}

	Layer operator <<(const uint& amount) const{
		return {mask << amount};
	}

	Layer operator >>(const uint& amount) const{
		return {mask >> amount};
	}
	
	Layer operator ~() const{
		return {~mask};
	}

	Layer& operator=(Layer value){
		this->mask = value;
	}
	
	bool operator ==(const Layer& other) const{
		return this->mask == other.mask;
	}
	
	bool operator !=(const Layer& other) const{
		return this->mask != other.mask;
	}

	operator uint(){
		return mask;
	}
};

class Collider : public Component{
	static Symbol type;
  protected:
	Collider(GameObject&, Vector2, uint = Layer::default);

  public:
	uint layerMask = Layer::default;
	Vector2 position;


  	static Symbol GetStaticType(){
		return type;
	}

	virtual Symbol GetType(){
		return type;
	}

	Vector2 GetWorldPosition();

	virtual ColliderType GetColliderType();

	~Collider();
};

