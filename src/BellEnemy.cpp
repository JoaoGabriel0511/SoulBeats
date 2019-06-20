#include "../include/BellEnemy.h"

BellEnemy::BellEnemy(GameObject& associated, int movingDistance, int movingSpeed, GameObject * character) : Component(associated) {
    this->character = character;
    Collider* collider;
    collider = new Collider(associated, {2,2}, {-140,0});
    Start();
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
    side = RIGHT;
    bellEnemySprite = new Sprite(associated,ENEMY_IDLE_SPRITE,ENEMY_IDLE_FRAME_COUNT,ENEMY_IDLE_DURATION/ENEMY_IDLE_FRAME_COUNT);
    bellEnemySprite->SetScale({2,2});
}

void BellEnemy::Update(float dt) {
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
            }
            break;
        case LOOKING_LEFT:
            lookLeft.Update(dt);
            if(lookLeft.Get() >= ENEMY_LOOKING_LEFT_DURATION) {
                SwitchBellEnemyState(IDLE, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION/ENEMY_IDLE_FRAME_COUNT, &idleTimer);
            }
            break;
        default:
            break;
    }
}


void BellEnemy::SwitchBellEnemyState(BellEnemyState state, string sprite, int frameCount, float frameTime, Timer * timer){
    bellEnemySprite->SwitchSprite(sprite,frameCount,frameTime);
    timer->Restart();
    this->state = state;
}

void BellEnemy::Render() {}

void BellEnemy::NotifyCollision(GameObject& other) {
    if(other.GetComponent("Attack") != NULL){
        associated.RequestedDelete();
    }
}

BellEnemy::~BellEnemy() {
    character = NULL;
}