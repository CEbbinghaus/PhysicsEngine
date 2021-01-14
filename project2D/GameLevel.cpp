#pragma once

#include "GameLevel.h"

#include <mlkrng.h>

#include "ColliderManager.h"
#include "Font.h"

mlk::rng random = mlk::rng();

GameLevel* GameLevel::instance = nullptr;

void GameLevel::update(float deltaTime) {
	if (Master::input->WasKeyPressed(aie::INPUT_KEY_ESCAPE))
		Master::application->Quit();

	if (Master::input->WasKeyPressed(aie::INPUT_KEY_F3))
		ColliderManager::Instance->debug = !ColliderManager::Instance->debug;

	if (Master::input->WasKeyPressed(aie::INPUT_KEY_F4))
		Master::application->SetVSync(Vsync = !Vsync);
}

void GameLevel::draw(aie::Renderer2D& renderer) {
	char fps[32];
	sprintf_s(fps, 32, "%i", Master::application->GetFPS());
	renderer.DrawText(font32, fps, Master::application->GetWindowWidth() - 100, Master::application->GetWindowHeight() - 32);
}

GameLevel::GameLevel() {
	instance = this;
	font32 = new aie::Font("./font/consolas.ttf", 32);
	font200 = new aie::Font("./font/consolas.ttf", 200);

	Master::instance->LoadLevel(this);

	for (int i = 0; i < 10; ++i) {
		Circle* c = new Circle(random.get<float>(10, 100));
		c->transform.Position = getRandomScreenPos();
		circles.push(c);

		Square* s = new Square(random.get<float>(10, 100));
		s->transform.Position = getRandomScreenPos();
		squares.push(s);
	}
}

GameLevel::~GameLevel() {
	delete font32;
	delete font200;

	for (Circle* c : circles) {
		delete c;
	}
	for (Square* s : squares) {
		delete s;
	}

	instance = nullptr;
}
