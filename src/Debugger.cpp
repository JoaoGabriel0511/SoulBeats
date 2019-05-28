#include "../include/Debugger.h"
bool Debugger::lookLoopGame;
bool Debugger::lookInputManager;
bool Debugger::lookUpdateLevelState;
bool Debugger::lookUpdateState;
bool Debugger::lookSprite;
Debugger::Debugger() {
    lookLoopGame = false;
    lookUpdateLevelState = false;
    lookUpdateState = true;
    lookInputManager = false;
    lookSprite = false;
}

Debugger::~Debugger(){}

Debugger& Debugger::GetInstance() {
    static  Debugger debugger;
    return debugger;
}