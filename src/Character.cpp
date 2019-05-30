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
    isLeaftSide = false;
}

void Character::Update(float dt)
{
    InputManager &input = InputManager::GetInstance();
    if (isInvincible)
    {
        blinkTimer.Update(dt);
        if (blinkTimer.Get() >= BLINKING_DURATION)
        {
            if (charSprite->isBlinking)
            {
                charSprite->isBlinking = false;
            }
            else
            {
                charSprite->isBlinking = true;
            }
            blinkTimer.Restart();
        }
        invincibilityTimer.Update(dt);
        if (invincibilityTimer.Get() >= INVINCIBILITY_DURATION)
        {
            charSprite->isBlinking = false;
            endingInvincibilityTimer.Update(dt);
            if (endingInvincibilityTimer.Get() >= ENDING_INVINCIBILITY_DURATION)
            {
                isInvincible = false;
            }
        }
    }
    if (gotHit)
    {
        velocity.y += gravity;
        recoverFromHitTimer.Update(dt);
        if (associated.box.y >= 500 || !isAttacking)
        {
            if (recoverFromHitTimer.Get() >= HURT_DURATION)
            {
                gotHit = false;
                velocity.x = 0;
                charSprite->SwitchSprite(IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
            }
            velocity.y = 0;
            gravity = 0;
        }
    }
    else
    {
        if (input.IsKeyDown(D_KEY))
        {
            velocity.x = WALKING_SPEED;
            if (isStill && !isRising && !isFalling)
            {
                charSprite->SwitchSprite(WALKING_SPRITE, WALKING_FRAME_COUNT, WALKING_FRAME_TIME);
            }
            isStill = false;
            isLeaftSide = false;
            charSprite->flip = false;
        }
        if (input.IsKeyDown(A_KEY))
        {
            velocity.x = -1 * WALKING_SPEED;
            if (isStill && !isRising && !isFalling)
            {
                charSprite->SwitchSprite(WALKING_SPRITE, WALKING_FRAME_COUNT, WALKING_FRAME_TIME);
            }
            isStill = false;
            isLeaftSide = true;
            charSprite->flip = true;
        }
        if (input.KeyPress(W_KEY))
        {
            if (!isRising && !isFalling)
            {
                velocity.y = JUMPING_SPEED;
                gravity = GRAVITY_RISING;
                isRising = true;
                beforeRisingDone = false;
                charSprite->SwitchSprite(BEFORE_RISE_SPRITE, BEFORE_RISE_FRAME_COUNT, BEFORE_RISE_FRAME_TIME);
                beforeRiseTimer.Restart();
            }
        }
        if (input.KeyPress(SPACE_KEY))
        {
            isAttacking = true;
            attackGO = new GameObject();
            attackGO->box.z = 1;
            Attack *attack = new Attack(*attackGO, {1, 1}, {0, 0}, &associated, 50, 25, 10, 10);
            Game::GetInstance().GetCurrentState().AddObject(attackGO);
            attackTimer.Restart();
            charSprite->SwitchSprite(ATTACKING_SPRITE, ATTACKING_FRAME_COUNT, ATTACKING_FRAME_TIME);
        }
        if (isAttacking)
        {
            int isLeaft = isLeaftSide ? -1 : 1;

            attackTimer.Update(dt);
            velocity.x = isLeaft * ATTACKING_SPEED;
            if (attackTimer.Get() >= ATTACK_DURATION)
            {
                velocity.x = 0;
                associated.box.x = associated.box.x + 2;
                attackGO->RequestedDelete();
                isAttacking = false;
                charSprite->SwitchSprite(IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
            }
        }
        if (input.KeyRelease(D_KEY) || input.KeyRelease(A_KEY))
        {
            velocity.x = 0;
            if (!isRising && !isFalling)
            {
                charSprite->SwitchSprite(IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
                isStill = true;
            }
        }
        if (isRising || isFalling || isLanding)
        {
            beforeRiseTimer.Update(dt);
            if (beforeRiseTimer.Get() >= BEFORE_RISE_DURATION && !beforeRisingDone)
            {
                charSprite->SwitchSprite(RISING_SPRITE, RISING_FRAME_COUNT, RISING_FRAME_TIME);
                beforeRiseTimer.Restart();
                beforeRisingDone = true;
            }
            velocity.y += gravity;
            if (velocity.y + 3 * gravity >= 0 && isRising)
            {
                charSprite->SwitchSprite(PEAK_SPRITE, PEAK_FRAME_COUNT, PEAK_FRAME_TIME);
                peakDone = false;
                gravity = GRAVITY_PEAK;
                peakTimer.Restart();
                isRising = false;
                isFalling = true;
            }
            if (isFalling && !peakDone)
            {
                peakTimer.Update(dt);
                if (peakTimer.Get() >= PEAK_DURATION)
                {
                    peakDone = true;
                    gravity = GRAVITY_FALLING;
                    charSprite->SwitchSprite(FALLING_SPRITE, FALLING_FRAME_COUNT, FALLING_FRAME_TIME);
                }
            }
            if (associated.box.y >= 500 && isFalling)
            {
                isStill = true;
                isFalling = false;
                velocity.y = 0;
                gravity = 0;
                charSprite->SwitchSprite(IDLE_SPRITE, IDLE_FRAME_COUNT, IDLE_FRAME_TIME);
            }
        }
    }
    associated.box += velocity * dt;
}

bool Character::Is(string type)
{
    bool result = false;
    if (type == "Character")
    {
        result = true;
    }
    return result;
}

void Character::NotifyCollision(GameObject &other)
{
    if (!isInvincible)
    {
        if (other.GetComponent("BellEnemy") != NULL)
        {
            if (other.box.x > associated.box.x)
            {
                velocity.x = -1 * HURT_DEFLECT_SPEED;
            }
            else
            {
                velocity.x = HURT_DEFLECT_SPEED;
            }
            velocity.y = HURT_BOUNCING_SPEED;
            gravity = HURT_GRAVITY;
            gotHit = true;
            isInvincible = true;
            invincibilityTimer.Restart();
            endingInvincibilityTimer.Restart();
            blinkTimer.Restart();
            charSprite->SwitchSprite(HURT_SPRITE, HURT_FRAME_COUNT, HURT_FRAME_TIME);
            recoverFromHitTimer.Restart();
        }
    }
}