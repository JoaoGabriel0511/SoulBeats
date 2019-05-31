#ifndef BEAT_H
#define BEAT_H
#define IDLE_HEART_SPRITE "assets/img/heart/HeartStill.png"
#define BEATING_HEART_SPRITE "assets/img/heart/Heart.png"
#define BEAT_FALSE_LIMIT 2.0
#define BEAT_TRUE_LIMIT 0.5
#define STILL_FRAME_COUNT 1
#define FRAME_COUNT 8
#define FRAME_TIME 0.08
#include "Component.h"
#include "Sprite.h"
#include "Timer.h"

class Beat : public Component {
    Sprite* beatSprite;
    Timer trueTimer;
    Timer falseTimer;
    bool onBeat;

    public:
        Beat(GameObject& associated);
        void Update(float dt);
        void Start();
        void Render();
        bool Is(string type);
        bool GetOnBeat();
};

#endif