#include "../include/Debugger.h"
bool Debugger::lookLoopGame;
bool Debugger::lookInputManager;
bool Debugger::lookUpdateStageState;
bool Debugger::lookUpdateState;
bool Debugger::lookUpdateAlien;
bool Debugger::lookUpdateBullet;
bool Debugger::lookUpdatePenguinBody;
Debugger::Debugger() {
    lookLoopGame = false;
    lookUpdateStageState = false;
    lookUpdateState = false;
    lookInputManager = false;
    lookUpdateAlien = false;
    lookUpdateBullet = false;
    lookUpdatePenguinBody = false;
}

Debugger::~Debugger(){}

Debugger& Debugger::GetInstance() {
    static  Debugger debugger;
    return debugger;
}