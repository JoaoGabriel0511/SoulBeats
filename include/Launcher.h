#ifndef LAUNCHER
#define LAUNCHER
#define LAUNCHER_UP "assets/img/interactables/Lançadores/LauncherUp.png"
#define LAUNCHER_UP_RIGHT "assets/img/interactables/Lançadores/LauncherDiagRight.png"
#define LAUNCHER_UP_LEFT "assets/img/interactables/Lançadores/LauncherDiagLeft.png"
#define LAUNCHER_RIGHT "assets/img/interactables/Lançadores/LauncherRight.png"
#define LAUNCHER_LEFT "assets/img/interactables/Lançadores/LauncherLeft.png"
#define LAUNCHER_DOWN "assets/img/interactables/Lançadores/LauncherDown.png"
#include "Component.h"
#include "Sprite.h"
#include "Collider.h"
#include "Launcher.h"
#include "Character.h"

class Launcher : public Component {
    public:
        enum LauncherType {
            UP,
            UP_RIGHT,
            UP_LEFT,
            LEFT,
            RIGHT,
            DOWN
        };
    private:
        Sprite* launcherSprite;
        Collider* launcherCollider;
        LauncherType type;
        GameObject *character;
        Vect2 pointPos;
        float dt;
    public:
        Launcher(GameObject& associated, LauncherType type, GameObject* character);
        bool Is(string type);
        void Update(float dt);
        void NotifyCollision(GameObject& other);
        void Start();
};

#endif