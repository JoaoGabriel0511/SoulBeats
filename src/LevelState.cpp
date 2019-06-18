#include "../include/LevelState.h"

LevelState::LevelState() : State() {
    Start();
}

void LevelState::LoadAssets() {
    //Adicionando Background
    CameraFollower *cameraFollower;
    bg = new GameObject();
    GameObject* bellEnemyGO;
    BellEnemy* bellEnemy;
    Sprite *levelSprite;
    cameraFollower = new CameraFollower(*bg);
    levelSprite = new Sprite(*bg, "assets/img/background/Sprite-0001.png");
    bg->box.h = Game::GetInstance().GetHeight();
    bg->box.w = Game::GetInstance().GetWidth();
    objectArray.emplace_back(bg);
    //// Beat Game Object
    beat = new GameObject();
    beat->box.x = 900;
    beat->box.y = 30;
    beat->box.z = 5;
    Beat* beat_component = new Beat(*beat);
    // new CameraFollower(*beat);
    global_beat = beat_component;
    objectArray.emplace_back(beat);

    //Adicionando Personagem

    GameObject * characterGO;
    characterGO = new GameObject();
    characterGO->box.x = 200;
    characterGO->box.y = 383;
    characterGO->box.z = 4;
    new Character(*characterGO);
    Camera::Follow(characterGO);
    objectArray.emplace_back(characterGO);

    //Personagem Adicionado

    //Adicionando Inimigo

    bellEnemyGO = new GameObject();
    bellEnemy = new BellEnemy(*bellEnemyGO,10,10,characterGO);
    bellEnemyGO->box.x = 600;
    bellEnemyGO->box.y = 420;
    bellEnemyGO->box.z = 4;
    objectArray.emplace_back(bellEnemyGO);

    //Inimigo Adicionado

    //Adicionando TileMap Terreno ForeGround

    TileSet *tileSet;
    TileMap *tileMapTerrFore;
    TileMapCollider *tileMapTerrForeCollider;
    tileTerrForeGO = new GameObject();
    tileTerrForeGO->box.z = 3;
    tileSet = new TileSet(32, 32, "assets/img/tileSet/TilesetTerrain.png");
    tileMapTerrFore = new TileMap(*tileTerrForeGO, "assets/map/MAPA TESTE._Terreno Foreground.txt", tileSet);
    tileMapTerrForeCollider = new TileMapCollider(*tileTerrForeGO, tileMapTerrFore);
    objectArray.emplace_back(tileTerrForeGO);

    //TileMap Terreno ForeGround Adicionado

    //Adicionando TileMap Decoracao ForeGround

    TileMap *tileMapDecoFore;
    GameObject *tileDecoForeGO = new GameObject();
    tileDecoForeGO->box.z = 4;
    tileMapDecoFore = new TileMap(*tileDecoForeGO, "assets/map/MAPA TESTE._Decoração Foreground.txt", tileSet);
    objectArray.emplace_back(tileDecoForeGO);

    //TileMap Decoracao ForeGround Adicionada

    //Adicionando TileMap Decoracao BackGround

    TileMap *tileMapDecoBack;
    GameObject *tileDecoBackGO = new GameObject();
    tileDecoBackGO->box.z = 4;
    tileMapDecoBack = new TileMap(*tileDecoBackGO, "assets/map/MAPA TESTE._Decoração Background.txt", tileSet);
    objectArray.emplace_back(tileDecoBackGO);

    //TileMap Decoracao BackGround Adicionada

    //Adicionando TileMap Terreno BackGround

    TileMap *tileMapTerrBack;
    tileTerrBackGO = new GameObject();
    tileTerrBackGO->box.z = 2;
    tileMapTerrBack = new TileMap(*tileTerrBackGO, "assets/map/MAPA TESTE._Terreno Background.txt", tileSet);
    TileMapCollider *tileMapTerrBackCollider = new TileMapCollider(*tileTerrBackGO, tileMapTerrBack);
    objectArray.emplace_back(tileTerrBackGO);

    //TileMap Decoracao Terreno Adicionada

    //Adicionando TileMap Decoracao BackGround

    TileMap *tileMapTerrBacker;
    GameObject *tileTerrBackerGO = new GameObject();
    tileTerrBackerGO->box.z = 1;
    tileMapTerrBacker = new TileMap(*tileTerrBackerGO, "assets/map/MAPA TESTE._Terreno Backgrounder.txt", tileSet);
    objectArray.emplace_back(tileTerrBackerGO);
    
    //TileMap Decoracao BackGround Adicionada

}

void LevelState::Pause() {

}

void LevelState::Resume() {

}

void LevelState::Update(float dt) {
    TileMapCollider *tileMapForeCollider = ((TileMapCollider*) tileTerrForeGO->GetComponent("TileMapCollider").get());
    TileMapCollider *tileMapBackCollider = ((TileMapCollider*) tileTerrBackGO->GetComponent("TileMapCollider").get());
    State::Update(dt);
    for(int i = tileMapForeCollider->boxes.size() - 1; i >= 0; i--) {
        for(int j = objectArray.size()-1; j >= 0 ; j--) {
            if(objectArray[j]->GetComponent("Collider") != NULL) {
                if(Collision::IsColliding(((Collider*) objectArray[j]->GetComponent("Collider").get())->box, tileMapForeCollider->boxes[i], objectArray[j]->angleDeg, 0) == true) {
                    objectArray[j]->NotifyCollisionWithMap(tileMapForeCollider->boxes[i]);
                }
            }
		}
    }
    for(int i = tileMapBackCollider->boxes.size() - 1; i >= 0; i--) {
        for(int j = objectArray.size()-1; j >= 0 ; j--) {
            if(objectArray[j]->GetComponent("Collider") != NULL) {
                if(Collision::IsColliding(((Collider*) objectArray[j]->GetComponent("Collider").get())->box, tileMapBackCollider->boxes[i], objectArray[j]->angleDeg, 0) == true) {
                    objectArray[j]->NotifyCollisionWithMap(tileMapBackCollider->boxes[i]);
                }
            }
		}
    }
    if(InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
}

GameObject* LevelState::GetBeatObject(){
    return this->beat;
}