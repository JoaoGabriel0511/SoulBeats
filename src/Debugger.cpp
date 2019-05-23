#include "../include/Debugger.h"
bool Debugger::lookLoopGame;
bool Debugger::lookInputManager;
bool Debugger::lookUpdateLevelState;
bool Debugger::lookUpdateState;
Debugger::Debugger() {
    lookLoopGame = false;
    lookUpdateLevelState = false;
    lookUpdateState = false;
    lookInputManager = false;
}

Debugger::~Debugger(){}

Debugger& Debugger::GetInstance() {
    static  Debugger debugger;
    return debugger;
}