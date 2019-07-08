#ifndef COLLECTABLE_DATA_H
#define COLLECTABLE_DATA_H
#include "Vect2.h"

class CollectableData
{
private:
    Vect2 collectablePos;
public:
    bool isCollected;
    bool wasCollected;
    Vect2 GetCollectablePos() {return collectablePos;}
    CollectableData(bool isCollected, Vect2 collectablePos){
        this->collectablePos = collectablePos;
        this->isCollected = isCollected;
    }
};



#endif