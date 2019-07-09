#include "../include/Debugger.h"
bool Debugger::lookLoopGame;
bool Debugger::lookInputManager;
bool Debugger::lookUpdateLevelState;
bool Debugger::lookUpdateState;
bool Debugger::lookSprite;
bool Debugger::lookCharCollision;
bool Debugger::cameraDebugMode;
Debugger::Debugger() {
    lookLoopGame = false;
    lookUpdateLevelState = false;
    lookUpdateState = false;
    lookInputManager = false;
    lookSprite = false;
    lookCharCollision = false;
    cameraDebugMode = true;
}

Debugger::~Debugger(){}

Debugger& Debugger::GetInstance() {
    static  Debugger debugger;
    return debugger;
}