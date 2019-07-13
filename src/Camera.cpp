#include "../include/Camera.h"
using namespace std;

GameObject * Camera::focus;
Vect2 Camera::pos;
Vect2 Camera::speed;
bool Camera::debug = false;
bool Camera::followX = true;
bool Camera::followY = true;

void Camera::Follow(GameObject * focus){
    Camera::focus = focus;
}

void Camera::UnFollow() {
    Camera::focus = NULL;
}

bool Camera::IsOnCamera(Rect box, float paralaxX, float paralaxY) {
    bool result = true;
    if(box.x + paralaxX * pos.x > GameInfo::GetInstance().WIDTH + 50 || box.x + box.w + pos.x * paralaxX < -50) {
        result = false;
    }
    if(box.y + paralaxY * pos.y > GameInfo::GetInstance().HEIGHT + 50 || box.y + box.h + pos.y * paralaxY < -50) {
        result = false;
    }
    return result;
}

bool Camera::IsOnCamera(Rect box) {
    bool result = true;
    if(box.x + pos.x > GameInfo::GetInstance().WIDTH + 50 || box.x + box.w + pos.x < -50) {
        result = false;
    }
    if(box.y + pos.y > GameInfo::GetInstance().HEIGHT + 50 || box.y + box.h + pos.y < -50) {
        result = false;
    }
    return result;
}

void Camera::Update(float dt) {
    InputManager inputManager = InputManager::GetInstance();
    if(focus == NULL) {
        if(debug) {
            if(inputManager.IsKeyDown(W_KEY)) {
                speed.x = 0;
                speed.y = 500 * dt;
            }
            if(inputManager.IsKeyDown(D_KEY)) {
                speed.x = -500 * dt;
                speed.y = 0;
            }
            if(inputManager.IsKeyDown(A_KEY)) {
                speed.x = 500 * dt;
                speed.y = 0;
            }
            if(inputManager.IsKeyDown(S_KEY)) {
                speed.x = 0;
                speed.y = -500 * dt;
            }
            if(inputManager.KeyRelease(W_KEY)) {
                speed.x = 0;
                speed.y = 0;
            }
            if(inputManager.KeyRelease(D_KEY)) {
                speed.x = 0;
                speed.y = 0;
            }
            if(inputManager.KeyRelease(A_KEY)) {
                speed.x = 0;
                speed.y = 0;
            }
            if(inputManager.KeyRelease(S_KEY)) {
                speed.x = 0;
                speed.y = 0;
            }
            pos = pos + speed;
            cout<<"pos x "<<(GameInfo::GetInstance().WIDTH / 2) - pos.x<<endl;
            cout<<"pos y "<<(GameInfo::GetInstance().HEIGHT / 2) - pos.y<<endl;
        }
    } else {
        if(followX) {
            pos.x = -1 * (focus->box.x - (GameInfo::GetInstance().WIDTH / 2)) - 100;
        }
        if(followY) {
            pos.y = -1 * (focus->box.y - (GameInfo::GetInstance().HEIGHT / 2)) + 50;
        }
    }
}