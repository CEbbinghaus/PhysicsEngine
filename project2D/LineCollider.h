#pragma once
#include "Collider.h"

class LineCollider : public Collider {
    static Symbol type;

   public:
    float rotation;

    static Symbol GetStaticType() {
        return type;
    }
    virtual Symbol GetType() {
        return type;
    }

    Vector2 GetVector(){
        return Vector2(sinf(rotation), cosf(rotation));
    }

    Vector2 GetNormal(){
        return Vector2(cosf(rotation), -sinf(rotation));
    }

    LineCollider(GameObject& parent, Vector2 position, float rotation = 0) : Collider(parent, position) {
        this->rotation = rotation;
    }

    ColliderType GetColliderType() override {
        return ColliderType::line;
    }
};