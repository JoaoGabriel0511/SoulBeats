#ifndef VICTORY_STATE
#define VICTORY_STATE
#define VICTORY_LAYER1_SPRITE "assets/img/background/results/ResultsCamada1.png"
#define VICTORY_LAYER2_SPRITE "assets/img/background/results/ResultsCamada2.png"
#define VICTORY_LAYER3_SPRITE "assets/img/background/results/ResultsCamada3.png"
#define VICTORY_LAYER4_SPRITE "assets/img/background/results/ResultsCamada4.png"
#define VICTORY_LAYER5_SPRITE "assets/img/background/results/ResultsCamada5.png"
#define VICTORY_LAYER6_SPRITE "assets/img/background/results/ResultsCamada6.png"
#define COMPLETE_SPRITE "assets/img/background/results/ResultsClear.png"
#define YOUR_RANK_IS_SPRITE "assets/img/background/results/ResultsYourRanking2.png"
#define RESULT_SPRITE "assets/img/background/results/ResultsResults.png"
#define COLLECTABLE_ICON_SPRITE "assets/img/background/results/Icon1.png"
#define DEATH_ICON_SPRITE "assets/img/background/results/Icon4.png"
#define TIME_ICON_SPRITE "assets/img/background/results/Icon3.png"
#define ATTACK_ICON_SPRITE "assets/img/background/results/Icon5.png"
#define HEART_ICON_SPRITE "assets/img/background/results/Icon2.png"
#define POP_ICON_SOUND "assets/audio/SFX/PegandoItem1.wav"
#define COLLECTABLE_ICON_TIME 1 * 0.5
#define DEATH_ICON_TIME 4 * 0.5
#define TIME_ICON_TIME 3 * 0.5
#define ATTACK_ICON_TIME 5 * 0.5
#define HEART_ICON_TIME 2 * 0.5
#define RESULT_TIME 6 * 0.5
#define YOUR_RANK_IS_TIME 7 * 0.5
#define LAYER1_BEGINING_POS_X -800
#define LAYER2_BEGINING_POS_X -1000
#define LAYER3_BEGINING_POS_X -1200
#define LAYER4_BEGINING_POS_X -1400
#define LAYER5_BEGINING_POS_X -1600
#define LAYER6_BEGINING_POS_X -1800
#define LAYER_BEGINING_POS_Y 0
#define LAYER_VELOCITY_Y 0
#define LAYER_VELOCITY_X 3
#define SWITCH_MUSIC_TIME 20
#define COLLECTABLES_POINTS 2000
#define DEATH_PENALTHY 10000
#define DAMAGE_PENALTHY 100
#define UNDER_TWO_MIN_POINTS 10000
#define UNDER_TREE_MIN_POINTS 5000
#define UNDER_FOUR_MIN_POINTS 2500
#define MORE_THAN_FOUR_MIN_POINTS 0
#define MAESTRO_SPRITE "assets/img/Rankings/maestro (1).png"
#define MAESTRO_FRAME_COUNT 5
#define MAESTRO_FRAME_TIME 0.0877
#define FIASCO_SPRITE "assets/img/Rankings/fiasco (1).png"
#define FIASCO_FRAME_COUNT 1
#define FIASCO_FRAME_TIME 0.0877
#define CATCHY_SPRITE "assets/img/Rankings/Catchy (1).png"
#define CATCHY_FRAME_COUNT 6
#define CATCHY_FRAME_TIME 0.0877
#define BRAVO_SPRITE "assets/img/Rankings/BRAVO (1).png"
#define BRAVO_FRAME_COUNT 10
#define BRAVO_FRAME_TIME 0.0877
#define CATCHY_LIMIT 10000
#define BRAVO_LIMIT 20000
#define MAESTRO_LIMIT 30000
#define VICTORY_BG_MUSIC "assets/audio/FINAL2.1(Soul.Mus).wav"
#define VICTORY_BG_MUSIC_2 "assets/audio/TelaDeResultados.wav"
#include "State.h"
#include "Text.h"
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
    GameObject *resultLayer;
    GameObject *resultScore;
    GameObject *heartIconGO;
    GameObject *damageScoreGO;
    GameObject *deathIconGO;
    GameObject *deathScoreGO;
    GameObject *timeIconGO;
    GameObject *timeScoreGO;
    GameObject *attackIconGO;
    GameObject *attackScoreGO;
    GameObject *collectableIconGO;
    GameObject *collectableScoreGO;
    GameObject *popSoundGO;
    GameObject *rankGO;
    MovingLayer *movingLayer6;
    Sound *popSound;
    Sprite* completeLayerSprite;
    Sprite* yourRankIsLayerSprite;
    Sprite* heartIconSprite;
    Sprite* deathIconSprite;
    Sprite* timeIconSprite;
    Sprite* attackIconSprite;
    Sprite* resultSprite;
    Sprite* collectableIconSprite;
    Sprite* rankSprite;
    Text* damageScoreText;
    Text* deathScoreText;
    Text* timeScoreText;
    Text* collectableScoreText;
    Text* attackScoreText;
    Text* resultScoreText;
    Timer heartIconTimer;
    Timer deathIconTimer;
    Timer timeIconTimer;
    Timer attackIconTimer;
    Timer collectableIconTimer;
    Timer yourRankIsTimer;
    Timer resultTimer;
    Timer switchMusicTimer;
    Music *music;
    bool playedCompletedSound;
    bool playedResultSound;
    bool playedCollectableIconSound;
    bool playedHeartIconSound;
    bool playedTimeIconSound;
    bool playedDeathIconSound;
    bool playedAttackIconSound;
    bool switchedMusic;
    bool playedYourRankIsSound;
    int collectablesPoints;
    int deathPenalthy;
    int damagePenalthy;
    int timePoints;
    int result;
    void CalculatePoints();
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