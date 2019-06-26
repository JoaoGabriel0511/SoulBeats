#ifndef ACCORDION_ENEMY_H
#define ACCORDION_ENEMY_H
#include "Component.h"
#include "Sprite.h"
#define ENEMY_IDLE_SPRITE "assets/img/enemies/Accordion/SanfonaIdle.png"
#define ENEMY_IDLE_FRAME_COUNT 8
#define ENEMY_IDLE_DURATION 0.447
#define ENEMY_LOOKING_UP_SPRITE "assets/img/enemies/Accordion/SanfonaBoioing.png"
#define ENEMY_LOOKING_UP_FRAME_COUNT 4
#define ENEMY_LOOKING_UP_DURATION 0.447
#define ENEMY_LOOKING_DOWN_SPRITE "assets/img/enemies/Accordion/SanfonaDown.png"
#define ENEMY_LOOKING_DOWN_FRAME_COUNT 2
#define ENEMY_LOOKING_DOWN_DURATION 0.447

class AccordionEnemy : public Component
{
    float distance;
    enum AccordionEnemyState
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
    AccordionEnemyState state;
    int movingDistance;
    int movingSpeed;
    Sprite *accordionEnemySprite;
    Side side;
    Timer idleTimer;
    Timer lookDown;
    Timer lookUp;
    GameObject *character;
    void SwitchAccordionEnemyState(AccordionEnemyState state, string sprite, int frameCount, float frameTime, Timer *timer);

  public:
    AccordionEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character);
    ~AccordionEnemy();
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);
    bool Is(string type);
};

#endif