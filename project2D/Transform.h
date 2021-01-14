#pragma once
#include <memory>
#include <atyp_Array.h>
#include <atyp_Vector3.h>
#include <atyp_Vector2.h>
#include <atyp_Matrix3.h>

class GameObject;

class Transform{
	friend GameObject;


	void updateLocalTransform();
	void updateGlobalTransform();

	Matrix3 globalTransform;
	Matrix3 localTransform;

public:
	GameObject& gameObject;

	Matrix3 GetGlobalTransform();
	Matrix3 GetLocalTransform();


	static Transform* root;


	Array<Transform*> children;

	Transform* Parent;
	void TransferParent(Transform*);
	void SetParent(Transform*);
	void SetParent(GameObject*);
	void SetParent(std::nullptr_t);

	Vector2 Position;
	Vector2 Scale;
	float Rotation;
	
	Transform(GameObject&);
	Transform(GameObject&, Matrix3);
	Transform(GameObject&, Vector2, Vector2, float);
	~Transform();

	Transform operator *(Transform& other);
	Matrix3 operator *(Matrix3& other);

	operator Matrix3();
};

Matrix3 operator * (Matrix3& lhs, Transform& rhs);