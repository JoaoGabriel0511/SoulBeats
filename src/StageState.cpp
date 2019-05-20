#include "../include/StageState.h"
#include <iostream>
#include "unistd.h"
#define PI 3.149
using namespace std;
StageState::StageState() {
    quitRequested = false;
	started = false;
	popRequested = false;
}

void StageState::Resume() {}
void StageState::Pause() {
	((Music*) bg->GetComponent("Music").get())->Stop(0);
}

void StageState::Start() {
	cout <<"Carregando assets do Stagestate..."<< endl;
	LoadAssets();
	cout << "Assets do Stagestate carregados" << endl;
	StartArray();
	started = true;
	cout << "Preparando para tocar a musica do Stagestate..."<<endl;
    ((Music*) bg->GetComponent("Music").get())->Play(-1);
	cout << "Musica do Stagestate tocando" << endl;
}

void StageState::Update(float dt) {
	Camera::Update(dt);
	EndState *endState;
	Debugger debugger = Debugger::GetInstance();
	if(debugger.lookUpdateStageState) {
		cout<<"   inicio do Update do StageState"<<endl;
		cout<<"   >>antes de pegar a instance do inputManager"<<endl;
	}
	InputManager inputManager = InputManager::GetInstance();
	if(debugger.lookUpdateStageState) {
		cout<<"   >>depois de pegar a instance do inputManager"<<endl;
	}
	if(inputManager.QuitRequested()){
		if(debugger.lookUpdateStageState) {
			cout<<"   Leu input de saida"<<endl;
		}
		quitRequested = true;
	} else {
		if(inputManager.KeyPress(ESCAPE_KEY)) {
			popRequested = true;
			((Music*) bg->GetComponent("Music").get())->Stop(0);
		}
	}
	for(int j = 0; j < objectArray.size(); j++) {
		if(debugger.lookUpdateStageState) {
			cout<<"isDEad StageState Update "<<j<<" "<<objectArray[j]->IsDead()<<endl;
		}
		if(objectArray[j]->IsDead() == true) {
			objectArray.erase(objectArray.begin() + j);
			if(debugger.lookUpdateStageState) {
				cout<<"depois do erase"<<endl;
			}
		}
		if(PenguinBody::player == NULL) {
			GameData::playerVictory = false;
			PopRequested();
			((Music*) bg->GetComponent("Music").get())->Stop(0);
			endState = new EndState();
			Game::GetInstance().Push(endState);
		} else {
			if(Alien::alienCount == 0) {
				GameData::playerVictory = true;
				PopRequested();
				((Music*) bg->GetComponent("Music").get())->Stop(0);
				endState = new EndState();
				Game::GetInstance().Push(endState);
			}
		}
	}
	if(debugger.lookUpdateStageState) {
		cout<<"   Inicio dos updates no object array"<<endl;
	}
    UpdateArray(dt);
	for(int i = objectArray.size() - 1; i >= 0 ; i--) {
		if(objectArray[i]->GetComponent("Collider") != NULL) {
			for(int j = i-1; j >= 0 ; j--) {
				if(objectArray[j]->GetComponent("Collider") != NULL) {
					if(Collision::IsColliding(objectArray[i]->box, objectArray[j]->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg) == true) {
						objectArray[i]->NotifyCollision(*objectArray[j].get());
						objectArray[j]->NotifyCollision(*objectArray[i].get());
					}
				}
			}
		}
    }
	if(debugger.lookUpdateStageState) {
		cout<<"   Fim do Update do StageState"<<endl;
	}
}

void StageState::Render() {
	for(int j = 0; j < 3; j++) {
		for(int i = 0; i < objectArray.size(); i++) {
			if(objectArray[i]->box.z == j) {
				objectArray[i]->Render();
			}
			if(j == 0 && objectArray[i]->GetComponent("TileMap") != NULL) {
				((TileMap*) objectArray[i]->GetComponent("TileMap").get())->RenderLayer(0,Camera::pos.x,Camera::pos.y);
			}
			if(j == 2 && objectArray[i]->GetComponent("TileMap") != NULL) {
				((TileMap*) objectArray[i]->GetComponent("TileMap").get())->RenderLayer(1,Camera::pos.x,Camera::pos.y);
			}
		}
	}
}

