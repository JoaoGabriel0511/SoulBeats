#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "Component.h"
#include "Sprite.h"
#include "Character.h"
#define COLLECTABLE_IDLE_SPRITE "assets/img/interactables/Collectable.png"
#define COLLECTABLE_IDLE_FRAME_COUNT 8
#define COLLECTABLE_IDLE_DURATION 0.747
#define COLLECTABLE_HIT_SOUND "assets/audio/SFX/GolpeForte2.wav"
#define COLLECTABLE_DEFEND_SOUND "assets/audio/SFX/GolpeIneficaz1.wav"
#define COLLECTABLE_SOUND "assets/audio/SFX/Sino1.wav"

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

  public:
    Collectable(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character);
    ~Collectable();
    void Update(float dt);
    void Render();
    void Start();
    void NotifyCollision(GameObject &other);
    bool Is(string type);
};

#endif