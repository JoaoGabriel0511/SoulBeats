#include "../include/Sprite.h"
using namespace std;

Sprite::Sprite(GameObject &associated, int frameCount, float frameTime) : Component(associated) {
    texture = NULL;
    scale.x = 1;
    scale.y = 1;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->secondsToSelfDestruct = 0;
    currentFrame = 0;
    animate = true;
    flip = false;
    timeElapsed = 0;
    isBlinking = false;
}

Sprite::Sprite(GameObject &associated, string file, int frameCount, float frameTime) : Component(associated) {
    texture = NULL;
    scale.x = 1;
    scale.y = 1;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->secondsToSelfDestruct = 0;
    this->Open(file);
    currentFrame = 0;
    animate = true;
    flip = false;
    timeElapsed = 0;
    isBlinking = false;
}

Sprite::Sprite(GameObject &associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated) {
    texture = NULL;
    scale.x = 1;
    scale.y = 1;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
    this->Open(file);
    currentFrame = 0;
    animate = true;
    flip = false;
    timeElapsed = 0;
    isBlinking = false;
}

Sprite::Sprite(GameObject &associated, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated) {
    texture = NULL;
    scale.x = 1;
    scale.y = 1;
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    this->secondsToSelfDestruct = secondsToSelfDestruct;
    currentFrame = 0;
    animate = true;
    flip = false;
    timeElapsed = 0;
    isBlinking = false;
}

Sprite::Sprite(GameObject &associated, string file) : Component(associated) {
    texture = NULL;
    scale.x = 1;
    scale.y = 1;
    this->frameCount = 1;
    this->frameTime = 1;
    this->secondsToSelfDestruct = 0;
    this->Open(file);
    currentFrame = 0;
    animate = true;
    flip = false;
    timeElapsed = 0;
    isBlinking = false;
}

Sprite::Sprite(GameObject &associated) : Component(associated) {
    texture = NULL;
    scale.x = 1;
    scale.y = 1;
    this->frameCount = 1;
    this->frameTime = 1;
    this->secondsToSelfDestruct = 0;
    currentFrame = 0;
    animate = true;
    flip = false;
    timeElapsed = 0;
    isBlinking = false;
}

void Sprite::Update(float dt) {
    timeElapsed += dt;
    float x = 0;
    if(secondsToSelfDestruct > 0) {
        selfDestructCount.Update(dt);
        if(selfDestructCount.Get() >= secondsToSelfDestruct) {
            associated.RequestedDelete();
        }
    }
    if(timeElapsed >= frameTime) {
        currentFrame++;
        timeElapsed = 0;
        if(currentFrame >= frameCount) {
            currentFrame = 0;
        }
        SetClip(currentFrame * associated.box.w, 0, associated.box.w, associated.box.h);
    }
}

bool Sprite::Is(string type) {
    bool result = false;
    if(type == "Sprite") {
        result = true;
    }
    return result;
}

bool Sprite::Open(string file) {
    texture = Resources::GetImage(file);
    if(texture == NULL){
        if(Debugger::GetInstance().lookSprite) {
            cout << "ERROR CRASHOU: Sprite.Open IMG_LoadTexture"<<endl;
            cout << SDL_GetError() << endl;
        }
        return false;
    } else {
        if(Debugger::GetInstance().lookSprite) {
            cout << "Imagem "<< file <<" do sprite carregada" << endl;
        }
        SDL_QueryTexture(texture.get(), NULL, NULL, &associated.box.w, &associated.box.h);
        currentFrame = 0;
        associated.box.w = associated.box.w / frameCount;
        SetClip(currentFrame * associated.box.w, 0, associated.box.w, associated.box.h);
        return true;
    }
}

void Sprite::SetScaleX(float scalex, float scaley) {
    if(scalex > 0) {
        scale.x = scalex;
    }
    if(scaley > 0) {
        scale.y = scaley;
    }
    associated.box.x = associated.box.x - (((scalex-1) * associated.box.x)/2);
    associated.box.y = associated.box.y - (((scaley-1) * associated.box.y)/2);
}

void Sprite::SetClip(int x, int y, int w, int h){
    clipRect.h = h;
    clipRect.w = w;
    clipRect.x = x;
    clipRect.y = y;
}

void Sprite::Render() {
    if(!isBlinking) {
        Render(associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y, associated.box.w, associated.box.h);
    }
}

void Sprite::Render(float x, float y, float w, float h) {
    SDL_Rect dstRect{ int(x), int(y), w*scale.y, h*scale.y };
    if(flip) {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angleDeg, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angleDeg, NULL, SDL_FLIP_NONE);
    }
}

int Sprite::GetHeight() {
    return associated.box.h;
}

int Sprite::GetWidth() {
    return associated.box.w;
}

bool Sprite::IsOpen(){
    bool isOpen;
    if(texture != NULL) {
        isOpen = true;
    } else {
        isOpen = false;
    }
    return isOpen;
}

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    SetClip(associated.box.x, 0, associated.box.w, associated.box.h);
}

void Sprite::SetFrameCount(int frameCount) {
    associated.box.w = associated.box.w * this->frameCount;
    this->frameCount = frameCount;
    associated.box.w = associated.box.w / this->frameCount;
}

void Sprite::SetFrameTime(float frameTime) {
    this->frameTime = frameTime;
}

void Sprite::SwitchSprite(string file, int frameCount, float frameTime) {
    this->frameCount = frameCount;
    this->frameTime = frameTime;
    Open(file);
}

int Sprite::GetCurrentFrame() {
    return currentFrame;
}

void Sprite::SetScale(Vect2 scale) {
    this->scale = scale;
}