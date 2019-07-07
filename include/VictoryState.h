#ifndef VICTORY_STATE
#define VICTORY_STATE
#define VICTORY_LAYER1_SPRITE "assets/img/background/results/ResultsCamada1.png"
#define VICTORY_LAYER2_SPRITE "assets/img/background/results/ResultsCamada2.png"
#define VICTORY_LAYER3_SPRITE "assets/img/background/results/ResultsCamada3.png"
#define VICTORY_LAYER4_SPRITE "assets/img/background/results/ResultsCamada4.png"
#define VICTORY_LAYER5_SPRITE "assets/img/background/results/ResultsCamada5.png"
#define VICTORY_LAYER6_SPRITE "assets/img/background/results/ResultsCamada6.png"
#define COMPLETE_SPRITE "assets/img/background/results/ResultsClear.png"
#define YOUR_RANK_IS_SPRITE "assets/img/background/results/ResultsYourRanking.png"
#define COLLECTABLE_ICON_SPRITE "assets/img/background/results/Icon1.png"
#define DEATH_ICON_SPRITE "assets/img/background/results/Icon4.png"
#define TIME_ICON_SPRITE "assets/img/background/results/Icon3.png"
#define ATTACK_ICON_SPRITE "assets/img/background/results/Icon5.png"
#define HEART_ICON_SPRITE "assets/img/background/results/Icon2.png"
#define POP_ICON_SOUND "assets/audio/SFX/PegandoItem1.wav"
#define COLLECTABLE_ICON_TIME 0.5
#define DEATH_ICON_TIME 2
#define TIME_ICON_TIME 1.5
#define ATTACK_ICON_TIME 2.5
#define HEART_ICON_TIME 1
#define YOUR_RANK_IS_TIME 3
#define LAYER1_BEGINING_POS_X -800
#define LAYER2_BEGINING_POS_X -1000
#define LAYER3_BEGINING_POS_X -1200
#define LAYER4_BEGINING_POS_X -1400
#define LAYER5_BEGINING_POS_X -1600
#define LAYER6_BEGINING_POS_X -1800
#define LAYER_BEGINING_POS_Y 0
#define LAYER_VELOCITY_Y 0
#define LAYER_VELOCITY_X 3
#define VICTORY_BG_MUSIC "assets/audio/TelaDeResultados.wav"
#include "State.h"
#include "LevelData.h"
#include "MovingLayer.h"

class VictoryState : public State {
    GameObject *layer1;
    GameObject *layer2;
    GameObject *layer3;
    GameObject *layer4;
    GameObject *layer5;
    GameObject *layer6;
    GameObject *bgMusic;
    GameObject *completeLayer;
    GameObject *yourRankIsLayer;
    GameObject *heartIconGO;
    GameObject *deathIconGO;
    GameObject *timeIconGO;
    GameObject *attackIconGO;
    GameObject *collectableIconGO;
    GameObject *popSoundGO;
    MovingLayer *movingLayer6;
    Sound *popSound;
    Sprite* completeLayerSprite;
    Sprite* yourRankIsLayerSprite;
    Sprite* heartIconSprite;
    Sprite* deathIconSprite;
    Sprite* timeIconSprite;
    Sprite* attackIconSprite;
    Sprite* collectableIconSprite;
    Timer heartIconTimer;
    Timer deathIconTimer;
    Timer timeIconTimer;
    Timer attackIconTimer;
    Timer collectableIconTimer;
    Timer yourRankIsTimer;
    Music *music;
    bool playedCompletedSound;
    bool playedCollectableIconSound;
    bool playedHeartIconSound;
    bool playedTimeIconSound;
    bool playedDeathIconSound;
    bool playedAttackIconSound;
    bool playedYourRankIsSound;
    public:
        VictoryState();
        void Pause();
        void Resume();
        void StartData();
        void Start();
        void Update(float dt);
        void LoadAssets();
};


#endif