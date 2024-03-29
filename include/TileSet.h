#ifndef TILE_SET_H
#define TILE_SET_H
#include "Sprite.h"
#include "GameObject.h"
class Sprite;
class TileSet {
    Sprite* tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
    public:
        TileSet(int tileWidth, int tileHeight, string file);
        bool RenderTile(unsigned index, float x, float y, float scale, int offsetX, int offsetY);
        int GetWidth();
        int GetHeight();
        int GetColums();
        int GetRows();
        //void SwitchTileSet(string file);
};
#endif