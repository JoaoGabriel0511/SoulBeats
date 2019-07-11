#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "Component.h"
#include "Sprite.h"
#include "Character.h"
#include "LevelData.h"
#define COLLECTABLE_IDLE_SPRITE "assets/img/interactables/Collectable.png"
#define COLLECTABLE_IDLE_FRAME_COUNT 8
#define COLLECTABLE_IDLE_DURATION 0.747
#define COLLECTABLE_HIT_SOUND "assets/audio/SFX/PegandoItem2.1(Soul).wav"
using namespace std;

class Collectable : public Component
{
    float distance;
    enum CollectableState
    {
        IDLE,

    };
    enum Side
    {
        LEFT,
        RIGHT
    };
    CollectableState state;
    int movingDistance;
    int movingSpeed;
    Sprite *collectableSprite;
    Side side;
    Timer idleTimer;
    GameObject *character;
    Sound *sound;
    void SwitchCollectableState(CollectableState state, string sprite, int frameCount, float frameTime, Timer *timer);
    int index;
  public:
    Collectable(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character, int index);
    ~Collectable();
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);
    bool Is(string type);
};

#endif