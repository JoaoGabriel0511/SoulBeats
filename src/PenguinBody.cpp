#include "../include/PenguinBody.h"
#define PI 3.14159265

PenguinBody *PenguinBody::player;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    Sprite * penguinSprite;
    Collider *collider;
    hp = 100000;
    angle = 0;
    current_angle = 0;
    acceleration = 0;
    linearSpeed = 0;
    maxAcceleration = 10;
    maxSpeed = 50;
    breaks = false;
    player = this;
    side = FRONT;
    collider = new Collider(associated);
    penguinSprite = new Sprite(associated, "assets/img/penguin.png");
    associated.AddComponent(shared_ptr<Component> (penguinSprite));
    associated.AddComponent(shared_ptr<Component> (collider));
}

PenguinBody::~PenguinBody() {
    player = NULL;
}

void PenguinBody::Start() {
    Game * instance;
    PenguinCannon * penguinCannon;
    pcannon = new GameObject();
    pcannon->box.z = 1;
    instance = &Game::GetInstance();
    penguinCannon = new PenguinCannon(*pcannon, &associated);
    pcannon->AddComponent(shared_ptr<Component> (penguinCannon));
    instance->GetCurrentState().AddObject(pcannon);
}

void PenguinBody::Update(float dt) {
    InputManager * input;
    Debugger * debugger;
    input = &InputManager::GetInstance();
    debugger = &Debugger::GetInstance();
    if(input->KeyRelease(W_KEY)) {
        acceleration = +7 * dt;
        breaks = true;
    }
    if(input->KeyRelease(S_KEY)) {
        acceleration = -7 * dt;
        breaks = true;
    }
    if(input->IsKeyDown(A_KEY)) {
        angle--;
        angle = angle % 360;
        if(angle < 0 ) {
            angle = 360;
        }
    }
    if(input->IsKeyDown(D_KEY)) {
        angle++;
        angle = angle % 360;
        if(angle < 0 ) {
            angle = 360;
        }
    }
    if(input->IsKeyDown(W_KEY)) {
        acceleration = -1 * maxAcceleration * dt;
        side = FRONT;
        current_angle = angle;
    }
    if(input->IsKeyDown(S_KEY)) {
        acceleration = maxAcceleration * dt;
        side = BACK;
        current_angle = angle;
    }
    if(linearSpeed <= maxSpeed && linearSpeed >= -1 * maxSpeed) {
        linearSpeed = linearSpeed + acceleration;
    }
    if(breaks == true) {
        if(side == BACK) {
            if(debugger->lookUpdatePenguinBody) {
                cout<<"comecou a freiar"<<endl;
            }
            if(linearSpeed <= 0) {
                if(debugger->lookUpdatePenguinBody) {
                    cout<<"terminou de freiar"<<endl;
                }
                linearSpeed = 0;
                acceleration = 0;
                breaks = false;
            }
        } else {
            if(side == FRONT) {
                if(debugger->lookUpdatePenguinBody) {
                    cout<<"comecou a freiar"<<endl;
                }
                if(linearSpeed >= 0) {
                    if(debugger->lookUpdatePenguinBody) {
                        cout<<"terminou de freiar"<<endl;
                    }
                    linearSpeed = 0;
                    acceleration = 0;
                    breaks = false;
                }
            }
        }
    }
    if(debugger->lookUpdatePenguinBody) {
        cout<<"linearSpeed: "<<linearSpeed<<endl;
        cout<<"acceleration: "<<acceleration<<endl;
        cout<<"angle: "<<angle<<endl;
        cout<<"current_angle: "<<current_angle<<endl;
        cout<<"cos(angle): "<<cos(current_angle)<<endl;
        cout<<"sin(angle): "<<sin(current_angle)<<endl;
        cout<<"speed x: "<<linearSpeed * cos(angle)<<endl;
        cout<<"speed y: "<<linearSpeed * sin(angle)<<endl;
    }
    associated.angleDeg = angle;
    associated.box.x = associated.box.x - linearSpeed * cos(current_angle*PI/180);
    associated.box.y = associated.box.y - linearSpeed * sin(current_angle*PI/180);
    if(associated.box.x < 0) {
        associated.box.x = 0;
        linearSpeed = 0;
        acceleration = 0;
    }
    if(associated.box.x > 1408) {
        associated.box.x = 1408;
        acceleration = 0;
        linearSpeed = 0;
    }
    if(associated.box.y > 1280) {
        associated.box.y = 1280;
        acceleration = 0;
        linearSpeed = 0;
    }
    if(associated.box.y < 0) {
        associated.box.y = 0;
        acceleration = 0;
        linearSpeed = 0;
    }
    pcannon->Update(dt);
    Camera::Update(dt);
    if(hp <= 0) {
        Camera::UnFollow();
        pcannon->RequestedDelete();
        associated.RequestedDelete();
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(string type) {
    bool result = false;
    if(type == "PenguinBody") {
        result = true;
    }
    return result;
}

void PenguinBody::NotifyCollision(GameObject &other) {
    GameObject * explosion;
    Sprite * explosionSprite;
    Sound * explosionSound;
    Game * instance;
    instance = &Game::GetInstance();
    if(other.GetComponent("Bullet") != NULL) {
        if(((Bullet*) other.GetComponent("Bullet").get())->targetsPlayer == true) {
            hp = hp - ((Bullet*) other.GetComponent("Bullet").get())->GetDamage();
            other.RequestedDelete();
            if(hp <= 0) {
                explosion = new GameObject();
                explosion->box.z = 1;
                explosion->box.x = associated.box.x + associated.box.w / 2 - explosion->box.w / 2;
                explosion->box.y = associated.box.y + associated.box.h / 2 - explosion->box.h / 2;
                explosionSprite = new Sprite(*explosion, "assets/img/penguindeath.png", 5, 0.05, 0.25);
                explosionSound = new Sound(*explosion, "assets/audio/boom.wav");
                explosion->AddComponent(shared_ptr<Component> (explosionSprite));
                explosion->AddComponent(shared_ptr<Component> (explosionSound));
                instance->GetCurrentState().AddObject(explosion);
                explosionSound->Play(1);
            }
        }
    }
}