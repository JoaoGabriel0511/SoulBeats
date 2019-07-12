#include "../include/LevelState.h"

LevelState::LevelState() : State(){
}

void LevelState::StartData() {
    if(LevelData::GetInstance().isNewLevel) {
        // Plataformas
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {3200, 2600}, 500, true));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(true, false, {6530 , 2700}, 500, true));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {6900, 2850}, 300, true));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {7500, 2200}, 400, false));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {7650, 2200}, 300, true));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {7800, 2200}, 400, false));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, false, {9500, 1750}, 400, false));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, false, {9800, 1750}, 400, false));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, false, {9990, 1500}, 400, false));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {9800, 1100}, 400, true));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {12100, 2100}, 300, true));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {12420, 2100}, 300, true));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {13550, 2350}, 400, false));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(false, true, {13300, 1800}, 500, true));
        LevelData::GetInstance().movingPlatformsData.emplace_back(new MovingPlatformsData(true, false, {13000, 1800}, 500, false));
        // Plataformas

        // Launchers
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP_RIGHT, {4979,2650}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::LEFT, {5766,2997}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP, {7400,2600}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP_LEFT, {8540,2370}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP, {7194,1710}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP_RIGHT, {7600,1200}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP_RIGHT, {7600,1120}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP_RIGHT, {7600,1040}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP_RIGHT, {8100,1200}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP_RIGHT, {8100,1120}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP_RIGHT, {8100,1040}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::DOWN, {8600,1200}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::DOWN, {8600,1120}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::DOWN, {8600,1040}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP, {11210,1020}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::DOWN, {11050,1225}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::DOWN, {10650,1590}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::DOWN, {10860,1875}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::DOWN, {10600,2170}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::RIGHT, {9500,2420}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP, {12125,2530}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP, {12455,2530}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::RIGHT, {12420,1520}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::LEFT, {12150,1520}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::RIGHT, {11650,1520}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP, {13700,2170}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP, {13200,1558}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::RIGHT, {13680,910}));
        LevelData::GetInstance().launcherData.emplace_back(new LauncherData(Launcher::UP, {11430,2550}));
        // Launchers

        // Jumping
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({2140,3100}));
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({3277,3092}));
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({6270,2840}));
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({6900,3030}));
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({7650,2320}));
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({7300,1436}));
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({13826,2390}));
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({13812,1875}));
        LevelData::GetInstance().jumpPadData.emplace_back(new JumpPadData({14000,1180}));
        // Jumping

        // CheckPoint
        LevelData::GetInstance().checkPointData.emplace_back(new CheckPointData(false, {2875,2440}));
        LevelData::GetInstance().checkPointData.emplace_back(new CheckPointData(false, {7520,2380}));
        LevelData::GetInstance().checkPointData.emplace_back(new CheckPointData(false, {10150,975}));
        LevelData::GetInstance().checkPointData.emplace_back(new CheckPointData(false, {12300,2575}));
        // CheckPoint

        //HEART
        LevelData::GetInstance().heartData.emplace_back(new HeartData(false, {3520,2830}));
        LevelData::GetInstance().heartData.emplace_back(new HeartData(false, {9339,1783}));
        LevelData::GetInstance().heartData.emplace_back(new HeartData(false, {11210,800}));
        LevelData::GetInstance().heartData.emplace_back(new HeartData(false, {11430,2200}));
        LevelData::GetInstance().heartData.emplace_back(new HeartData(false, {11550,1720}));
        LevelData::GetInstance().heartData.emplace_back(new HeartData(false, {11600,1720}));
        LevelData::GetInstance().heartData.emplace_back(new HeartData(false, {11650,1720}));
        //HEART

        //Collectables
        LevelData::GetInstance().collectableData.emplace_back(new CollectableData(false, {1691,3036}));
        LevelData::GetInstance().collectableData.emplace_back(new CollectableData(false, {4149,3036}));
        LevelData::GetInstance().collectableData.emplace_back(new CollectableData(false, {8620,2357}));
        LevelData::GetInstance().collectableData.emplace_back(new CollectableData(false, {8600,1280}));
        LevelData::GetInstance().collectableData.emplace_back(new CollectableData(false, {9700,2440}));
        LevelData::GetInstance().collectableData.emplace_back(new CollectableData(false, {12290,1869}));
        //Collectables

        //BELL ENEMY
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {1700,2630}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {4850,2640}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {2100,2510}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {7620,1800}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {7680,1800}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {8670,1670}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {10200,1740}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {9600,1420}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {10800,1230}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {10918,2580}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {13510,2445}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {13000,1550}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {14630,970}, EnemyData::BELL, true, true));
        //BELL ENEMY

        //ACCORDION ENEMY
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {3100,3080}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {4321,3085}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {7230,2570}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {9600,1810}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {9800,1810}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {10750,1550}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {11656,2505}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {13645,1875}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {12980,1160}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {13240,2505}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {13820,1160}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {15150,850}, EnemyData::ACCORDION, true, true));
        //ACCORDION ENEMY

        //HARP ENEMY
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {2700,2300}, EnemyData::HARP, false, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {3800,2300}, EnemyData::HARP, true, false));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {6750,2770}, EnemyData::HARP, false, false));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {8020,1500}, EnemyData::HARP, false, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {11200,885}, EnemyData::HARP, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {10310,2360}, EnemyData::HARP, true, false));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {12100,2350}, EnemyData::HARP, true, false));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {12830,2170}, EnemyData::HARP, false, false));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {13446,1600}, EnemyData::HARP, true, false));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {13610,800}, EnemyData::HARP, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {15800,600}, EnemyData::HARP, false, true));
        //HARP ENEMY
        LevelData::GetInstance().isNewLevel = false;
    }
    LevelData::GetInstance().Start();
}

