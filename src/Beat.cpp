#include "../include/Beat.h"

Beat::Beat(GameObject& associated) : Component(associated){
}

void Beat::Start(){
    heartBackground = new GameObject();
    backgroundSprite = new Sprite(*heartBackground, BEATING_HEART_BG, 1, 1);
    backgroundSprite->SetScale({2,2});
    heartBackground->box.z = 6;
    Game::GetInstance().GetCurrentStatePointer()->AddObject(heartBackground);
    beatSprite = new Sprite(associated, BEATING_HEART_SPRITE, FRAME_COUNT, BEAT_TRUE_LIMIT/FRAME_COUNT);
    beatSprite->SetScale({2,2});
    onBeat = true;
    onBeatAnimation = true;
}

void Beat::Update(float dt){
    associated.box.x = 902 - Camera::pos.x;
    associated.box.y = 3 - Camera::pos.y;
    heartBackground->box.x = 854 - Camera::pos.x;
    heartBackground->box.y = 1 - Camera::pos.y;
    if(onBeatAnimation){
    	if(trueTimer.Get() >= BEAT_TRUE_LIMIT - BEAT_OFFSET){
    		onBeat = false;
    	}
        if(trueTimer.Get() >= BEAT_TRUE_LIMIT){
            onBeatAnimation = false;
            beatSprite->SwitchSprite(IDLE_HEART_SPRITE, STILL_FRAME_COUNT, 1);
            trueTimer.Restart();
        }
        trueTimer.Update(dt);
        falseTimer.Update(dt);
    } else {
    	if(falseTimer.Get() >= BEAT_FALSE_LIMIT - BEAT_OFFSET) {
    		onBeat = true;
    	}
        if(falseTimer.Get() >= BEAT_FALSE_LIMIT){
            onBeatAnimation = true;
            beatSprite->SwitchSprite(BEATING_HEART_SPRITE, FRAME_COUNT, BEAT_TRUE_LIMIT/FRAME_COUNT);
            falseTimer.Restart();
        }
        falseTimer.Update(dt);
    }
}

void Beat::Render(){}

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

bool Beat::GetOnBeatAnimation() {
    return onBeatAnimation;
}