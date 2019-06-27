#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H
#define BEGINING_MUSIC "assets/audio/GamePlay(Loop1).wav"
#define DEVELOPMENT_MUSIC "assets/audio/GamePlay(Loop2).wav"
#define BEGINING_MUSIC_TIME 32
#define DEVELOPMENT_MUSIC_TIME 21
#define MAIN_MUSIC_TIME 21
#define STOP_MUSIC_TIME 0.2
#define BEFORE_FINISH_LEVEL_TIME 3
#define MAIN_MUSIC "assets/audio/GamePlay(Loop3).wav"
#include "State.h"
#include "Beat.h"
#include "Character.h"
#include "BellEnemy.h"
#include "HarpEnemy.h"
#include "AccordionEnemy.h"
#include "TileMap.h"
#include "TileMapCollider.h"
#include "TileSet.h"
#include "Game.h"
#include "Goal.h"
#include "VictoryState.h"
class LevelState : public State {
    GameObject *bg;
    GameObject *tileTerrForeGO;
    GameObject *tileTerrBackGO;
    GameObject *beat;
    GameObject *goalGO;
    Timer beginingMusicTimer;
    Timer developmentMusicTimer;
    Timer mainMusicTimer;
    Timer musicStopTimer;
    Timer beforeFinishLevelTimer;
    void UpdateMusic(float dt);
    bool switchedBegininMusic;
    bool switchedDevelopmentMusic;
    public:
        LevelState();
        void Pause();
        bool levelCompleted;
        void Resume();
        void Start();
        void Update(float dt);
        void LoadAssets();
        GameObject* GetBeatObject();
};

#endif