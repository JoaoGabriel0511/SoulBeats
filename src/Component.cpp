#include "../include/Component.h"
using namespace std;

Component::Component(GameObject &associated) : associated(associated) {
    associated.AddComponent(shared_ptr<Component> (this));
}

void Component::Update(float dt){}
void Component::Render(){}
bool Component::Is(string type){}
Component::~Component(){}
void Component::NotifyCollision(GameObject& other){}
void Component::NotifYCollisionWithMap(Rect box) {}