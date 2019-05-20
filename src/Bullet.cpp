#include "../include/Bullet.h"

Bullet::Bullet(GameObject& associated, Vect2 direction, float speed, int damage, float maxDistance, string sprite, int frameCount) : Component(associated) {
    Sprite * bulletSprite;
    const float PI = 3.14159265;
    double angleDeg;
    Debugger * debugger;
    if(sprite == "assets/img/penguinbullet.png") {
        targetsPlayer = false;
    } else {
        targetsPlayer = true;
    }
    *debugger = Debugger::GetInstance();
    Collider *collider;
    if(debugger->lookUpdateBullet) {
        cout<<"Criando um novo bullet na Pos x "<<associated.box.x<<" y "<<associated.box.y<<endl;
        cout<<"Direcao do bullet x "<<direction.x<<" y "<<direction.y<<endl;
    }
    this->start.x = associated.box.x;
    this->start.y = associated.box.y;
    this->speed = speed;
    this->direction = direction;
    distance = maxDistance;
    this->damage = damage;
    bulletSprite = new Sprite(associated, sprite, frameCount, 0.1);
    collider = new Collider(associated);
    associated.AddComponent(shared_ptr<Component> (bulletSprite));
    associated.AddComponent(shared_ptr<Component> (collider));
    angleDeg = acos(direction.x) * 180.0 / PI;
    if(direction.y < 0){
        angleDeg = angleDeg * -1;
    }
    if(debugger->lookUpdateBullet){
        cout<<"angulo "<<angleDeg<<endl;
    }
    associated.angleDeg = angleDeg;
    if(debugger->lookUpdateBullet){
        cout<<"Criou o novo bullet"<<endl;
    }
}

void Bullet::Update(float dt) {
    Debugger * debugger;
    *debugger = Debugger::GetInstance();
    Vect2 goPos;
    goPos.x = associated.box.x;
    goPos.y = associated.box.y;
    if(start.DistanceTo(goPos) > distance) {
        associated.RequestedDelete();
    }
    if(debugger->lookUpdateBullet) {
        cout<<"Inicio do update de bullet"<<endl;
        cout<<"Direcao do bullet x "<<direction.x<<" y "<<direction.y<<endl;
        cout<<"Pos da bullet x "<<associated.box.x<<" y "<<associated.box.y<<endl;
    }
    goPos = goPos + (direction * speed);
    associated.box.x = goPos.x;
    associated.box.y = goPos.y;
    if(debugger->lookUpdateBullet){
        cout<<"Fim do update de bullet"<<endl;
    }
}

void Bullet::Render() {

}

int Bullet::GetDamage() {
    return damage;
}

bool Bullet::Is(string type) {
    bool result = false;
    if(type == "Bullet") {
        result = true;
    }
    return result;
}

