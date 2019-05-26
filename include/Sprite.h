#ifndef SPRITE_H
#define SPRITE_H
#include "SDL2/SDL.h"
#include "Component.h"
#include "Vect2.h"
#include "Resources.h"
#include "Timer.h"
using namespace std;
class Sprite : public Component {
    shared_ptr<SDL_Texture> texture;
    SDL_Rect clipRect;
    Vect2 scale;
    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;
    float secondsToSelfDestruct;
    Timer selfDestructCount;
    public:
        Sprite(GameObject &associated, int frameCount, float frameTime);
        Sprite(GameObject &associated, int frameCount, float frameTime, float secondsToSelfDestruct);
        Sprite(GameObject &associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct);
        Sprite(GameObject &associated, string file, int frameCount, float frameTime);
        Sprite(GameObject &associated, string file);
        Sprite(GameObject &associated);
        ~Sprite();
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
        int GetCurrentFrame();
        bool Open(string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        void Render(float x, float y, float w, float h);
        int GetWidth();
        void SwitchSprite(string file, int frameCount, float frameTime);
        int GetHeight();
        void SetScaleX(float scalex, float scaley);
        Vect2 GetScale();
        bool IsOpen();
        void Update(float dt);
        bool Is(string type);
        bool animate;
        bool flip;
};
#endif