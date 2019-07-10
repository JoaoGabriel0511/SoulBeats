#ifndef JUMP_PAD_DATA_H
#define JUMP_PAD_DATA_H
#include "Vect2.h"

class JumpPadData
{
private:
    Vect2 jumpPadPos;
public:
    JumpPadData(Vect2 jumpPadPos){
        this->jumpPadPos = jumpPadPos;
    }
    Vect2 GetJumpPadPos() {return jumpPadPos;}
    ~JumpPadData();
};

#endif