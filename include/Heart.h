#ifndef HEART_H
#define HEART_H
#define HEART_SPRITE "assets/img/interactables/heart.png"
#include "Component.h"
#include "Sprite.h"
#include "LevelData.h"

class Heart : public Component
{
private:
    Sprite *heartSprite;
    Sound *sound;
    int index;
    Collider *heartCollider;
public:
    Heart(GameObject& associated, int index);
    bool Is(string type);
    void Start();
    void NotifyCollision(GameObject& other);
    void Update(float dt) {}
};

#endif