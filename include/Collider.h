#ifndef COLLIDER_H
#define COLLIDER_H
#include "Component.h"


class Collider : public Component{
    Vect2 scale;
    Vect2 offset;
    public:
        Collider(GameObject& associated, Vect2 scale, Vect2 offset);
        Collider(GameObject& associated);
        Rect box;
        void Update(float dt);
        void Render();
        bool Is(string type);
        void SetScale(Vect2 scale);
        void SetOffset(Vect2 offset);
};



#endif