void LevelState::Start() {
    State::Start();
    levelCompleted = false;
    beforeFinishLevelTimer.Restart();
}

void LevelState::LoadAssets() {
    //Adicionando Background

    CameraFollower *cameraFollower;
    bg = new GameObject();

    GameObject *launcherGO;
    Launcher *launcher;

    GameObject *collectable1GO;
    Collectable *collectable1;
    GameObject *collectable2GO;
    Collectable *collectable2;

    Sprite *levelSprite;
    Music *levelMusic;
    cameraFollower = new CameraFollower(*bg);
    levelSprite = new Sprite(*bg, "assets/img/background/Fundo.png");
    //global_beat->BeginBeat();
    if(LevelData::GetInstance().musicState == LevelData::INTRO) {
        levelMusic = new Music(*bg, INTRO_MUSIC);
        levelMusic->Play(1);
    } else{
        if(LevelData::GetInstance().musicState == LevelData::BEGINING) {
            levelMusic = new Music(*bg, BEGINING_MUSIC);
            levelMusic->Play(1);
        } else {
            if(LevelData::GetInstance().musicState == LevelData::DEVELOPMENT) {
                levelMusic = new Music(*bg, DEVELOPMENT_MUSIC);
                levelMusic->Play(1);
            } else {
                if(LevelData::GetInstance().musicState == LevelData::MAIN) {
                    levelMusic = new Music(*bg, MAIN_MUSIC);
                    levelMusic->Play(1);
                }
            }
        }
    }
    beginingMusicTimer.Restart();
    developmentMusicTimer.Restart();
    musicStopTimer.Restart();
    bg->box.h = Game::GetInstance().GetHeight();
    bg->box.w = Game::GetInstance().GetWidth();
    objectArray.emplace_back(bg);

    //Adicionando Montanha

    TileSet *tileSetMontain;
    TileMap *tileMapMontain;
    GameObject *montain = new GameObject();
    tileSetMontain = new TileSet(317, 288, "assets/img/background/Montanhas.png");
    tileMapMontain = new TileMap(*montain, "assets/map/MapaMontanha.txt", tileSetMontain, 4, -1024, -850, 0.1, 0.2);
    objectArray.emplace_back(montain);

    //Montanha Adicionada

    //Adicionando Floresta 2

    TileSet *tileSetFlorest2;
    TileMap *tileMapFlorest2;
    GameObject *florest2 = new GameObject();
    tileSetFlorest2 = new TileSet(512, 144, "assets/img/background/Pines2.png");
    tileMapFlorest2 = new TileMap(*florest2, "assets/map/MapaFloresta2.txt", tileSetFlorest2, 2, -1024, -50, 0.5, 0.5);
    objectArray.emplace_back(florest2);

    //Floresta 2 Adicionada

    //Adicionando Holofotes

    GameObject *spotlights = new GameObject();
    new Spotlights(*spotlights);
    objectArray.emplace_back(spotlights);

    //Holofotes adicionados

    //Adicionando Floresta 1.5

    TileSet *tileSetFlorest1_5;
    TileMap *tileMapFlorest1_5;
    GameObject *florest1_5 = new GameObject();
    tileSetFlorest1_5 = new TileSet(512, 144, "assets/img/background/Pines1.5.png");
    tileMapFlorest1_5 = new TileMap(*florest1_5, "assets/map/MapaFloresta1.5.txt", tileSetFlorest1_5, 3, -1024, -30, 0.7, 0.7);
    objectArray.emplace_back(florest1_5);

    //Floresta 1.5 Adicionada


    //Adicionando Floresta 1

    TileSet *tileSetFlorest1;
    TileMap *tileMapFlorest1;
    GameObject *florest1 = new GameObject();
    tileSetFlorest1 = new TileSet(512, 144, "assets/img/background/Pines1.png");
    tileMapFlorest1 = new TileMap(*florest1, "assets/map/MapaFloresta1.txt", tileSetFlorest1, 4, -1024, -250, 1.1, 0.9);
    objectArray.emplace_back(florest1);

    //Floresta 1 Adicionada

    //// Beat Game Object
    beat = new GameObject();
    beat->box.z = 7;
    Beat *beat_component = new Beat(*beat);
    global_beat = beat_component;
    objectArray.emplace_back(beat);

    //Adicionando CheckPoints

    for(int i = 0; i < LevelData::GetInstance().checkPointData.size(); i++) {
        GameObject * checkPointGO;
        checkPointGO = new GameObject();
        checkPointGO->box.x = LevelData::GetInstance().checkPointData[i]->GetCheckPointPos().x;
        checkPointGO->box.y = LevelData::GetInstance().checkPointData[i]->GetCheckPointPos().y;
        checkPointGO->box.z = 5;
        new CheckPoint(*checkPointGO, i);
        objectArray.emplace_back(checkPointGO);
    }

    //CheckPoints Adicionados

    //Adicionando Coracoes
    for (int i = 0; i < LevelData::GetInstance().heartData.size(); i++){
        if(LevelData::GetInstance().heartData[i]->isCollected == false) {
            GameObject* heartGO = new GameObject();
            heartGO->box.x = LevelData::GetInstance().heartData[i]->GetHeartPos().x;
            heartGO->box.y = LevelData::GetInstance().heartData[i]->GetHeartPos().y;
            heartGO->box.z = 5;
            new Heart(*heartGO, i);
            objectArray.emplace_back(heartGO);
        }
    }
    //Coracoes adicionados

    //Adicionando Personagem

    characterGO = new GameObject();
    if(LevelData::GetInstance().pos == NULL) {
        characterGO->box.x = 500;
        characterGO->box.y = 3100;
    } else {
        characterGO->box.x = LevelData::GetInstance().pos->x - 100;
        characterGO->box.y = LevelData::GetInstance().pos->y - 95;
    }
    characterGO->box.z = 5;
    new Character(*characterGO);
    if(Debugger::GetInstance().cameraDebugMode) {
        Camera::debug = true;
    } else {
        Camera::followX = true;
        Camera::followY = true;
        Camera::Follow(characterGO);
    }
    //Personagem Adicionada


    //Jumping Pad Adicionado

    //Adicionando Launcher

    for(int i = 0; i < LevelData::GetInstance().launcherData.size(); i++){
        GameObject *launcherGO;
        launcherGO = new GameObject();
        launcherGO->box.x = LevelData::GetInstance().launcherData[i]->GetLauncherPos().x;
        launcherGO->box.y = LevelData::GetInstance().launcherData[i]->GetLauncherPos().y;
        launcherGO->box.z = 5;
        new Launcher(*launcherGO, LevelData::GetInstance().launcherData[i]->GetLauncherType(), characterGO);
        objectArray.emplace_back(launcherGO);
    }
    objectArray.emplace_back(characterGO);

    //Launcher Adicionado

    //Adding Jumping Pad
    for(int i = 0; i < LevelData::GetInstance().jumpPadData.size(); i++) {
        GameObject* padGO = new GameObject();
        padGO->box.x = LevelData::GetInstance().jumpPadData[i]->GetJumpPadPos().x;
        padGO->box.y = LevelData::GetInstance().jumpPadData[i]->GetJumpPadPos().y;
        padGO->box.z = 5;
        new JumpingPad(*padGO, characterGO);
        objectArray.emplace_back(padGO);
    }

    //Adicionando Inimigos

    for(int i = 0; i < LevelData::GetInstance().enemyData.size(); i++) {
        if(LevelData::GetInstance().enemyData[i]->isDead == false) {
            GameObject *enemyGO;
            enemyGO = new GameObject();
            enemyGO->box.x = LevelData::GetInstance().enemyData[i]->GetEnemyPos().x;
            enemyGO->box.y = LevelData::GetInstance().enemyData[i]->GetEnemyPos().y;
            enemyGO->box.z = 5;
            if(LevelData::GetInstance().enemyData[i]->type == EnemyData::BELL) {
                new BellEnemy(*enemyGO, 10, 10, characterGO, i);
            } else {
                if(LevelData::GetInstance().enemyData[i]->type == EnemyData::HARP) {
                    new HarpEnemy(*enemyGO, 10, 10, characterGO, i, LevelData::GetInstance().enemyData[i]->harpMoveX, LevelData::GetInstance().enemyData[i]->harpMoveY);
                } else {
                    if(LevelData::GetInstance().enemyData[i]->type == EnemyData::ACCORDION){
                        new AccordionEnemy(*enemyGO, 10, 10, characterGO, i);
                    }
                }
            }
            objectArray.emplace_back(enemyGO);
        }
    }

    //Inimigos Adicionandos

    //Adicionando Coletável ( Collectable )
    for(int i = 0; i < LevelData::GetInstance().collectableData.size(); i++){
        if(LevelData::GetInstance().collectableData[i]->isCollected == false) {
            GameObject * collectableGO = new GameObject();
            new Collectable(*collectableGO, 10, 10, characterGO, i);
            collectableGO->box.x = LevelData::GetInstance().collectableData[i]->GetCollectablePos().x;
            collectableGO->box.y = LevelData::GetInstance().collectableData[i]->GetCollectablePos().y;
            collectableGO->box.z = 5;
            objectArray.emplace_back(collectableGO);
        }
    }
    //Coletável ( Collectable ) Adicionado

    //Adicionando plataformas que se movem

    for(int i = 0; i < LevelData::GetInstance().movingPlatformsData.size(); i++) {
        GameObject *movingPlataformsGO = new GameObject();
        new MovingPlatforms(*movingPlataformsGO, LevelData::GetInstance().movingPlatformsData[i]->GetVelocity(),
        LevelData::GetInstance().movingPlatformsData[i]->GetMoveX(), LevelData::GetInstance().movingPlatformsData[i]->GetMoveY(),
        LevelData::GetInstance().movingPlatformsData[i]->GetBack());
        movingPlataformsGO->box.x = LevelData::GetInstance().movingPlatformsData[i]->GetMovingPlatformsPos().x;
        movingPlataformsGO->box.y = LevelData::GetInstance().movingPlatformsData[i]->GetMovingPlatformsPos().y;
        movingPlataformsGO->box.z = 4;
        objectArray.emplace_back(movingPlataformsGO);
    }

    //Plataformas que se movem adicionadas

    //Adicionando TileMap Terreno ForeGround

    TileSet *tileSet;
    TileMap *tileMapTerrFore;
    TileMapCollider *tileMapTerrForeCollider;
    tileTerrForeGO = new GameObject();
    tileTerrForeGO->box.z = 4;
    tileSet = new TileSet(32, 32, "assets/img/tileSet/TilesetTerrain.png");
    tileMapTerrFore = new TileMap(*tileTerrForeGO, "assets/map/MAPA TESTE._Terreno Foreground.txt", tileSet, 2, 0, 0, 1, 1);
    tileMapTerrForeCollider = new TileMapCollider(*tileTerrForeGO, tileMapTerrFore);
    objectArray.emplace_back(tileTerrForeGO);

    //TileMap Terreno ForeGround Adicionado

    //Adicionando TileMap Decoracao ForeGround~

    TileMap *tileMapDecoFore;
    GameObject *tileDecoForeGO = new GameObject();
    tileDecoForeGO->box.z = 6;
    tileMapDecoFore = new TileMap(*tileDecoForeGO, "assets/map/MAPA TESTE._Decoração Foreground.txt", tileSet, 2, 0, 0, 1, 1);
    objectArray.emplace_back(tileDecoForeGO);

    //TileMap Decoracao ForeGround Adicionada

    //Adicionando TileMap Decoracao BackGround

    TileMap *tileMapDecoBack;
    GameObject *tileDecoBackGO = new GameObject();
    tileDecoBackGO->box.z = 2;
    tileMapDecoBack = new TileMap(*tileDecoBackGO, "assets/map/MAPA TESTE._Decoração Background.txt", tileSet, 2, 0, 0, 1, 1);
    objectArray.emplace_back(tileDecoBackGO);

    //TileMap Decoracao BackGround Adicionada

    //Adicionando TileMap Terreno BackGround

    TileMap *tileMapTerrBack;
    tileTerrBackGO = new GameObject();
    tileTerrBackGO->box.z = 3;
    tileMapTerrBack = new TileMap(*tileTerrBackGO, "assets/map/MAPA TESTE._Terreno Background.txt", tileSet, 2, 0, 0, 1, 1);
    TileMapCollider *tileMapTerrBackCollider = new TileMapCollider(*tileTerrBackGO, tileMapTerrBack);
    objectArray.emplace_back(tileTerrBackGO);

    //Adicionando Text

    GameObject *collectablesUIGO = new GameObject();
    collectablesUIGO->box.z = 7;
    collectablesUI = new UIText(*collectablesUIGO, {50,200}, "assets/img/background/results/Icon1.png");
    objectArray.emplace_back(collectablesUIGO);

    GameObject *pointsUIGO = new GameObject();
    pointsUIGO->box.z = 7;
    pointsUI = new UIText(*pointsUIGO, {50,250}, "assets/img/background/results/Icon5.png");
    objectArray.emplace_back(pointsUIGO);

    GameObject *timeUIGO = new GameObject();
    timeUIGO->box.z = 7;
    timeUI = new UIText(*timeUIGO, {50,300}, "assets/img/background/results/Icon3.png");
    objectArray.emplace_back(timeUIGO);

    //TileMap Decoracao Terreno Adicionada

    //Adicionando TileMap Decoracao BackGrounder

    TileMap *tileMapDecoBacker;
    GameObject *tileDecoBackerGO = new GameObject();
    tileDecoBackerGO->box.z = 1;
    tileMapDecoBacker = new TileMap(*tileDecoBackerGO, "assets/map/MAPA TESTE._Decoração Backgrounder.txt", tileSet, 2, 0, 0, 1, 1);
    objectArray.emplace_back(tileDecoBackerGO);

    //TileMap Decoracao BackGrounder adicionda

    //Adicionando TileMap Decoracao BackGround

    TileMap *tileMapTerrBacker;
    GameObject *tileTerrBackerGO = new GameObject();
    tileTerrBackerGO->box.z = 0;
    tileMapTerrBacker = new TileMap(*tileTerrBackerGO, "assets/map/MAPA TESTE._Terreno Backgrounder.txt", tileSet, 2, 0, 0, 1, 1);
    objectArray.emplace_back(tileTerrBackerGO);

    //TileMap Decoracao BackGround Adicionada


    //Adicionando Goal

    goalGO = new GameObject();
    Goal *goal;
    goal = new Goal(*goalGO);
    goalGO->box.x = 16580;
    goalGO->box.y = 550;
    //goalGO->box.x = 300;
    //goalGO->box.y = 3000;
    goalGO->box.z = 5;
    objectArray.emplace_back(goalGO);

    //Goal adicionado

    // Adding ComboSystem 
    GameObject* comboGo;
    comboGo = new GameObject();
    comboGo->box.z = 7;
    comboGo->box.x = 837 - Camera::pos.x;
    comboGo->box.y = 1 - Camera::pos.y;
    comboSystem = new ComboSystem(*comboGo); 
    // sp->SetScale({10, 10});  
    objectArray.emplace_back(comboGo);
    

}

