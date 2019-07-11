#ifndef CHECK_POINT_H
#define CHECK_POINT_H
#define CHECK_POINT_INACTIVE_IDLE_SPRITE "assets/img/interactables/Checkpoint/CheckpointRedIdle.png"
#define CHECK_POINT_ACTIVE_IDLE_SPRITE "assets/img/interactables/Checkpoint/CheckpointGreenIdle.png"
#define CHECK_POINT_INACTIVE_SPIN_SPRITE "assets/img/interactables/Checkpoint/CheckpointRedRight.png"
#define CHECK_POINT_ACTIVE_SPIN_SPRITE "assets/img/interactables/Checkpoint/CheckpointGreenRight.png"
#define CHECK_POINT_ACTIVE_SPIN_FRAME_COUNT 8
#define CHECK_POINT_INACTIVE_SPIN_FRAME_COUNT 8
#define CHECK_POINT_ACTIVE_SPIN_DURATION 1.5
#define CHECK_POINT_INACTIVE_SPIN_DURATION 1.5
#define CHECK_POINT_SOUND "assets/audio/SFX/Checkpoint3(SOUL).wav"
#include "Component.h"
#include "LevelState.h"
#include "LevelData.h"
#include "Sprite.h"

class CheckPoint : public Component
{
    Sprite *checkPointSprite;
    Collider *checkPointCollider;
    enum CheckPointState {INACTIVE, ACTIVE, SPINING_ACTIVE, SPINING_INACTIVE};
    CheckPointState state;
    Timer spinTimer;
    int index;
    Sound *sound;
    public:
        CheckPoint(GameObject& associated, int index);
        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);
        void NotifyCollision (GameObject& other);
        ~CheckPoint();
};


#endif