#include "../include/BellEnemy.h"
#include "Game.h"
#include "../include/LevelState.h"

BellEnemy::BellEnemy(GameObject& associated, int movingDistance, int movingSpeed, GameObject * character, int index) : Component(associated) {
    this->character = character;
    Collider* collider;
    sound = new Sound(associated);
    this->index = index;
    collider = new Collider(associated, {2,2}, {-140,0});
}

bool BellEnemy::Is(string type) {
    bool result = false;
    if(type == "BellEnemy"){
        result = true;
    }
    return result;
}

void BellEnemy::Start() {
    state = IDLE;
    idleTimer.Restart();
    hp = 2;
    side = RIGHT;
    bellEnemySprite = new Sprite(associated,BELL_ENEMY_IDLE_SPRITE,BELL_ENEMY_IDLE_FRAME_COUNT,BELL_ENEMY_IDLE_DURATION/BELL_ENEMY_IDLE_FRAME_COUNT);
    bellEnemySprite->SetScale({2,2});
    lifeBar = new GameObject();
    lifeBarSprite = new Sprite(*lifeBar, FULL_LIFE_BAR);
    lifeBarSprite->SetScale({2,2});
    lifeBar->box.x = associated.box.x + 63;
    lifeBar->box.y = associated.box.y - 50;
    lifeBar->box.z = 5;
    switched = false;
    tookHit = false;
    Game::GetInstance().GetCurrentStatePointer()->AddObject(lifeBar);
}

void BellEnemy::Update(float dt) {
    switch (state) {
        case IDLE:
            idleTimer.Update(dt);
            if(global_beat->GetOnBeat()) {
                if(!switched) {
                    if(character->box.x > associated.box.x) {
                        SwitchBellEnemyState(LOOKING_LEFT, BELL_ENEMY_LOOKING_LEFT_SPRITE, BELL_ENEMY_LOOKING_LEFT_FRAME_COUNT, (global_beat->GetFalseDuration()/2)/BELL_ENEMY_LOOKING_LEFT_FRAME_COUNT, &lookLeft);
                    } else{
                        SwitchBellEnemyState(LOOKING_RIGHT, BELL_ENEMY_LOOKING_RIGHT_SPRITE, BELL_ENEMY_LOOKING_RIGHT_FRAME_COUNT, (global_beat->GetFalseDuration()/2) / BELL_ENEMY_LOOKING_RIGHT_FRAME_COUNT, &lookRight);
                    }
                    switched = true;
                }
            } else {
                switched = false;
            }
            break;
        case LOOKING_RIGHT:
            lookRight.Update(dt);
            if(lookRight.Get() >= (global_beat->GetFalseDuration()/2)) {
                SwitchBellEnemyState(IDLE, BELL_ENEMY_IDLE_SPRITE, BELL_ENEMY_IDLE_FRAME_COUNT, (global_beat->GetFalseDuration()/2)/BELL_ENEMY_IDLE_FRAME_COUNT, &idleTimer);
                sound->Open(BELL_SOUND);
                if(Camera::IsOnCamera(associated.box)) {
                    sound->Play(1);
                }
            }
            break;
        case LOOKING_LEFT:
            lookLeft.Update(dt);
            if(lookLeft.Get() >= (global_beat->GetFalseDuration()/2)) {
                SwitchBellEnemyState(IDLE, BELL_ENEMY_IDLE_SPRITE, BELL_ENEMY_IDLE_FRAME_COUNT, (global_beat->GetFalseDuration()/2)/BELL_ENEMY_IDLE_FRAME_COUNT, &idleTimer);
                sound->Open(BELL_SOUND);
                if(Camera::IsOnCamera(associated.box)) {
                    sound->Play(1);
                }
            }
            break;
        default:
            break;
    }
    if(tookHit) {
        blinkingTimer.Update(dt);
        if(blinkingTimer.Get() >= BLINKING_TIME) {
            tookHit = false;
            cout<<"aqui"<<endl;
            bellEnemySprite->isBlinking = false;
        }
    }
}


void BellEnemy::SwitchBellEnemyState(BellEnemyState state, string sprite, int frameCount, float frameTime, Timer * timer){
    bellEnemySprite->SwitchSprite(sprite,frameCount,frameTime);
    timer->Restart();
    this->state = state;
}

void BellEnemy::Render() {}

void BellEnemy::NotifyCollision(GameObject& other) {
    GameObject * explosion;
    Sprite * explosionSprite;
    GameObject * hitSpark;
    Sprite * hitSparkSprite;
    if(other.GetComponent("Attack") != NULL) {
        if(state != IDLE) {
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
                lifeBarSprite->SwitchSprite(HALF_LIFE_BAR, 1, 0);
            }
            if(hp <= 0) {
                sound->Open(BELL_ENEMY_DEATH_SOUND);
                sound->Play(1);
                LevelData::GetInstance().enemyData[index]->wasKilled = true;
                explosion = new GameObject();
                explosionSprite = new Sprite(*explosion, BELL_ENEMY_DEATH_SPRITE, BELL_ENEMY_DEATH_FRAME_COUNT, BELL_ENEMY_DEATH_DURATION/BELL_ENEMY_DEATH_FRAME_COUNT, BELL_ENEMY_DEATH_DURATION);
                explosionSprite->SetScale({3,3});
                explosion->box.z = 5;
                explosion->box.x = associated.box.x - explosion->box.w / 2;
                explosion->box.y = associated.box.y - explosion->box.h / 2;
                Game::GetInstance().GetCurrentState().AddObject(explosion);
                associated.RequestedDelete();
            } else {
                bellEnemySprite->isBlinking = true;
                tookHit = true;
                blinkingTimer.Restart();
                sound->Open(BELL_ENEMY_HIT_SOUND);
                sound->Play(1);
            }
        } else {
            sound->Open(BELL_ENEMY_DEFEND_SOUND);
            sound->Play(1);
        }
        if(hp > 0) {
            ((Character*) character->GetComponent("Character").get())->HitKnockBack();
        }
        sound->Open(BELL_SOUND);
    }
}

BellEnemy::~BellEnemy() {
	sound->Stop();
    lifeBar->RequestedDelete();
    character = NULL;
}