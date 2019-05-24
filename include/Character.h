#ifndef CHARACTER_H
#define CHARACTER_H
#define IDLE_SPRITE "assets/img/char/SoulBeatsCharIdleR.png"
#define WALKING_SPRITE "assets/img/char/SoulBeatsCharWalkR.png"
#define WALKING_FRAME_COUNT 8
#define WALKING_FRAME_TIME 0.06
#define IDLE_FRAME_COUNT 8
#define IDLE_FRAME_TIME 0.1
#define RISING_SPRITE "assets/img/char/SoulBeatsCharRiseR.png"
#define RISING_FRAME_COUNT 4
#define RISING_FRAME_TIME 0.1
#define BEFORE_RISE_SPRITE "assets/img/char/SoulBeatsCharBeforeRiseR.png"
#define BEFORE_RISE_FRAME_COUNT 1
#define BEFORE_RISE_FRAME_TIME 0
#define PEAK_SPRITE "assets/img/char/SoulBeatsCharPeakR.png"
#define PEAK_FRAME_COUNT 1
#define PEAK_FRAME_TIME 0
#define FALLING_SPRITE "assets/img/char/SoulBeatsCharFallR.png"
#define FALLING_FRAME_COUNT 4
#define FALLING_FRAME_TIME 0.05
#define LANDING_SPRITE "assets/img/char/SoulBeatsCharLandlR.png"
#define LANDING_FRAME_COUNT 2
#define LANDING_FRAME_TIME 0.1
#define BEFORE_RISE_DURATION 0.2
#define PEAK_DURATION 0.23
#define WALKING_SPEED 3
#define JUMPING_SPEED -15
#define GRAVITY 0.5
#define MAX_FALL_SPEED 4
#define LANDING_DURATION 1
#include "Component.h"
#include "Sprite.h"

class Character : public Component {
    Vect2 velocity;
    Sprite *charSprite;
    bool isStill;
    bool isRising;
    bool isFalling;
    bool beforeRisingDone;
    bool peakDone;
    bool landingDone;
    Timer beforeRiseTimer;
    Timer peakTimer;
    Timer landingTimer;
    float gravity;
    public:
        Character(GameObject &associated);
        void Update(float dt);
        void Start();
        bool Is(string type);

};

#endif