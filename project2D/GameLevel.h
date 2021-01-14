#pragma once

#include "Circle.h"
#include "Includes.h"
#include "Line.h"
#include "Square.h"

enum class Object {
	player,
	asteroid,
	bullet,
	count
};

class GameLevel : public Level {
   public:
	static GameLevel* instance;

	bool Vsync;

	Array<Circle*> circles;
	Array<Square*> squares;

	//Player player;
	aie::Font* font32;
	aie::Font* font200;

	void update(float);
	void draw(aie::Renderer2D&);

	GameLevel();
	~GameLevel();
};