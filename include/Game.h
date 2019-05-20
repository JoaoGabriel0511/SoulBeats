#ifndef GAME_H
#define GAME_H
#include <string>
#include "GameData.h"
#include "State.h"
#include <stack>
#include "SDL2/SDL_ttf.h"
using namespace std;

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
        float GetWidth();
        float GetHeight();
        void Run();
        void Push(State* state);
        float GetDeltaTime();
        SDL_Renderer * GetRenderer();
        static Game& GetInstance();
};
#endif