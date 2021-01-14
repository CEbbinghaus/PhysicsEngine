#pragma once
#include "Collider.h"

#ifndef BoxCollider_Init
#define BoxCollider_Init

class BoxCollider : public Collider {
    static Symbol type;
    
    Vector2 extents;
   public:

    static Symbol GetStaticType() {
        return type;
    }

    virtual Symbol GetType() {
        return type;
    }

    BoxCollider(GameObject& parent, Vector2 position, Vector2 size) : Collider(parent, position) {
        extents = size;
    }

    BoxCollider(GameObject& parent, Vector2 position, float width, float height) : Collider(parent, position) {
        extents.x = width;
        extents.y = height;
    }
  
    float GetWidth(){
        return extents.x;
    }

    float GetHeight(){
        return extents.y;
    }

    void SetSize(const Vector2& value){
        extents = value;
    }

    Vector2 min(){
        return GetWorldPosition() - (0.5f * extents);
    }

    Vector2 max(){
        return GetWorldPosition() + (0.5f * extents);
    }

    ColliderType GetColliderType() override {
        return ColliderType::box;
    }
};

#endif