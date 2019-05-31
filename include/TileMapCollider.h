#ifndef TILE_MAP_COLLIDER
#define TILE_MAP_COLLIDER
#include "Component.h"
#include "TileMap.h"
using namespace std;

class TileMapCollider : public Component {
    TileMap* tileMap;
    public:
        TileMapCollider(GameObject& associated, TileMap* tileMap);
        bool Is(string type);
        void Start();
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);
        vector<Rect> boxes;
};


#endif