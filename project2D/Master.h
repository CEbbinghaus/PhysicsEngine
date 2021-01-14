#pragma once
#include "Application.h"
#include "Game.h"
#include "Input.h"
#include "Level.h"
#include "Renderer2D.h"
#include "atyp_Array.h"

class Manager {
   public:
	virtual ~Manager();
	Manager();
	virtual void update(float deltaTime) = 0;
	virtual void draw(aie::Renderer2D& renderer) = 0;
};

class Master : public aie::Game {
	static Level* level;
	static Array<Manager*> managers;

	aie::Renderer2D& camera;

	void Update(float deltaTime);
	void Draw();

	Array<GameObject*> tbDeleted;

   public:
	static aie::Input* input;
	static aie::Application* application;
	static Master* instance;

	static void RegisterManager(Manager*);
	static void LoadLevel(Level*);

	static void CreateGame();
	static void RunGame();
	static void DestroyGame();

	static void DeleteObject(GameObject*);

	Master();
	~Master();
};
