#ifndef JPAD_H
#define JPAD_H
#define JUMPING_PAD_SPRITE "assets/img/interactables/JumpingPad.png"

#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Character.h"
#include "GameObject.h"

class JumpingPad : public Component {
 
    private:
        Sprite* padSprite;
        Collider* padCollider;
        GameObject *character;

    public:
        JumpingPad(GameObject& associated, GameObject* character);
        bool Is(string type);
        void Update(float dt);
        void NotifyCollision(GameObject& other);
        void Start();
};

#endif