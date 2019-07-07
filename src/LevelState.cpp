#include "../include/LevelState.h"

LevelState::LevelState() : State(){
}

void LevelState::StartData() {
    if(LevelData::GetInstance().isNewLevel) {
        LevelData::GetInstance().checkPointData.emplace_back(new CheckPointData(false, {3580,2440}));
        LevelData::GetInstance().checkPointData.emplace_back(new CheckPointData(false, {7484,2630}));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {1700,2630}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {4908,2640}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {5187,2900}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {8636,3025}, EnemyData::BELL, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {2750,2610}, EnemyData::HARP, false, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {4285,2486}, EnemyData::HARP, true, false));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {7000,2770}, EnemyData::HARP, false, false));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {4321,3085}, EnemyData::ACCORDION, true, true));
        LevelData::GetInstance().enemyData.emplace_back(new EnemyData(false, {7287,2570}, EnemyData::ACCORDION, true, true));
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
    if(LevelData::GetInstance().musicState == LevelData::BEGINING) {
        levelMusic = new Music(*bg, BEGINING_MUSIC);
	    levelMusic->Play(1);
    } else {
        if(LevelData::GetInstance().musicState == LevelData::DEVELOPMENT) {
            levelMusic = new Music(*bg, DEVELOPMENT_MUSIC);
	        levelMusic->Play(1);
        } else {
            if(LevelData::GetInstance().musicState == LevelData::MAIN) {
                levelMusic == new Music(*bg, MAIN_MUSIC);
                levelMusic->Stop(0);
            }
        }
    }
    beginingMusicTimer.Restart();
    developmentMusicTimer.Restart();
    mainMusicTimer.Update(100);
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
    beat->box.z = 6;
    Beat *beat_component = new Beat(*beat);
    global_beat = beat_component;
    objectArray.emplace_back(beat);

    //Adicionando CheckPoints

    for(int i = 0; i < LevelData::GetInstance().checkPointData.size(); i++) {
        GameObject * checkPointGO;
        checkPointGO = new GameObject();
        checkPointGO->box.x = LevelData::GetInstance().checkPointData[i]->GetCheckPointPos().x;
        checkPointGO->box.y = LevelData::GetInstance().checkPointData[i]->GetCheckPointPos().y;
        checkPointGO->box.z = 4;
        new CheckPoint(*checkPointGO, i);
        objectArray.emplace_back(checkPointGO);
    }

    //CheckPoints Adicionados

    //Adicionando Personagem

    characterGO = new GameObject();
    if(LevelData::GetInstance().pos == NULL) {
        characterGO->box.x = 500;
        characterGO->box.y = 3100;
    } else {
        characterGO->box.x = LevelData::GetInstance().pos->x - 100;
        characterGO->box.y = LevelData::GetInstance().pos->y - 95;
    }
    characterGO->box.z = 4;
    new Character(*characterGO);
    Camera::followX = true;
    Camera::followY = true;
    Camera::Follow(characterGO);

    
    //Personagem Adicionada

    //Adding Jumping Pad
    GameObject* padGO;
    JumpingPad* pad;
    padGO = new GameObject();
    padGO->box.x = 1300;
    padGO->box.y = 2600;
    padGO->box.z = 4;
    pad = new JumpingPad(*padGO, characterGO);
    objectArray.emplace_back(padGO);
    //Adicionando Launcher

    launcherGO = new GameObject();
    launcherGO->box.x = 1450;
    launcherGO->box.y = 2600;
    launcherGO->box.z = 4;
    launcher = new Launcher(*launcherGO, Launcher::DOWN, characterGO);
    objectArray.emplace_back(launcherGO);
    objectArray.emplace_back(characterGO);

    //Launcher Adicionado

    //Adicionando Inimigos

    for(int i = 0; i < LevelData::GetInstance().enemyData.size(); i++) {
        if(LevelData::GetInstance().enemyData[i]->isDead == false) {
            GameObject *enemyGO;
            enemyGO = new GameObject();
            enemyGO->box.x = LevelData::GetInstance().enemyData[i]->GetEnemyPos().x;
            enemyGO->box.y = LevelData::GetInstance().enemyData[i]->GetEnemyPos().y;
            enemyGO->box.z = 4;
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

    collectable1GO = new GameObject();
    collectable1 = new Collectable(*collectable1GO, 10, 10, characterGO);
    collectable1GO->box.x = 1691;
    collectable1GO->box.y = 3036;
    collectable1GO->box.z = 4;
    objectArray.emplace_back(collectable1GO);

    //Adicionando Coletável ( Collectable )

    collectable1GO = new GameObject();
    collectable1 = new Collectable(*collectable1GO, 10, 10, characterGO);
    collectable1GO->box.x = 4149;
    collectable1GO->box.y = 3036;
    collectable1GO->box.z = 4;
    objectArray.emplace_back(collectable1GO);

    //Adicionando TileMap Terreno ForeGround

    TileSet *tileSet;
    TileMap *tileMapTerrFore;
    TileMapCollider *tileMapTerrForeCollider;
    tileTerrForeGO = new GameObject();
    tileTerrForeGO->box.z = 3;
    tileSet = new TileSet(32, 32, "assets/img/tileSet/TilesetTerrain.png");
    tileMapTerrFore = new TileMap(*tileTerrForeGO, "assets/map/MAPA TESTE._Terreno Foreground.txt", tileSet, 2, 0, 0, 1, 1);
    tileMapTerrForeCollider = new TileMapCollider(*tileTerrForeGO, tileMapTerrFore);
    objectArray.emplace_back(tileTerrForeGO);

    //TileMap Terreno ForeGround Adicionado

    //Adicionando TileMap Decoracao ForeGround~

    TileMap *tileMapDecoFore;
    GameObject *tileDecoForeGO = new GameObject();
    tileDecoForeGO->box.z = 4;
    tileMapDecoFore = new TileMap(*tileDecoForeGO, "assets/map/MAPA TESTE._Decoração Foreground.txt", tileSet, 2, 0, 0, 1, 1);
    objectArray.emplace_back(tileDecoForeGO);

    //TileMap Decoracao ForeGround Adicionada

    //Adicionando TileMap Decoracao BackGround

    TileMap *tileMapDecoBack;
    GameObject *tileDecoBackGO = new GameObject();
    tileDecoBackGO->box.z = 4;
    tileMapDecoBack = new TileMap(*tileDecoBackGO, "assets/map/MAPA TESTE._Decoração Background.txt", tileSet, 2, 0, 0, 1, 1);
    objectArray.emplace_back(tileDecoBackGO);

    //TileMap Decoracao BackGround Adicionada

    //Adicionando TileMap Terreno BackGround

    TileMap *tileMapTerrBack;
    tileTerrBackGO = new GameObject();
    tileTerrBackGO->box.z = 2;
    tileMapTerrBack = new TileMap(*tileTerrBackGO, "assets/map/MAPA TESTE._Terreno Background.txt", tileSet, 2, 0, 0, 1, 1);
    TileMapCollider *tileMapTerrBackCollider = new TileMapCollider(*tileTerrBackGO, tileMapTerrBack);
    objectArray.emplace_back(tileTerrBackGO);

    //TileMap Decoracao Terreno Adicionada

    //Adicionando TileMap Decoracao BackGround

    TileMap *tileMapTerrBacker;
    GameObject *tileTerrBackerGO = new GameObject();
    tileTerrBackerGO->box.z = 1;
    tileMapTerrBacker = new TileMap(*tileTerrBackerGO, "assets/map/MAPA TESTE._Terreno Backgrounder.txt", tileSet, 2, 0, 0, 1, 1);
    objectArray.emplace_back(tileTerrBackerGO);

    //TileMap Decoracao BackGround Adicionada

    //Adicionando Goal

    goalGO = new GameObject();
    Goal *goal;
    goal = new Goal(*goalGO);
    goalGO->box.x = 9687;
    goalGO->box.y = 2900;
    // goalGO->box.x = 300;
    // goalGO->box.y = 3000;
    goalGO->box.z = 4;
    objectArray.emplace_back(goalGO);

    //Goal adicionado
}

void LevelState::Pause()
{
}

void LevelState::Resume()
{
}

void LevelState::UpdateMusic(float dt)
{
    switch(LevelData::GetInstance().musicState){
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
        popRequested = true;
        victoryState = new VictoryState();
        bg->RequestedDelete();
        Game::GetInstance().Push(victoryState);
        for(int k = 0; k < objectArray.size(); k++) {
            if(objectArray[k]->IsDead() == true) {
                objectArray.erase(objectArray.begin() + k);
            }
        }
    }
}

void LevelState::UpdateCameraFocus(float dt) {
    if(characterGO->box.x >= 500) {
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