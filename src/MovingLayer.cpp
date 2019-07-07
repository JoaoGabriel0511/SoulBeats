#include "../include/MovingLayer.h"

MovingLayer::MovingLayer(GameObject& associated, string spriteFile, Vect2 beginingPos, Vect2 layerVelocity) : Component(associated) {
    this->spriteFile = spriteFile;
    this->beginingPos = beginingPos;
    this->layerVelocity = layerVelocity;
    layerSprite = new Sprite(associated, spriteFile);
}

void MovingLayer::Start() {
    finishedX = false;
    finishedY = false;
}

void MovingLayer::Update(float dt) {
    /*beginingPos.x += layerVelocity.x;
    if(beginingPos.x >= 0 ){
        beginingPos.x = 0;
    }*/
    if(beginingPos.x > 0){
        beginingPos.x -= layerVelocity.x;
        if(beginingPos.x <= 0) {
            beginingPos.x = 0;
        }
    } else {
        if(beginingPos.x < 0) {
            beginingPos.x += layerVelocity.x;
            if(beginingPos.x >= 0) {
                beginingPos.x = 0;
            }
        } else {
            finishedX = true;
        }
    }
    if(beginingPos.y > 0) {
        beginingPos.y -= layerVelocity.y;
        if(beginingPos.y <= 0) {
            beginingPos.y = 0;
        }
    } else {
        if(beginingPos.y < 0) {
            beginingPos.y += layerVelocity.y;
            if(beginingPos.y >= 0) {
                beginingPos.y = 0;
            }
        } else {
            finishedY = true;
        }
    }
    associated.box.x = beginingPos.x - Camera::pos.x;
    associated.box.y = beginingPos.y - Camera::pos.y;
}

bool MovingLayer::Is(string type) {
    bool result = false;
    if(type == "MovingLayer") {
        result = true;
    }
    return result;
}

bool MovingLayer::HasFinished() {
    return finishedX && finishedY;
}