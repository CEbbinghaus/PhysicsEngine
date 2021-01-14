#include "Master.h"

#include "ColliderManager.h"
#include "PhysicsManager.h"

Master* Master::instance = nullptr;

aie::Input* Master::input = nullptr;
aie::Application* Master::application = nullptr;
Level* Master::level = nullptr;
Array<Manager*> Master::managers = {};

void Master::Update(float deltaTime) {
	for (Manager* manager : managers)
		manager->update(deltaTime);

	if (level)
		level->tick(deltaTime);

	while (!tbDeleted.isEmpty()) {
		GameObject* gm = tbDeleted.pop();
		delete gm;
	}
}

void Master::Draw() {
	application->ClearScreen();
	camera.Begin();
	for (Manager* manager : managers) {
		manager->draw(camera);
	}
	if (level)
		level->render(camera);
	camera.End();
}

void Master::RegisterManager(Manager* m) {
	managers.push(m);
}

void Master::LoadLevel(Level* a_level) {
	level = a_level;
	Transform::root = &(level->transform);
}

void Master::CreateGame() {
	printf("Creating Game\n");
	instance = new Master();
	new ColliderManager();
	new PhysicsManager();
}

void Master::RunGame() {
	printf("Starting Game\n");
	if (instance)
		instance->Run();
}

void Master::DestroyGame() {
	printf("Destroying Game\n");
	if (instance)
		delete instance;
	instance = nullptr;
}

void Master::DeleteObject(GameObject* gm) {
	if (instance && instance->tbDeleted.indexOf(gm) == -1)
		instance->tbDeleted.push(gm);
}

Master::Master() : Game("Physics Simulation", 1920, 1080, false), camera(*(new aie::Renderer2D())) {
	level = nullptr;
	if (instance) throw "There can only be One Instance of the Game";
	input = aie::Input::GetInstance();
	application = aie::Application::GetInstance();
	tbDeleted = Array<GameObject*>(0);
}

Master::~Master() {
	printf("Deleting everything\n");
	delete &camera;
	for (Manager* m : managers) {
		delete m;
	}
}

Manager::Manager() {
	Master::RegisterManager(this);
}

Manager::~Manager() {
}
