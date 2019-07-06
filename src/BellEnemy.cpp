#include "../include/BellEnemy.h"

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
    bellEnemySprite = new Sprite(associated,ENEMY_IDLE_SPRITE,ENEMY_IDLE_FRAME_COUNT,ENEMY_IDLE_DURATION/ENEMY_IDLE_FRAME_COUNT);
    bellEnemySprite->SetScale({2,2});
    lifeBar = new GameObject();
    lifeBarSprite = new Sprite(*lifeBar, FULL_LIFE_BAR);
    lifeBarSprite->SetScale({2,2});
    lifeBar->box.x = associated.box.x + 63;
    lifeBar->box.y = associated.box.y - 50;
    lifeBar->box.z = 5;
    Game::GetInstance().GetCurrentStatePointer()->AddObject(lifeBar);
}

void BellEnemy::Update(float dt) {
    if(Camera::IsOnCamera(associated.box)) {
        switch (state) {
            case IDLE:
                idleTimer.Update(dt);
                if(idleTimer.Get() >= ENEMY_IDLE_DURATION) {
                    if(character->box.x > associated.box.x) {
                        SwitchBellEnemyState(LOOKING_LEFT, ENEMY_LOOKING_LEFT_SPRITE, ENEMY_LOOKING_LEFT_FRAME_COUNT, ENEMY_LOOKING_LEFT_DURATION/ENEMY_LOOKING_LEFT_FRAME_COUNT, &lookLeft);
                    } else{
                        SwitchBellEnemyState(LOOKING_RIGHT, ENEMY_LOOKING_RIGHT_SPRITE, ENEMY_LOOKING_RIGHT_FRAME_COUNT, ENEMY_LOOKING_RIGHT_DURATION / ENEMY_LOOKING_RIGHT_FRAME_COUNT, &lookRight);
                    }
                }
                break;
            case LOOKING_RIGHT:
                lookRight.Update(dt);
                if(lookRight.Get() >= ENEMY_LOOKING_RIGHT_DURATION) {
                    SwitchBellEnemyState(IDLE, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION/ENEMY_IDLE_FRAME_COUNT, &idleTimer);
                    sound->Open(BELL_SOUND);
                    sound->Play(1);
                }
                break;
            case LOOKING_LEFT:
                lookLeft.Update(dt);
                if(lookLeft.Get() >= ENEMY_LOOKING_LEFT_DURATION) {
                    SwitchBellEnemyState(IDLE, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION/ENEMY_IDLE_FRAME_COUNT, &idleTimer);
                    sound->Open(BELL_SOUND);
                    sound->Play(1);
                }
                break;
            default:
                break;
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
    if(other.GetComponent("Attack") != NULL) {
        if(state != IDLE) {
            sound->Open(ENEMY_HIT_SOUND);
            sound->Play(1);
            if(((Character*) character->GetComponent("Character").get())->AttackOnBeat()) {
                hp=0;
            } else {
                hp--;
            }
            if(hp == 1) {
                lifeBarSprite->SwitchSprite(HALF_LIFE_BAR, 1, 0);
            }
            if(hp <= 0) {
                LevelData::GetInstance().enemyData[index]->wasKilled = true;
                associated.RequestedDelete();
            }
        } else {
            sound->Open(ENEMY_DEFEND_SOUND);
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