#include "../include/HarpEnemy.h"

HarpEnemy::HarpEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character) : Component(associated)
{
    this->character = character;
    Collider *collider;
    //initalPos = associated.box;
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
    switchSides.Restart();
    sound = new Sound(associated, HARP_SOUND);
    harpEnemySprite = new Sprite(associated, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION / ENEMY_IDLE_FRAME_COUNT);
    harpEnemySprite->SetScale({2, 2});
    velocity = {-1 * ENEMY_VELOCITY_X, -1 * ENEMY_VELOCITY_Y};
}

void HarpEnemy::Update(float dt)
{
    switch (state)
    {
    case LOOKING_DOWN:
        lookDown.Update(dt);
        if (lookDown.Get() >= ENEMY_LOOKING_DOWN_DURATION)
        {
            velocity.y = -1 * ENEMY_VELOCITY_Y;
            if(Camera::IsOnCamera(associated.box)) {
                sound->Play(1);
            }
            SwitchHarpEnemyState(LOOKING_UP, ENEMY_LOOKING_UP_SPRITE, ENEMY_LOOKING_UP_FRAME_COUNT, ENEMY_LOOKING_UP_FRAME_TIME, &lookUp);
        }
        break;
    case LOOKING_UP:
        lookUp.Update(dt);
        if (lookUp.Get() >= ENEMY_LOOKING_UP_DURATION)
        {
            velocity.y = ENEMY_VELOCITY_Y;
            if(Camera::IsOnCamera(associated.box)) {
                sound->Play(1);
            }
            SwitchHarpEnemyState(LOOKING_DOWN, ENEMY_LOOKING_DOWN_SPRITE, ENEMY_LOOKING_DOWN_FRAME_COUNT, ENEMY_LOOKING_UP_FRAME_TIME, &lookDown);
        }
        break;
    default:
        break;
    }
    switchSides.Update(dt);
    if(switchSides.Get() >= ENEMY_SWITCH_SIDES_TIME) {
        if(Camera::IsOnCamera(associated.box)) {
            sound->Play(1);
        }
        switchSides.Restart();
        if(harpEnemySprite->flip) {
            harpEnemySprite->flip = false;
            velocity.x = -1 * ENEMY_VELOCITY_X;
        } else {
            harpEnemySprite->flip = true;
            velocity.x = ENEMY_VELOCITY_X;
        }
    }
    associated.box += velocity;
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
        sound->Open(ENEMY_HIT_SOUND);
        sound->Play(1);
        associated.RequestedDelete();
        ((Character*) character->GetComponent("Character").get())->HitKnockBack();
    }
}

HarpEnemy::~HarpEnemy()
{
    character = NULL;
}