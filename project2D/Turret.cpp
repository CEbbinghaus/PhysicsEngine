#include "Turret.h"

#include "Bullet.h"
#include "Game.h"
#include "Master.h"

void Turret::shoot() {
	Bullet* b = new Bullet();
	b->transform.Position = Vector2(transform.GetGlobalTransform().Pos.x, transform.GetGlobalTransform().Pos.y);
	Vector3 dir = transform.GetGlobalTransform().AxisY;
	b->Direction = Vector2(dir.x, dir.y);

	//b->transform.SetParent(Game::instance);
	//Game::instance->bullets.push(b);
}

void Turret::update(float deltaTime) {
	cooldown.Update(deltaTime);
	auto input = Master::input;

	if (input->IsKeyDown(aie::INPUT_KEY_Q)) {
		transform.Rotation += rotationSpeed * deltaTime;
	}

	if (input->IsKeyDown(aie::INPUT_KEY_E)) {
		transform.Rotation -= rotationSpeed * deltaTime;
	}

	if (input->WasKeyPressed(aie::INPUT_KEY_SPACE)) {
		if (cooldown.hasRunOut) {
			shoot();
			cooldown.Reset();
		}
	}
}

void Turret::draw(aie::Renderer2D& render) {
	render.DrawSpriteTransformed3x3(texture, transform.GetGlobalTransform());
}

Turret::Turret() : cooldown(0.5f) {
	texture = new aie::Texture("./textures/barrelBeige.png");
}

Turret::~Turret() {
	delete texture;
}
