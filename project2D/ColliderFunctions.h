#include <atyp_Vector2.h>
#include "ColliderManager.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "LineCollider.h"


bool CircleCircle(Colission& out, Collider* a, Collider* b){
	CircleCollider& ca = *(CircleCollider*)a;
	CircleCollider& cb = *(CircleCollider*)b;

	Vector2 aPos = ca.GetWorldPosition();
	Vector2 bPos = cb.GetWorldPosition();

	float distance = (aPos - bPos).magnitude();

	//Exit Early since the Two Circles arent colliding
	if(distance > ca.radius + cb.radius)return false;

	//Check for Two Colliding Objects at the same position
	if(distance == 0.0f){
		out.depth = ca.radius;
    	out.normal = Vector2( 1, 0 );
	} else{
		out.depth = ((ca.radius + cb.radius) - distance);
		out.normal = -(aPos - bPos).normalise();
	}

	return true;
}

bool CircleBox(Colission& out, Collider* a, Collider* b){
	CircleCollider& ca = *(CircleCollider*)a;
	BoxCollider& bb = *(BoxCollider*)b;

	Vector2 center = Vector2::clamp(ca.GetWorldPosition(), bb.min(), bb.max());

	if(center == ca.GetWorldPosition()){
		center = bb.GetWorldPosition();
	}

	Vector2 displacement = center - ca.GetWorldPosition();

	float overlap = ca.radius - displacement.magnitude();

	if (overlap > 0.0f){
		out.normal = displacement.normalise();
		out.depth = overlap;
		return true;
	}
	return false;
}

bool CircleLine(Colission& out, Collider* a, Collider* b){
	CircleCollider& ca = *(CircleCollider*)a;
	LineCollider& lb = *(LineCollider*)b;

	float position_dot_normal = Vector2::dot(ca.GetWorldPosition(), lb.GetNormal());

	float distance = position_dot_normal - (lb.GetWorldPosition().magnitude() + ca.radius);

	if (distance < 0.0f){
		out.normal = -(lb.GetNormal());
		out.depth = distance;
		return true;
	}else
		return false;
}

bool BoxBox(Colission& out, Collider* a, Collider* b){
	BoxCollider& ba = *(BoxCollider*)a;
	BoxCollider& bb = *(BoxCollider*)b;

	Vector2 apos = ba.GetWorldPosition();
	Vector2 bpos = bb.GetWorldPosition();

	Vector2 distance = apos - bpos;
	
	Vector2 amax = ba.max();
	Vector2 bmax = bb.max();
	Vector2 amin = ba.min();
	Vector2 bmin = bb.min();
	
	//immediately Dismiss Non Colliding Boxes
	if(!(amax.x >= bmin.x && amin.x <= bmax.x &&
		 amax.y >= bmin.y && amin.y <= bmax.y)){
		return false;
	}

	Vector2 aextent = (amax - amin) / 2;
	Vector2 bextent = (bmax - bmin) / 2;

	Vector2 overlap = aextent + bextent - Vector2::Abs(distance);

	if(overlap.x < overlap.y){ 
		if(overlap.x > 0)
			out.normal = Vector2(1, 0);
		else
			out.normal = Vector2(-1, 0);

		out.depth = overlap.x;
	}else{
		if(overlap.y > 0)
			out.normal = Vector2(0, 1);
		else
			out.normal = Vector2(0, -1);

		out.depth = overlap.y;
	}
	
	return true;
}

bool BoxLine(Colission& out, Collider* a, Collider* b){
	BoxCollider& sa = *(BoxCollider*)a;
	LineCollider& lb = *(LineCollider*)b;
	out.depth = 0;
	out.normal = Vector2(0.0f);
	return false;
}

bool LineLine(Colission& out, Collider* a, Collider* b){
	out.depth = 0;
	out.normal = Vector2(0.0f);
	return false;
}