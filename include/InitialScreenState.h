#ifndef INITIAL_SCREEN_STATE
#define INITIAL_SCREEN_STATE
#define INITIAL_SCREEN_BACKGROUND_SPRITE "assets/img/menu/TelaInicialFundo.png"
#define INITIAL_SCREEN_FLOOR_1_SPRITE "assets/img/menu/TelaInicialChão1.png" 
#define INITIAL_SCREEN_FLOOR_2_SPRITE "assets/img/menu/TelaInicialChão2.png"
#define MENU_HEART_SPRITE  "assets/img/menu/TelaInicialLogo.png"
#define MENU_CHARACTER_SPRITE_SHEET "assets/img/menu/SB_pose.png"
#define MENU_HIGHLIGHT_SPRITE_1 "assets/img/menu/TelaInicialLuzESombra1.png"
#define MENU_HIGHLIGHT_SPRITE_2 "assets/img/menu/TelaInicialLuzESombra2.png"

#define INTIAL_SCREEN_MUSIC "assets/audio/MENU.wav"

#define FLOOR_CHANGE_INTERVAL 0.5
#define MENU_CHARACTER_FRAME_TIME 0.2
#include "State.h"
#include "LevelData.h"
#include "MovingLayer.h"

class InitialScreenState : public State {

    GameObject* backgroundGo;
    GameObject* floorGo;
    GameObject* heartGo;
    GameObject* characterGo;
    GameObject* highlightGo;

    Sprite* floorSprite;
    Sprite* characterSprite;
    Sprite* highlightSprite;
    Timer floorChangeTimer;
    
    bool floorOnInitialState;


    public:
        InitialScreenState();
        void Pause();
        void Resume();
        void StartData();
        void Start();
        void Update(float dt);
        void LoadAssets();
};


#endif