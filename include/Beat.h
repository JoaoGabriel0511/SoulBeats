#ifndef BEAT_H
#define BEAT_H
#define IDLE_HEART_SPRITE "assets/img/heart/HeartCalm.png"
#define BEATING_HEART_SPRITE "assets/img/heart/HeartBeatHard.png"
#define BEATING_HEART_BG "assets/img/heart/Interface do coração.png"
#define BEATING_HEART_BG_DARK "assets/img/heart/Interface do coração escura.png"
#define BEATING_HEART_LIGHT_SPRITE "assets/img/heart/HeartBeatHard2.png"
#define WAVE_SPRITE "assets/img/heart/HeartWaves.png"
#define WAVE_FRAME_COUNT 5
#define HEART_SMOOTH_FRAME_COUNT 3
#define BEAT_FALSE_LIMIT 0.6666666
#define BEAT_TRUE_LIMIT 0.2222222
#define BEAT_OFFSET 0.011111
#define STILL_FRAME_COUNT 1
#define FRAME_COUNT 1
#define DARK_TIME 0.3
#include "Component.h"
#include "Sprite.h"
#include "Timer.h"

class Beat : public Component {
    Sprite* beatSprite;
    Sprite* waveSprite;
    Timer trueTimer;
    Timer falseTimer;
    Timer darkTimer;
    bool actionOnBeat;
    bool onBeat;
    bool switched;
    bool onBeatAnimation;
    bool hasBegun;
    GameObject *beatWave;
    GameObject *heartBackground;
    Sprite *backgroundSprite;
    public:
        Beat(GameObject& associated);
        void Update(float dt);
        void Start();
        void Render();
        void BeginBeat();
        void ActionOnBeat();
        bool Is(string type);
        bool GetOnBeat();
        bool HasBegun();
        float GetFalseDuration();
        bool GetOnBeatAnimation();
};

#endif