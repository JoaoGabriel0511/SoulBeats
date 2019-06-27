#include "../include/LevelState.h"

LevelState::LevelState() : State()
{
    Start();
}

void LevelState::Start() {
    State::Start();
    levelCompleted = false;
    switchedBegininMusic = false;
    switchedDevelopmentMusic = false;
    beforeFinishLevelTimer.Restart();
}

void LevelState::LoadAssets() {
    //Adicionando Background

    CameraFollower *cameraFollower;
    bg = new GameObject();
    GameObject *bellEnemyGO;
    BellEnemy *bellEnemy;
    GameObject *harpEnemyGO;
    HarpEnemy *harpEnemy;
    GameObject *accordionEnemyGO;
    AccordionEnemy *accordionEnemy;
    Sprite *levelSprite;
    Music *levelMusic;
    cameraFollower = new CameraFollower(*bg);
    levelSprite = new Sprite(*bg, "assets/img/background/Fundo.png");
    levelMusic = new Music(*bg, BEGINING_MUSIC);
    levelMusic->Play(-1);
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
    GameObject* heartBackground = new GameObject();
    new Sprite(*heartBackground, BEATING_HEART_BG, 1, 1);
    heartBackground->box.x = 901;
    heartBackground->box.y = 31;
    heartBackground->box.z = 5;
    objectArray.emplace_back(heartBackground);
    beat = new GameObject();
    beat->box.x = 900;
    beat->box.y = 30;
    beat->box.z = 6;
    Beat* beat_component = new Beat(*beat, heartBackground);
    global_beat = beat_component;
    objectArray.emplace_back(beat);

    //Adicionando Personagem

    GameObject *characterGO;
    characterGO = new GameObject();
    characterGO->box.x = 150;
    characterGO->box.y = 3100;
    characterGO->box.z = 4;
    new Character(*characterGO);
    Camera::Follow(characterGO);
    objectArray.emplace_back(characterGO);

    //Personagem Adicionado

    //Adicionando Inimigo ( BellEnemy )

    bellEnemyGO = new GameObject();
    bellEnemy = new BellEnemy(*bellEnemyGO, 10, 10, characterGO);
    bellEnemyGO->box.x = 1700;
    bellEnemyGO->box.y = 2630;
    bellEnemyGO->box.z = 4;
    objectArray.emplace_back(bellEnemyGO);

    //Adicionando Inimigo ( HarpEnemy )

    harpEnemyGO = new GameObject();
    harpEnemy = new HarpEnemy(*harpEnemyGO, 10, 10, characterGO);
    harpEnemyGO->box.x = 2300;
    harpEnemyGO->box.y = 2590;
    harpEnemyGO->box.z = 4;
    objectArray.emplace_back(harpEnemyGO);

    //Adicionando Inimigo ( AccordionEnemy )

    accordionEnemyGO = new GameObject();
    accordionEnemy = new AccordionEnemy(*accordionEnemyGO, 10, 10, characterGO);
    accordionEnemyGO->box.x = 2500;
    accordionEnemyGO->box.y = 2990;
    accordionEnemyGO->box.z = 4;
    objectArray.emplace_back(accordionEnemyGO);

    //Inimigo Adicionado

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

    //Adicionando TileMap Decoracao ForeGround

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

void LevelState::UpdateMusic(float dt) {
    beginingMusicTimer.Update(dt);
    if(beginingMusicTimer.Get() >= BEGINING_MUSIC_TIME){
        if(!switchedBegininMusic) {
            switchedBegininMusic = true;
            ((Music*) bg->GetComponent("Music").get())->Open(DEVELOPMENT_MUSIC);
            ((Music*) bg->GetComponent("Music").get())->Play(-1);
        }
        developmentMusicTimer.Update(dt);
        if(developmentMusicTimer.Get() >= DEVELOPMENT_MUSIC_TIME) {
            if(!switchedDevelopmentMusic) {
                switchedDevelopmentMusic = true;
                ((Music*) bg->GetComponent("Music").get())->Open(MAIN_MUSIC);
                ((Music*) bg->GetComponent("Music").get())->Play(-1);
            }
            mainMusicTimer.Update(dt);
            if(mainMusicTimer.Get() >= MAIN_MUSIC_TIME) {
                ((Music*) bg->GetComponent("Music").get())->Stop(0);
                musicStopTimer.Update(dt);
                if(musicStopTimer.Get() >= STOP_MUSIC_TIME) {
                    ((Music*) bg->GetComponent("Music").get())->Open(BEGINING_MUSIC);
                    ((Music*) bg->GetComponent("Music").get())->Play(-1);
                    mainMusicTimer.Restart();
                    developmentMusicTimer.Restart();
                    beginingMusicTimer.Restart();
                    musicStopTimer.Restart();
                    switchedBegininMusic = false;
                    switchedDevelopmentMusic = false;
                }
            }
        }
    }
}

void LevelState::Update(float dt) {
    VictoryState *victoryState;
    TileMapCollider *tileMapForeCollider = ((TileMapCollider*) tileTerrForeGO->GetComponent("TileMapCollider").get());
    TileMapCollider *tileMapBackCollider = ((TileMapCollider*) tileTerrBackGO->GetComponent("TileMapCollider").get());
    if(!levelCompleted) {
        State::Update(dt);
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
        UpdateMusic(dt);
    } else {
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
}

GameObject *LevelState::GetBeatObject()
{
    return this->beat;
}