void LevelState::Pause()
{
}

void LevelState::Resume()
{
}

void LevelState::UpdateMusic(float dt)
{
    if(characterGO->box.x >= SWITCH_TO_DEVELOP_MUSIC) {
        LevelData::GetInstance().switchedBegininMusic = true;
    }
    if(characterGO->box.x >= SWITCH_TO_MAIN_MUSIC) {
        LevelData::GetInstance().switchedDevelopmentMusic = true;
    }
    switch(LevelData::GetInstance().musicState){
        case LevelData::INTRO:
            introTimer.Update(dt);
            if(introTimer.Get() >= INTRO_MUSIC_TIME) {
                ((Music *) bg->GetComponent("Music").get())->Open(BEGINING_MUSIC);
                LevelData::GetInstance().musicState = LevelData::BEGINING;
                ((Music *) bg->GetComponent("Music").get())->Play(1);
                global_beat->BeginBeat();
            }
            break;
        case LevelData::BEGINING:
            beginingMusicTimer.Update(dt);
            if(beginingMusicTimer.Get() >= BEGINING_MUSIC_TIME){
                if(LevelData::GetInstance().switchedBegininMusic) {
                    ((Music *) bg->GetComponent("Music").get())->Open(DEVELOPMENT_MUSIC);
                    LevelData::GetInstance().musicState = LevelData::DEVELOPMENT;
                }
                beginingMusicTimer.Restart();
                ((Music *) bg->GetComponent("Music").get())->Play(1);
            }
            break;
        case LevelData::DEVELOPMENT:
            developmentMusicTimer.Update(dt);
            if(developmentMusicTimer.Get() >= DEVELOPMENT_MUSIC_TIME){
                if(LevelData::GetInstance().switchedDevelopmentMusic) {
                    ((Music *) bg->GetComponent("Music").get())->Open(MAIN_MUSIC);
                    LevelData::GetInstance().musicState = LevelData::MAIN;
                }
                developmentMusicTimer.Restart();
                ((Music *) bg->GetComponent("Music").get())->Play(1);
            }
            break;
        case LevelData::MAIN:
            mainMusicTimer.Update(dt);
            if(mainMusicTimer.Get() >= MAIN_MUSIC_TIME) {
	            mainMusicTimer.Restart();
                ((Music *) bg->GetComponent("Music").get())->Play(1);
            }
            break;
        default:
            break;
    }
}

