#include "../include/Beat.h"

Beat::Beat(GameObject& associated) : Component(associated){
    Start();
}

void Beat::Start(){
    beatSprite = new Sprite(associated, BEATING_SPRITE, FRAME_COUNT, FRAME_TIME);
    onBeat = true;
}

void Beat::Update(float dt){
    if(onBeat){
        if(trueTimer.Get() >= BEAT_LIMIT){
            onBeat = false;
            trueTimer.Restart();
        }
        trueTimer.Update(dt);
    } else {
        if(falseTimer.Get() >= BEAT_INTERVAL){
            onBeat = true;
            falseTimer.Restart();
        }
        falseTimer.Update(dt);
    }
}

void Beat::Render(){}


bool Beat::Is(string type){
    return (type == "Beat") ? true : false;
}