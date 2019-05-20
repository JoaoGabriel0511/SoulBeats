#ifndef STAGE_STATE_H
#define STAGE_STATE_H
#include "Sprite.h"
#include "Music.h"
#include "EndState.h"
#include "Face.h"
#include "Sound.h"
#include "TileMap.h"
#include "Debugger.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include <vector>
#include <memory>
using namespace std;
class tileMap;

class StageState : public State{
    GameObject *bg;
    public:
        void Start();
        void Pause();
        void Resume();
        StageState();
        ~StageState();
        void LoadAssets();
        void Update(float dt);
        void Render();
};
#endif