#include "../include/TileMapCollider.h"
#define PI 3.14159265

TileMapCollider::TileMapCollider(GameObject& associated, TileMap *tileMap) : Component(associated) {
    this->tileMap = tileMap;
}

void TileMapCollider::Start() {
    int width = tileMap->GetWidth();
    int height = tileMap->GetHeight();
    int depth = tileMap->GetDepth();
    int index;
    int auxh;
    int auxw;
    Rect box;
    for(int z = 0; z < depth; z++) {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                index = tileMap->At(x,y,z);
                if(index == 18 || index == 17 || index == 11 || index == 1 || index == 2 || index == 71
                || index == 3  || index == 6 || index == 88 || index == 19 || index == 87
                || index == 53 || index == 38 || index == 54 || index == 34 || index == 71 || index == 50
                || index == 24 || index == 50 || index == 35 || index == 33 || index == 55 || index == 51
                || index == 39 || index == 19 || index == 49 || index == 86 || index == 85 || index == 69
                || index == 87 || index == 56 || index == 72 || index == 101 || index == 102 || index == 103
                || index == 104 || index == 66 || index == 84 || index == 67 || index == 68 || index == 57
                || index == 58 || index == 148 || index == 7) {
                    auxh = tileMap->GetTileSet()->GetHeight() * tileMap->GetScale();
                    auxw = tileMap->GetTileSet()->GetWidth() * tileMap->GetScale();
                    box.h = auxh;
                    box.w = auxw;
                    box.x = auxw * x;
                    box.y = auxh * y;
                    box.z = index;
                    boxes.emplace_back(box);
                } else {
                    if(index == 8 || index == 68) {
                        auxh = tileMap->GetTileSet()->GetHeight() * tileMap->GetScale();
                        auxw = tileMap->GetTileSet()->GetWidth() * tileMap->GetScale();
                        box.h = auxh - 30;
                        box.w = auxw - 23;
                        box.x = auxw * x;
                        box.y = (auxh * y) + 30;
                        //box.z = index;
                        boxes.emplace_back(box);
                    } else {
                        if(index == 5 || index == 65) {
                            auxh = tileMap->GetTileSet()->GetHeight() * tileMap->GetScale();
                            auxw = tileMap->GetTileSet()->GetWidth() * tileMap->GetScale();
                            box.h = auxh - 30;
                            box.w = auxw - 23;
                            box.x = auxw * x + 23;
                            box.y = (auxh * y) + 30;
                            //box.z = index;
                            boxes.emplace_back(box);
                        }
                    }
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
        if(Camera::IsOnCamera(boxes[i])) {
            Vect2 center( boxes[i].GetCenter() );
            SDL_Point points[5];

            Vect2 point = (Vect2(boxes[i].x, boxes[i].y) - center) + center + Camera::pos;
            points[0].x = (int) point.x;
            points[0].y = (int) point.y;
            points[4].x = (int) point.x;
            points[4].y = (int) point.y;

            point = (Vect2(boxes[i].x + boxes[i].w, boxes[i].y) - center) + center + Camera::pos;
            points[1].x = (int) point.x;
            points[1].y = (int) point.y;

            point = (Vect2(boxes[i].x + boxes[i].w, boxes[i].y + boxes[i].h) - center) + center + Camera::pos;
            points[2].x = (int) point.x;
            points[2].y = (int) point.y;

            point = (Vect2(boxes[i].x, boxes[i].y + boxes[i].h) - center) + center + Camera::pos;
            points[3].x = (int) point.x;
            points[3].y = (int) point.y;

            SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
        }
    }
    #endif // DEBUG
}

void TileMapCollider::NotifyCollision(GameObject& other) {

}