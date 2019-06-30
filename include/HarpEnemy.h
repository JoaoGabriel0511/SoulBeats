#ifndef HARP_ENEMY_H
#define HARP_ENEMY_H
#include "Component.h"
#include "Sprite.h"
#include "Character.h"
#include "LevelData.h"
#define ENEMY_IDLE_SPRITE "assets/img/enemies/Harp/HarpNormal.png"
#define ENEMY_IDLE_FRAME_COUNT 16
#define ENEMY_IDLE_DURATION 0.447
#define ENEMY_LOOKING_UP_SPRITE "assets/img/enemies/Harp/HarpUp.png"
#define ENEMY_LOOKING_UP_FRAME_COUNT 16
#define ENEMY_LOOKING_UP_FRAME_TIME 0.0877
#define ENEMY_LOOKING_DOWN_FRAME_TIME 0.0877
#define ENEMY_LOOKING_UP_DURATION 1
#define ENEMY_LOOKING_DOWN_SPRITE "assets/img/enemies/Harp/HarpDown.png"
#define ENEMY_LOOKING_DOWN_FRAME_COUNT 16
#define ENEMY_LOOKING_DOWN_DURATION 1
#define ENEMY_SWITCH_SIDES_TIME 4
#define ENEMY_VELOCITY_X 1
#define ENEMY_VELOCITY_Y 1
#define ENEMY_HIT_SOUND "assets/audio/SFX/GolpeForte2.wav"
#define HARP_SOUND "assets/audio/SFX/Harp1.wav"
#define FULL_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigosFull.png"
#define TWO_THIRDS_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigos2terços.png"
#define ONE_THIRD_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigos1terço.png"

class HarpEnemy : public Component
{
    float distance;
    enum HarpEnemyState
    {
        IDLE,
        LOOKING_DOWN,
        LOOKING_UP,
        MOVING_DOWN,
        MOVING_UP
    };
    enum Side
    {
        UP,
        DOWN
    };
    HarpEnemyState state;
    int movingDistance;
    int movingSpeed;
    Sprite *harpEnemySprite;
    Side side;
    Sound *sound;
    Timer idleTimer;
    Timer lookDown;
    Timer lookUp;
    Timer switchSides;
    GameObject *character;
    Vect2 velocity;
    Rect initalPos;
    int hp;
    GameObject *lifeBar;
    Sprite *lifeBarSprite;
    int index;
    void SwitchHarpEnemyState(HarpEnemyState state, string sprite, int frameCount, float frameTime, Timer *timer);

  public:
    HarpEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character, int index);
    ~HarpEnemy();
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);
    bool Is(string type);
};

#endif