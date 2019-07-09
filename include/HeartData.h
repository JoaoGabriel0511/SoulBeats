#ifndef HEART_DATA_H
#define HEART_DATA_H
#include "Vect2.h"

class HeartData
{
private:
    Vect2 heartPos;
public:
    bool isCollected;
    bool wasCollected;
    Vect2 GetHeartPos() {return heartPos;}
    HeartData(bool isCollected, Vect2 heartPos){
        this->isCollected = isCollected;
        this->heartPos = heartPos;
    }
};

#endif