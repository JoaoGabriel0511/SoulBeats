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
    switchedMusic = false;
    putedContinueText = false;
    CalculatePoints();
    //LevelData::GetInstance().clear();
    State::Start();
}

void VictoryState::CalculatePoints() {
    collectablesPoints = LevelData::GetInstance().collectablesCollected * COLLECTABLES_POINTS;
    deathPenalthy = -1 * LevelData::GetInstance().deathCount * DEATH_PENALTHY;
    damagePenalthy = -1 * LevelData::GetInstance().damageCount * DAMAGE_PENALTHY;
    if(LevelData::GetInstance().time <= 120) {
        timePoints = UNDER_TWO_MIN_POINTS;
    } else if(LevelData::GetInstance().time <= 180) {
        timePoints = UNDER_TREE_MIN_POINTS;
    } else if(LevelData::GetInstance().time <= 240) {
        timePoints = UNDER_FOUR_MIN_POINTS;
    } else {
        timePoints = MORE_THAN_FOUR_MIN_POINTS;
    }
    result = collectablesPoints + deathPenalthy + damagePenalthy + timePoints + LevelData::GetInstance().enemyPoints;
    rankGO = new GameObject();
    rankGO->box.z = 7;
    if(result >= MAESTRO_LIMIT) {
        rankSprite = new Sprite(*rankGO, MAESTRO_SPRITE, MAESTRO_FRAME_COUNT, MAESTRO_FRAME_TIME);
        rankGO->box.x = 550 - Camera::pos.x;
        rankGO->box.y = 100 - Camera::pos.y;
    } else if(result >= BRAVO_LIMIT) {
        rankSprite = new Sprite(*rankGO, BRAVO_SPRITE, BRAVO_FRAME_COUNT, BRAVO_FRAME_TIME);
        rankGO->box.x = 600 - Camera::pos.x;
        rankGO->box.y = 100 - Camera::pos.y;
    } else if(result >= CATCHY_LIMIT) {
        rankSprite = new Sprite(*rankGO, CATCHY_SPRITE, CATCHY_FRAME_COUNT, CATCHY_FRAME_TIME);
        rankGO->box.x = 600 - Camera::pos.x;
        rankGO->box.y = 100 - Camera::pos.y;
    } else {
        rankSprite = new Sprite(*rankGO, FIASCO_SPRITE, FIASCO_FRAME_COUNT, FIASCO_FRAME_TIME);
        rankGO->box.x = 600 - Camera::pos.x;
        rankGO->box.y = 100 - Camera::pos.y;
    }
    rankSprite->SetScale({3,3});
    rankSprite->isBlinking = true;
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
    resultScore = new GameObject();
    yourRankIsLayer = new GameObject();
    heartIconGO = new GameObject();
    damageScoreGO = new GameObject();
    deathIconGO = new GameObject();
    deathScoreGO = new GameObject();
    timeIconGO = new GameObject();
    timeScoreGO = new GameObject();
    attackIconGO = new GameObject();
    attackScoreGO = new GameObject();
    collectableIconGO = new GameObject();
    collectableScoreGO = new GameObject();
    popSoundGO = new GameObject();
    // Camera::pos.x = 0;
    // Camera::pos.y = 0;
    Camera::UnFollow();
    popSound = new Sound(*popSoundGO, POP_ICON_SOUND);
    heartIconSprite = new Sprite(*heartIconGO, HEART_ICON_SPRITE);
    damageScoreText = new Text(*damageScoreGO, "assets/font/editundo.ttf", 40, Text::SOLID, std::to_string(LevelData::GetInstance().damageCount) + " X -" + std::to_string(DAMAGE_PENALTHY) + " -> " + std::to_string(damagePenalthy), SDL_Color {255,255,255}, 0);
    damageScoreText->isBlink = true;
    deathIconSprite = new Sprite(*deathIconGO, DEATH_ICON_SPRITE);
    deathScoreText = new Text(*deathScoreGO, "assets/font/editundo.ttf", 40, Text::SOLID, std::to_string(LevelData::GetInstance().deathCount) + " X -" + std::to_string(DEATH_PENALTHY) + " -> " + std::to_string(deathPenalthy), SDL_Color {255,255,255}, 0);
    deathScoreText->isBlink = true;
    timeIconSprite = new Sprite(*timeIconGO, TIME_ICON_SPRITE);
    timeScoreText = new Text(*timeScoreGO, "assets/font/editundo.ttf", 40, Text::SOLID, std::to_string(LevelData::GetInstance().time) + " -> " + std::to_string(timePoints), SDL_Color {255,255,255}, 0);
    timeScoreText->isBlink = true;
    attackIconSprite = new Sprite(*attackIconGO, ATTACK_ICON_SPRITE);
    attackScoreText = new Text(*attackScoreGO, "assets/font/editundo.ttf", 40, Text::SOLID, std::to_string(LevelData::GetInstance().enemyPoints), SDL_Color {255,255,255}, 0);
    attackScoreText->isBlink = true;
    collectableIconSprite = new Sprite(*collectableIconGO, COLLECTABLE_ICON_SPRITE);
    collectableScoreText = new Text(*collectableScoreGO, "assets/font/editundo.ttf", 40, Text::SOLID, std::to_string(LevelData::GetInstance().collectablesCollected) + " X " + std::to_string(COLLECTABLES_POINTS) + " -> " + std::to_string(collectablesPoints), SDL_Color {255,255,255}, 0);
    collectableScoreText->isBlink = true;
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
    resultScoreText = new Text(*resultScore, "assets/font/editundo.ttf", 60, Text::SOLID, std::to_string(result), SDL_Color {255,255,255}, 0);
    resultScoreText->isBlink = true;
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
    resultScore->box.x = 300 - Camera::pos.x;
    resultScore->box.y = 525 - Camera::pos.y;
    yourRankIsLayer->box.w = GameInfo::GetInstance().WIDTH;
    yourRankIsLayer->box.h = GameInfo::GetInstance().HEIGHT;
    yourRankIsLayer->box.x = 0 - Camera::pos.x;
    yourRankIsLayer->box.y = 0 - Camera::pos.y;
    collectableIconGO->box.x = 60 - Camera::pos.x;
    collectableIconGO->box.y = 150 - Camera::pos.y;
    collectableScoreGO->box.x = 150 - Camera::pos.x;
    collectableScoreGO->box.y = 170 - Camera::pos.y;
    heartIconGO->box.x = 60 - Camera::pos.x;
    heartIconGO->box.y = 220 - Camera::pos.y;
    damageScoreGO->box.x = 150 - Camera::pos.x;
    damageScoreGO->box.y = 240 - Camera::pos.y;
    timeIconGO->box.x = 60 - Camera::pos.x;
    timeIconGO->box.y = 290 - Camera::pos.y;
    timeScoreGO->box.x = 150 - Camera::pos.x;
    timeScoreGO->box.y = 310 - Camera::pos.y;
    deathIconGO->box.x = 60 - Camera::pos.x;
    deathIconGO->box.y = 360 - Camera::pos.y;
    deathScoreGO->box.x = 150 - Camera::pos.x;
    deathScoreGO->box.y = 380 - Camera::pos.y;
    attackIconGO->box.x = 60 - Camera::pos.x;
    attackIconGO->box.y = 430 - Camera::pos.y;
    attackScoreGO->box.x = 150 - Camera::pos.x;
    attackScoreGO->box.y = 450 - Camera::pos.y;
    music->Play(1);
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
    objectArray.emplace_back(damageScoreGO);
    objectArray.emplace_back(deathScoreGO);
    objectArray.emplace_back(timeScoreGO);
    objectArray.emplace_back(attackScoreGO);
    objectArray.emplace_back(collectableScoreGO);
    objectArray.emplace_back(resultScore);
    objectArray.emplace_back(rankGO);
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
        continueTextTimer.Update(dt);
        if(heartIconTimer.Get() >= HEART_ICON_TIME){
            heartIconSprite->isBlinking = false;
            damageScoreText->isBlink = false;
            if(!playedHeartIconSound){
                popSound->Play(1);
                playedHeartIconSound = true;
            }
        }
        if(deathIconTimer.Get() >= DEATH_ICON_TIME){
            deathIconSprite->isBlinking = false;
            deathScoreText->isBlink = false;
            if(!playedDeathIconSound){
                popSound->Play(1);
                playedDeathIconSound = true;
            }
        }
        if(timeIconTimer.Get() >= TIME_ICON_TIME){
            timeIconSprite->isBlinking = false;
            timeScoreText->isBlink = false;
            if(!playedTimeIconSound){
                popSound->Play(1);
                playedTimeIconSound = true;
            }
        }
        if(attackIconTimer.Get() >= ATTACK_ICON_TIME){
            attackIconSprite->isBlinking = false;
            attackScoreText->isBlink = false;
            if(!playedAttackIconSound){
                popSound->Play(1);
                playedAttackIconSound = true;
            }
        }
        if(collectableIconTimer.Get() >= COLLECTABLE_ICON_TIME){
            collectableIconSprite->isBlinking = false;
            collectableScoreText->isBlink = false;
            if(!playedCollectableIconSound){
                popSound->Play(1);
                playedCollectableIconSound = true;
            }
        }
        if(yourRankIsTimer.Get() >= YOUR_RANK_IS_TIME) {
            yourRankIsLayerSprite->isBlinking = false;
            rankSprite->isBlinking = false;
            if(!playedYourRankIsSound) {
                popSound->Play(1);
                playedYourRankIsSound = true;
            }
        }
        if(resultTimer.Get() >= RESULT_TIME) {
            resultSprite->isBlinking = false;
            resultScoreText->isBlink = false;
            if(!playedResultSound) {
                popSound->Play(1);
                playedResultSound = true;
            }
        }
    }
    switchMusicTimer.Update(dt);
    if(switchMusicTimer.Get() >= SWITCH_MUSIC_TIME) {
        if(!switchedMusic) {
            music->Open(VICTORY_BG_MUSIC_2);
            music->Play(-1);
            switchedMusic = true;
        }
    }
    if(continueTextTimer.Get() >= CONTINUE_TEXT_TIME) {
        if(!putedContinueText) {
            GameObject *continueTextGO = new GameObject();
            Text* continueText = new Text(*continueTextGO, "assets/font/editundo.ttf", 40, Text::SOLID, "Press Enter to continue", SDL_Color {255,255,255}, 0);
            continueTextGO->box.x = 500 - Camera::pos.x;
            continueTextGO->box.y = 500 - Camera::pos.y;
            continueTextGO->box.z = 1;
            putedContinueText = true;
            objectArray.emplace_back(continueTextGO);
        }
        putedContinueText = true;
        if(InputManager::GetInstance().KeyPress(SDLK_RETURN)){
            popRequested = true;
            music->Stop(0);
            LevelData::GetInstance().clear();
            Camera::pos.x = 0;
            Camera::pos.y = 0;
        }
    }
}

void VictoryState::Pause() {}

void VictoryState::Resume() {}

void VictoryState::StartData() {}