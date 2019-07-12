#include "../include/AccordionEnemy.h"
#include "Game.h"
#include "../include/LevelState.h"

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
    accordionEnemySprite = new Sprite(associated, ACCORDION_ENEMY_IDLE_SPRITE, ACCORDION_ENEMY_IDLE_FRAME_COUNT, (global_beat->GetFalseDuration()/3) / ACCORDION_ENEMY_IDLE_FRAME_COUNT);
    sound = new Sound(associated, ARCCORDION_SOUND);
    accordionEnemySprite->SetScale({2, 2});
    lifeBar = new GameObject();
    lifeBarSprite = new Sprite(*lifeBar, FULL_LIFE_BAR);
    lifeBarSprite->SetScale({2,2});
    lifeBar->box.x = associated.box.x + 63;
    lifeBar->box.y = associated.box.y - 10;
    lifeBar->box.z = 5;
    hp = 4;
    switched = false;
    tookHit = false;
    Game::GetInstance().GetCurrentStatePointer()->AddObject(lifeBar);
}

void AccordionEnemy::Update(float dt)
{
    if(global_beat->HasBegun()){
        switch (state)
        {
        case IDLE:
            inicialPos = associated.box.y;
            finalPos = associated.box.y - ACCORDION_ENEMY_JUMP_HEIGHT;
            idleTimer.Update(dt);
            if (idleTimer.Get() >= (global_beat->GetFalseDuration()/3))
            {
                SwitchAccordionEnemyState(CHARGING, ACCORDION_ENEMY_CHARGING_SPRITE, ACCORDION_ENEMY_CHARGING_FRAME_COUNT, ((float) (global_beat->GetFalseDuration()/3)/ACCORDION_ENEMY_CHARGING_FRAME_COUNT), &chargingTimer);
            }
            break;
        case CHARGING:
            chargingTimer.Update(dt);
            if(global_beat->GetOnBeat()) {
                if(!switched) {
                    float jumpDuration = ACCORDION_ENEMY_JUMP_HEIGHT / ACCORDION_ENEMY_VELOCITY_JUMPING;
                    SwitchAccordionEnemyState(JUMP, ACCORDION_ENEMY_JUMP_SPRITE, ACCORDION_ENEMY_JUMP_FRAME_COUNT, ((float) (global_beat->GetFalseDuration()/3)/ ACCORDION_ENEMY_JUMP_FRAME_COUNT), &jumpTimer);
                    velocityY = ACCORDION_ENEMY_VELOCITY_JUMPING;
                    if(Camera::IsOnCamera(associated.box)) {
                        sound->Play(1);
                    }
                    switched = true;
                }
            } else {
                switched = false;
            }
            break;
        case JUMP:
            if(associated.box.y <= finalPos) {
                velocityY = 0;
                associated.box.y = finalPos;
                state = BOING;
                accordionEnemySprite->SwitchSprite(ACCORDION_ENEMY_BOING_SPRITE, ACCORDION_ENEMY_BOING_FRAME_COUNT, (global_beat->GetFalseDuration()/3) / ACCORDION_ENEMY_BOING_FRAME_COUNT);
                boingTimer.Restart();
            }
            break;
        case BOING:
            boingTimer.Update(dt);
            if(global_beat->GetOnBeat()) {
                if(!switched) {
                    float fallDuration = ACCORDION_ENEMY_JUMP_HEIGHT / ACCORDION_ENEMY_VELOCITY_FALLING;
                    SwitchAccordionEnemyState(FALL, ACCORDION_ENEMY_FALL_SPRITE, ACCORDION_ENEMY_FALL_FRAME_COUNT, ((float) (global_beat->GetFalseDuration()/3)/ ACCORDION_ENEMY_FALL_FRAME_COUNT), &fallTimer);
                    velocityY = ACCORDION_ENEMY_VELOCITY_FALLING;
                    if(Camera::IsOnCamera(associated.box)) {
                        sound->Play(1);
                    }
                    switched = true;
                }
            } else {
                switched = false;
            }
            break;
        case FALL:
            if(associated.box.y >= inicialPos) {
                velocityY = 0;
                associated.box.y = inicialPos;
                state = IDLE;
                accordionEnemySprite->SwitchSprite(ACCORDION_ENEMY_IDLE_SPRITE, ACCORDION_ENEMY_IDLE_FRAME_COUNT, (global_beat->GetFalseDuration()/3) / ACCORDION_ENEMY_IDLE_FRAME_COUNT);
                idleTimer.Restart();
            }
            break;
        default:
            break;
        }
        if(tookHit) {
            blinkingTimer.Update(dt);
            if(blinkingTimer.Get() >= BLINKING_TIME) {
                tookHit = false;
                accordionEnemySprite->isBlinking = false;
            }
        }
        associated.box.y += velocityY;
        lifeBar->box.y = associated.box.y - 10;
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
    GameObject* explosion;
    Sprite* explosionSprite;
    GameObject * hitSpark;
    Sprite * hitSparkSprite;
    if (other.GetComponent("Attack") != NULL)
    {
        hitSpark = new GameObject();
        hitSparkSprite = new Sprite(*hitSpark, HIT_SPARK_SPRITE, HIT_SPARK_FRAME_COUNT, HIT_SPARK_DURATION/HIT_SPARK_FRAME_COUNT, HIT_SPARK_DURATION);
        hitSparkSprite->SetScale({2,2});
        hitSpark->box.z = 5;
        if(((Attack*)other.GetComponent("Attack").get())->isLeftSide) {
            hitSpark->box.x = associated.box.x;
        } else {
            hitSpark->box.x = associated.box.x + associated.box.w;
        }
        hitSpark->box.y = associated.box.y + (associated.box.h/2);
        Game::GetInstance().GetCurrentState().AddObject(hitSpark);
        if(((Character*) character->GetComponent("Character").get())->AttackOnBeat()) {
            hp=0;
            comboSystem->UpdateKilledEnemy();
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
            sound->Open(ACCORDION_ENEMY_DEATH_SOUND);
            sound->Play(1);
            LevelData::GetInstance().enemyData[index]->wasKilled = true;
            explosion = new GameObject();
            explosionSprite = new Sprite(*explosion, ACCORDION_ENEMY_DEATH_SPRITE, ACCORDION_ENEMY_DEATH_FRAME_COUNT, ACCORDION_ENEMY_DEATH_DURATION/ACCORDION_ENEMY_DEATH_FRAME_COUNT, ACCORDION_ENEMY_DEATH_DURATION);
            explosionSprite->SetScale({3,3});
            LevelData::GetInstance().enemyPoints += ACCORDION_POINTS;
            LevelData::GetInstance().enemyData[index]->wasKilled = true;
            explosion->box.z = 5;
            explosion->box.x = associated.box.x - explosion->box.w / 2;
            explosion->box.y = associated.box.y - explosion->box.h / 2;
            Game::GetInstance().GetCurrentState().AddObject(explosion);
            associated.RequestedDelete();
            //Resources::updateScore(10);
        } else {
            tookHit = true;
            accordionEnemySprite->isBlinking = true;
            blinkingTimer.Restart();
            sound->Open(ACCORDION_ENEMY_HIT_SOUND);
            sound->Play(1);
            ((Character*) character->GetComponent("Character").get())->HitKnockBack();
        }
        sound->Open(ARCCORDION_SOUND);
    }
}

AccordionEnemy::~AccordionEnemy()
{
    lifeBar->RequestedDelete();
    character = NULL;
}