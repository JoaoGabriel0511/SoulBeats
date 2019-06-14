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
    Beat* beat_component = new Beat(*beat);
    // new CameraFollower(*beat);
    global_beat = beat_component;
    objectArray.emplace_back(beat);

    //Adicionando Personagem

    GameObject * characterGO;
    characterGO = new GameObject();
    characterGO->box.x = 200;
    characterGO->box.y = 383;
    characterGO->box.z = 1;
    new Character(*characterGO);
    Camera::Follow(characterGO);
    objectArray.emplace_back(characterGO);

    //Personagem Adicionado

    //Adicionando Inimigo

    bellEnemyGO = new GameObject();
    bellEnemy = new BellEnemy(*bellEnemyGO,10,10,characterGO);
    bellEnemyGO->box.x = 600;
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
    TileMapCollider *tileMapCollider = ((TileMapCollider*) tileGO->GetComponent("TileMapCollider").get());
    State::Update(dt);
    for(int i = tileMapCollider->boxes.size() - 1; i >= 0; i--) {
        for(int j = objectArray.size()-1; j >= 0 ; j--) {
            if(objectArray[j]->GetComponent("Collider") != NULL) {
                if(Collision::IsColliding(((Collider*) objectArray[j]->GetComponent("Collider").get())->box, tileMapCollider->boxes[i], objectArray[j]->angleDeg, 0) == true) {
                    objectArray[j]->NotifyCollisionWithMap(tileMapCollider->boxes[i]);
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