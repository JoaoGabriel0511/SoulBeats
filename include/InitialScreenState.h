#ifndef INITIAL_SCREEN_STATE
#define INITIAL_SCREEN_STATE
#define INITIAL_SCREEN_BACKGROUND_SPRITE "assets/img/menu/TelaInicialFundo.png"
#define INITIAL_SCREEN_FLOOR_1_SPRITE "assets/img/menu/TelaInicialChão1.png" 
#define INITIAL_SCREEN_FLOOR_2_SPRITE "assets/img/menu/TelaInicialChão2.png"
#define MENU_HEART_SPRITE  "assets/img/menu/TelaInicialLogo.png"
#define MENU_CHARACTER_SPRITE_SHEET "assets/img/menu/SB_pose.png"
#define MENU_HIGHLIGHT_SPRITE_1 "assets/img/menu/TelaInicialLuzESombra1.png"
#define MENU_HIGHLIGHT_SPRITE_2 "assets/img/menu/TelaInicialLuzESombra2.png"
#define OPTION_CREDITS_0 "assets/img/menu/options/TitleCredits.png"
#define OPTION_CREDITS_1 "assets/img/menu/options/TitleCreditsSelect.png"
#define OPTION_LORE_0 "assets/img/menu/options/TitleLore.png"
#define OPTION_LORE_1 "assets/img/menu/options/TitleLoreSelect.png"
#define OPTION_START_0 "assets/img/menu/options/TitleStart.png"
#define OPTION_START_1 "assets/img/menu/options/TitleStartSelect.png"
#define OPTION_QUIT_0 "assets/img/menu/options/TitleQuit.png"
#define OPTION_QUIT_1 "assets/img/menu/options/TitleQuitSelect.png"


#define INTIAL_SCREEN_MUSIC "assets/audio/MENU.wav"
#define MENU_CHOOSING_SFX "assets/audio/SFX/menu/Escolhendo2.1(Soul).wav"
#define MENU_SELECTING_SFX "assets/audio/SFX/menu/Selecionando2.1(Soul).wav"

#define FLOOR_CHANGE_INTERVAL 0.545454545
#define MENU_CHARACTER_FRAME_TIME 0.08
#include "State.h"
#include "LevelData.h"
#include "LoreState.h"
#include "MovingLayer.h"

class InitialScreenState : public State {

    GameObject* backgroundGo;
    GameObject* floorGo;
    GameObject* heartGo;
    GameObject* characterGo;
    GameObject* highlightGo;
    GameObject* startOptionGo;
    GameObject* creditsOptionGo;
    GameObject* exitOptionGo;
    GameObject* loreOptionGo;

    Sprite* floorSprite;
    Sprite* characterSprite;
    Sprite* highlightSprite;
    Sprite* startSprite;
    Sprite* exitSprite;
    Sprite* loreSprite;
    Sprite* creditsSprite;
    Sound* choosingSound;
    Sound* selectingSound;

    Timer floorChangeTimer;
    Music * menuMusic;
    enum Options {START,CREDITS, QUIT, LORE};
    bool floorOnInitialState;
    Options selectedOption;

    public:
        InitialScreenState();
        void Pause();
        void Resume();
        void StartData();
        void Start();
        void Update(float dt);
        void UpdateMenuInput(float dt);
        void LoadAssets();

};


#endif