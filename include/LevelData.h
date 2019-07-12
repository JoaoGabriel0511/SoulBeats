#ifndef LEVEL_DATA
#define LEVEL_DATA
#include "Vect2.h"
#include "CheckPointData.h"
#include "EnemyData.h"
#include "LauncherData.h"
#include "JumpPadData.h"
#include "CollectableData.h"
#include "MovingPlatformsData.h"
#include "HeartData.h"
#include <vector>
using namespace std;

class LevelData {
    public:
        bool isNewLevel;
        bool switchedBegininMusic;
        bool switchedDevelopmentMusic;
        enum MusicState {
            INTRO,
            MAIN,
            DEVELOPMENT,
            BEGINING
        };
        MusicState musicState;
        vector<CheckPointData*> checkPointData;
        vector<EnemyData*> enemyData;
        vector<LauncherData*> launcherData;
        vector<JumpPadData*> jumpPadData;
        vector<CollectableData*> collectableData;
        vector<MovingPlatformsData*> movingPlatformsData;
        vector<HeartData*> heartData;
        int collectablesCollected;
        int deathCount;
        int damageCount;
        int enemyPoints;
        int savedEnemyPoints;
        int time;
        void clear();
        Vect2 *pos;
        LevelData();
        ~LevelData();
        void Start();
        void Reset();
        static LevelData& GetInstance();

};


#endif