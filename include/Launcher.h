#ifndef LAUNCHER
#define LAUNCHER
#define LAUNCHER_UP "assets/img/interactables/Lançadores/LauncherUp.png"
#define LAUNCHER_UP_RIGHT "assets/img/interactables/Lançadores/LauncherDiagRight.png"
#define LAUNCHER_UP_LEFT "assets/img/interactables/Lançadores/LauncherDiagLeft.png"
#define LAUNCHER_RIGHT "assets/img/interactables/Lançadores/LauncherRight.png"
#define LAUNCHER_LEFT "assets/img/interactables/Lançadores/LauncherLeft.png"
#define LAUNCHER_DOWN "assets/img/interactables/Lançadores/LauncherDown.png"
#define RISING_RIGHT_SPRITE "assets/img/char/SoulBeatsCharRiseR.png"
#define RISING_LEFT_SPRITE "assets/img/char/SoulBeatsCharRiseL.png"
#define RISING_FRAME_COUNT 3
#define RISING_FRAME_TIME 0.08333
#define PEAK_RIGHT_SPRITE "assets/img/char/SoulBeatsCharPeakR.png"
#define PEAK_LEFT_SPRITE "assets/img/char/SoulBeatsCharPeakL.png"
#define PEAK_FRAME_COUNT 1
#define PEAK_FRAME_TIME 0
#define FALLING_RIGHT_SPRITE "assets/img/char/SoulBeatsCharFallR.png"
#define FALLING_LEFT_SPRITE "assets/img/char/SoulBeatsCharFallL.png"
#define FALLING_FRAME_COUNT 4
#define FALLING_FRAME_TIME 0.08333
#define LAUNCHER_VELOCITY_X 500
#define LAUNCHER_VELOCITY_Y 500
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
        string characterLaunchSprite;
        int characterLaunchSpriteFameCount;
        float characterLaunchSpriteFrameTime;
        Collider* launcherCollider;
        bool isCharacterLeft;
        LauncherType type;
        GameObject *character;
        Vect2 pointPos;
        Vect2 launchVelocity;
        float dt;
    public:
        Launcher(GameObject& associated, LauncherType type, GameObject* character);
        bool Is(string type);
        void Update(float dt);
        void NotifyCollision(GameObject& other);
        void Start();
};

#endif