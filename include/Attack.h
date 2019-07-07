#ifndef ATTACK_H
#define ATTACK_H
#include "Component.h"
#include "Collider.h"

class Attack : public Component{
    GameObject* attackOrigin;
    float offsetX;
    float offsetY;
    public:
        bool isLeftSide;
        Attack(GameObject& associated, Vect2 scale, Vect2 offset, GameObject* attackOrigin, int width, int height, float offsetX, float offsetY);
        ~Attack();
        void Update(float dt);
        void NotifyCollision(GameObject& other);
        void Render();
        void Start();
        bool Is(string type);
};


#endif