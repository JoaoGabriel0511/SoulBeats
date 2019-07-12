#ifndef COMBO_H
#define COMBO_H
#define NICE_SPRITE "assets/img/combo/Nice.png"
#define GREAT_SPRITE "assets/img/combo/Great.png"
#define BRAVO_SPRITE "assets/img/combo/Bravo.png"
#define COMBO_BAR_SPRITE "assets/img/combo/comboBar.png"
#define COMBO_BAR_DECREASE_TIME 0.08

#define COMBO_INTERVAL 1.7
#define MESSAGE_TIME 0.43
#define MESSAGE_FRAME_TIME 0.05

#include "Component.h"
#include "Sprite.h"
#include "Timer.h"

class ComboSystem : public Component {
    GameObject* comboBarGo;
    Sprite* comboLevelSprite;
    Sprite* comboBarSprite;
    

    Timer comboTimer;
    Timer messageTimer;
    enum ComboLevel {NONE, NICE,GREAT, BRAVO};

    ComboLevel comboLevel;
    bool comboFlag;
    bool playMessage;

    public:
        ComboSystem(GameObject& associated);
    
        void Update(float dt);
        void Start();
        void Render();
        bool Is(string type);
        
        void UpdateKilledEnemy();
        void RestartComboTimer();

};

#endif