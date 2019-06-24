#ifndef BELL_ENEMY_H
#define BELL_ENEMY_H
#include "Component.h"
#include "Sprite.h"
#include "Character.h"
#define ENEMY_IDLE_SPRITE "assets/img/enemies/BelIdlel.png"
#define ENEMY_IDLE_FRAME_COUNT 9
#define ENEMY_IDLE_DURATION 0.747
#define ENEMY_LOOKING_LEFT_SPRITE "assets/img/enemies/BelIPeekL.png"
#define ENEMY_LOOKING_LEFT_FRAME_COUNT 9
#define ENEMY_LOOKING_LEFT_DURATION 0.747
#define ENEMY_LOOKING_RIGHT_SPRITE "assets/img/enemies/BelIPeekR.png"
#define ENEMY_LOOKING_RIGHT_FRAME_COUNT 9
#define ENEMY_LOOKING_RIGHT_DURATION 0.747

class BellEnemy : public Component {
    float distance;
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
    GameObject *character;
    void SwitchBellEnemyState(BellEnemyState state, string sprite, int frameCount, float frameTime, Timer * timer);
    public:
        BellEnemy(GameObject& associated, int movingDistance, int movingSpeed, GameObject *character);
        ~BellEnemy();
        void Update(float dt);
        void Render();
        void Start();
        void NotifyCollision(GameObject& other);
        bool Is(string type);
};


#endif