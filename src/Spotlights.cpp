#include "../include/Spotlights.h"
#include "Game.h"
#include "../include/LevelState.h"

Spotlights::Spotlights(GameObject& associated) : Component(associated) {
    this->state = LEFT;
    spotlightsMidleTileSet = new TileSet(512, 288, "assets/img/holofote/HolofoteMeio.png");
    spotlightsLeftTileSet = new TileSet(512, 288, "assets/img/holofote/HolofoteEsquerda.png");
    spotlightsRightTileSet = new TileSet(512, 288, "assets/img/holofote/HolofoteDireita.png");
    this->spotlightsTileMap = new TileMap(associated, "assets/map/MapaHolofotes.txt", spotlightsMidleTileSet, 4, -1024, 50, 0.7, 0.7);
    bool switched = false;
}

Spotlights::~Spotlights(){
}

void Spotlights::Render() {}

bool Spotlights::Is(string type){
    bool result = false;
    if(type == "Spotlights") {
        result = true;
    }
    return result;
}

void Spotlights::Update(float dt) {
    if(global_beat->GetOnBeat()) {
        if(state == LEFT) {
            spotlightsTileMap->SetTileSet(spotlightsLeftTileSet);
        } else {
            if(state == RIGHT) {
                spotlightsTileMap->SetTileSet(spotlightsRightTileSet);
            }
        }
        switched = false;
    } else {
        spotlightsTileMap->SetTileSet(spotlightsMidleTileSet);
        if(!switched) {
            if(state == LEFT) {
                state = RIGHT;
            } else {
                if(state == RIGHT) {
                    state = LEFT;
                }
            }
            switched = true;
        }
    }
}