void LevelState::Update(float dt) {
    if(!levelCompleted) {
        LevelCycle(dt);
    } else {
        VictoryCycle(dt);
    }
}

void LevelState::VictoryCycle(float dt) {
    VictoryState *victoryState;
    ((Music*) bg->GetComponent("Music").get())->Stop(0);
    Camera::UnFollow();
    goalGO->Update(dt);
    beforeFinishLevelTimer.Update(dt);
    if(beforeFinishLevelTimer.Get() >= BEFORE_FINISH_LEVEL_TIME ) {
        //popRequested = true;
        victoryState = new VictoryState();
        //bg->RequestedDelete();
        Game::GetInstance().Push(victoryState);
    }
}

void LevelState::UpdateCameraFocus(float dt) {
    if(characterGO->box.x >= 500 && characterGO->box.x <= 16287) {
        Camera::followX = true;
    } else {
        Camera::followX = false;
    }
    if(characterGO->box.y <=  3100) {
        Camera::followY = true;
    } else {
        Camera::followY = false;
    }
}


void LevelState::LevelCycle(float dt) {
    TileMapCollider *tileMapForeCollider = ((TileMapCollider*) tileTerrForeGO->GetComponent("TileMapCollider").get());
    TileMapCollider *tileMapBackCollider = ((TileMapCollider*) tileTerrBackGO->GetComponent("TileMapCollider").get());
    UpdateCameraFocus(dt);
    collectablesUI->UpdateText(std::to_string(LevelData::GetInstance().collectablesCollected));
    pointsUI->UpdateText(std::to_string(LevelData::GetInstance().enemyPoints));
    timeUI->UpdateText(std::to_string(LevelData::GetInstance().time));
    timeTimer.Update(dt);
    if(timeTimer.Get() >= 1) {
        timeTimer.Restart();
        LevelData::GetInstance().time++;
    }
    for (int i = tileMapForeCollider->boxes.size() - 1; i >= 0; i--)
    {
        if(Camera::IsOnCamera(tileMapForeCollider->boxes[i]))
        {
            for (int j = objectArray.size() - 1; j >= 0; j--)
            {
                if(Camera::IsOnCamera(objectArray[j]->box))
                {
                    if (objectArray[j]->GetComponent("Collider") != NULL)
                    {
                        if (Collision::IsColliding(((Collider *)objectArray[j]->GetComponent("Collider").get())->box, tileMapForeCollider->boxes[i], objectArray[j]->angleDeg, 0) == true)
                        {
                            objectArray[j]->NotifyCollisionWithMap(tileMapForeCollider->boxes[i]);
                        }
                    }
                }
            }
        }
    }
    for (int i = tileMapBackCollider->boxes.size() - 1; i >= 0; i--)
    {
        if(Camera::IsOnCamera(tileMapBackCollider->boxes[i]))
        {
            for (int j = objectArray.size() - 1; j >= 0; j--)
            {
                if(Camera::IsOnCamera(objectArray[j]->box))
                {
                    if (objectArray[j]->GetComponent("Collider") != NULL)
                    {
                        if (Collision::IsColliding(((Collider *)objectArray[j]->GetComponent("Collider").get())->box, tileMapBackCollider->boxes[i], objectArray[j]->angleDeg, 0) == true)
                        {
                            objectArray[j]->NotifyCollisionWithMap(tileMapBackCollider->boxes[i]);
                        }
                    }
                }
            }
        }
    }
    State::Update(dt);
    UpdateMusic(dt);
}

GameObject *LevelState::GetBeatObject()
{
    return this->beat;
}