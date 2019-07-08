#ifndef MOVING_PLATFORMS_DATA_H
#define MOVING_PLATFORMS_DATA_H
#include "Vect2.h"

class MovingPlatformsData
{
private:
    Vect2 movingPlatformsPos;
    float velocity;
    bool moveX;
public:
    Vect2 GetMovingPlatformsPos() {return movingPlatformsPos;}
    bool GetMoveX() {return moveX;}
    float GetVelocity() {return velocity;}
    MovingPlatformsData(bool moveX, Vect2 movingPlataformsPos, float velocity){
        this->movingPlatformsPos = movingPlataformsPos;
        this->moveX = moveX;
        this->velocity = velocity;
    }
    ~MovingPlatformsData();
};


#endif