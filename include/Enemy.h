/*#ifndef ENEMY_H
#define ENEMY_H

#include "Component.h"

class Enemy : public Component {
    public:
        Enemy(GameObject& associated);
        virtual void Update(float dt) = 0;
        virtual bool Is(string type) = 0;
        virtual void Render() = 0;
        ~Enemy();
};

#endif*/