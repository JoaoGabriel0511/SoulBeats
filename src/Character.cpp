#include "../include/Character.h"
#include "Game.h"
#include "../include/LevelState.h"
#define PI 3.14159265

Character::Character(GameObject &associated) : Component(associated){
    Collider *collider;
    collider = new Collider(associated, {2, 2}, {-140, -60});
    Start();
}

void Character::Start() {
    charSprite = new Sprite(associated, IDLE_SPRITE_RIGHT, IDLE_RIGHT_FRAME_COUNT, IDLE_FRAME_TIME);
    charSprite->SetScale({2,2});
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
    attackOnBeat = false;
    isOnGround = false;
    canCancelKnockBack = false;
    isLeftSide = false;
    isOnSlope = false;
    canAttack = true;
    finishIdle = false;
    hasChanged = false;
    jumpedOnBeat = false;
    recoveringFromHitKnockback = false;
    wasLeftSide = isLeftSide;
    wasOnGround = isOnGround;
    gravity = GRAVITY_FALLING;
    idleTimer.Restart();
}

void Character::Update(float dt) {
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    oldPosition = collider->box;
    oldVelocity = velocity;
    InputManager &input = InputManager::GetInstance();
    idleTimer.Update(dt);
    float beforeRiserDuration;
    wasLeftSide = isLeftSide;
    if(idleTimer.Get() >= IDLE_DURATION && isOnGround && !finishIdle) {
        if(isLeftSide) {
            charSprite->SwitchSprite(LITSEN_TO_MUSIC_LEFT_SPRITE, LITSEN_TO_MUSIC_FRAME_COUNT, LISTEN_TO_MUSIC_FRAME_TIME);
        } else {
            charSprite->SwitchSprite(LITSEN_TO_MUSIC_RIGHT_SPRITE, LITSEN_TO_MUSIC_FRAME_COUNT, LISTEN_TO_MUSIC_FRAME_TIME);
        }
        finishIdle = true;
    }
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
                idleTimer.Restart();
                finishIdle = false;
                if(isLeftSide){
                    charSprite->SwitchSprite(IDLE_SPRITE_LEFT, IDLE_LEFT_FRAME_COUNT, IDLE_FRAME_TIME);
                } else {
                    charSprite->SwitchSprite(IDLE_SPRITE_RIGHT, IDLE_RIGHT_FRAME_COUNT, IDLE_FRAME_TIME);
                }
            }
        }
    }
    else {
        if(recoveringFromHitKnockback){
            hitRecoverTimer.Update(dt);
            if(hitRecoverTimer.Get() >= RECOVER_DURATION ) {
                velocity.x = 0;
                canCancelKnockBack = true;
                isStill = true;
                recoveringFromHitKnockback = false;
                hitRecoverTimer.Restart();
                if(isLeftSide) {
                    charSprite->SwitchSprite(IDLE_SPRITE_LEFT, IDLE_LEFT_FRAME_COUNT, IDLE_FRAME_TIME);
                } else {
                    charSprite->SwitchSprite(IDLE_SPRITE_RIGHT, IDLE_RIGHT_FRAME_COUNT, IDLE_FRAME_TIME);
                }
            }
        } if(!recoveringFromHitKnockback || canCancelKnockBack) {
            if (isAttacking) {
                attackTimer.Update(dt);
                if (attackTimer.Get() >= ATTACK_DURATION) {
                    velocity.x = 0;
                    gravity = GRAVITY_FALLING;
                    associated.box.x = associated.box.x + 2;
                    attackGO->RequestedDelete();
                    isAttacking = false;
                    attackOnBeat = false;
                    peakDone = true;
                    if(isOnGround) {
                        isStill = true;
                        if(isLeftSide){
                            charSprite->SwitchSprite(IDLE_SPRITE_LEFT, IDLE_LEFT_FRAME_COUNT, IDLE_FRAME_TIME);
                        } else {
                            charSprite->SwitchSprite(IDLE_SPRITE_RIGHT, IDLE_RIGHT_FRAME_COUNT, IDLE_FRAME_TIME);
                        }
                        idleTimer.Restart();
                        finishIdle = false;
                    } else {
                        if(isLeftSide) {
                            charSprite->SwitchSprite(FALLING_LEFT_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                        } else {
                            charSprite->SwitchSprite(FALLING_RIGHT_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                        }
                    }
                }
                isStill = true;
            } else {
                if (input.IsKeyDown(D_KEY)) {
                    velocity.x = WALKING_SPEED;
                    if((isStill || (!wasOnGround) || (isLeftSide)) && isOnGround ) {
                        charSprite->SwitchSprite(WALKING_SPRITE_RIGHT, WALKING_FRAME_COUNT, WALKING_FRAME_TIME);
                    }
                    isStill = false;
                    isLeftSide = false;
                    //charSprite->flip = false;
                } else {
                    if (input.IsKeyDown(A_KEY)) {
                        velocity.x = -1 * WALKING_SPEED;
                        if ((isStill || (!wasOnGround) || (!isLeftSide)) && isOnGround) {
                            charSprite->SwitchSprite(WALKING_SPRITE_LEFT, WALKING_FRAME_COUNT, WALKING_FRAME_TIME);
                        }
                        isStill = false;
                        isLeftSide = true;
                        //charSprite->flip = true;
                    }
                }
                if (input.KeyPress(W_KEY)) {
                    if (isOnGround) {
                        if(global_beat->GetOnBeat() == true){
                            velocity.y = JUMPING_SPEED_ON_BEAT;
                            jumpedOnBeat = true;
                        } else {
                            jumpedOnBeat = false;
                            velocity.y = JUMPING_SPEED;
                        }
                        gravity = GRAVITY_RISING;
                        isRising = true;
                        isOnGround = false;
                        beforeRisingDone = false;
                        if(isLeftSide) {
                            if( global_beat->GetOnBeat() == true) {
                                charSprite->SwitchSprite(BEFORE_RISE_LEFT_SPRITE_ON_BEAT,BEFORE_RISE_FRAME_COUNT,BEFORE_RISE_DURATION_ON_BEAT/BEFORE_RISE_FRAME_COUNT);
                            } else {
                                charSprite->SwitchSprite(BEFORE_RISE_LEFT_SPRITE,BEFORE_RISE_FRAME_COUNT,BEFORE_RISE_DURATION/BEFORE_RISE_FRAME_COUNT);
                            }
                        } else {
                            if( global_beat->GetOnBeat() == true) {
                                charSprite->SwitchSprite(BEFORE_RISE_RIGHT_SPRITE_ON_BEAT,BEFORE_RISE_FRAME_COUNT,BEFORE_RISE_DURATION_ON_BEAT/BEFORE_RISE_FRAME_COUNT);
                            } else {
                                charSprite->SwitchSprite(BEFORE_RISE_RIGHT_SPRITE,BEFORE_RISE_FRAME_COUNT,BEFORE_RISE_DURATION/BEFORE_RISE_FRAME_COUNT);
                            }
                        }
                        beforeRiseTimer.Restart();
                    }
                }
                if (input.KeyPress(SPACE_KEY)) {
                    if(canAttack) {
                        int isLeft = isLeftSide ? -1 : 1;
                        gravity = 0;
                        velocity.y = 0;
                        isAttacking = true;
                        canAttack = false;
                        isRising = false;
                        peakDone = true;
                        if(global_beat->GetOnBeat() == true){
                            velocity.x = isLeft * ON_BEAT_ATTACKING_SPEED;
                            attackOnBeat = true;
                        } else {
                            velocity.x = isLeft * ATTACKING_SPEED;
                        }
                        attackGO = new GameObject();
                        attackGO->box.z = 4;
                        if(isLeftSide) {
                            Attack *attack = new Attack(*attackGO, {2, 2}, {0, 0}, &associated, 50, 25, -6, 76);
                        } else {
                            Attack *attack = new Attack(*attackGO, {2, 2}, {0, 0}, &associated, 50, 25, 126, 76);
                        }
                        Game::GetInstance().GetCurrentState().AddObject(attackGO);
                        attackTimer.Restart();
                        if(isOnGround) {
                            if(isLeftSide) {
                                if(global_beat->GetOnBeat() == true) {
                                    charSprite->SwitchSprite(ATTACK_LEFT_SPRITE_ON_BEAT, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                                } else {
                                    charSprite->SwitchSprite(ATTACK_LEFT_SPRITE, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                                }
                            } else {
                                if(global_beat->GetOnBeat() == true) {
                                    charSprite->SwitchSprite(ATTACK_RIGHT_SPRITE_ON_BEAT, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                                } else {
                                    charSprite->SwitchSprite(ATTACK_RIGHT_SPRITE, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                                }
                            }
                        } else {
                            if(isLeftSide) {
                                if(global_beat->GetOnBeat() == true) {
                                    charSprite->SwitchSprite(ATTACK_AIR_LEFT_SPRITE_ON_BEAT, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                                } else {
                                    charSprite->SwitchSprite(ATTACK_AIR_LEFT_SPRITE, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                                }
                            } else {
                                if(global_beat->GetOnBeat() == true) {
                                    charSprite->SwitchSprite(ATTACK_AIR_RIGHT_SPRITE_ON_BEAT, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                                } else {
                                    charSprite->SwitchSprite(ATTACK_AIR_RIGHT_SPRITE, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                                }
                            }
                        }
                    }
                }
                if (input.KeyRelease(D_KEY) || input.KeyRelease(A_KEY)) {
                    velocity.x = 0;
                    if(isOnGround) {
                        if(isLeftSide) {
                            charSprite->SwitchSprite(IDLE_SPRITE_LEFT, IDLE_LEFT_FRAME_COUNT, IDLE_FRAME_TIME);
                        } else {
                            charSprite->SwitchSprite(IDLE_SPRITE_RIGHT, IDLE_RIGHT_FRAME_COUNT, IDLE_FRAME_TIME);
                        }
                        idleTimer.Restart();
                        finishIdle = false;
                        isStill = true;
                    }
                }
                if (isRising || isFalling) {
                    if(peakDone && isRising) {
                        beforeRiseTimer.Update(dt);
                        if(jumpedOnBeat) {
                            beforeRiserDuration = BEFORE_RISE_DURATION_ON_BEAT;
                        } else {
                            beforeRiserDuration = BEFORE_RISE_DURATION;
                        }
                        if (beforeRiseTimer.Get() >= beforeRiserDuration && !beforeRisingDone) {
                            if(isLeftSide) {
                                charSprite->SwitchSprite(RISING_LEFT_SPRITE, RISING_FRAME_COUNT, RISING_FRAME_TIME);
                            } else {
                                charSprite->SwitchSprite(RISING_RIGHT_SPRITE, RISING_FRAME_COUNT, RISING_FRAME_TIME);
                            }
                            beforeRiseTimer.Restart();
                            beforeRisingDone = true;
                        }
                    }
                    if(isRising) {
                        if(isLeftSide && !wasLeftSide) {
                            charSprite->SwitchSprite(RISING_LEFT_SPRITE, RISING_FRAME_COUNT, RISING_FRAME_TIME);
                        } else {
                            if(!isLeftSide && wasLeftSide) {
                                charSprite->SwitchSprite(RISING_RIGHT_SPRITE, RISING_FRAME_COUNT, RISING_FRAME_TIME);
                            }
                        }
                    }
                    if(!peakDone) {
                        if(isLeftSide && !wasLeftSide) {
                            charSprite->SwitchSprite(PEAK_LEFT_SPRITE, PEAK_FRAME_COUNT, PEAK_FRAME_TIME);
                        } else {
                            if(!isLeftSide && wasLeftSide) {
                                charSprite->SwitchSprite(PEAK_RIGHT_SPRITE, PEAK_FRAME_COUNT, PEAK_FRAME_TIME);
                            }
                        }
                    }
                    if(isFalling) {
                        if(isLeftSide && !wasLeftSide) {
                            charSprite->SwitchSprite(FALLING_LEFT_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                        } else {
                            if(!isLeftSide && wasLeftSide) {
                                charSprite->SwitchSprite(FALLING_RIGHT_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                            }
                        }
                    }
                    if (velocity.y + 3 * gravity >= 0 && isRising) {
                        if(isLeftSide) {
                            charSprite->SwitchSprite(PEAK_LEFT_SPRITE, PEAK_FRAME_COUNT, PEAK_FRAME_TIME);
                        } else {
                            charSprite->SwitchSprite(PEAK_RIGHT_SPRITE, PEAK_FRAME_COUNT, PEAK_FRAME_TIME);
                        }
                        peakDone = false;
                        gravity = GRAVITY_PEAK;
                        peakTimer.Restart();
                        isRising = false;
                        isFalling = true;
                    }
                    if (isFalling && !peakDone && !isRising && !hasChanged) {
                        peakTimer.Update(dt);
                        if(peakTimer.Get() >= PEAK_DURATION) {
                            peakDone = true;
                            hasChanged = true;
                            gravity = GRAVITY_FALLING;
                            if(isLeftSide) {
                                charSprite->SwitchSprite(FALLING_LEFT_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                            } else {
                                charSprite->SwitchSprite(FALLING_RIGHT_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                            }
                        }
                    }
                }
            }
        }
    }
    if(velocity.y <= MAX_FALL_SPEED) {
        velocity.y += gravity;
    }
    associated.box += velocity * dt;
    Camera::Update(dt);
    isFalling = true;
    peakDone = false;
    wasOnGround = isOnGround;
    isOnGround = false;
}

bool Character::Is(string type) {
    bool result = false;
    if (type == "Character") {
        result = true;
    }
    return result;
}

void Character::NotifyCollision(GameObject &other) {
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
                attackOnBeat = false;
                associated.box.x = associated.box.x + 2;
                attackGO->RequestedDelete();
            }
            invincibilityTimer.Restart();
            endingInvincibilityTimer.Restart();
            blinkTimer.Restart();
            if(isLeftSide) {
                charSprite->SwitchSprite(HURT_SPRITE_LEFT, HURT_FRAME_COUNT, HURT_FRAME_TIME);
            } else {
                charSprite->SwitchSprite(HURT_SPRITE_RIGHT, HURT_FRAME_COUNT, HURT_FRAME_TIME);
            }
            recoverFromHitTimer.Restart();
        }
    }
}

void Character::NotifYCollisionWithMap(Rect tileBox) {
    Rect pastPosition;
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    if(Debugger::GetInstance().lookCharCollision) {
        cout<<"collider->box.x: "<<collider->box.x<<endl;
        cout<<"collider->box.y: "<<collider->box.y<<endl;
        cout<<"collider->box.w: "<<collider->box.w<<endl;
        cout<<"collider->box.h: "<<collider->box.h<<endl;
        cout<<"box.x: "<<tileBox.x<<endl;
        cout<<"box.y: "<<tileBox.y<<endl;
        cout<<"box.w: "<<tileBox.w<<endl;
        cout<<"box.h: "<<tileBox.h<<endl;
    }
    if(tileBox.z == 101 || tileBox.z == 102 || tileBox.z == 103 || tileBox.z == 148 || tileBox.z == 104 ||
       tileBox.z == 67 || tileBox.z == 68 || tileBox.z == 57 || tileBox.z == 58 || tileBox.z == 66 || tileBox.z == 84){
        if(tileBox.z == 67) {
           LightSlope1Collision(tileBox);
           isOnSlope == true;
        } else {
            if(tileBox.z == 66) {
                LightSlope2Collision(tileBox);
                isOnSlope = true;
            } else {
                LightGroundCollision(tileBox);
                isOnSlope = false;
            }
        }
    } else {
        if(tileBox.z == 7) {
            SolidSlope1Collision(tileBox);
            isOnSlope = true;
        } else {
            if(tileBox.z == 6) {
                SolidSlope2Collision(tileBox);
                isOnSlope = true;
            } else {
                SolidGroundCollision(tileBox);
                isOnSlope = false;
            }
        }
    }
}

void Character::SolidGroundCollision(Rect tileBox) {
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    if(velocity.y > 0) {
        if((collider->box.y + collider->box.h - 50 <= tileBox.y) && (collider->box.x + collider->box.w > tileBox.x + 24) && (collider->box.x < tileBox.x + tileBox.w - 24)) {
            LandOnground();
            associated.box.y = tileBox.y - associated.box.h - 45;
        }
    }
    if(velocity.y <= 0) {
        if((collider->box.y >= tileBox.y) && (collider->box.x + collider->box.w > tileBox.x + 24) && (collider->box.x < tileBox.x + tileBox.w - 24)) {
            velocity.y = 0;
            associated.box.y = tileBox.y + tileBox.h - 45;
        }
    }
    if((velocity.x >= 0) && (collider->box.x < tileBox.x)) {
        if((collider->box.y + collider->box.h - 50 > tileBox.y) && (collider->box.y + 50 < tileBox.y + tileBox.h)) {
            velocity.x = 0;
            associated.box.x = tileBox.x - associated.box.w - 35;
        }
    }
    if((velocity.x <= 0) && (collider->box.x > tileBox.x) && (collider->box.y + 40 < tileBox.y + tileBox.h)) {
        if((collider->box.y + collider->box.h - 40 > tileBox.y)) {
            velocity.x = 0;
            associated.box.x = tileBox.x + tileBox.w - 75;
        }
    }
}

void Character::LightGroundCollision(Rect tileBox) {
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    if(velocity.y > 0) {
        if((collider->box.y + collider->box.h - 25 <= tileBox.y) && (collider->box.x + collider->box.w > tileBox.x + 12) && (collider->box.x < tileBox.x + tileBox.w - 12)) {
            LandOnground();
            associated.box.y = tileBox.y - associated.box.h - 45;
        }
    }
}

void Character::LandOnground() {
    if(!wasOnGround) {
        if(isLeftSide){
            charSprite->SwitchSprite(IDLE_SPRITE_LEFT, IDLE_LEFT_FRAME_COUNT, IDLE_FRAME_TIME);
        } else {
            charSprite->SwitchSprite(IDLE_SPRITE_RIGHT, IDLE_RIGHT_FRAME_COUNT, IDLE_FRAME_TIME);
        }
        idleTimer.Restart();
        finishIdle = false;
    }
    isOnGround = true;
    canAttack = true;
    isFalling = false;
    isRising = false;
    peakDone = true;
    hasChanged = false;
    if(!wasOnGround){
        isStill = true;
    }
    gravity = GRAVITY_FALLING;
    velocity.y = 0;
}

void Character::SolidSlope2Collision(Rect tileBox) {
    float posX;
    float posY;
    float tang;
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    tang = (float)(tileBox.h)/(float)(tileBox.w + 40);
    posX = collider->box.x + collider->box.w - (tileBox.x - 40);
    posY = posX * tang;
    posY = tileBox.y + tileBox.h - posY;
    if(velocity.y > 0) {
        if((collider->box.y + collider->box.h >= posY) && (collider->box.x + collider->box.w > tileBox.x) && (collider->box.x < tileBox.x + tileBox.w)) {
            associated.box.y = posY - associated.box.h - 20;
            LandOnground();
        }
    }
    if(velocity.y <= 0) {
        if((collider->box.y >= posY) && (collider->box.x + collider->box.w > tileBox.x + 24) && (collider->box.x < tileBox.x + tileBox.w - 24)) {
            velocity.y = 0;
            associated.box.y = posY + tileBox.h - 45;
        }
    }
    if((velocity.x >= 0) && (collider->box.x < tileBox.x)) {
        if((collider->box.y + collider->box.h - 60 > posY) && (collider->box.y + 50 < posY + tileBox.h)) {
            if(isOnSlope) {
                velocity.x = 0;
                associated.box.x = tileBox.x - associated.box.w - 35;
            } else {
                associated.box.y =  posY - associated.box.h - 40;
            }
        }
    }
    if((velocity.x <= 0) && (collider->box.x > tileBox.x) && (collider->box.y + 40 < posY + tileBox.h)) {
        if((collider->box.y + collider->box.h - 40 > posY)) {
            velocity.x = 0;
            associated.box.x = tileBox.x + tileBox.w - 75;
        }
    }
}

void Character::LightSlope2Collision(Rect tileBox) {
    float posX;
    float posY;
    float tang;
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    tang = (float)(tileBox.h)/(float)(tileBox.w + 40);
    posX = collider->box.x + collider->box.w - (tileBox.x - 40);
    posY = posX * tang;
    posY = tileBox.y + tileBox.h - posY;
    if(velocity.y > 0) {
        if((collider->box.y + collider->box.h - 25 >= posY) && (collider->box.x + collider->box.w > tileBox.x) && (collider->box.x < tileBox.x + tileBox.w)) {
            associated.box.y = posY - associated.box.h - 20;
            LandOnground();
        }
    }
    if((velocity.x >= 0) && (collider->box.x < tileBox.x)) {
        if((collider->box.y + collider->box.h - 60 > posY) && (collider->box.y + 80 < posY + tileBox.h)) {
            if(isOnSlope) {
                velocity.x = 0;
                associated.box.x = tileBox.x - associated.box.w - 35;
            } else {
                associated.box.y =  posY - associated.box.h - 40;
            }
        }
    }
}

void Character::HitKnockBack() {
    if (isLeftSide) {
        velocity.x = HURT_DEFLECT_SPEED;
        charSprite->SwitchSprite(RECOVER_SPRITE_LEFT, RECOVER_FRAME_COUNT, RECOVER_DURATION / RECOVER_FRAME_COUNT);
    }
    else {
        velocity.x = -1 * HURT_DEFLECT_SPEED;
        charSprite->SwitchSprite(RECOVER_SPRITE_RIGHT, RECOVER_FRAME_COUNT, RECOVER_DURATION / RECOVER_FRAME_COUNT);
    }
    isAttacking = false;
    if(attackOnBeat == true) {
        canCancelKnockBack = true;
    }
    attackOnBeat = false;
    hitRecoverTimer.Restart();
    recoveringFromHitKnockback = true;
}

void Character::LightSlope1Collision(Rect tileBox) {
    float posX;
    float posY;
    float tang;
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    tang = (float)(tileBox.h)/(float)(tileBox.w + 40);
    posX = tileBox.x + tileBox.w + 40 - collider->box.x;
    posY = posX * tang;
    posY = tileBox.y + tileBox.h - posY;
    if(velocity.y > 0) {
        if((collider->box.y + collider->box.h - 25 >= posY) && (collider->box.x + collider->box.w > tileBox.x) && (collider->box.x < tileBox.x + tileBox.w)) {
            associated.box.y = posY - associated.box.h - 20;
            LandOnground();
        }
    }
    if((velocity.x <= 0) && (collider->box.x > tileBox.x) && (collider->box.y + 70 < posY + tileBox.h)) {
        if((collider->box.y + collider->box.h - 42 > posY)) {
            if(isOnSlope) {
                velocity.x = 0;
                associated.box.x = tileBox.x + tileBox.w - 75;
            } else {
                associated.box.y =  posY - associated.box.h - 40;
            }
        }
    }
}


void Character::SolidSlope1Collision(Rect tileBox) {
    float posX;
    float posY;
    float tang;
    Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
    tang = (float)(tileBox.h)/(float)(tileBox.w + 40);
    posX = tileBox.x + tileBox.w + 40 - collider->box.x;
    posY = posX * tang;
    posY = tileBox.y + tileBox.h - posY;
    if(velocity.y > 0) {
        if((collider->box.y + collider->box.h - 25 >= posY) && (collider->box.x + collider->box.w > tileBox.x) && (collider->box.x < tileBox.x + tileBox.w)) {
            associated.box.y = posY - associated.box.h - 20;
            LandOnground();
        }
    }
    if(velocity.y <= 0) {
        if((collider->box.y >= posY) && (collider->box.x + collider->box.w > tileBox.x + 24) && (collider->box.x < tileBox.x + tileBox.w - 24)) {
            velocity.y = 0;
            associated.box.y = posY + tileBox.h - 45;
        }
    }
    if((velocity.x >= 0) && (collider->box.x < tileBox.x)) {
        if((collider->box.y + collider->box.h - 60 > posY) && (collider->box.y + 50 < posY + tileBox.h)) {
            velocity.x = 0;
            associated.box.x = tileBox.x - associated.box.w - 35;
        }
    }
    if((velocity.x <= 0) && (collider->box.x > tileBox.x) && (collider->box.y + 40 < posY + tileBox.h)) {
        if((collider->box.y + collider->box.h - 42 > posY)) {
            if(isOnSlope) {
                velocity.x = 0;
                associated.box.x = tileBox.x + tileBox.w - 75;
            } else {
                associated.box.y =  posY - associated.box.h - 40;
            }
        }
    }
}
