#ifndef UI_H
#define UI_H
#define HP_HEART_SPRITE "assets/img/heart/HeartStill.png"
#include "Component.h"
#include "Sprite.h"
#include "Timer.h"

class UserInterface {
    Sprite* heartSprite;
    public:
        UserInterface();
        void RenderHPIndication(unsigned index, float x, float y, float scale, int offsetX, int offsetY);
};
#endif