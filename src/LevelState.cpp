#include "../include/LevelState.h"

LevelState::LevelState() : State() {
    Start();
}

void LevelState::LoadAssets() {
    //Adicionando Background

    bg = new GameObject();
    GameObject* bellEnemyGO;
    BellEnemy* bellEnemy;
    Sprite *levelSprite;
    levelSprite = new Sprite(*bg, "assets/img/background/Sprite-0001.png");
    bg->box.h = Game::GetInstance().GetHeight();
    bg->box.w = Game::GetInstance().GetWidth();
    objectArray.emplace_back(bg);

    //Background Adicionado

    //Adicionando Personagem

    GameObject * characterGO;
    characterGO = new GameObject();
    characterGO->box.x = 200;
    characterGO->box.y = 383;
    characterGO->box.z = 1;
    new Character(*characterGO);
    objectArray.emplace_back(characterGO);

    //Personagem Adicionado

    //Adicionando Inimigo

    bellEnemyGO = new GameObject();
    bellEnemy = new BellEnemy(*bellEnemyGO,10,10,characterGO);
    bellEnemyGO->box.x = 100;
    bellEnemyGO->box.y = 420;
    bellEnemyGO->box.z = 1;
    objectArray.emplace_back(bellEnemyGO);

    //Inimigo Adicionado

    //Adicionando TileMap

    TileSet *tileSet;
    TileMap *tileMap;
    TileMapCollider *tileMapCollider;
    Collider *collider;
    tileGO = new GameObject();
    tileGO->box.z = 0;
    tileSet = new TileSet(64, 64, "assets/img/tileSet/TilesetLight.png");
    tileMap = new TileMap(*tileGO, "assets/map/tileMap.txt", tileSet);
    tileMapCollider = new TileMapCollider(*tileGO, tileMap);
    objectArray.emplace_back(tileGO);

    //TileMap Adicionado
}

void LevelState::Pause() {

}

void LevelState::Resume() {

}

void LevelState::Update(float dt) {
    State::Update(dt);
    TileMapCollider *tileMapCollider = ((TileMapCollider*) tileGO->GetComponent("TileMapCollider").get());
    for(int i = tileMapCollider->boxes.size() - 1; i >= 0; i--) {
        for(int j = objectArray.size()-1; j >= 0 ; j--) {
            if(objectArray[j]->GetComponent("Collider") != NULL) {
                if(Collision::IsColliding(((Collider*) objectArray[i]->GetComponent("Collider").get())->box, tileMapCollider->boxes[i], objectArray[i]->angleDeg, 0) == true) {
                    objectArray[i]->NotifyCollision(*tileGO);
                    tileGO->NotifyCollision(*objectArray[i].get());
                }
            }
		}
    }
    if(InputManager::GetInstance().QuitRequested()){
        quitRequested = true;
    }
}