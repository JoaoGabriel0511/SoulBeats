#ifndef GAME_H
#define GAME_H
#include <string>
#include "GameData.h"
#include "GameInfo.h"
#include "State.h"
#include <stack>
#include "SDL2/SDL_ttf.h"

using namespace std;
class Beat;
extern Beat* global_beat;
extern bool global_hit_flag;

class State;
class Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *storedState;
    static Game *instance;
    int frameStart;
    float dt;
    float width;
    float height;
    void CalculateDeltaTime();
    stack<State*> stateStack;
    public:
        Game(string title, int width, int height);
        ~Game();
        State& GetCurrentState();
        State* GetCurrentStatePointer();
        float GetWidth();
        float GetHeight();
        void Run();
        void Push(State* state);
        float GetDeltaTime();
        SDL_Renderer * GetRenderer();
        static Game& GetInstance();
        void gameRanking();
};
#endif