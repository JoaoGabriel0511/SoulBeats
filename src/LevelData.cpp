#include "../include/LevelData.h"

LevelData::LevelData() {
    isNewLevel = true;
    switchedDevelopmentMusic = false;
    switchedBegininMusic = false;
    musicState = BEGINING;
    deathCount = 0;
    damageCount = 0;
    enemyPoints = 0;
    savedEnemyPoints = 0;
    collectablesCollected = 0;
    time = 0;
}

LevelData::~LevelData() {}

LevelData& LevelData::GetInstance() {
    static  LevelData LevelData;
    return LevelData;
}

void LevelData::clear() {
    isNewLevel = true;
    switchedDevelopmentMusic = false;
    switchedBegininMusic = false;
    musicState = BEGINING;
    deathCount = 0;
    damageCount = 0;
    enemyPoints = 0;
    savedEnemyPoints = 0;
    time = 0;
    collectablesCollected = 0;
    pos = NULL;
    enemyData.clear();
    collectableData.clear();
    heartData.clear();
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
    enemyPoints = savedEnemyPoints;
}

void LevelData::Reset() {
    checkPointData.clear();
    enemyData.clear();
}

