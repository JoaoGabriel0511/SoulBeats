#ifndef VICTORY_STATE
#define VICTORY_STATE
#define VICTORY_BG_SPRITE "assets/img/background/Results.png"
#define VICTORY_BG_MUSIC "assets/audio/TelaDeResultados.wav"
#include "State.h"
#include "LevelData.h"

class VictoryState : public State {
    GameObject *bg;
    Music *music;
    public:
        VictoryState();
        void Pause();
        void Resume();
        void StartData();
        void Start();
        void LoadAssets();
};


#endif