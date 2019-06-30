#ifndef LEVEL_DATA
#define LEVEL_DATA
#include "Vect2.h"
#include "CheckPointData.h"
#include "EnemyData.h"
#include <vector>
using namespace std;

class LevelData {
    public:
        bool isNewLevel;
        vector<CheckPointData*> checkPointData;
        vector<EnemyData*> enemyData;
        void clear();
        Vect2 *pos;
        LevelData();
        ~LevelData();
        void Start();
        void Reset();
        static LevelData& GetInstance();

};


#endif