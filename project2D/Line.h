#pragma once
#include "GameObject.h"
#include "Rigidbody.h"
#include "LineCollider.h"

class Line : public GameObject{
  public:
    Line(): GameObject({new LineCollider(*this, Vector2::zero(), 1.570795)}){
        GetComponent<LineCollider>()->layerMask = Layer::default | Layer::one;
    }
};