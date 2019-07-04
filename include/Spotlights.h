#ifndef SPOTLIGHTS
#define SPOTLIGHTS
#include "Component.h"
#include "TileMap.h"
#include "Game.h"
    class Spotlights : public Component {
        TileMap *spotlightsTileMap;
        TileSet *spotlightsMidleTileSet;
        TileSet *spotlightsLeftTileSet;
        TileSet *spotlightsRightTileSet;
        enum SpotlightsState {RIGHT, LEFT};
        SpotlightsState state;
        bool switched;
    public:
        Spotlights(GameObject& associated);
        ~Spotlights();
        void Start() {}
        void Update(float dt);
        void Render();
        bool Is(string type);

    };
#endif