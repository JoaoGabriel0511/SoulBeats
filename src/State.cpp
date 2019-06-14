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
	StartArray();
	LoadAssets();
}

void State::Pause() {}
void State::Resume() {}

void State::Update(float dt) {
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
		if(objectArray[i]->GetComponent("Collider") != NULL) {
			for(int j = i-1; j >= 0 ; j--) {
				if(objectArray[j]->GetComponent("Collider") != NULL) {
					if(Collision::IsColliding(((Collider*) objectArray[i]->GetComponent("Collider").get())->box, ((Collider*) objectArray[j]->GetComponent("Collider").get())->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg) == true) {
						objectArray[i]->NotifyCollision(*objectArray[j].get());
						objectArray[j]->NotifyCollision(*objectArray[i].get());
					}
				}
			}
		}
    }
	for(int k = 0; k < objectArray.size(); k++) {
		if(objectArray[k]->IsDead() == true) {
			objectArray.erase(objectArray.begin() + k);
		}
	}
}

void State::RenderArray() {
	for(int j = 0; j < 3; j++) {
		for(int i = 0; i < objectArray.size(); i++) {
			if(objectArray[i]->box.z == j) {
				objectArray[i]->Render();
			}
		}
	}
}