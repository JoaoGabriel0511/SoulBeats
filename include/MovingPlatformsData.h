#ifndef MOVING_PLATFORMS_DATA_H
#define MOVING_PLATFORMS_DATA_H
#include "Vect2.h"

class MovingPlatformsData
{
private:
    Vect2 movingPlatformsPos;
    float velocity;
    bool moveX;
    bool moveY;
    bool back;
public:
    Vect2 GetMovingPlatformsPos() {return movingPlatformsPos;}
    bool GetMoveX() {return moveX;}
    bool GetMoveY() {return moveY;}
    bool GetBack() {return back;}
    float GetVelocity() {return velocity;}
    MovingPlatformsData(bool moveX, bool moveY, Vect2 movingPlataformsPos, float velocity, bool back){
        this->movingPlatformsPos = movingPlataformsPos;
        this->moveX = moveX;
        this->moveY = moveY;
        this->back = back;
        this->velocity = velocity;
    }
    ~MovingPlatformsData();
};


#endif