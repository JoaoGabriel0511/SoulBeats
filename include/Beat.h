#ifndef BEAT_H
#define BEAT_H
#define IDLE_HEART_SPRITE "assets/img/heart/HeartStill.png"
#define BEATING_HEART_SPRITE "assets/img/heart/Heart.png"
#define BEAT_INTERVAL 1.0
#define STILL_FRAME_COUNT 1
#define FRAME_COUNT 8
#define FRAME_TIME 0.08
#define BEAT_LIMIT 0.5
#include "Component.h"
#include "Sprite.h"

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
};

#endif