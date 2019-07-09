#include "../include/CheckPoint.h"

CheckPoint::CheckPoint(GameObject& associated, int index) : Component(associated) {
    this->index = index;
}

CheckPoint::~CheckPoint() {}

bool CheckPoint::Is(string type) {
    bool result = false;
    if(type == "CheckPoint") {
        result = true;
    }
    return result;
}

void CheckPoint::Start() {
    if(LevelData::GetInstance().checkPointData[index]->isActive == false) {
        state = INACTIVE;
        spinTimer.Restart();
        checkPointSprite = new Sprite(associated, CHECK_POINT_INACTIVE_IDLE_SPRITE);
    } else {
        state = ACTIVE;
        checkPointSprite = new Sprite(associated, CHECK_POINT_ACTIVE_IDLE_SPRITE);
    }
    checkPointSprite->SetScale({2,2});
    this->sound = new Sound(associated, CHECK_POINT_SOUND);
    checkPointCollider = new Collider(associated, {2,2}, {-130, 0});
}

void CheckPoint::Render() {}

void CheckPoint::Update(float dt) {
    switch (state)
    {
    case SPINING_INACTIVE:
        spinTimer.Update(dt);
        if(spinTimer.Get() >= CHECK_POINT_INACTIVE_SPIN_DURATION) {
            spinTimer.Restart();
            checkPointSprite->SwitchSprite(CHECK_POINT_ACTIVE_SPIN_SPRITE, CHECK_POINT_ACTIVE_SPIN_FRAME_COUNT, CHECK_POINT_ACTIVE_SPIN_DURATION/(8*CHECK_POINT_ACTIVE_SPIN_FRAME_COUNT));
            state = SPINING_ACTIVE;
        }
        break;
    case SPINING_ACTIVE:
        spinTimer.Update(dt);
        if(spinTimer.Get() >= CHECK_POINT_ACTIVE_SPIN_DURATION) {
            spinTimer.Restart();
            checkPointSprite->SwitchSprite(CHECK_POINT_ACTIVE_IDLE_SPRITE, 1, 0);
            state = ACTIVE;
        }
        break;
    default:
        break;
    }
}

void CheckPoint::NotifyCollision(GameObject& other) {
    if(state == INACTIVE && other.GetComponent("Character") != NULL) {
        sound->Play(1);
        LevelData::GetInstance().checkPointData[index]->isActive = true;
        /*if(!LevelData::GetInstance().switchedBegininMusic) {
            LevelData::GetInstance().switchedBegininMusic = true;
        } else {
            if(!LevelData::GetInstance().switchedDevelopmentMusic) {
                LevelData::GetInstance().switchedDevelopmentMusic = true;
            }
        }*/
        if(LevelData::GetInstance().pos == NULL) {
            LevelData::GetInstance().pos = new Vect2(associated.box.x, associated.box.y);
        } else {
            LevelData::GetInstance().pos->x = associated.box.x;
            LevelData::GetInstance().pos->y = associated.box.y;
        }
        for(int i = 0; i < LevelData::GetInstance().enemyData.size(); i++) {
            LevelData::GetInstance().enemyData[i]->isDead = LevelData::GetInstance().enemyData[i]->wasKilled;
        }
        for(int i = 0; i < LevelData::GetInstance().collectableData.size(); i++) {
            LevelData::GetInstance().collectableData[i]->isCollected = LevelData::GetInstance().collectableData[i]->wasCollected;
        }
        state = SPINING_INACTIVE;
        checkPointSprite->SwitchSprite(CHECK_POINT_INACTIVE_SPIN_SPRITE, CHECK_POINT_INACTIVE_SPIN_FRAME_COUNT, CHECK_POINT_INACTIVE_SPIN_DURATION/(8*CHECK_POINT_INACTIVE_SPIN_FRAME_COUNT));
    }
}

