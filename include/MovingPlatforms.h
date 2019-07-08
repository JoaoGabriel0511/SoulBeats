#ifndef MOVING_PLATFORMS_H
#define MOVING_PLATFORMS_H
#define PLATFORM_SPRITE "assets/img/interactables/JumpingPad.png"
#include "Component.h"

class MovingPlatforms : public Component
{
private:
    float velocity;
    bool movingX;
    bool switched;
public:
    MovingPlatforms(GameObject& associated, float velocity, bool movingX);
    bool Is(string type);
    void Start();
    bool GetMovingX() {return movingX;}
    float GetVelocity() {return velocity;}
    void Update(float dt);
};

#endif