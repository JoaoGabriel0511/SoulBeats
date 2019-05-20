#ifndef DEBUGGER
#define DEBUGGER
class Debugger {
public:
    Debugger();
    ~Debugger();
    static Debugger& GetInstance();
    static bool lookUpdateStageState;
    static bool lookUpdateState;
    static bool lookLoopGame;
    static bool lookInputManager;
    static bool lookUpdateBullet;
    static bool lookUpdateAlien;
    static bool lookUpdatePenguinBody;
};
#endif