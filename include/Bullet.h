#ifndef BULLET_H
#define BULLET_H
#include "Component.h"
#include "Sprite.h"
#include "Vect2.h"
#include "Collider.h"
    class Component;
    class Bullet : public Component {
        float speed;
        Vect2 start;
        Vect2 direction;
        float distance;
        int damage;
        public:
            Bullet(GameObject& associated, Vect2 direction, float speed, int damage, float maxDistance, string sprite, int frameCount);
            void Update(float dt);
            void Render();
            bool targetsPlayer;
            bool Is(string type);
            int GetDamage();
    };

#endif