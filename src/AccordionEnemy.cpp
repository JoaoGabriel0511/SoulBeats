#include "../include/AccordionEnemy.h"

AccordionEnemy::AccordionEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character) : Component(associated)
{
    this->character = character;
    Collider *collider;
    collider = new Collider(associated, {2, 2}, {-140, 0});
    Start();
}

bool AccordionEnemy::Is(string type)
{
    bool result = false;
    if (type == "AccordionEnemy")
    {
        result = true;
    }
    return result;
}

void AccordionEnemy::Start()
{
    state = IDLE;
    idleTimer.Restart();
    side = DOWN;
    accordionEnemySprite = new Sprite(associated, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION / ENEMY_IDLE_FRAME_COUNT);
    accordionEnemySprite->SetScale({2, 2});
}

void AccordionEnemy::Update(float dt)
{
    switch (state)
    {
    case IDLE:
        idleTimer.Update(dt);
        if (idleTimer.Get() >= ENEMY_IDLE_DURATION)
        {
            if (character->box.x > associated.box.x)
            {
                SwitchAccordionEnemyState(LOOKING_UP, ENEMY_LOOKING_UP_SPRITE, ENEMY_LOOKING_UP_FRAME_COUNT, ENEMY_LOOKING_UP_DURATION / ENEMY_LOOKING_UP_FRAME_COUNT, &lookUp);
            }
            else
            {
                SwitchAccordionEnemyState(LOOKING_DOWN, ENEMY_LOOKING_DOWN_SPRITE, ENEMY_LOOKING_DOWN_FRAME_COUNT, ENEMY_LOOKING_DOWN_DURATION / ENEMY_LOOKING_DOWN_FRAME_COUNT, &lookDown);
            }
        }
        break;
    case LOOKING_DOWN:
        lookDown.Update(dt);
        if (lookDown.Get() >= ENEMY_LOOKING_DOWN_DURATION)
        {
            SwitchAccordionEnemyState(IDLE, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION / ENEMY_IDLE_FRAME_COUNT, &idleTimer);
        }
        break;
    case LOOKING_UP:
        lookUp.Update(dt);
        if (lookUp.Get() >= ENEMY_LOOKING_UP_DURATION)
        {
            SwitchAccordionEnemyState(IDLE, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION / ENEMY_IDLE_FRAME_COUNT, &idleTimer);
        }
        break;
    default:
        break;
    }
}

void AccordionEnemy::SwitchAccordionEnemyState(AccordionEnemyState state, string sprite, int frameCount, float frameTime, Timer *timer)
{
    accordionEnemySprite->SwitchSprite(sprite, frameCount, frameTime);
    timer->Restart();
    this->state = state;
}

void AccordionEnemy::Render() {}

void AccordionEnemy::NotifyCollision(GameObject &other)
{
    if (other.GetComponent("Attack") != NULL)
    {
        associated.RequestedDelete();
    }
}

AccordionEnemy::~AccordionEnemy()
{
    character = NULL;
}