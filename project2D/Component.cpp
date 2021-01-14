#include "Component.h"

Symbol Component::type = Symbol("base");

GameObject& Component::getParent(){
	return parent;
}

Component::Component(GameObject& p) : parent(p){}
