#include "../include/Launcher.h"
#include "Game.h"
#include "../include/LevelState.h"


Launcher::Launcher(GameObject& associated, LauncherType type, GameObject* character) : Component(associated) {
    this->type = type;
    this->character = character;
}

void Launcher::Start() {
    sound = new Sound(associated, LAUNCHER_SOUND);
    switch (type) {
        case UP:
            launcherSprite = new Sprite(associated, LAUNCHER_UP);
            pointPos = {associated.box.x - 3 * associated.box.w, associated.box.y - (character->box.h)};
            launchVelocity = {0, -1.5 * LAUNCHER_VELOCITY_Y};
            break;
        case UP_RIGHT:
            launcherSprite = new Sprite(associated, LAUNCHER_UP_RIGHT);
            pointPos = {associated.box.x + associated.box.w, associated.box.y - (character->box.h)};
            launchVelocity = {LAUNCHER_VELOCITY_X, -1 * LAUNCHER_VELOCITY_Y};
            isCharacterLeft = false;
            characterLaunchSprite = RISING_RIGHT_SPRITE;
            characterLaunchSpriteFameCount = RISING_FRAME_COUNT;
            characterLaunchSpriteFrameTime = RISING_FRAME_TIME;
            break;
        case UP_LEFT:
            launcherSprite = new Sprite(associated, LAUNCHER_UP_LEFT);
            pointPos = {associated.box.x - character->box.w, associated.box.y - (character->box.h)};
            launchVelocity = {-1 * LAUNCHER_VELOCITY_X, -1 * LAUNCHER_VELOCITY_Y};
            isCharacterLeft = true;
            characterLaunchSprite = RISING_LEFT_SPRITE;
            characterLaunchSpriteFameCount = RISING_FRAME_COUNT;
            characterLaunchSpriteFrameTime = RISING_FRAME_TIME;
            break;
        case RIGHT:
            launcherSprite = new Sprite(associated, LAUNCHER_RIGHT);
            pointPos = {associated.box.x + associated.box.w, associated.box.y + associated.box.h/2 - (character->box.h/2)};
            launchVelocity = {1.5*LAUNCHER_VELOCITY_X, 0};
            isCharacterLeft = false;
            characterLaunchSprite = PEAK_RIGHT_SPRITE;
            characterLaunchSpriteFameCount = PEAK_FRAME_COUNT;
            characterLaunchSpriteFrameTime = PEAK_FRAME_TIME;
            break;
        case LEFT:
            launcherSprite = new Sprite(associated, LAUNCHER_LEFT);
            pointPos = {associated.box.x - 2*character->box.w, associated.box.y + associated.box.h/2 - (character->box.h/2)};
            launchVelocity = {-1.5 * LAUNCHER_VELOCITY_X, 0};
            isCharacterLeft = true;
            characterLaunchSprite = PEAK_LEFT_SPRITE;
            characterLaunchSpriteFameCount = PEAK_FRAME_COUNT;
            characterLaunchSpriteFrameTime = PEAK_FRAME_TIME;
            break;
        case DOWN:
            launcherSprite = new Sprite(associated, LAUNCHER_DOWN);
            pointPos = {associated.box.x - 3 * associated.box.w, associated.box.y + associated.box.h};
            launchVelocity = {0, 1.5*LAUNCHER_VELOCITY_Y};
            break;
            break;
        default:
            break;
    }
    launcherSprite->SetScale({2,2});
    launcherCollider = new Collider(associated, {2,2}, {0, 0});
}

void Launcher::NotifyCollision(GameObject& other) {
    float launchDuration;
    if(other.GetComponent("Attack") != NULL) {
        comboSystem->RestartComboTimer();
        switch (type) {
        case UP:
            isCharacterLeft = ((Character*) character->GetComponent("Character").get())->IsCharacterLeftSide();
            if(isCharacterLeft) {
                characterLaunchSprite = RISING_LEFT_SPRITE;
            } else {
                characterLaunchSprite = RISING_RIGHT_SPRITE;
            }
            characterLaunchSpriteFameCount = RISING_FRAME_COUNT;
            characterLaunchSpriteFrameTime = RISING_FRAME_TIME;
            break;
        case DOWN:
            isCharacterLeft = ((Character*) character->GetComponent("Character").get())->IsCharacterLeftSide();
            if(isCharacterLeft) {
                characterLaunchSprite = FALLING_LEFT_SPRITE;
            } else {
                characterLaunchSprite = FALLING_RIGHT_SPRITE;
            }
            characterLaunchSpriteFameCount = FALLING_FRAME_COUNT;
            characterLaunchSpriteFrameTime = FALLING_FRAME_TIME;
            break;
        default:
            break;
        }
        character->box.x = pointPos.x;
        character->box.y = pointPos.y - (character->box.h);
        if(((Character*) character->GetComponent("Character").get())->AttackOnBeat()) {
            sound->Open(LAUNCHER_SOUND_ON_BEAT);
            launchDuration = 0.5;
        } else {
            sound->Open(LAUNCHER_SOUND);
            launchDuration = 0.25;
        }
        sound->Play(1);
        //character->Update(0);
        ((Character*) character->GetComponent("Character").get())->LaunchCharacter(launchVelocity, isCharacterLeft,
                                        characterLaunchSprite, characterLaunchSpriteFameCount, characterLaunchSpriteFrameTime, launchDuration);
    }
}

void Launcher::Update(float dt) {
    this->dt = dt;
}

bool Launcher::Is(string type) {
    bool result = false;
    if(type == "Launcher") {
        result = true;
    }
    return result;
}