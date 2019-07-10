#include "../include/VictoryState.h"

VictoryState::VictoryState() : State() {
}

void VictoryState::Start() {
    playedCompletedSound = false;
    playedCollectableIconSound = false;
    playedHeartIconSound = false;
    playedTimeIconSound = false;
    playedDeathIconSound = false;
    playedAttackIconSound = false;
    playedYourRankIsSound = false;
    playedResultSound = false;
    LevelData::GetInstance().clear();
    State::Start();
}

void VictoryState::LoadAssets() {
    // Adicionando Background
    layer1 = new GameObject();
    layer2 = new GameObject();
    layer3 = new GameObject();
    layer4 = new GameObject();
    layer5 = new GameObject();
    layer6 = new GameObject();
    bgMusic = new GameObject();
    completeLayer = new GameObject();
    resultLayer = new GameObject();
    yourRankIsLayer = new GameObject();
    heartIconGO = new GameObject();
    deathIconGO = new GameObject();
    timeIconGO = new GameObject();
    attackIconGO = new GameObject();
    collectableIconGO = new GameObject();
    popSoundGO = new GameObject();
    // Camera::pos.x = 0;
    // Camera::pos.y = 0;
    Camera::UnFollow();
    popSound = new Sound(*popSoundGO, POP_ICON_SOUND);
    heartIconSprite = new Sprite(*heartIconGO, HEART_ICON_SPRITE);
    deathIconSprite = new Sprite(*deathIconGO, DEATH_ICON_SPRITE);
    timeIconSprite = new Sprite(*timeIconGO, TIME_ICON_SPRITE);
    attackIconSprite = new Sprite(*attackIconGO, ATTACK_ICON_SPRITE);
    collectableIconSprite = new Sprite(*collectableIconGO, COLLECTABLE_ICON_SPRITE);
    heartIconSprite->SetScale({2,2});
    deathIconSprite->SetScale({2,2});
    timeIconSprite->SetScale({2,2});
    attackIconSprite->SetScale({2,2});
    collectableIconSprite->SetScale({2,2});
    heartIconSprite->isBlinking = true;
    deathIconSprite->isBlinking = true;
    timeIconSprite->isBlinking = true;
    attackIconSprite->isBlinking = true;
    collectableIconSprite->isBlinking = true;
    new MovingLayer(*layer1, VICTORY_LAYER1_SPRITE, {LAYER1_BEGINING_POS_X, LAYER_BEGINING_POS_Y}, {LAYER_VELOCITY_X, LAYER_VELOCITY_Y});
    new MovingLayer(*layer2, VICTORY_LAYER2_SPRITE, {LAYER2_BEGINING_POS_X, LAYER_BEGINING_POS_Y}, {LAYER_VELOCITY_X, LAYER_VELOCITY_Y});
    new MovingLayer(*layer3, VICTORY_LAYER3_SPRITE, {LAYER3_BEGINING_POS_X, LAYER_BEGINING_POS_Y}, {LAYER_VELOCITY_X, LAYER_VELOCITY_Y});
    new MovingLayer(*layer4, VICTORY_LAYER4_SPRITE, {LAYER4_BEGINING_POS_X, LAYER_BEGINING_POS_Y}, {LAYER_VELOCITY_X, LAYER_VELOCITY_Y});
    new MovingLayer(*layer5, VICTORY_LAYER5_SPRITE, {LAYER5_BEGINING_POS_X, LAYER_BEGINING_POS_Y}, {LAYER_VELOCITY_X, LAYER_VELOCITY_Y});
    movingLayer6 = new MovingLayer(*layer6, VICTORY_LAYER6_SPRITE, {LAYER6_BEGINING_POS_X, LAYER_BEGINING_POS_Y}, {LAYER_VELOCITY_X, LAYER_VELOCITY_Y});
    completeLayerSprite = new Sprite(*completeLayer, COMPLETE_SPRITE);
    completeLayerSprite->isBlinking = true;
    resultSprite = new Sprite(*resultLayer, RESULT_SPRITE);
    resultSprite->isBlinking = true;
    yourRankIsLayerSprite = new Sprite(*yourRankIsLayer, YOUR_RANK_IS_SPRITE);
    yourRankIsLayerSprite->isBlinking = true;
    music = new Music(*bgMusic, VICTORY_BG_MUSIC);
    layer1->box.w = GameInfo::GetInstance().WIDTH;
    layer1->box.h = GameInfo::GetInstance().HEIGHT;
    layer1->box.x = LAYER1_BEGINING_POS_X - Camera::pos.x;
    layer1->box.y = LAYER_BEGINING_POS_Y - Camera::pos.y;
    layer2->box.w = GameInfo::GetInstance().WIDTH;
    layer2->box.h = GameInfo::GetInstance().HEIGHT;
    layer2->box.x = LAYER2_BEGINING_POS_X - Camera::pos.x;
    layer2->box.y = LAYER_BEGINING_POS_Y - Camera::pos.y;
    layer3->box.w = GameInfo::GetInstance().WIDTH;
    layer3->box.h = GameInfo::GetInstance().HEIGHT;
    layer3->box.x = LAYER3_BEGINING_POS_X - Camera::pos.x;
    layer3->box.y = LAYER_BEGINING_POS_Y - Camera::pos.y;
    layer4->box.w = GameInfo::GetInstance().WIDTH;
    layer4->box.h = GameInfo::GetInstance().HEIGHT;
    layer4->box.x = LAYER4_BEGINING_POS_X - Camera::pos.x;
    layer4->box.y = LAYER_BEGINING_POS_Y - Camera::pos.y;
    layer5->box.w = GameInfo::GetInstance().WIDTH;
    layer5->box.h = GameInfo::GetInstance().HEIGHT;
    layer5->box.x = LAYER5_BEGINING_POS_X - Camera::pos.x;
    layer5->box.y = LAYER_BEGINING_POS_Y - Camera::pos.y;
    layer6->box.w = GameInfo::GetInstance().WIDTH;
    layer6->box.h = GameInfo::GetInstance().HEIGHT;
    layer6->box.x = LAYER6_BEGINING_POS_X - Camera::pos.x;
    layer6->box.y = LAYER_BEGINING_POS_Y - Camera::pos.y;
    completeLayer->box.w = GameInfo::GetInstance().WIDTH;
    completeLayer->box.h = GameInfo::GetInstance().HEIGHT;
    completeLayer->box.x = 0 - Camera::pos.x;
    completeLayer->box.y = 0 - Camera::pos.y;
    resultLayer->box.w = GameInfo::GetInstance().WIDTH;
    resultLayer->box.h = GameInfo::GetInstance().HEIGHT;
    resultLayer->box.x = 0 - Camera::pos.x;
    resultLayer->box.y = 0 - Camera::pos.y;
    yourRankIsLayer->box.w = GameInfo::GetInstance().WIDTH;
    yourRankIsLayer->box.h = GameInfo::GetInstance().HEIGHT;
    yourRankIsLayer->box.x = 0 - Camera::pos.x;
    yourRankIsLayer->box.y = 0 - Camera::pos.y;
    collectableIconGO->box.x = 60 - Camera::pos.x;
    collectableIconGO->box.y = 150 - Camera::pos.y;
    heartIconGO->box.x = 60 - Camera::pos.x;
    heartIconGO->box.y = 220 - Camera::pos.y;
    timeIconGO->box.x = 60 - Camera::pos.x;
    timeIconGO->box.y = 290 - Camera::pos.y;
    deathIconGO->box.x = 60 - Camera::pos.x;
    deathIconGO->box.y = 360 - Camera::pos.y;
    attackIconGO->box.x = 60 - Camera::pos.x;
    attackIconGO->box.y = 430 - Camera::pos.y;
    music->Play(-1);
    objectArray.emplace_back(bgMusic);
    objectArray.emplace_back(layer1);
    objectArray.emplace_back(layer2);
    objectArray.emplace_back(layer3);
    objectArray.emplace_back(layer4);
    objectArray.emplace_back(layer5);
    objectArray.emplace_back(layer6);
    objectArray.emplace_back(completeLayer);
    objectArray.emplace_back(yourRankIsLayer);
    objectArray.emplace_back(resultLayer);
    objectArray.emplace_back(heartIconGO);
    objectArray.emplace_back(deathIconGO);
    objectArray.emplace_back(timeIconGO);
    objectArray.emplace_back(attackIconGO);
    objectArray.emplace_back(collectableIconGO);
    objectArray.emplace_back(popSoundGO);
    // Background Adicionado
}

