#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H
#define BEGINING_MUSIC "assets/audio/GamePlay(Loop1).wav"
#define DEVELOPMENT_MUSIC "assets/audio/GamePlay(Loop2).wav"
#define BEGINING_MUSIC_TIME 32
#define DEVELOPMENT_MUSIC_TIME 21
#define MAIN_MUSIC_TIME 21
#define STOP_MUSIC_TIME 0.2
#define MAIN_MUSIC "assets/audio/GamePlay(Loop3).wav"
#include "State.h"
#include "Beat.h"
#include "Character.h"
#include "BellEnemy.h"
#include "TileMap.h"
#include "TileMapCollider.h"
#include "TileSet.h"
#include "Game.h"

class LevelState : public State {
    GameObject *bg;
    GameObject *tileTerrForeGO;
    GameObject *tileTerrBackGO;
    GameObject* beat;
    Timer beginingMusicTimer;
    Timer developmentMusicTimer;
    Timer mainMusicTimer;
    Timer musicStopTimer;
    void UpdateMusic(float dt);
    bool switchedBegininMusic;
    bool switchedDevelopmentMusic;
    public:
        LevelState();
        void Pause();
        void Resume();
        void Update(float dt);
        void LoadAssets();
        GameObject* GetBeatObject();
};

#endif