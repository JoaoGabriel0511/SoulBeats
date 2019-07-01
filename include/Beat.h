#ifndef BEAT_H
#define BEAT_H
#define IDLE_HEART_SPRITE "assets/img/heart/HeartStill.png"
#define BEATING_HEART_SPRITE "assets/img/heart/Heart.png"
#define BEATING_HEART_BG "assets/img/heart/Interface do coração.png"
#define BEAT_FALSE_LIMIT 0.4
#define BEAT_TRUE_LIMIT 0.2
#define STILL_FRAME_COUNT 1
#define FRAME_COUNT 8
#include "Component.h"
#include "Sprite.h"
#include "Timer.h"

class Beat : public Component {
    Sprite* beatSprite;
    Timer trueTimer;
    Timer falseTimer;
    bool onBeat;
    GameObject *heartBackground;
    Sprite *backgroundSprite;
    public:
        Beat(GameObject& associated);
        void Update(float dt);
        void Start();
        void Render();
        bool Is(string type);
        bool GetOnBeat();
};

#endif