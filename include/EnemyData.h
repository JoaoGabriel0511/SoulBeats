#ifndef ENEMY_DATA_H
#define ENEMY_DATA_H
#include "Vect2.h"

class EnemyData
{
private:
    Vect2 enemyPos;
public:
    bool isDead;
    bool wasKilled;
    bool harpMoveX;
    bool harpMoveY;
    enum EnemyType {
        BELL,
        HARP,
        ACCORDION
    };
    EnemyType type;
    Vect2 GetEnemyPos() { return enemyPos;}
    EnemyData(bool isDead, Vect2 enemyPos, EnemyType type, bool harpMoveX, bool harpMoveY) {
        this->isDead = isDead;
        this->type = type;
        this->enemyPos = enemyPos;
        this->harpMoveX = harpMoveX;
        this->harpMoveY = harpMoveY;
    }
};


#endif