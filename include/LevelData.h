#ifndef LEVEL_DATA
#define LEVEL_DATA
#include "Vect2.h"
#include "CheckPointData.h"
#include "EnemyData.h"
#include "LauncherData.h"
#include "JumpPadData.h"
#include "CollectableData.h"
#include "MovingPlatformsData.h"
#include <vector>
using namespace std;

class LevelData {
    public:
        bool isNewLevel;
        bool switchedBegininMusic;
        bool switchedDevelopmentMusic;
        enum MusicState {
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
        void clear();
        Vect2 *pos;
        LevelData();
        ~LevelData();
        void Start();
        void Reset();
        static LevelData& GetInstance();

};


#endif