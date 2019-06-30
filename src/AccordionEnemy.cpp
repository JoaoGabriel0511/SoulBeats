#include "../include/AccordionEnemy.h"

AccordionEnemy::AccordionEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character, int index) : Component(associated)
{
    this->character = character;
    Collider *collider;
    collider = new Collider(associated, {2, 2}, {-120, -40}, {0, 20});
    velocityY = 0;
    this->index = index;
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
    accordionEnemySprite = new Sprite(associated, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION / ENEMY_IDLE_FRAME_COUNT);
    sound = new Sound(associated, ARCCORDION_SOUND);
    accordionEnemySprite->SetScale({2, 2});
    lifeBar = new GameObject();
    lifeBarSprite = new Sprite(*lifeBar, FULL_LIFE_BAR);
    lifeBarSprite->SetScale({2,2});
    lifeBar->box.x = associated.box.x + 63;
    lifeBar->box.y = associated.box.y - 10;
    lifeBar->box.z = 5;
    hp = 4;
    Game::GetInstance().GetCurrentStatePointer()->AddObject(lifeBar);
}

void AccordionEnemy::Update(float dt)
{
    switch (state)
    {
    case IDLE:
        inicialPos = associated.box.y;
        finalPos = associated.box.y - ENEMY_JUMP_HEIGHT;
        idleTimer.Update(dt);
        if (idleTimer.Get() >= ENEMY_IDLE_DURATION)
        {
            SwitchAccordionEnemyState(CHARGING, ENEMY_CHARGING_SPRITE, ENEMY_CHARGING_FRAME_COUNT, ((float) ENEMY_CHARGING_DURATION/ENEMY_CHARGING_FRAME_COUNT), &chargingTimer);
        }
        break;
    case CHARGING:
        chargingTimer.Update(dt);
        if(chargingTimer.Get() >= ENEMY_CHARGING_DURATION) {
            float jumpDuration = ENEMY_JUMP_HEIGHT / ENEMY_VELOCITY_JUMPING;
            SwitchAccordionEnemyState(JUMP, ENEMY_JUMP_SPRITE, ENEMY_JUMP_FRAME_COUNT, ((float) jumpDuration/ ENEMY_JUMP_FRAME_COUNT), &jumpTimer);
            velocityY = ENEMY_VELOCITY_JUMPING;
            if(Camera::IsOnCamera(associated.box)) {
                sound->Play(1);
            }
        }
        break;
    case JUMP:
        if(associated.box.y <= finalPos) {
            velocityY = 0;
            associated.box.y = finalPos;
            state = BOING;
            accordionEnemySprite->SwitchSprite(ENEMY_BOING_SPRITE, ENEMY_BOING_FRAME_COUNT, ENEMY_BOING_DURATION / ENEMY_BOING_FRAME_COUNT);
            boingTimer.Restart();
        }
        break;
    case BOING:
        boingTimer.Update(dt);
        if(boingTimer.Get() >= ENEMY_BOING_DURATION) {
            float fallDuration = ENEMY_JUMP_HEIGHT / ENEMY_VELOCITY_FALLING;
            SwitchAccordionEnemyState(FALL, ENEMY_FALL_SPRITE, ENEMY_FALL_FRAME_COUNT, ((float) fallDuration/ ENEMY_FALL_FRAME_COUNT), &fallTimer);
            velocityY = ENEMY_VELOCITY_FALLING;
            if(Camera::IsOnCamera(associated.box)) {
                sound->Play(1);
            }
        }
        break;
    case FALL:
        if(associated.box.y >= inicialPos) {
            velocityY = 0;
            associated.box.y = inicialPos;
            state = IDLE;
            accordionEnemySprite->SwitchSprite(ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION / ENEMY_IDLE_FRAME_COUNT);
            idleTimer.Restart();
        }
        break;
    default:
        break;
    }
    associated.box.y += velocityY;
    lifeBar->box.y = associated.box.y - 10;
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
        sound->Open(ENEMY_HIT_SOUND);
        sound->Play(1);
        if(((Character*) character->GetComponent("Character").get())->AttackOnBeat()) {
            hp-=2;
        } else {
            hp--;
        }
        if(hp == 1) {
            lifeBarSprite->SwitchSprite(ONE_FOURTH_LIFE_BAR, 1, 0);
        }
        if(hp == 2) {
            lifeBarSprite->SwitchSprite(HALF_LIFE_BAR, 1, 0);
        }
        if(hp == 3) {
            lifeBarSprite->SwitchSprite(THREE_FOURTHS_LIFE_BAR, 1, 0);
        }
        if(hp <= 0) {
            LevelData::GetInstance().enemyData[index]->wasKilled = true;
            associated.RequestedDelete();
        }
        ((Character*) character->GetComponent("Character").get())->HitKnockBack();
        sound->Open(ARCCORDION_SOUND);
    }
}

AccordionEnemy::~AccordionEnemy()
{
    lifeBar->RequestedDelete();
    character = NULL;
}