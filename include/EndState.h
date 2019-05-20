#ifndef END_STATE_H
#define END_STATE_H
#include "State.h"
#include "GameData.h"
#include "TitleState.h"
#include "Text.h"
class EndState : public State {
    GameObject *bg;
    public:
        EndState();
        ~EndState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};

#endif