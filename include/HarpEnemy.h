#ifndef HARP_ENEMY_H
#define HARP_ENEMY_H
#include "Component.h"
#include "Sprite.h"
#define ENEMY_IDLE_SPRITE "assets/img/enemies/Harp/HarpNormal.png"
#define ENEMY_IDLE_FRAME_COUNT 5
#define ENEMY_IDLE_DURATION 0.447
#define ENEMY_LOOKING_UP_SPRITE "assets/img/enemies/Harp/HarpUp.png"
#define ENEMY_LOOKING_UP_FRAME_COUNT 4
#define ENEMY_LOOKING_UP_DURATION 0.447
#define ENEMY_LOOKING_DOWN_SPRITE "assets/img/enemies/Harp/HarpDown.png"
#define ENEMY_LOOKING_DOWN_FRAME_COUNT 9
#define ENEMY_LOOKING_DOWN_DURATION 0.447

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
    Timer idleTimer;
    Timer lookDown;
    Timer lookUp;
    GameObject *character;
    void SwitchHarpEnemyState(HarpEnemyState state, string sprite, int frameCount, float frameTime, Timer *timer);

  public:
    HarpEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character);
    ~HarpEnemy();
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);
    bool Is(string type);
};

#endif