void VictoryState::Update(float dt) {
    State::Update(dt);
    if(movingLayer6->HasFinished()) {
        completeLayerSprite->isBlinking = false;
        if(!playedCompletedSound){
            popSound->Play(1);
            playedCompletedSound = true;
        }
        heartIconTimer.Update(dt);
        deathIconTimer.Update(dt);
        timeIconTimer.Update(dt);
        attackIconTimer.Update(dt);
        collectableIconTimer.Update(dt);
        yourRankIsTimer.Update(dt);
        resultTimer.Update(dt);
        if(heartIconTimer.Get() >= HEART_ICON_TIME){
            heartIconSprite->isBlinking = false;
            if(!playedHeartIconSound){
                popSound->Play(1);
                playedHeartIconSound = true;
            }
        }
        if(deathIconTimer.Get() >= DEATH_ICON_TIME){
            deathIconSprite->isBlinking = false;
            if(!playedDeathIconSound){
                popSound->Play(1);
                playedDeathIconSound = true;
            }
        }
        if(timeIconTimer.Get() >= TIME_ICON_TIME){
            timeIconSprite->isBlinking = false;
            if(!playedTimeIconSound){
                popSound->Play(1);
                playedTimeIconSound = true;
            }
        }
        if(attackIconTimer.Get() >= ATTACK_ICON_TIME){
            attackIconSprite->isBlinking = false;
            if(!playedAttackIconSound){
                popSound->Play(1);
                playedAttackIconSound = true;
            }
        }
        if(collectableIconTimer.Get() >= COLLECTABLE_ICON_TIME){
            collectableIconSprite->isBlinking = false;
            if(!playedCollectableIconSound){
                popSound->Play(1);
                playedCollectableIconSound = true;
            }
        }
        if(yourRankIsTimer.Get() >= YOUR_RANK_IS_TIME) {
            yourRankIsLayerSprite->isBlinking = false;
            if(!playedYourRankIsSound) {
                popSound->Play(1);
                playedYourRankIsSound = true;
            }
        }
        if(resultTimer.Get() >= RESULT_TIME) {
            resultSprite->isBlinking = false;
            if(!playedResultSound) {
                popSound->Play(1);
                playedResultSound = true;
            }
        }
    }
}

void VictoryState::Pause() {}

void VictoryState::Resume() {}

void VictoryState::StartData() {}