#include "../include/Character.h"
#include "Game.h"
#include "../include/LevelState.h"
#define PI 3.14159265

Character::Character(GameObject &associated) : Component(associated)
{
    Collider *collider;
    collider = new Collider(associated, {2, 2}, {-140, -60});
    lifeBarGO = new GameObject();
    lifeBarGO->box.z = 7;
    lifeBar = new LifeBar(*lifeBarGO);
    Game::GetInstance().GetCurrentStatePointer()->AddObject(lifeBarGO);
}

Character::~Character() {
    if(jumpingEfectGO) {
        jumpingEfectGO->RequestedDelete();
    }
}

void Character::Start()
{
    charSprite = new Sprite(associated, IDLE_SPRITE_RIGHT, IDLE_RIGHT_FRAME_COUNT, IDLE_FRAME_TIME);
    charSprite->SetScale({2, 2});
    sound = new Sound(associated);
    isStill = true;
    isRising = false;
    isDead = false;
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
    isOnMovingPlatform = false;
    canAttack = true;
    finishIdle = false;
    hasChanged = false;
    jumpedOnBeat = false;
    isLaunching = false;
    idleState = UP;
    launchDuration = 0;
    recoveringFromHitKnockback = false;
    isOnTopOfJumpingPad = false;
    switchedIdleOnBeat = false;
    jumpingEfect = false;
    wasLeftSide = isLeftSide;
    wasOnGround = isOnGround;
    gravity = GRAVITY_FALLING;
    idleTimer.Restart();
    walkingSoundTimer.Restart();
    jumpingEfectGO = new GameObject();
    jumpingEffectSprite = new Sprite(*jumpingEfectGO,JUMPING_EFECT_SPRITE, JUMPING_EFECT_FRAME_COUNT, (JUMPING_EFECT_DURATION/JUMPING_EFECT_FRAME_COUNT) + 0.01);
    jumpingEffectSprite->SetScale({2,2});
    jumpingEfectGO->box.z = 5;
    if(isLeftSide) {
        jumpingEfectGO->box.x = associated.box.x;
    } else {
        jumpingEfectGO->box.x = associated.box.x + (associated.box.w/2) ;
    }
    jumpingEfectGO->box.y = associated.box.y + associated.box.h;
    Game::GetInstance().GetCurrentState().AddObject(jumpingEfectGO);
    jumpingEffectSprite->isBlinking = true;
    movingPlatformVelocity = {0,0};
}

