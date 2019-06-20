#include "../include/Debugger.h"
bool Debugger::lookLoopGame;
bool Debugger::lookInputManager;
bool Debugger::lookUpdateLevelState;
bool Debugger::lookUpdateState;
bool Debugger::lookSprite;
bool Debugger::lookCharCollision;
Debugger::Debugger() {
    lookLoopGame = false;
    lookUpdateLevelState = true;
    lookUpdateState = false;
    lookInputManager = false;
    lookSprite = false;
    lookCharCollision = true;
}

Debugger::~Debugger(){}

Debugger& Debugger::GetInstance() {
    static  Debugger debugger;
    return debugger;
}