void StageState::LoadAssets(){
    Sprite *sprite;
	CameraFollower *cameraFollower;
	TileSet *tileSet;
	TileMap *tileMap;
	GameObject *tileGO;
	GameObject *alien1GO;
	GameObject *alien2GO;
	GameObject *alien3GO;
	GameObject *penguinGO;
	Alien *alien1;
	Alien *alien2;
	Alien *alien3;
    Music *music;
	PenguinBody *penguinBody;
	penguinGO = new GameObject();
	cout<<"		->GameObject do penguin criado"<<endl;
	penguinBody = new PenguinBody(*penguinGO);
	cout<<"		->Penguin criado"<<endl;
	penguinGO->AddComponent(shared_ptr<Component> (penguinBody));
	penguinGO->box.x = 704;
	penguinGO->box.y = 640;
	penguinGO->box.z = 1;
	Camera::Follow(penguinGO);
	cout<<"		->Camera seguindo o penguin"<<endl;
	alien1GO = new GameObject();
	alien2GO = new GameObject();
	alien3GO = new GameObject();
	cout<<"		->GameObjects dos aliens criados"<<endl;
	alien1GO->box.x = 533;
	alien1GO->box.y = 300;
	alien1GO->box.z = 1;
	alien2GO->box.x = 708;
	alien2GO->box.y = 106;
	alien2GO->box.z = 1;
	alien3GO->box.x = 201;
	alien3GO->box.y = 539;
	alien3GO->box.z = 1;
	alien1 = new Alien(*alien1GO, 3, penguinGO, 0);
	alien2 = new Alien(*alien2GO, 3, penguinGO, 5);
	alien3 = new Alien(*alien3GO, 3, penguinGO, 10);
	cout<<"		->Aliens criados"<<endl;
	alien1GO->AddComponent(shared_ptr<Component> (alien1));
	alien2GO->AddComponent(shared_ptr<Component> (alien2));
	alien3GO->AddComponent(shared_ptr<Component> (alien3));
	tileSet = new TileSet(64, 64, "assets/img/tileset.png");
	cout<<"		->TileSet criado"<<endl;
	tileMap = new TileMap(*tileGO, "assets/map/tileMap.txt", tileSet);
	cout<<"		->TileMap criado"<<endl;
    bg = new GameObject();
	cout<<"		->Game Object bg criado"<<endl;
	tileGO = new GameObject();
	tileGO->box.z = 0;
	cout<<"		->Game Object tileGO criado"<<endl;
	tileGO->AddComponent(shared_ptr<Component> (tileMap));
	cout<<"		->TileMap adicionado como componet de tileGO"<<endl;
    sprite = new Sprite(*bg, "assets/img/ocean.jpg");
	cameraFollower = new CameraFollower(*bg);
	cout<<"		->Sprite do backgroud criado"<<endl;
	bg->box.h = sprite->GetHeight();
	bg->box.w = sprite->GetWidth();
    music = new Music(*bg, "assets/audio/stageState.ogg");
	cout<<"		->Musica de fundo criada"<<endl;
    bg->AddComponent(shared_ptr<Component> (sprite));
	bg->AddComponent(shared_ptr<Component> (cameraFollower));
	cout<<"		->Sprite do background adicionado ao component bg"<<endl;
    bg->AddComponent(shared_ptr<Component> (music));
	cout<<"		->Musica de fundo adicionada ao component bg"<<endl;
	AddObject(bg);
	cout<<"		->Game Object bg adicionado ao array de Game Objects"<<endl;
	AddObject(tileGO);
	cout<<"		->Game Object tileGO adicionado ao array de Game Objects"<<endl;
	AddObject(alien1GO);
	AddObject(alien2GO);
	AddObject(alien3GO);
	cout<<"		->Game Objects alien1GO alien2GO alien3GO adicionados ao array de Game Objects"<<endl;
	AddObject(penguinGO);
	cout<<"		->Game Object penguinGO adicionado ao array de Game Objects"<<endl;
}

StageState::~StageState() {
    objectArray.clear();
}