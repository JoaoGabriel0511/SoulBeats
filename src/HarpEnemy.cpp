#include "../include/HarpEnemy.h"
#include "Game.h"
#include "../include/LevelState.h"


HarpEnemy::HarpEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character, int index, bool moveX,
                     bool moveY) : Component(associated)
{
    this->character = character;
    Collider *collider;
    this->index = index;
    this->moveX = moveX;
    this->moveY = moveY;
    this->tookHit = false;
    //initalPos = associated.box;
    collider = new Collider(associated, {2, 2}, {-70, -80});
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
    hp = 3;
    switchSides.Restart();
    sound = new Sound(associated, HARP_SOUND);
    harpEnemySprite = new Sprite(associated, HARP_ENEMY_IDLE_SPRITE, HARP_ENEMY_IDLE_FRAME_COUNT, HARP_ENEMY_IDLE_DURATION / HARP_ENEMY_IDLE_FRAME_COUNT);
    harpEnemySprite->SetScale({2, 2});
    velocity = {-1 * HARP_ENEMY_VELOCITY_X, -1 * HARP_ENEMY_VELOCITY_Y};
    if(moveX && !moveY) {
        velocity.x = velocity.x * 6;
    } else {
        if(!moveX && moveY) {
            velocity.y = velocity.y * 3;
        }
    }
    lifeBar = new GameObject();
    lifeBarSprite = new Sprite(*lifeBar, FULL_LIFE_BAR);
    lifeBarSprite->SetScale({2,2});
    lifeBar->box.x = associated.box.x + 35;
    lifeBar->box.y = associated.box.y - 20;
    lifeBar->box.z = 5;
    switched = false;
    Game::GetInstance().GetCurrentStatePointer()->AddObject(lifeBar);
}

void HarpEnemy::Update(float dt)
{
	if(global_beat->HasBegun()) {
        if(moveY) {
            switch (state) {
                case LOOKING_DOWN:
                    lookDown.Update(dt);
                    if (global_beat->GetOnBeat()) {
                        if(!switched){
                            if(moveX) {
                                velocity.y = -1 * HARP_ENEMY_VELOCITY_Y;
                            } else {
                                velocity.y = -3 * HARP_ENEMY_VELOCITY_Y;
                            }
                            if (Camera::IsOnCamera(associated.box)) {
                                sound->Open(HARP_SOUND);
                                sound->Play(1);
                            }
                            SwitchHarpEnemyState(LOOKING_UP, HARP_ENEMY_LOOKING_UP_SPRITE, HARP_ENEMY_LOOKING_UP_FRAME_COUNT,
                                                HARP_ENEMY_LOOKING_UP_FRAME_TIME, &lookUp);
                            switched = true;
                        }
                    } else {
                        switched = false;
                    }
                    break;
                case LOOKING_UP:
                    lookUp.Update(dt);
                    if (global_beat->GetOnBeat()) {
                        if(!switched) {
                            if(moveX) {
                                velocity.y =  HARP_ENEMY_VELOCITY_Y;
                            } else {
                                velocity.y = 3 * HARP_ENEMY_VELOCITY_Y;
                            }
                            if (Camera::IsOnCamera(associated.box)) {
                                sound->Open(HARP_BACK_SOUND);
                                sound->Play(1);
                            }
                            SwitchHarpEnemyState(LOOKING_DOWN, HARP_ENEMY_LOOKING_DOWN_SPRITE, HARP_ENEMY_LOOKING_DOWN_FRAME_COUNT,
                                                HARP_ENEMY_LOOKING_UP_FRAME_TIME, &lookDown);
                            switched = true;
                        }
                    } else {
                        switched = false;
                    }
                    break;
                default:
                    break;
            }
        }
        if(moveX) {
            if(moveY) {
                switchSides.Update(dt);
                if (switchSides.Get() >= HARP_ENEMY_SWITCH_SIDES_TIME) {
                    switchSides.Restart();
                    if (harpEnemySprite->flip) {
                        harpEnemySprite->flip = false;
                        velocity.x = -1 * HARP_ENEMY_VELOCITY_X;
                    } else {
                        harpEnemySprite->flip = true;
                        velocity.x = HARP_ENEMY_VELOCITY_X;
                    }
                }
            } else {
                if(global_beat->GetOnBeat()){
                    if(!switched) {
                        if (harpEnemySprite->flip) {
                            harpEnemySprite->flip = false;
                            if(Camera::IsOnCamera(associated.box)){
                                sound->Open(HARP_BACK_SOUND);
                                sound->Play(1);
                            }
                            velocity.x = -6 * HARP_ENEMY_VELOCITY_X;
                        } else {
                            if(Camera::IsOnCamera(associated.box)){
                                sound->Open(HARP_SOUND);
                                sound->Play(1);
                            }
                            harpEnemySprite->flip = true;
                            velocity.x = 6 * HARP_ENEMY_VELOCITY_X;
                        }
                        switched = true;
                    }
                } else {
                    switched = false;
                }
            }
        }
        lifeBar->box.x = associated.box.x + 35;
        lifeBar->box.y = associated.box.y - 20;
        if(moveX) {
            associated.box.x += velocity.x * dt;
        }
        if(moveY) {
            associated.box.y += velocity.y * dt;
        }
        if(tookHit) {
            blinkingTimer.Update(dt);
            if(blinkingTimer.Get() >= BLINKING_TIME) {
                tookHit = false;
                harpEnemySprite->isBlinking = false;
            }
        }
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
    GameObject * explosion;
    Sprite * explosionSprite;
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
        } else {
            hp--;
        }
        if(hp == 1) {
            lifeBarSprite->SwitchSprite(ONE_THIRD_LIFE_BAR, 1, 0);
        }
        if(hp == 2) {
            lifeBarSprite->SwitchSprite(TWO_THIRDS_LIFE_BAR, 1, 0);
        }
        if(hp <= 0) {
            sound->Open(HARP_ENEMY_DEATH_SOUND);
            sound->Play(1);
            LevelData::GetInstance().enemyData[index]->wasKilled = true;
            explosion = new GameObject();
            explosionSprite = new Sprite(*explosion, HARP_ENEMY_DEATH_SPRITE, HARP_ENEMY_DEATH_FRAME_COUNT, HARP_ENEMY_DEATH_DURATION/HARP_ENEMY_DEATH_FRAME_COUNT, HARP_ENEMY_DEATH_DURATION);
            explosionSprite->SetScale({3,3});
            explosion->box.z = 5;
            explosion->box.x = associated.box.x - explosion->box.w / 2;
            explosion->box.y = associated.box.y - explosion->box.h / 2;
            Game::GetInstance().GetCurrentState().AddObject(explosion);
            associated.RequestedDelete();
            //Resources::updateScore(15);
        } else {
            tookHit = true;
            harpEnemySprite->isBlinking = true;
            blinkingTimer.Restart();
            sound->Open(HARP_ENEMY_HIT_SOUND);
            sound->Play(1);
            ((Character*) character->GetComponent("Character").get())->HitKnockBack();
        }
        sound->Open(HARP_SOUND);
    }
}

HarpEnemy::~HarpEnemy()
{
    lifeBar->RequestedDelete();
    character = NULL;
}