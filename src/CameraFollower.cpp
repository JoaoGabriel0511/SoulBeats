#include "../include/CameraFollower.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {}

bool CameraFollower::Is(string type) {
    bool result = false;
    if(type == "CameraFollower") {
        result = true;
    }
    return result;
}

void CameraFollower::Render() {}

void CameraFollower::Update(float dt) {
    associated.box.x = -1 * Camera::pos.x;
    associated.box.y = -1 * Camera::pos.y;
}