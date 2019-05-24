#include "../include/Character.h"

Character::Character(GameObject &associated) : Component(associated) {
    Start();
}

void Character::Start() {
    charSprite = new Sprite(associated, IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
    isStill = true;
    isRising = false;
    isFalling = false;
    beforeRisingDone = true;
    peakDone = true;
    isLanding = false;
    landingDone = true;
}

void Character::Update(float dt){
    InputManager& input = InputManager::GetInstance();
    if(input.IsKeyDown(D_KEY)) {
        velocity.x = WALKING_SPEED;
        if(isStill && !isRising && !isFalling) {
            charSprite->SwitchSprite(WALKING_SPRITE,WALKING_FRAME_COUNT,WALKING_FRAME_TIME);
        }
        isStill = false;
        charSprite->flip = false;
    }
    if(input.IsKeyDown(A_KEY)) {
        velocity.x = -1 * WALKING_SPEED;
        if(isStill && !isRising && !isFalling) {
            charSprite->SwitchSprite(WALKING_SPRITE,WALKING_FRAME_COUNT,WALKING_FRAME_TIME);
        }
        isStill = false;
        charSprite->flip = true;
    }
    if(input.KeyPress(SPACE_KEY)) {
        if(!isRising && !isFalling) {
            velocity.y = JUMPING_SPEED;
            gravity = GRAVITY_RISING;
            isRising = true;
            beforeRisingDone = false;
            charSprite->SwitchSprite(BEFORE_RISE_SPRITE,BEFORE_RISE_FRAME_COUNT,BEFORE_RISE_FRAME_TIME);
            beforeRiseTimer.Restart();
        }
    }
    if(input.KeyRelease(D_KEY) || input.KeyRelease(A_KEY)) {
        velocity.x = 0;
        if(!isRising && !isFalling) {
            charSprite->SwitchSprite(IDLE_SPRITE,IDLE_FRAME_COUNT,IDLE_FRAME_TIME);
            isStill = true;
        }
    }
    if(isRising || isFalling || isLanding) {
        beforeRiseTimer.Update(dt);
        if(beforeRiseTimer.Get() >= BEFORE_RISE_DURATION && !beforeRisingDone) {
            charSprite->SwitchSprite(RISING_SPRITE,RISING_FRAME_COUNT,RISING_FRAME_TIME);
            beforeRiseTimer.Restart();
            beforeRisingDone = true;
        }
        velocity.y += gravity;
        if(velocity.y + 3*gravity >= 0 && isRising) {
            charSprite->SwitchSprite(PEAK_SPRITE,PEAK_FRAME_COUNT,PEAK_FRAME_TIME);
            peakDone = false;
            gravity = GRAVITY_PEAK;
            peakTimer.Restart();
            isRising = false;
            isFalling = true;
        }
        if(isFalling && !peakDone) {
            peakTimer.Update(dt);
            if(peakTimer.Get() >= PEAK_DURATION) {
                peakDone = true;
                gravity = GRAVITY_FALLING;
                charSprite->SwitchSprite(FALLING_SPRITE,FALLING_FRAME_COUNT,FALLING_FRAME_TIME);
            }
        }
        if(associated.box.y >= 500 && isFalling) {
            isStill = true;
            isFalling = false;
            velocity.y = 0;
            gravity = 0;
            charSprite->SwitchSprite(IDLE_SPRITE,IDLE_FRAME_COUNT,IDLE_FRAME_TIME);
        }
    }
    associated.box += velocity * dt;
}

bool Character::Is(string type){
    bool result = false;
    if(type == "Character") {
        result = true;
    }
    return result;
}