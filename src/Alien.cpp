#include "../include/Alien.h"
#define PI 3.14159265
int Alien::alienCount;
Alien::Alien(GameObject& associated, int nMinions, GameObject * player, float timeOfsset) : Component(associated) {
    Sprite *alienSprite;
    Collider *collider;
    collider = new Collider(associated);
    alienSprite = new Sprite(associated, "assets/img/alien.png");
    associated.AddComponent(shared_ptr<Component> (alienSprite));
    associated.AddComponent(shared_ptr<Component> (collider));
    isNewAction = true;
    hp = 50;
    rotationSpeed = 0.5;
    alienCount++;
    state = RESTING;
    this->nMinions = nMinions;
    this->timeOffset = timeOffset;
    this->player = player;
}

void Alien::Start() {
    cout<<"start do alien"<<endl;
    for(int i = 0; i < nMinions; i++){
        cout<<"add minion "<<i<<endl;
        AddMinion(i);
        cout<<"adicionou"<<endl;
    }
}

void Alien::AddMinion(int arc) {
    GameObject * newGO;
    Game *instance;
    instance = &Game::GetInstance();
    Minion * minion;
    newGO = new GameObject();
    newGO->box.z = 1;
    minion = new Minion(*newGO, associated, arc * 120);
    newGO->AddComponent(shared_ptr<Component> (minion));
    State * state;
    state = &instance->GetCurrentState();
    minionArray.emplace_back(state->AddObject(newGO));
}

Alien::~Alien() {
    minionArray.clear();
    Alien::alienCount--;
}

void Alien::Update(float dt) {
    Debugger *debugger;
    Game *instance;
    debugger = &Debugger::GetInstance();
    InputManager inputManager = InputManager::GetInstance();
    Action *newAction;
    int mousePosX = inputManager.GetMouseX();
    int mousePosY = inputManager.GetMouseY();
    associated.angleDeg -= rotationSpeed;
    if(state == RESTING) {
        shootTimer.Update(dt);
        if(shootTimer.Get() >= 1) {
            ShootBullet(dt);
            shootTimer.Restart();
        }
        restTimer.Update(dt);
        if(restTimer.Get() >= 5 + timeOffset) {
            destination.x = player->box.x;
            destination.y = player->box.y;
            state = MOVING;
        }
    } else {
        if(state == MOVING) {
            MoveAlien(dt);
        }
    }
    if(hp <= 0) {
        associated.RequestedDelete();
        for(int i = 0; i < minionArray.size(); i++){
            minionArray[i].lock()->RequestedDelete();
        }
    }
}

void Alien::ShootBullet(float dt) {
    GameObject * closestMinion;
    GameObject * currentMinion;
    bool first = true;
    Vect2 currentMinionPos;
    Vect2 closestMinionPos;
    Vect2 target;
    target.x = player->box.x;
    target.y = player->box.y;
    closestMinion = NULL;
    currentMinion = NULL;
    for(int i = 0; i < minionArray.size(); i++){
        currentMinion = minionArray[i].lock().get();
        currentMinionPos.x = currentMinion->box.x;
        currentMinionPos.y = currentMinion->box.y;
        if(first) {
            first = false;
            closestMinion = currentMinion;
            closestMinionPos.x = closestMinion->box.x;
            closestMinionPos.y = closestMinion->box.y;
        } else {
            if(currentMinionPos.DistanceTo(target) <  closestMinionPos.DistanceTo(target)){
                closestMinion = currentMinion;
                closestMinionPos.x = closestMinion->box.x;
                closestMinionPos.y = closestMinion->box.y;
           }
        }
    }
    if(closestMinion != NULL) {
        start.x = closestMinion->box.x;
        start.y = closestMinion->box.y;
        end.x = player->box.x;
        end.y = player->box.y;
        direction = end - start;
        direction = direction.Normalize();
        ((Minion*) closestMinion->GetComponent("Minion").get())->Shoot(direction);
    }
}

void Alien::MoveAlien(float dt) {
    Debugger * debugger;
    *debugger = Debugger::GetInstance();
    if(debugger->lookUpdateAlien) {
        cout<<"   Leu acao de mover na fila"<<endl;
    }
    if(isNewAction) {
        if(debugger->lookUpdateAlien) {
            cout<<"     Eh nova acao"<<endl;
        }
        hipspeed = 300 * dt;
        start.x = associated.box.x;
        start.y = associated.box.y;
        end = destination;
        goPos = start;
        distance = start.DistanceTo(end);
        direction = end - start;
        direction = direction.Normalize();
        if(debugger->lookUpdateAlien) {
            cout<<"Direction x "<<direction.x<<" y "<<direction.y<<endl;
        }
        isNewAction = false;
    }
    goPos = goPos + (direction * hipspeed);
    associated.box.x = goPos.x;
    associated.box.y = goPos.y;
    if(debugger->lookUpdateAlien) {
        cout<<"  Cordenadas de inicio (x: "<< start.x <<", y: "<<start.y<<")"<<endl;
        cout<<"  Cordenadas de destino (x: "<< end.x <<", y: "<<end.y<<")"<<endl;
        cout<<"  Cordenadas atuais (x: "<< associated.box.x <<", y: "<<associated.box.y<<")"<<endl;
        cout<<"  Distancia "<< distance<<endl;
    }
    if(start.DistanceTo(goPos) >= distance) {
        if(debugger->lookUpdateAlien) {
            cout<<"chegou ao destino"<<endl;
        }
        associated.box.x = end.x;
        associated.box.y = end.y;
        hipspeed = 0;
        isNewAction = true;
        restTimer.Restart();
        state = RESTING;
    }
}

void Alien::Render() {}

bool Alien::Is(string type) {
    bool result = false;
    if(type == "Alien") {
        result = true;
    }
    return result;
}

void Alien::NotifyCollision(GameObject& other) {
    GameObject * explosion;
    Sprite * explosionSprite;
    Sound * explosionSound;
    Game * instance;
    instance = &Game::GetInstance();
    if(other.GetComponent("Bullet") != NULL) {
        if(((Bullet*) other.GetComponent("Bullet").get())->targetsPlayer == false) {
            hp = hp - ((Bullet*) other.GetComponent("Bullet").get())->GetDamage();
            other.RequestedDelete();
            if(hp <= 0) {
                explosion = new GameObject();
                explosion->box.z = 1;
                explosion->box.x = associated.box.x + associated.box.w / 2 - explosion->box.w / 2;
                explosion->box.y = associated.box.y + associated.box.h / 2 - explosion->box.h / 2;
                explosionSprite = new Sprite(*explosion, "assets/img/aliendeath.png", 4, 0.05, 0.2);
                explosionSound = new Sound(*explosion, "assets/audio/boom.wav");
                explosion->AddComponent(shared_ptr<Component> (explosionSprite));
                explosion->AddComponent(shared_ptr<Component> (explosionSound));
                instance->GetCurrentState().AddObject(explosion);
                explosionSound->Play(1);
            }
        }
    }
}