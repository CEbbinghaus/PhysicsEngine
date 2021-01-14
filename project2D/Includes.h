#pragma once
#include <atyp_Array.h>
#include <atyp_Matrix3.h>
#include <atyp_Vector2.h>
#include <atyp_Vector3.h>
#include <atyp_Vector4.h>

#include "./External/mlkrng.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Level.h"
#include "LineCollider.h"
#include "Master.h"
#include "Symbol.h"
#include "Texture.h"
#include "Transform.h"

#define _USE_MATH_DEFINES
#include <math.h>

static mlk::rng Random;

static Vector2 getRandomDirection() {
	float rotation = Random.get<float>() * M_PI;
	return Vector2(sinf(rotation), cosf(rotation));
}

static Vector2 getRandomScreenPos() {
	return Vector2(Random.get<float>(0.0f, Master::application->GetWindowWidth()), Random.get<float>(0.0f, Master::application->GetWindowHeight()));
}
