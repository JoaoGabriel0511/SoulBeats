#include "../include/Collectable.h"


Collectable::Collectable(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character) : Component(associated)
{
    this->character = character;
    Collider *collider;
    sound = new Sound(associated);
    collider = new Collider(associated, {2, 2}, {-140, 0});
    Start();
}

bool Collectable::Is(string type)
{
    bool result = false;
    if (type == "Collectable")
    {
        result = true;
    }
    return result;
}

void Collectable::Start()
{
    state = IDLE;
    idleTimer.Restart();
    collectableSprite = new Sprite(associated, COLLECTABLE_IDLE_SPRITE, COLLECTABLE_IDLE_FRAME_COUNT, COLLECTABLE_IDLE_DURATION / COLLECTABLE_IDLE_FRAME_COUNT);
    collectableSprite->SetScale({2, 2});
}

void Collectable::Update(float dt)
{

    if (Camera::IsOnCamera(associated.box))
    {
        switch (state)
        {
        case IDLE:
            idleTimer.Update(dt);
            break;
        default:
            break;
        }
    }
}

void Collectable::SwitchCollectableState(CollectableState state, string sprite, int frameCount, float frameTime, Timer *timer)
{
    collectableSprite->SwitchSprite(sprite, frameCount, frameTime);
    timer->Restart();
    this->state = state;
}

void Collectable::Render() {}

void Collectable::NotifyCollision(GameObject &other)
{
    if (other.GetComponent("Character") != NULL)
    {
        Resources::updateScore();
        sound->Open(COLLECTABLE_HIT_SOUND);
        sound->Play(1);
        associated.RequestedDelete();
    }
}

Collectable::~Collectable()
{
    character = NULL;
}