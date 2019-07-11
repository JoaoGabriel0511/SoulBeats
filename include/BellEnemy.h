#ifndef BELL_ENEMY_H
#define BELL_ENEMY_H
#include "Component.h"
#include "Sprite.h"
#include "Character.h"
#include "LevelData.h"
#define BELL_ENEMY_IDLE_SPRITE "assets/img/enemies/BelIdlel.png"
#define BELL_ENEMY_IDLE_FRAME_COUNT 9
#define BELL_ENEMY_IDLE_DURATION 0.747
#define BELL_ENEMY_LOOKING_LEFT_SPRITE "assets/img/enemies/BelIPeekL.png"
#define BELL_ENEMY_LOOKING_LEFT_FRAME_COUNT 9
#define BELL_ENEMY_LOOKING_LEFT_DURATION 0.747
#define BELL_ENEMY_LOOKING_RIGHT_SPRITE "assets/img/enemies/BelIPeekR.png"
#define BELL_ENEMY_LOOKING_RIGHT_FRAME_COUNT 9
#define BELL_ENEMY_LOOKING_RIGHT_DURATION 0.747
#define BELL_ENEMY_DEATH_SPRITE "assets/img/enemies/Boom.png"
#define BELL_ENEMY_DEATH_DURATION 0.5
#define BELL_ENEMY_DEATH_FRAME_COUNT 10
#define BELL_ENEMY_HIT_SOUND "assets/audio/SFX/GolpeForte2.wav"
#define BELL_ENEMY_DEATH_SOUND "assets/audio/SFX/InimigoMorrendo3(SOUL).wav"
#define BELL_ENEMY_DEFEND_SOUND "assets/audio/SFX/DefesaSino(Soul).wav"
#define BELL_SOUND "assets/audio/SFX/Sino1.wav"
#define FULL_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigosFull.png"
#define HALF_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigos1meio.png"
#define HIT_SPARK_SPRITE "assets/img/enemies/HitSparks/Hit.png"
#define HIT_SPARK_DURATION 0.5
#define BLINKING_TIME 0.2
#define HIT_SPARK_FRAME_COUNT 5

class BellEnemy : public Component {
    float distance;
    GameObject *lifeBar;
    Sprite *lifeBarSprite;
    enum BellEnemyState { IDLE, LOOKING_RIGHT, LOOKING_LEFT, MOVING_RIGHT, MOVING_LEFT };
    enum Side {LEFT,RIGHT};
    BellEnemyState state;
    int movingDistance;
    int movingSpeed;
    Sprite *bellEnemySprite;
    Side side;
    Timer idleTimer;
    Timer lookRight;
    Timer lookLeft;
    Timer blinkingTimer;
    GameObject *character;
    Sound *sound;
    int index;
    bool tookHit;
    int hp;
    bool switched;
    void SwitchBellEnemyState(BellEnemyState state, string sprite, int frameCount, float frameTime, Timer * timer);
    public:
        BellEnemy(GameObject& associated, int movingDistance, int movingSpeed, GameObject *character, int index);
        ~BellEnemy();
        void Update(float dt);
        void Render();
        void Start();
        void NotifyCollision(GameObject& other);
        bool Is(string type);
};


#endif