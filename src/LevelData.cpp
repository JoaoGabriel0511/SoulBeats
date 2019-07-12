#include "../include/LevelData.h"

LevelData::LevelData() {
    isNewLevel = true;
    switchedDevelopmentMusic = false;
    switchedBegininMusic = false;
    musicState = BEGINING;
    deathCount = 0;
    damageCount = 0;
}

LevelData::~LevelData() {}

LevelData& LevelData::GetInstance() {
    static  LevelData LevelData;
    return LevelData;
}

void LevelData::clear() {
    // pos = NULL;
}

void LevelData::Start() {
    collectablesCollected = 0;
    for(int i = 0; i < enemyData.size(); i++) {
        enemyData[i]->wasKilled = enemyData[i]->isDead;
    }
    for(int i = 0; i < collectableData.size(); i++) {
        collectableData[i]->wasCollected = collectableData[i]->isCollected;
        if(collectableData[i]->isCollected) {
            collectablesCollected++;
        }
    }
    for (int i = 0; i < heartData.size(); i++) {
        heartData[i]->wasCollected = heartData[i]->isCollected;
    }
}

void LevelData::Reset() {
    checkPointData.clear();
    enemyData.clear();
}

