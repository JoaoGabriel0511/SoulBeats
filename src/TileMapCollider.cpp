#include "../include/TileMapCollider.h"

TileMapCollider::TileMapCollider(GameObject& associated, TileMap *tileMap) : Component(associated) {
    this->tileMap = tileMap;
    Start();
}

void TileMapCollider::Start() {
    int width = tileMap->GetWidth();
    int height = tileMap->GetHeight();
    int depth = tileMap->GetDepth();
    int index;
    Rect box;
    for(int z = 0; z < depth; z++) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                index = tileMap->At(x,y,z);
                if(index == 11) {
                    box.h = tileMap->GetTileSet()->GetHeight();
                    box.w = tileMap->GetTileSet()->GetWidth();
                    box.x = box.w * x;
                    box.y = box.h * y;
                    boxes.emplace_back(box);
                }
            }
        }
    }
}

bool TileMapCollider::Is(string type) {
    bool result = false;
    if(type == "TileMapCollider") {
        result = true;
    }
    return result;
}

void TileMapCollider::Update(float dt) {
}

void TileMapCollider::Render() {
    #ifdef DEBUG
    for(int i = 0; i < boxes.size(); i++) {
        Vect2 center( boxes[i].GetCenter() );
        SDL_Point points[5];

        Vect2 point = (Vect2(boxes[i].x, boxes[i].y) - center) + center - Camera::pos;
        points[0].x = (int) point.x;
        points[0].y = (int) point.y;
        points[4].x = (int) point.x;
        points[4].y = (int) point.y;

        point = (Vect2(boxes[i].x + boxes[i].w, boxes[i].y) - center) + center - Camera::pos;
        points[1].x = (int) point.x;
        points[1].y = (int) point.y;

        point = (Vect2(boxes[i].x + boxes[i].w, boxes[i].y + boxes[i].h) - center) + center - Camera::pos;
        points[2].x = (int) point.x;
        points[2].y = (int) point.y;

        point = (Vect2(boxes[i].x, boxes[i].y + boxes[i].h) - center) + center - Camera::pos;
        points[3].x = (int) point.x;
        points[3].y = (int) point.y;

        SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
    }
    #endif // DEBUG
}

void TileMapCollider::NotifyCollision(GameObject& other) {

}