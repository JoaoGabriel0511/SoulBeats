#ifndef MOVING_LAYER
#define MOVING_LAYER
#include "Component.h"
#include "Sprite.h"

class MovingLayer : public Component {
    private:
        Sprite* layerSprite;
        string spriteFile;
        Vect2 beginingPos;
        Vect2 layerVelocity;
        bool finishedX;
        bool finishedY;
    public:
        MovingLayer(GameObject& associated, string spriteFile, Vect2 beginingPos, Vect2 layerVelocity);
        bool Is(string type);
        void Start();
        void Update(float dt);
        bool HasFinished();
};


#endif