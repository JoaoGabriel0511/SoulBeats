#ifndef GOAL_H
#define GOAL_H
#define GOAL_SPRITE "assets/img/interactables/Goal.png"
#define GOAL_FRAME_COUNT 20
#define GOAL_FRAME_TIME 0.083333
#define GOAL_QUICK_FRAME_TIME 0.005
#define GOAL_INCRESSE_TIME 0.005
#define GOAL_SPINING_TIME 0.5
#include "Component.h"
#include "Sprite.h"
#include "LevelState.h"

class Goal : public Component {
    Sprite *goalSprite;
    Timer spiningTimer;
    bool charTochedIt;
    int updateSpriteTimes;
    public:
        Goal(GameObject &associated);
        // ~Goal();
        void Update(float dt);
        void Start();
        void Render();
        bool Is(string type);
        void NotifyCollision (GameObject& other);
};


#endif