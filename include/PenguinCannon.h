#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Bullet.h"
#include "Timer.h"
class Component;
class PenguinCannon : public Component {
    GameObject * pbody;
    Vect2 direction;
    float angle;
    public:
        Timer timer;
        PenguinCannon(GameObject& associated, GameObject * penguinBody);
        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vect2 direction);
};

#endif