#ifndef ALIEN_H
#define ALIEN_H
#include "Action.h"
#include "Game.h"
#include "Minion.h"
#include "Debugger.h"
#include "Timer.h"
#include "Collider.h"
#include <queue>
#include <cmath>
    class Component;
    class Alien : public Component {
        Vect2 direction;
        Vect2 start;
        Vect2 goPos;
        Vect2 end;
        float distance;
        float hipspeed;
        float timeOffset;
        int hp;
        int nMinions;
        bool isNewAction;
        void MoveAlien(float dt);
        void ShootBullet(float dt);
        void AddMinion(int arc);
        float rotationSpeed;
        GameObject* player;
        vector<weak_ptr<GameObject>> minionArray;
        enum AlienState { MOVING, RESTING };
        AlienState state;
        Timer restTimer;
        Timer shootTimer;
        Vect2 destination;
        public:
            Alien(GameObject& associated, int nMinions,  GameObject * player, float timeOfsset);
            ~Alien();
            static int alienCount;
            void Start();
            void Update(float dt);
            void Render();
            bool Is(string type);
            void NotifyCollision (GameObject& other);
    };

#endif