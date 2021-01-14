#pragma once
#include "GameObject.h"
#include "Rigidbody.h"
#include "BoxCollider.h"

class Square : public GameObject{
  public:
    BoxCollider* bCollider;
    Rigidbody* rb;

    Vector2 Size;

    Vector3 color;

    Square(float magnitude = 100): Size(Vector2(100, 100)), GameObject({new BoxCollider(*this, Vector2::zero(), 0, 0), new Rigidbody(*this)}){
        color = Vector3(Random.get<float>(.5f, 1.f));
        Size = Vector2::one() * magnitude;

        bCollider = GetComponent<BoxCollider>();
        bCollider->layerMask = Layer::default | Layer::one;
        bCollider->SetSize(Size);


        rb = GetComponent<Rigidbody>();
        rb->mass = magnitude;
        //rb->useGravity = false;
    }

    void update(float deltaTime) override{
        if (transform.Position.x < Size.x / 2){
            rb->velocity *= Vector2(-1, 1);
            transform.Position.x = Size.x / 2;
        }
        if (transform.Position.x > Master::application->GetWindowWidth() - Size.x / 2){
            rb->velocity *= Vector2(-1, 1);
            transform.Position.x = Master::application->GetWindowWidth() - Size.x / 2;
        }
        if (transform.Position.y < Size.y / 2){
            rb->velocity *= Vector2(1, -1);
            transform.Position.y = Size.y / 2;
        }
        if (transform.Position.y > Master::application->GetWindowHeight() - Size.y / 2){
            rb->velocity *= Vector2(1, -1);
            transform.Position.y = Master::application->GetWindowHeight() - Size.y / 2;
        }
    }

    void draw(aie::Renderer2D& renderer){
        renderer.SetRenderColour(color.x, color.y, color.z);
        renderer.DrawBox(transform.Position.x, transform.Position.y, Size.x, Size.y);
        renderer.SetRenderColour(0xffffffff);
    }
};