void Character::IdleUpdate(float dt) {
    if(isLeftSide) {
        if(global_beat->GetOnBeat()) {
            if(!switchedIdleOnBeat){
                if(idleState == UP){
                    idleState = DOWN;
                    charSprite->SwitchSprite(IDLE_SPRITE_DOWN_LEFT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                } else {
                    idleState = UP;
                    charSprite->SwitchSprite(IDLE_SPRITE_UP_LEFT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                }
                switchedIdleOnBeat = true;
            }
        } else {
            switchedIdleOnBeat = false;
        }
    } else {
        if(global_beat->GetOnBeat()) {
            if(!switchedIdleOnBeat) {
                if(idleState == UP){
                    idleState = DOWN;
                    charSprite->SwitchSprite(IDLE_SPRITE_DOWN_RIGHT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                } else {
                    idleState = UP;
                    charSprite->SwitchSprite(IDLE_SPRITE_UP_RIGHT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                }
                switchedIdleOnBeat = true;
            }
        } else {
            switchedIdleOnBeat = false;
        }
    }
}

void Character::Update(float dt)
{
    //cout << "Character is on (" << associated.box.x << " , " << associated.box.y << ")\n";
    // cout << "Camera is on (" << Camera::pos.x << " , " << Camera::pos.y << ")\n";

    Collider *collider = ((Collider *)associated.GetComponent("Collider").get());
    oldPosition = collider->box;
    oldVelocity = velocity;
    InputManager &input = InputManager::GetInstance();
    wasLeftSide = isLeftSide;
    BangUpdate(dt);
    IsInvincibleUpdate(dt);
    if(isStill && !finishIdle) {
        IdleUpdate(dt);
    }

    if(lifeBar->HP() <= 0){
        if(isDead == false) {
            LevelData::GetInstance().deathCount++;
        }
        isDead = true;
        Camera::UnFollow();
    }

    if(associated.box.y >= MAX_CHARACTER_HEIGHT && !Camera::debug){
        cout << "Character passed the height limit" << endl;
        deathTimer.Update(dt);
        if(deathTimer.Get() >= DEATH_SCREEN_TIME){
            LevelState* levelState;
            levelState = new LevelState();
            Game::GetInstance().Push(levelState);
        }
    }

    if (gotHit)
    {
        GotHit(dt);
    } else {
        if(isLaunching) {
            LaunchUpdate(dt);
        }
        else {
            if(recoveringFromHitKnockback){
                RecoverFromHitKnockback(dt);
            } if(!recoveringFromHitKnockback || canCancelKnockBack) {
                if(canCancelKnockBack && !isOnGround) {
                    isFalling = true;
                    peakDone = false;
                    isRising = false;
                    hasChanged = false;
                }
                if (isAttacking) {
                    AttackUpdate(dt);
                } else {
                    MoveSideWays(dt);
                    Jump(dt);
                    DoAttack(dt);
                    StopMovingSideWays(dt);
                    ApplyPhysics(dt);
                }
            }
        }
    }
    if (velocity.y <= MAX_FALL_SPEED)
    {
        velocity.y += gravity;
    }
    associated.box += (velocity + movingPlatformVelocity) * dt;
    if(jumpingEfect) {
        if(isLeftSide) {
            jumpingEfectGO->box.x = associated.box.x + associated.box.w;
        } else {
            jumpingEfectGO->box.x = associated.box.x + (associated.box.w/2) ;
        }
        jumpingEfectGO->box.y = associated.box.y + associated.box.h;
        jumpingEffectTimer.Update(dt);
        if(jumpingEffectTimer.Get() >= JUMPING_EFECT_DURATION){
            jumpingEfect = false;
            jumpingEffectSprite->isBlinking = true;
            jumpingEffectTimer.Restart();
        }
    }
    Camera::Update(dt);
    isFalling = true;
    peakDone = false;
    wasOnGround = isOnGround;
    isOnTopOfJumpingPad = false;
    isOnGround = false;
    //isOnMovingPlatform = false;
    movingPlatformVelocity = {0,0};
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
    if(!isDead) {
        if ( other.GetComponent("JumpingPad") ){
            //JumpingPadCollision(other);
            isOnTopOfJumpingPad = true;
        } else {
            if ( other.GetComponent("BellEnemy") != NULL || other.GetComponent("HarpEnemy") != NULL || other.GetComponent("AccordionEnemy") != NULL)
            {
                if (!isInvincible && !recoveringFromHitKnockback)
                {
                    EnemyCollision(other);
                }
            } else {
                if(other.GetComponent("MovingPlatforms") != NULL){
                    MovingPlatformsCollision(other);
                } else {
                    if(other.GetComponent("Heart") != NULL) {
                        HeartCollision(other);
                    }
                }
            }
        }
    }
}

void Character::HeartCollision(GameObject& other) {
    if(lifeBar->HP() < 5){
        sound->Open(GET_HEART_SOUND);
        sound->Play(1);
    }
    lifeBar->GetHP();
}

void Character::MovingPlatformsCollision(GameObject& other) {
    Collider * collider = ((Collider *)associated.GetComponent("Collider").get());
    Collider * platformCollider = ((Collider *)other.GetComponent("Collider").get());
    if (velocity.y > 0 || isAttacking || gotHit)
    {
        if ((collider->box.y + collider->box.h - 10 <= platformCollider->box.y) && (collider->box.x + collider->box.w > platformCollider->box.x + 24) && (collider->box.x < platformCollider->box.x + platformCollider->box.w - 24))
        {
            LandOnground();
            associated.box.y = platformCollider->box.y - associated.box.h - 90;
            if(((MovingPlatforms*) other.GetComponent("MovingPlatforms").get())->GetMovingX()){
                movingPlatformVelocity.x = ((MovingPlatforms*) other.GetComponent("MovingPlatforms").get())->GetVelocity();
            }
            if(((MovingPlatforms*) other.GetComponent("MovingPlatforms").get())->GetMovingY()) {
                movingPlatformVelocity.y = ((MovingPlatforms*) other.GetComponent("MovingPlatforms").get())->GetVelocity();
            }
        }
    }
}

void Character::EnemyCollision(GameObject& other) {
    sound->Open(TAKE_DAMGE_SOUND);
    sound->Play(1);
    if (other.box.x > associated.box.x)
    {
        velocity.x = -1 * HURT_DEFLECT_SPEED;
    }
    else
    {
        velocity.x = HURT_DEFLECT_SPEED;
    }
    if (!isOnGround)
    {
        velocity.y = HURT_BOUNCING_SPEED;
    }
    else
    {
        walkingSoundTimer.Restart();
    }
    gravity = HURT_GRAVITY;
    gotHit = true;
    lifeBar->LoseHP();
    LevelData::GetInstance().damageCount++;
    cout<<"damage "<<LevelData::GetInstance().damageCount<<endl;
    isInvincible = true;
    if (isAttacking)
    {
        isAttacking = false;
        attackOnBeat = false;
        //associated.box.x = associated.box.x + 2;
        attackGO->RequestedDelete();
    }
    invincibilityTimer.Restart();
    endingInvincibilityTimer.Restart();
    blinkTimer.Restart();
    if (isLeftSide)
    {
        charSprite->SwitchSprite(HURT_SPRITE_LEFT, HURT_FRAME_COUNT, HURT_FRAME_TIME);
    }
    else
    {
        charSprite->SwitchSprite(HURT_SPRITE_RIGHT, HURT_FRAME_COUNT, HURT_FRAME_TIME);
    }
    recoverFromHitTimer.Restart();
}

void Character::NotifYCollisionWithMap(Rect tileBox)
{
    Rect pastPosition;
    Collider *collider = ((Collider *)associated.GetComponent("Collider").get());
    if (Debugger::GetInstance().lookCharCollision)
    {
        cout << "collider->box.x: " << collider->box.x << endl;
        cout << "collider->box.y: " << collider->box.y << endl;
        cout << "collider->box.w: " << collider->box.w << endl;
        cout << "collider->box.h: " << collider->box.h << endl;
        cout << "box.x: " << tileBox.x << endl;
        cout << "box.y: " << tileBox.y << endl;
        cout << "box.w: " << tileBox.w << endl;
        cout << "box.h: " << tileBox.h << endl;
    }
    if (tileBox.z == 101 || tileBox.z == 102 || tileBox.z == 103 || tileBox.z == 148 || tileBox.z == 104 ||
        tileBox.z == 67 || tileBox.z == 68 || tileBox.z == 57 || tileBox.z == 58 || tileBox.z == 66 || tileBox.z == 84 ||
        tileBox.z == 149 || tileBox.z == 150 || tileBox.z == 151 || tileBox.z == 130 || tileBox.z == 129 || tileBox.z == 147)
    {
        if (tileBox.z == 67)
        {
            LightSlope1Collision(tileBox);
            isOnSlope == true;
        }
        else
        {
            if (tileBox.z == 66)
            {
                LightSlope2Collision(tileBox);
                isOnSlope = true;
            }
            else
            {
                LightGroundCollision(tileBox);
                isOnSlope = false;
            }
        }
    }
    else
    {
        if (tileBox.z == 7)
        {
            SolidSlope1Collision(tileBox);
            isOnSlope = true;
        }
        else
        {
            if (tileBox.z == 6)
            {
                SolidSlope2Collision(tileBox);
                isOnSlope = true;
            }
            else
            {
                SolidGroundCollision(tileBox);
                isOnSlope = false;
            }
        }
    }
}

void Character::SolidGroundCollision(Rect tileBox)
{
    if (!isDead) {
        Collider *collider = ((Collider *)associated.GetComponent("Collider").get());
        if (velocity.y > 0 || isAttacking || gotHit)
        {
            if ((collider->box.y + collider->box.h - 50 <= tileBox.y) && (collider->box.x + collider->box.w > tileBox.x + 24) && (collider->box.x < tileBox.x + tileBox.w - 24))
            {
                LandOnground();
                associated.box.y = tileBox.y - associated.box.h - 45;
            }
        }
        if (velocity.y <= 0)
        {
            if ((collider->box.y >= tileBox.y) && (collider->box.x + collider->box.w > tileBox.x + 24) && (collider->box.x < tileBox.x + tileBox.w - 24))
            {
                velocity.y = 0;
                associated.box.y = tileBox.y + tileBox.h - 45;
                /*if(isLaunching) {
                    isLaunching = false;
                    peakDone = true;
                    isFalling = true;
                    isRising = false;
                    gravity = GRAVITY_FALLING;
                }*/
            }
        }
        if ((velocity.x >= 0) && (collider->box.x < tileBox.x))
        {
            if ((collider->box.y + collider->box.h - 50 > tileBox.y) && (collider->box.y + 50 < tileBox.y + tileBox.h))
            {
                velocity.x = 0;
                associated.box.x = tileBox.x - associated.box.w - 35;
                /*if(isLaunching){
                    isLaunching = false;
                    peakDone = true;
                    isFalling = true;
                    isRising = false;
                    gravity = GRAVITY_FALLING;
                }*/
            }
        }
        if ((velocity.x <= 0) && (collider->box.x > tileBox.x) && (collider->box.y + 40 < tileBox.y + tileBox.h))
        {
            if ((collider->box.y + collider->box.h - 40 > tileBox.y))
            {
                velocity.x = 0;
                associated.box.x = tileBox.x + tileBox.w - 75;
                /*if(isLaunching){
                    isLaunching = false;
                    peakDone = true;
                    isFalling = true;
                    isRising = false;
                    gravity = GRAVITY_FALLING;
                }*/
            }
        }
    }
}

void Character::LightGroundCollision(Rect tileBox)
{

    if (!isDead){
        Collider *collider = ((Collider *)associated.GetComponent("Collider").get());
        if (velocity.y > 0 || isAttacking || gotHit)
        {
            if ((collider->box.y + collider->box.h - 25 <= tileBox.y) && (collider->box.x + collider->box.w > tileBox.x + 12) && (collider->box.x < tileBox.x + tileBox.w - 12))
            {
                LandOnground();
                associated.box.y = tileBox.y - associated.box.h - 45;
            }
        }
    }
}

void Character::LandOnground()
{

    if (!wasOnGround && !isAttacking && !gotHit)
    {
        if (isLeftSide)
        {
            if(idleState == UP){
                idleState = DOWN;
                charSprite->SwitchSprite(IDLE_SPRITE_DOWN_LEFT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
            } else {
                idleState = UP;
                charSprite->SwitchSprite(IDLE_SPRITE_UP_LEFT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
            }
        }
        else
        {
            if(idleState == UP){
                idleState = DOWN;
                charSprite->SwitchSprite(IDLE_SPRITE_DOWN_RIGHT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
            } else {
                idleState = UP;
                charSprite->SwitchSprite(IDLE_SPRITE_UP_RIGHT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
            }
        }
        idleTimer.Restart();
        finishIdle = false;
    }
    /*if(isLaunching) {
        isLaunching = false;
        peakDone = true;
        isFalling = true;
        isRising = false;
        gravity = GRAVITY_FALLING;
    }*/
    isOnGround = true;
    canAttack = true;
    isFalling = false;
    isRising = false;
    peakDone = true;
    hasChanged = false;
    if (!wasOnGround)
    {
        isStill = true;
    }
    gravity = GRAVITY_FALLING;
    velocity.y = 0;
}

void Character::SolidSlope2Collision(Rect tileBox) {
    if (!isDead){
        float posX;
        float posY;
        float tang;
        Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
        tang = (float)(tileBox.h)/(float)(tileBox.w + 40);
        posX = collider->box.x + collider->box.w - (tileBox.x - 40);
        posY = posX * tang;
        posY = tileBox.y + tileBox.h - posY;
        if (velocity.y > 0 || isAttacking || gotHit) {
            if((collider->box.y + collider->box.h >= posY) && (collider->box.x + collider->box.w > tileBox.x) && (collider->box.x < tileBox.x + tileBox.w)) {
                associated.box.y = posY - associated.box.h - 20;
                LandOnground();
            }
        }
        if(velocity.y <= 0) {
            if((collider->box.y >= posY) && (collider->box.x + collider->box.w > tileBox.x + 24) && (collider->box.x < tileBox.x + tileBox.w - 24)) {
                velocity.y = 0;
                associated.box.y = posY + tileBox.h - 45;
                /*if(isLaunching) {
                    isLaunching = false;
                    peakDone = true;
                    isFalling = true;
                    isRising = false;
                    gravity = GRAVITY_FALLING;
                }*/
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
            if((collider->box.y + collider->box.h - 60 > posY)) {
                velocity.x = 0;
                associated.box.x = tileBox.x + tileBox.w - 75;
            }
        }
    }
}

void Character::LightSlope2Collision(Rect tileBox) {
    if (!isDead){
        float posX;
        float posY;
        float tang;
        Collider *collider = ((Collider*) associated.GetComponent("Collider").get());
        tang = (float)(tileBox.h)/(float)(tileBox.w + 40);
        posX = collider->box.x + collider->box.w - (tileBox.x - 40);
        posY = posX * tang;
        posY = tileBox.y + tileBox.h - posY;
        if (velocity.y > 0 || isAttacking || gotHit) {
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
}

void Character::HitKnockBack()
{
    attackGO->RequestedDelete();
    if(attackOnBeat) {
        if (isLeftSide) {
            velocity.x = HIT_DEFLECT_SPEED;
            charSprite->SwitchSprite(RECOVER_SPRITE_LEFT_ON_BEAT, RECOVER_FRAME_COUNT, RECOVER_DURATION / RECOVER_FRAME_COUNT);
        }
        else {
            velocity.x = -1 * HIT_DEFLECT_SPEED;
            charSprite->SwitchSprite(RECOVER_SPRITE_RIGHT_ON_BEAT, RECOVER_FRAME_COUNT, RECOVER_DURATION / RECOVER_FRAME_COUNT);
        }
        canCancelKnockBack = true;
    } else {
        if (isLeftSide) {
            velocity.x = HIT_DEFLECT_SPEED;
            charSprite->SwitchSprite(RECOVER_SPRITE_LEFT, RECOVER_FRAME_COUNT, RECOVER_DURATION / RECOVER_FRAME_COUNT);
        }
        else {
            velocity.x = -1 * HIT_DEFLECT_SPEED;
            charSprite->SwitchSprite(RECOVER_SPRITE_RIGHT, RECOVER_FRAME_COUNT, RECOVER_DURATION / RECOVER_FRAME_COUNT);
        }
    }
    isAttacking = false;
    gravity = GRAVITY_FALLING;
    attackOnBeat = false;
    hitRecoverTimer.Restart();
    recoveringFromHitKnockback = true;
}

void Character::LightSlope1Collision(Rect tileBox)
{
    float posX;
    float posY;
    float tang;
    Collider *collider = ((Collider *)associated.GetComponent("Collider").get());
    tang = (float)(tileBox.h) / (float)(tileBox.w + 40);
    posX = tileBox.x + tileBox.w + 40 - collider->box.x;
    posY = posX * tang;
    posY = tileBox.y + tileBox.h - posY;
    if (velocity.y > 0 || isAttacking || gotHit)
    {
        if ((collider->box.y + collider->box.h - 25 >= posY) && (collider->box.x + collider->box.w > tileBox.x) && (collider->box.x < tileBox.x + tileBox.w))
        {
            associated.box.y = posY - associated.box.h - 20;
            LandOnground();
        }
    }
    if ((velocity.x <= 0) && (collider->box.x > tileBox.x) && (collider->box.y + 70 < posY + tileBox.h))
    {
        if ((collider->box.y + collider->box.h - 42 > posY))
        {
            if (isOnSlope)
            {
                velocity.x = 0;
                associated.box.x = tileBox.x + tileBox.w - 75;
            }
            else
            {
                associated.box.y = posY - associated.box.h - 40;
            }
        }
    }
}

void Character::SolidSlope1Collision(Rect tileBox)
{
    float posX;
    float posY;
    float tang;
    Collider *collider = ((Collider *)associated.GetComponent("Collider").get());
    tang = (float)(tileBox.h) / (float)(tileBox.w + 40);
    posX = tileBox.x + tileBox.w + 40 - collider->box.x;
    posY = posX * tang;
    posY = tileBox.y + tileBox.h - posY;
    if(!isDead) {
        if (velocity.y > 0 || isAttacking || gotHit)
        {
            if ((collider->box.y + collider->box.h - 25 >= posY) && (collider->box.x + collider->box.w > tileBox.x) && (collider->box.x < tileBox.x + tileBox.w))
            {
                associated.box.y = posY - associated.box.h - 20;
                LandOnground();
            }
        }
        if (velocity.y <= 0)
        {
            if ((collider->box.y >= posY) && (collider->box.x + collider->box.w > tileBox.x + 24) && (collider->box.x < tileBox.x + tileBox.w - 24))
            {
                velocity.y = 0;
                associated.box.y = posY + tileBox.h - 45;
            }
            /*if(isLaunching) {
                isLaunching = false;
                peakDone = true;
                isFalling = true;
                isRising = false;
                gravity = GRAVITY_FALLING;
            }*/
        }
        if ((velocity.x >= 0) && (collider->box.x < tileBox.x))
        {
            if ((collider->box.y + collider->box.h - 60 > posY) && (collider->box.y + 50 < posY + tileBox.h))
            {
                velocity.x = 0;
                associated.box.x = tileBox.x - associated.box.w - 35;
            }
        }
        if ((velocity.x <= 0) && (collider->box.x > tileBox.x) && (collider->box.y + 40 < posY + tileBox.h))
        {
            if ((collider->box.y + collider->box.h - 42 > posY))
            {
                if (isOnSlope)
                {
                    velocity.x = 0;
                    associated.box.x = tileBox.x + tileBox.w - 75;
                }
                else
                {
                    associated.box.y = posY - associated.box.h - 40;
                }
            }
        }
    }
}

void Character::BangUpdate(float dt) {
	if(!finishIdle) {
		idleTimer.Update(dt);
		if (idleTimer.Get() >= IDLE_DURATION && isOnGround) {
			if (isLeftSide) {
				charSprite->SwitchSprite(LITSEN_TO_MUSIC_LEFT_SPRITE, LITSEN_TO_MUSIC_FRAME_COUNT,
				                         LISTEN_TO_MUSIC_FRAME_TIME);
			} else {
				charSprite->SwitchSprite(LITSEN_TO_MUSIC_RIGHT_SPRITE, LITSEN_TO_MUSIC_FRAME_COUNT,
				                         LISTEN_TO_MUSIC_FRAME_TIME);
			}
			finishIdle = true;
		}
	}
}

void Character::IsInvincibleUpdate(float dt) {
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
}

void Character::RecoverFromHitKnockback(float dt) {
    hitRecoverTimer.Update(dt);
    if(hitRecoverTimer.Get() >= RECOVER_DURATION ) {
        velocity.x = 0;
        isStill = true;
        canAttack = true;
        attackTimer.Restart();
        recoveringFromHitKnockback = false;
        hitRecoverTimer.Restart();
        if(!isOnGround) {
            isFalling = true;
            peakDone = false;
            isRising = false;
            hasChanged = false;
        }
        if(isLeftSide) {
            charSprite->SwitchSprite(IDLE_SPRITE_LEFT, IDLE_LEFT_FRAME_COUNT, IDLE_FRAME_TIME);
        } else {
            charSprite->SwitchSprite(IDLE_SPRITE_RIGHT, IDLE_RIGHT_FRAME_COUNT, IDLE_FRAME_TIME);
        }
    }
}

void Character::GotHit(float dt) {
    recoverFromHitTimer.Update(dt);
    if (isOnGround)
    {
        if (recoverFromHitTimer.Get() >= HURT_DURATION)
        {
            gotHit = false;
            gravity = GRAVITY_FALLING;
            velocity.x = 0;
            idleTimer.Restart();
            finishIdle = false;
            if (isLeftSide)
            {
                if(idleState == UP){
                    idleState = DOWN;
                    charSprite->SwitchSprite(IDLE_SPRITE_DOWN_LEFT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                } else {
                    idleState = UP;
                    charSprite->SwitchSprite(IDLE_SPRITE_UP_LEFT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                }
            }
            else
            {
                if(idleState == UP){
                    idleState = DOWN;
                    charSprite->SwitchSprite(IDLE_SPRITE_DOWN_RIGHT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                } else {
                    idleState = UP;
                    charSprite->SwitchSprite(IDLE_SPRITE_UP_RIGHT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                }
            }
        }
    }
}

void Character::AttackUpdate(float dt) {
    attackTimer.Update(dt);
    if (attackTimer.Get() >= ATTACK_DURATION) {
        velocity.x = 0;
        gravity = GRAVITY_FALLING;
        associated.box.x = associated.box.x + 2;
        if(attackGO != NULL) {
            attackGO->RequestedDelete();
        }
        isAttacking = false;
        attackOnBeat = false;
        peakDone = true;
        finishIdle = false;
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
}

void Character::MoveSideWays(float dt) {
    if (InputManager::GetInstance().IsKeyDown(D_KEY)) {
        velocity.x = WALKING_SPEED;
        if((isStill || (!wasOnGround) || (isLeftSide)) && isOnGround ) {
            charSprite->SwitchSprite(WALKING_SPRITE_RIGHT, WALKING_FRAME_COUNT, WALKING_FRAME_TIME);
        }
        isStill = false;
        isLeftSide = false;
        if(isOnGround) {
            walkingSoundTimer.Update(dt);
            if(walkingSoundTimer.Get() >= WALKING_SOUND_TIMER) {
                sound->Open(WALKING_SOUND);
                sound->Play(1);
                walkingSoundTimer.Restart();
            }
        }
        canCancelKnockBack = false;
        recoveringFromHitKnockback = false;
        finishIdle = true;
        //charSprite->flip = false;
    } else {
        if (InputManager::GetInstance().IsKeyDown(A_KEY)) {
            velocity.x = -1 * WALKING_SPEED;
            if ((isStill || (!wasOnGround) || (!isLeftSide)) && isOnGround) {
                charSprite->SwitchSprite(WALKING_SPRITE_LEFT, WALKING_FRAME_COUNT, WALKING_FRAME_TIME);
            }
            if(isOnGround) {
                walkingSoundTimer.Update(dt);
                if(walkingSoundTimer.Get() >= WALKING_SOUND_TIMER) {
                    sound->Open(WALKING_SOUND);
                    sound->Play(1);
                    walkingSoundTimer.Restart();
                }
            }
            isStill = false;
            canCancelKnockBack = false;
            recoveringFromHitKnockback = false;
            isLeftSide = true;
            finishIdle = true;
            //charSprite->flip = true;
        }
    }
}

void Character::Jump(float dt) {
    if (InputManager::GetInstance().KeyPress(W_KEY)) {
        if (isOnGround) {
            walkingSoundTimer.Restart();
            //cout << "Is on top of Jumping Pad? " << isOnTopOfJumpingPad << endl;
            if(global_beat->GetOnBeat() == true){
                comboSystem->RestartComboTimer();
                if(isOnTopOfJumpingPad){
                    velocity.y = ULTRA_JUMP_SPEED;
                }
                else{
                    velocity.y = JUMPING_SPEED_ON_BEAT;
                }
                jumpedOnBeat = true;
                sound->Open(JUMPING_SOUND);
                sound->Play(1);
                global_beat->ActionOnBeat();
                jumpingEfect = true;
                jumpingEffectSprite->isBlinking = false;
                jumpingEffectSprite->SwitchSprite(JUMPING_EFECT_SPRITE, JUMPING_EFECT_FRAME_COUNT, (JUMPING_EFECT_DURATION/JUMPING_EFECT_FRAME_COUNT) + 0.01 );
            } else {
                jumpedOnBeat = false;
                velocity.y = JUMPING_SPEED;
                sound->Open(JUMPING_SOUND_ON_BEAT);
                sound->Play(1);
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
	        finishIdle = true;
        }
        canCancelKnockBack = false;
        recoveringFromHitKnockback = false;
    }
}

void Character::DoAttack(float dt) {
    Attack *attack;
    if (InputManager::GetInstance().KeyPress(SPACE_KEY)) {
        if(canAttack) {
            walkingSoundTimer.Restart();
            int isLeft = isLeftSide ? -1 : 1;
            gravity = 0;
            velocity.y = 0;
            isAttacking = true;
            finishIdle = true;
            canAttack = false;
            isRising = false;
            peakDone = true;
            if(global_beat->GetOnBeat() == true){
                comboSystem->RestartComboTimer();
                velocity.x = isLeft * ON_BEAT_ATTACKING_SPEED;
                attackOnBeat = true;
                sound->Open(ATTACK_SOUND_ON_BEAT);
                sound->Play(1);
                jumpingEffectSprite->isBlinking = false;
                jumpingEfect = true;
                jumpingEffectSprite->SwitchSprite(JUMPING_EFECT_SPRITE, JUMPING_EFECT_FRAME_COUNT, (JUMPING_EFECT_DURATION/JUMPING_EFECT_FRAME_COUNT) + 0.01);
            } else {
                attackOnBeat = false;
                velocity.x = isLeft * ATTACKING_SPEED;
                sound->Open(ATTACK_SOUND);
                sound->Play(1);
            }
            attackGO = new GameObject();
            attackGO->box.z = 4;
            if(isLeftSide) {
                attack = new Attack(*attackGO, {2, 2}, {0, 0}, &associated, 20, 25, 25, 76);
            } else {
                attack = new Attack(*attackGO, {2, 2}, {0, 0}, &associated, 20, 25, 155, 76);
            }
            attack->isLeftSide = isLeftSide;
            Game::GetInstance().GetCurrentState().AddObject(attackGO);
            attackTimer.Restart();
            if(isOnGround) {
                if(isLeftSide) {
                    if(global_beat->GetOnBeat() == true) {
                        global_beat->ActionOnBeat();
                        charSprite->SwitchSprite(ATTACK_LEFT_SPRITE_ON_BEAT, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                    } else {
                        charSprite->SwitchSprite(ATTACK_LEFT_SPRITE, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                    }
                } else {
                    if(global_beat->GetOnBeat() == true) {
                        global_beat->ActionOnBeat();
                        charSprite->SwitchSprite(ATTACK_RIGHT_SPRITE_ON_BEAT, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                    } else {
                        charSprite->SwitchSprite(ATTACK_RIGHT_SPRITE, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                    }
                }
            } else {
                if(isLeftSide) {
                    if(global_beat->GetOnBeat() == true) {
                        global_beat->ActionOnBeat();
                        charSprite->SwitchSprite(ATTACK_AIR_LEFT_SPRITE_ON_BEAT, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                    } else {
                        charSprite->SwitchSprite(ATTACK_AIR_LEFT_SPRITE, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                    }
                } else {
                    if(global_beat->GetOnBeat() == true) {
                        global_beat->ActionOnBeat();
                        charSprite->SwitchSprite(ATTACK_AIR_RIGHT_SPRITE_ON_BEAT, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                    } else {
                        charSprite->SwitchSprite(ATTACK_AIR_RIGHT_SPRITE, ATTACK_FRAME_COUNT, ATTACK_DURATION/ATTACK_FRAME_COUNT + 0.1);
                    }
                }
            }
            canCancelKnockBack = false;
            recoveringFromHitKnockback = false;
        }
    }
}

void Character::StopMovingSideWays(float dt) {
    if (InputManager::GetInstance().KeyRelease(D_KEY) || InputManager::GetInstance().KeyRelease(A_KEY)) {
        velocity.x = 0;
        if(isOnGround) {
            walkingSoundTimer.Restart();
            if(isLeftSide) {
                if(idleState == UP){
                    idleState = DOWN;
                    charSprite->SwitchSprite(IDLE_SPRITE_DOWN_LEFT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                } else {
                    idleState = UP;
                    charSprite->SwitchSprite(IDLE_SPRITE_UP_LEFT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                }
            } else {
                if(idleState == UP){
                    idleState = DOWN;
                    charSprite->SwitchSprite(IDLE_SPRITE_DOWN_RIGHT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                } else {
                    idleState = UP;
                    charSprite->SwitchSprite(IDLE_SPRITE_UP_RIGHT, IDLE_SPRITE_ON_BEAT_FRAME_COUNT, global_beat->GetFalseDuration()/IDLE_SPRITE_ON_BEAT_FRAME_COUNT);
                }
            }
            idleTimer.Restart();
            finishIdle = false;
            isStill = true;
        }
    }
}

void Character::ApplyPhysics(float dt) {
    float beforeRiserDuration;
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

bool Character::AttackOnBeat() {
    return attackOnBeat;
}

void Character::LaunchCharacter(Vect2 launchVelocity, bool isLeftSide,
 string launcherSprite, int launcherSpriteFrameCount, float launcherSpriteFrameTime, float launchDuration) {
    Collider *collider = ((Collider *)associated.GetComponent("Collider").get());
    this->isLeftSide = isLeftSide;
    charSprite->SwitchSprite(launcherSprite, launcherSpriteFrameCount, launcherSpriteFrameTime);
    collider->Update(0);
    isAttacking = false;
    canAttack = false;
    isOnGround = false;
    gravity = 0;
    velocity = launchVelocity;
    this->launchDuration = launchDuration;
    attackGO->RequestedDelete();
    isLaunching = true;
    LaunchTimer.Restart();
}

bool Character::IsCharacterLeftSide() {
    return isLeftSide;
}

void Character::LaunchUpdate(float dt) {
    LaunchTimer.Update(dt);
    if(LaunchTimer.Get() >= launchDuration){
        isLaunching = false;
        peakDone = true;
        isFalling = true;
        canAttack = true;
        isRising = false;
        velocity.x = 0;
        gravity = GRAVITY_FALLING;
    }
}