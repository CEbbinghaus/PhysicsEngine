#pragma once
#include "GameObject.h"
class Level : public GameObject{
	friend class Master;
public:
	Level();
	~Level();
};

