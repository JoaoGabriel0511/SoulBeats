#ifndef LEVEL_STATE_H
#define LEVEK_STATE_H
#include "State.h"
#include "Character.h"

class LevelState : public State {
    GameObject *bg;
    public:
        LevelState();
        void Pause();
        void Resume();
        void Update(float dt);
        void LoadAssets();
};

#endif