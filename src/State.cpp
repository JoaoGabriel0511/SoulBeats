#include "../include/State.h"
#include <iostream>
#include "unistd.h"
#define PI 3.149
using namespace std;

State::State() {
    popRequested = false;
	quitRequested = false;
	started = false;
}

State::~State() {
    objectArray.clear();
}

weak_ptr<GameObject> State::AddObject(GameObject * go) {
	weak_ptr<GameObject> weak_GO;
	shared_ptr<GameObject> shared_GO(go);
    objectArray.emplace_back(shared_GO);
	if(started == true) {
		go->Start();
	}
	weak_GO = shared_GO;
	return weak_GO;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
	weak_ptr<GameObject> weak_GO;
	for(int i = objectArray.size() - 1; i >= 0 ; i--) {
        if(objectArray[i].get() == go){
			weak_GO = objectArray[i];
		}
    }
	return weak_GO;
}

void State::Start() {
	started = true;
	StartData();
	LoadAssets();
	StartArray();
}

void State::Pause() {}
void State::Resume() {}

void State::StartData() {}

void State::Update(float dt) {
	if (InputManager::GetInstance().QuitRequested()) {
        quitRequested = true;
    }
	Camera::Update(dt);
	UpdateArray(dt);
}

void State::Render() {
	RenderArray();
}

bool State::QuitRequested() {
    return quitRequested;
}

bool State::PopRequested() {
	return popRequested;
}

void State::LoadAssets() {}

void State::StartArray() {
	for(int i = objectArray.size() - 1; i >= 0 ; i--) {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt) {
	for(int i = objectArray.size() - 1; i >= 0 ; i--) {
        objectArray[i]->Update(dt);
    }
	for(int i = objectArray.size() - 1; i >= 0 ; i--) {
		if(Camera::IsOnCamera(objectArray[i]->box))
        {
			if(objectArray[i]->GetComponent("Collider") != NULL) {
				for(int j = i-1; j >= 0 ; j--) {
					if(Camera::IsOnCamera(objectArray[j]->box))
                	{
						if(objectArray[j]->GetComponent("Collider") != NULL) {
							if(Collision::IsColliding(((Collider*) objectArray[i]->GetComponent("Collider").get())->box, ((Collider*) objectArray[j]->GetComponent("Collider").get())->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg) == true) {
								objectArray[i]->NotifyCollision(*objectArray[j].get());
								objectArray[j]->NotifyCollision(*objectArray[i].get());
							}
						}
					}
				}
			}
		}
    }
	for(int k = 0; k < objectArray.size(); k++) {
		if(objectArray[k]->IsDead() == true) {
			//delete objectArray[k].get();
			objectArray.erase(objectArray.begin() + k);
		}
	}
}

void State::RenderArray() {
	int maxLayer = 0;
	for(int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i]->box.z > maxLayer) {
			maxLayer = objectArray[i]->box.z;
		}
	}
	for(int j = 0; j <= maxLayer; j++) {
		for(int i = 0; i < objectArray.size(); i++) {
			if(objectArray[i]->box.z == j && (Camera::IsOnCamera(objectArray[i]->box) || (objectArray[i]->GetComponent("TileMap") != NULL) || (objectArray[i]->GetComponent("CameraFollower") != NULL))) {
				objectArray[i]->Render();
			}
		}
	}
}