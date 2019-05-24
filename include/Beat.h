#ifndef BEAT_H
#define BEAT_H
#define IDLE_SPRITE "assets/img/heart/Heart.png"
#define BEATING_SPRITE "assets/img/heart/Heart.png"
#define BEAT_INTERVAL 4.0
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