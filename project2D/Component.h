#pragma once
#include "GameObject.h"
#include "Symbol.h"
#include <type_traits>

enum componentType{
	undefined,
	collider,
	count
};


// Symbol typeof(){
// 	return something
// }


class Component{

	static Symbol type;

	GameObject& parent;

public:
	GameObject& getParent();

	static Symbol GetStaticType(){
		return type;
	}

	virtual Symbol GetType(){
		return type;
	}

	Component(GameObject&);

	virtual ~Component() = default;

	
};