#include "../include/Character.h"

Character::Character(GameObject &associated) : Component(associated)
{
    Collider *collider;
    collider = new Collider(associated, {1, 1}, {-70, -30});
    associated.AddComponent(shared_ptr<Component>(collider));
    Start();
}

void Character::Start()
{
    charSprite = new Sprite(associated, IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
    isStill = true;
    isRising = false;
    isFalling = false;
    beforeRisingDone = true;
    peakDone = true;
    isLanding = false;
    gotHit = false;
    landingDone = true;
    isInvincible = false;
    isAttacking = false;
    isOnGround = false;
    isLeaftSide = false;
}

void Character::Update(float dt) {
    InputManager &input = InputManager::GetInstance();
    if (isInvincible) {
        blinkTimer.Update(dt);
        if (blinkTimer.Get() >= BLINKING_DURATION) {
            if (charSprite->isBlinking) {
                charSprite->isBlinking = false;
            }
            else {
                charSprite->isBlinking = true;
            }
            blinkTimer.Restart();
        }
        invincibilityTimer.Update(dt);
        if (invincibilityTimer.Get() >= INVINCIBILITY_DURATION) {
            charSprite->isBlinking = false;
            endingInvincibilityTimer.Update(dt);
            if (endingInvincibilityTimer.Get() >= ENDING_INVINCIBILITY_DURATION) {
                isInvincible = false;
            }
        }
    }
    if (gotHit) {
        recoverFromHitTimer.Update(dt);
        if(isOnGround) {
            if(recoverFromHitTimer.Get() >= HURT_DURATION){
                gotHit = false;
                gravity = GRAVITY_FALLING;
                velocity.x = 0;
                charSprite->SwitchSprite(IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
            }
        }
    }
    else {
        if (isAttacking) {
            attackTimer.Update(dt);
            if (attackTimer.Get() >= ATTACK_DURATION) {
                velocity.x = 0;
                gravity = GRAVITY_FALLING;
                associated.box.x = associated.box.x + 2;
                attackGO->RequestedDelete();
                isAttacking = false;
                if(isOnGround) {
                    charSprite->SwitchSprite(IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
                } else {
                    charSprite->SwitchSprite(FALLING_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                }
            }
        } else {
            if (input.IsKeyDown(D_KEY)) {
                velocity.x = WALKING_SPEED;
                if (isStill && !isRising && !isFalling) {
                    charSprite->SwitchSprite(WALKING_SPRITE, WALKING_FRAME_COUNT, WALKING_FRAME_TIME);
                }
                isStill = false;
                isLeaftSide = false;
                charSprite->flip = false;
            }
            if (input.IsKeyDown(A_KEY)) {
                velocity.x = -1 * WALKING_SPEED;
                if (isStill && !isRising && !isFalling) {
                    charSprite->SwitchSprite(WALKING_SPRITE, WALKING_FRAME_COUNT, WALKING_FRAME_TIME);
                }
                isStill = false;
                isLeaftSide = true;
                charSprite->flip = true;
            }
            if (input.KeyPress(W_KEY)) {
                if (!isRising && !isFalling) {
                    velocity.y = JUMPING_SPEED;
                    gravity = GRAVITY_RISING;
                    isRising = true;
                    isOnGround = false;
                    beforeRisingDone = false;
                    charSprite->SwitchSprite(BEFORE_RISE_SPRITE, BEFORE_RISE_FRAME_COUNT, BEFORE_RISE_FRAME_TIME);
                    beforeRiseTimer.Restart();
                }
            }
            if (input.KeyPress(SPACE_KEY)) {
                int isLeaft = isLeaftSide ? -1 : 1;
                gravity = 0;
                velocity.y = 0;
                isAttacking = true;
                velocity.x = isLeaft * ATTACKING_SPEED;
                attackGO = new GameObject();
                attackGO->box.z = 1;
                if(isLeaftSide) {
                    Attack *attack = new Attack(*attackGO, {1, 1}, {0, 0}, &associated, 50, 25, -3, 38);
                } else {
                    Attack *attack = new Attack(*attackGO, {1, 1}, {0, 0}, &associated, 50, 25, 60, 38);
                }
                Game::GetInstance().GetCurrentState().AddObject(attackGO);
                attackTimer.Restart();
                charSprite->SwitchSprite(ATTACKING_SPRITE, ATTACKING_FRAME_COUNT, ATTACKING_FRAME_TIME);
            }
            if (input.KeyRelease(D_KEY) || input.KeyRelease(A_KEY)) {
                velocity.x = 0;
                if (!isRising && !isFalling) {
                    charSprite->SwitchSprite(IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
                    isStill = true;
                }
            }
            if (isRising || isFalling || isLanding) {
                beforeRiseTimer.Update(dt);
                if (beforeRiseTimer.Get() >= BEFORE_RISE_DURATION && !beforeRisingDone) {
                    charSprite->SwitchSprite(RISING_SPRITE, RISING_FRAME_COUNT, RISING_FRAME_TIME);
                    beforeRiseTimer.Restart();
                    beforeRisingDone = true;
                }
                velocity.y += gravity;
                if (velocity.y + 3 * gravity >= 0 && isRising && !isAttacking) {
                    charSprite->SwitchSprite(PEAK_SPRITE, PEAK_FRAME_COUNT, PEAK_FRAME_TIME);
                    peakDone = false;
                    gravity = GRAVITY_PEAK;
                    peakTimer.Restart();
                    isRising = false;
                    isFalling = true;
                }
                if (isFalling && !peakDone) {
                    peakTimer.Update(dt);
                    if (peakTimer.Get() >= PEAK_DURATION) {
                        peakDone = true;
                        gravity = GRAVITY_FALLING;
                        charSprite->SwitchSprite(FALLING_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                    }
                }
            }
        }
    }
    associated.box += velocity * dt;
}

bool Character::Is(string type) {
    bool result = false;
    if (type == "Character") {
        result = true;
    }
    return result;
}

void Character::NotifyCollision(GameObject &other) {
    cout<<__FILE__<<" :: "<<__LINE__<<endl;
    if (!isInvincible) {
        if (other.GetComponent("BellEnemy") != NULL) {
            if (other.box.x > associated.box.x) {
                velocity.x = -1 * HURT_DEFLECT_SPEED;
            }
            else {
                velocity.x = HURT_DEFLECT_SPEED;
            }
            if(!isOnGround) {
                velocity.y = HURT_BOUNCING_SPEED;
            }
            gravity = HURT_GRAVITY;
            gotHit = true;
            isInvincible = true;
            if(isAttacking) {
                isAttacking = false;
                associated.box.x = associated.box.x + 2;
                attackGO->RequestedDelete();
            }
            invincibilityTimer.Restart();
            endingInvincibilityTimer.Restart();
            blinkTimer.Restart();
            charSprite->SwitchSprite(HURT_SPRITE, HURT_FRAME_COUNT, HURT_FRAME_TIME);
            recoverFromHitTimer.Restart();
        }
    }
    cout<<__FILE__<<" :: "<<__LINE__<<endl;
}

void Character::NotifYCollisionWithMap(Rect box) {
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    if(Debugger::GetInstance().lookCharCollision) {
        cout<<"collider->box.x: "<<collider->box.x<<endl;
        cout<<"collider->box.y: "<<collider->box.y<<endl;
        cout<<"collider->box.w: "<<collider->box.w<<endl;
        cout<<"collider->box.h: "<<collider->box.h<<endl;
        cout<<"box.x: "<<box.x<<endl;
        cout<<"box.y: "<<box.y<<endl;
        cout<<"box.w: "<<box.w<<endl;
        cout<<"box.h: "<<box.h<<endl;
    }
    if(velocity.y > 0) {
        if((collider->box.y + collider->box.h - 25 <= box.y) && (collider->box.x + collider->box.w > box.x + 5) && (collider->box.x < box.x + box.w - 5)) {
            isStill = true;
            isOnGround = true;
            isFalling = false;
            gravity = GRAVITY_FALLING;
            velocity.y = 0;
            associated.box.y = box.y - associated.box.h + 20;
            charSprite->SwitchSprite(IDLE_SPRITE,IDLE_FRAME_COUNT,IDLE_FRAME_TIME);
        }
    }
    if(velocity.y <= 0) {
        if((collider->box.y >= box.y) && (collider->box.x + collider->box.w > box.x + 5) && (collider->box.x < box.x + box.w - 5)) {
            velocity.y = 0;
            associated.box.y = box.y + box.h - 20;
        }
    }
    if((velocity.x >= 0) && (collider->box.x < box.x)) {
        if((collider->box.y + collider->box.h - 15 > box.y)) {
            velocity.x = 0;
            associated.box.x = box.x - associated.box.w + 35;
        }
    }
    if((velocity.x <= 0) && (collider->box.x > box.x)) {
        if((collider->box.y + collider->box.h - 15 > box.y)) {
            velocity.x = 0;
            associated.box.x = box.x + box.w - 35;
        }
    }
}