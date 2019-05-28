#ifndef STATE_H
#define STATE_H
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Collision.h"
#include "Collider.h"
#include "CameraFollower.h"
#include "Debugger.h"
#include <vector>
#include <memory>
using namespace std;
class tileMap;

class State {
    public:
        virtual weak_ptr<GameObject> AddObject(GameObject *go);
        virtual weak_ptr<GameObject> GetObjectPtr(GameObject *go);
        virtual void Start();
        virtual void Pause() = 0;
        virtual void Resume() = 0;
        State();
        virtual ~State();
        virtual void LoadAssets() = 0;
        virtual void Update(float dt);
        virtual void Render();
        bool PopRequested();
        bool QuitRequested();
    protected:
        virtual void StartArray();
        virtual void UpdateArray(float dt);
        virtual void RenderArray();
        bool popRequested;
        bool quitRequested;
        bool started;
        vector<shared_ptr<GameObject>> objectArray;
};
#endif