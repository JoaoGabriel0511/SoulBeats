#include "../include/BellEnemy.h"

BellEnemy::BellEnemy(GameObject& associated, int movingDistance, int movingSpeed) : Component(associated) {
    Start(movingDistance, movingSpeed);
}

bool BellEnemy::Is(string type) {
    bool result = false;
    if(type == "BellEnemy"){
        result = true;
    }
    return result;
}

void BellEnemy::Start(int movingDistance, int movingSpeed) {
    state = IDLE;
    idleTimer.Restart();
    this->movingDistance = movingDistance;
    this->movingSpeed = movingSpeed;
    side = RIGHT;
    bellEnemySprite = new Sprite(associated,ENEMY_IDLE_SPRITE,ENEMY_IDLE_FRAME_COUNT,ENEMY_IDLE_DURATION/ENEMY_IDLE_FRAME_COUNT);
}

void BellEnemy::Update(float dt) {
    switch (state) {
        case IDLE:
            idleTimer.Update(dt);
            if(idleTimer.Get() >= ENEMY_IDLE_DURATION) {
                SwitchBellEnemyState(LOOKING_LEFT, ENEMY_LOOKING_LEFT_SPRITE, ENEMY_LOOKING_LEFT_FRAME_COUNT, ENEMY_LOOKING_LEFT_DURATION/ENEMY_LOOKING_LEFT_FRAME_COUNT, &lookLeft);
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
                SwitchBellEnemyState(LOOKING_RIGHT, ENEMY_LOOKING_RIGHT_SPRITE, ENEMY_LOOKING_RIGHT_FRAME_COUNT, ENEMY_LOOKING_RIGHT_DURATION / ENEMY_LOOKING_RIGHT_FRAME_COUNT, &lookRight);
            }
            break;
        default:
            break;
    }
}


void BellEnemy::SwitchBellEnemyState(BellEnemyState state, string sprite, int frameCount, float frameTime, Timer * timer){
    bellEnemySprite->SetFrameCount(frameCount);
    bellEnemySprite->SetFrameTime(frameTime);
    bellEnemySprite->Open(sprite);
    timer->Restart();
    this->state = state;
}

void BellEnemy::Render() {}