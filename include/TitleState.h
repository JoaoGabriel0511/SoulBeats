#ifndef TITLE_STATE_H
#define TITLE_STATE_H
#include "State.h"
#include "StageState.h"
#include "Text.h"

class TitleState : public State {
    GameObject *bg;
    GameObject *textGO;
    shared_ptr<Sprite> bgSprite;
    public:
        TitleState();
        ~TitleState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();
};


#endif