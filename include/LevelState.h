#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H
#define BEGINING_MUSIC "assets/audio/GamePlay(Loop1).wav"
#define DEVELOPMENT_MUSIC "assets/audio/GamePlay(Loop2).wav"
#define SWITCH_TO_DEVELOP_MUSIC 5000
#define SWITCH_TO_MAIN_MUSIC 9000
#define BEGINING_MUSIC_TIME 32.18
#define DEVELOPMENT_MUSIC_TIME 21.25
#define MAIN_MUSIC_TIME 21.25
#define STOP_MUSIC_TIME 0.0
#define BEFORE_FINISH_LEVEL_TIME 5
#define MAIN_MUSIC "assets/audio/GamePlay(Loop3).wav"
#define INTRO_MUSIC "assets/audio/INTRO(Soul.Mus).wav"
#define INTRO_MUSIC_TIME 21
#include "State.h"
#include "Launcher.h"
#include "Beat.h"
#include "Heart.h"
#include "Character.h"
#include "BellEnemy.h"
#include "HarpEnemy.h"
#include "AccordionEnemy.h"
#include "Collectable.h"
#include "TileMap.h"
#include "TileMapCollider.h"
#include "TileSet.h"
#include "Game.h"
#include "Goal.h"
#include "CheckPoint.h"
#include "LevelData.h"
#include "Spotlights.h"
#include "VictoryState.h"
#include "JumpingPad.h"
#include "MovingPlatforms.h"
#include "Text.h"
#include "UIText.h"

class LevelState : public State {
    GameObject *bg;
    GameObject *tileTerrForeGO;
    GameObject *tileTerrBackGO;
    GameObject *beat;
    GameObject *goalGO;
    GameObject *characterGO;
    UIText *collectablesUI;
    UIText *pointsUI;
    UIText *timeUI;
    Timer beginingMusicTimer;
    Timer developmentMusicTimer;
    Timer mainMusicTimer;
    Timer musicStopTimer;
    Timer beforeFinishLevelTimer;
    Timer introTimer;
    void StartData();
    void UpdateMusic(float dt);
    void LevelCycle(float dt);
    void UpdateCameraFocus(float dt);
    void VictoryCycle(float dt);
    Timer timeTimer;
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