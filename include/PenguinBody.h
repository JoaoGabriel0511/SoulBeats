#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H
#include "Component.h"
#include "PenguinCannon.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sprite.h"
class Component;
class PenguinBody : public Component {
    GameObject* pcannon;
    float acceleration;
    float linearSpeed;
    float maxSpeed;
    float maxAcceleration;
    int angle;
    int current_angle;
    bool breaks;
    enum Side { FRONT, BACK };
    Side side;
    int hp;
    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);
        bool Is(string type);
        static PenguinBody* player;
};

#endif