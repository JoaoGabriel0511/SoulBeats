#include "../include/LevelData.h"

LevelData::LevelData() {
    isNewLevel = true;
    switchedDevelopmentMusic = false;
    switchedBegininMusic = false;
    musicState = BEGINING;
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
    for(int i = 0; i < enemyData.size(); i++) {
        enemyData[i]->wasKilled = enemyData[i]->isDead;
    }
}

void LevelData::Reset() {
    checkPointData.clear();
    enemyData.clear();
}

