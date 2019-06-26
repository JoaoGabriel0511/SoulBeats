#include "../include/HarpEnemy.h"

HarpEnemy::HarpEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character) : Component(associated)
{
    this->character = character;
    Collider *collider;
    collider = new Collider(associated, {2, 2}, {-70, -80});
    Start();
}

bool HarpEnemy::Is(string type)
{
    bool result = false;
    if (type == "HarpEnemy")
    {
        result = true;
    }
    return result;
}

void HarpEnemy::Start()
{
    state = LOOKING_UP;
    idleTimer.Restart();
    side = DOWN;
    harpEnemySprite = new Sprite(associated, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION / ENEMY_IDLE_FRAME_COUNT);
    harpEnemySprite->SetScale({2, 2});
}

void HarpEnemy::Update(float dt)
{
    switch (state)
    {
    case LOOKING_DOWN:
        lookDown.Update(dt);
        if (lookDown.Get() >= ENEMY_LOOKING_DOWN_DURATION)
        {
            SwitchHarpEnemyState(LOOKING_UP, ENEMY_LOOKING_UP_SPRITE, ENEMY_LOOKING_UP_FRAME_COUNT, ENEMY_LOOKING_UP_DURATION / ENEMY_LOOKING_UP_FRAME_COUNT, &lookUp);
        }
        break;
    case LOOKING_UP:
        lookUp.Update(dt);
        if (lookUp.Get() >= ENEMY_LOOKING_UP_DURATION)
        {
            SwitchHarpEnemyState(LOOKING_DOWN, ENEMY_LOOKING_DOWN_SPRITE, ENEMY_LOOKING_DOWN_FRAME_COUNT, ENEMY_LOOKING_DOWN_DURATION / ENEMY_LOOKING_DOWN_FRAME_COUNT, &lookDown);
        }
        break;
    default:
        break;
    }
}

void HarpEnemy::SwitchHarpEnemyState(HarpEnemyState state, string sprite, int frameCount, float frameTime, Timer *timer)
{
    harpEnemySprite->SwitchSprite(sprite, frameCount, frameTime);
    timer->Restart();
    this->state = state;
}

void HarpEnemy::Render() {}

void HarpEnemy::NotifyCollision(GameObject &other)
{
    if (other.GetComponent("Attack") != NULL)
    {
        associated.RequestedDelete();
    }
}

HarpEnemy::~HarpEnemy()
{
    character = NULL;
}