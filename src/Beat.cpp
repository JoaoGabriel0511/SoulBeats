#include "../include/Beat.h"

Beat::Beat(GameObject& associated) : Component(associated){
}

void Beat::Start(){
    heartBackground = new GameObject();
    backgroundSprite = new Sprite(*heartBackground, BEATING_HEART_BG, 1, 1);
    beatWave = new GameObject();
    //waveSprite = new Sprite(*beatWave, WAVE_SPRITE, WAVE_FRAME_COUNT, BEAT_TRUE_LIMIT / WAVE_FRAME_COUNT);
    backgroundSprite->SetScale({2,2});
    heartBackground->box.z = 6;
    beatWave->box.z = 6;
    Game::GetInstance().GetCurrentStatePointer()->AddObject(heartBackground);
    Game::GetInstance().GetCurrentStatePointer()->AddObject(beatWave);
    beatSprite = new Sprite(associated, BEATING_HEART_SPRITE, FRAME_COUNT, BEAT_TRUE_LIMIT/FRAME_COUNT);
    beatSprite->SetScale({2,2});
    //waveSprite->SetScale({2,2});
    onBeat = false;
    onBeatAnimation = false;
    actionOnBeat = false;
    switched = false;
    hasBegun = false;
}

void Beat::BeginBeat () {
    onBeat = true;
    onBeatAnimation = true;
    hasBegun = true;
    waveSprite = new Sprite(*beatWave, WAVE_SPRITE, WAVE_FRAME_COUNT, BEAT_TRUE_LIMIT / WAVE_FRAME_COUNT);
    waveSprite->SetScale({2,2});
}

void Beat::Update(float dt){
    associated.box.x = 902 - Camera::pos.x;
    associated.box.y = 3 - Camera::pos.y;
    if(actionOnBeat) {
        heartBackground->box.x = 837 - Camera::pos.x;
        heartBackground->box.y = 1 - Camera::pos.y;
    } else {
        heartBackground->box.x = 854 - Camera::pos.x;
        heartBackground->box.y = 1 - Camera::pos.y;
    }
    beatWave->box.x = 902 - Camera::pos.x;
    beatWave->box.y = 1 - Camera::pos.y;
    if(hasBegun) {
        if(onBeatAnimation){
            if(trueTimer.Get() >= BEAT_TRUE_LIMIT - BEAT_OFFSET ){
                onBeat = false;
            }
            if(trueTimer.Get() >= BEAT_TRUE_LIMIT){
                onBeatAnimation = false;
                if(!actionOnBeat) {
                    beatSprite->SwitchSprite(IDLE_HEART_SPRITE, STILL_FRAME_COUNT, BEAT_FALSE_LIMIT/STILL_FRAME_COUNT);
                }
                trueTimer.Restart();
                waveSprite->isBlinking = true;
            }
            trueTimer.Update(dt);
            falseTimer.Update(dt);
        } else {
            if(falseTimer.Get() >= BEAT_FALSE_LIMIT - BEAT_OFFSET) {
                onBeat = true;
            }
            if(falseTimer.Get() >= BEAT_FALSE_LIMIT){
                onBeatAnimation = true;
                if(!actionOnBeat) {
                    beatSprite->SwitchSprite(BEATING_HEART_SPRITE, FRAME_COUNT, BEAT_TRUE_LIMIT/FRAME_COUNT);
                }
                waveSprite->isBlinking = false;
                waveSprite->SwitchSprite(WAVE_SPRITE, WAVE_FRAME_COUNT, (BEAT_TRUE_LIMIT/WAVE_FRAME_COUNT) + 0.01);
                falseTimer.Restart();
            }
            falseTimer.Update(dt);
            if(darkTimer.Get() >= DARK_TIME) {
                backgroundSprite->Open(BEATING_HEART_BG);
                heartBackground->box.x = 854 - Camera::pos.x;
                heartBackground->box.y = 1 - Camera::pos.y;
                beatSprite->SwitchSprite(IDLE_HEART_SPRITE, STILL_FRAME_COUNT, BEAT_FALSE_LIMIT/STILL_FRAME_COUNT);
                actionOnBeat = false;
                darkTimer.Restart();
            }
        }
        if(actionOnBeat){
            darkTimer.Update(dt);
        }
    }
}

void Beat::Render(){}

bool Beat::HasBegun() {
    return hasBegun;
}

float Beat::GetFalseDuration() {
    return BEAT_FALSE_LIMIT;
}


bool Beat::Is(string type){
    return (type == "Beat") ? true : false;
}

bool Beat::GetOnBeat(){
    // if(onBeat == true) cout << "returning true\n;"; else cout << "returning false\n;";
    return onBeat;
}

void Beat::ActionOnBeat() {
    backgroundSprite->Open(BEATING_HEART_BG_DARK);
    beatSprite->SwitchSprite(BEATING_HEART_LIGHT_SPRITE, FRAME_COUNT, 1);
    heartBackground->box.x = 840 - Camera::pos.x;
    heartBackground->box.y = 1 - Camera::pos.y;
    actionOnBeat = true;
    darkTimer.Restart();
}

bool Beat::GetOnBeatAnimation() {
    return onBeatAnimation;
}