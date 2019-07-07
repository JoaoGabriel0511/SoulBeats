#ifndef ACCORDION_ENEMY_H
#define ACCORDION_ENEMY_H
#include "Component.h"
#include "Sprite.h"
#include "Character.h"
#include "Sound.h"
#include "LevelState.h"
#define ACCORDION_ENEMY_IDLE_SPRITE "assets/img/enemies/Accordion/SanfonaIdle.png"
#define ACCORDION_ENEMY_CHARGING_SPRITE "assets/img/enemies/Accordion/SanfonaCharge.png"
#define ACCORDION_ENEMY_JUMP_SPRITE "assets/img/enemies/Accordion/SanfonaJump.png"
#define ACCORDION_ENEMY_BOING_SPRITE "assets/img/enemies/Accordion/SanfonaBoioing.png"
#define ACCORDION_ENEMY_FALL_SPRITE "assets/img/enemies/Accordion/SanfonaFall.png"
#define ACCORDION_ENEMY_FALL_FRAME_COUNT 7
#define ACCORDION_ENEMY_FALL_DURATION 0.3
#define ACCORDION_ENEMY_BOING_FRAME_COUNT 4
#define ACCORDION_ENEMY_BOING_DURATION 0.2
#define ACCORDION_ENEMY_JUMP_FRAME_COUNT 7
#define ACCORDION_ENEMY_JUMP_DURATION 0.3
#define ACCORDION_ENEMY_JUMP_HEIGHT 250
#define ACCORDION_ENEMY_CHARGING_DURATION 0.583333333
#define ACCORDION_ENEMY_CHARGING_FRAME_COUNT 7
#define ACCORDION_ENEMY_IDLE_FRAME_COUNT 8
#define ACCORDION_ENEMY_IDLE_DURATION 0.666666667
#define ACCORDION_ENEMY_VELOCITY_FALLING 5
#define ACCORDION_ENEMY_VELOCITY_JUMPING -5
#define ACCORDION_ENEMY_DEATH_SPRITE "assets/img/enemies/Boom.png"
#define ACCORDION_ENEMY_DEATH_DURATION 0.5
#define ACCORDION_ENEMY_DEATH_FRAME_COUNT 10
#define ARCCORDION_SOUND "assets/audio/SFX/Sanfona1.wav"
#define ACCORDION_ENEMY_HIT_SOUND "assets/audio/SFX/GolpeForte2.wav"
#define FULL_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigosFull.png"
#define HALF_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigos1meio.png"
#define THREE_FOURTHS_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigos3quartos.png"
#define ONE_FOURTH_LIFE_BAR "assets/img/enemies/LifeBar/VidaInimigos1quarto.png"
#define HIT_SPARK_SPRITE "assets/img/enemies/HitSparks/Hit.png"
#define HIT_SPARK_DURATION 0.5
#define HIT_SPARK_FRAME_COUNT 8

class AccordionEnemy : public Component
{
    float velocityY;
    enum AccordionEnemyState
    {
        IDLE,
        CHARGING,
        JUMP,
        BOING,
        FALL
    };
    AccordionEnemyState state;
    Sprite *accordionEnemySprite;
    Timer boingTimer;
    Timer idleTimer;
    Timer chargingTimer;
    Timer jumpTimer;
    Timer fallTimer;
    float inicialPos;
    float finalPos;
    Sound *sound;
    GameObject *character;
    void SwitchAccordionEnemyState(AccordionEnemyState state, string sprite, int frameCount, float frameTime, Timer *timer);
    GameObject *lifeBar;
    Sprite *lifeBarSprite;
    int hp;
    int index;
    bool switched;
  public:
    AccordionEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character, int index);
    ~AccordionEnemy();
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);
    bool Is(string type);
};

#endif