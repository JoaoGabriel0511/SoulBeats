//
// Created by joao on 30/06/19.
//

#ifndef SOULBEATS_LIFEBAR_H
#define SOULBEATS_LIFEBAR_H
#define HP_5 "assets/img/char/LifeBar/LifeBarUp5.png"
#define HP_5_4 "assets/img/char/LifeBar/LifeBarUp5-4.png"
#define HP_4 "assets/img/char/LifeBar/LifeBarUp4.png"
#define HP_4_3 "assets/img/char/LifeBar/LifeBarUp4-3.png"
#define HP_3 "assets/img/char/LifeBar/LifeBarUp3.png"
#define HP_3_2 "assets/img/char/LifeBar/LifeBarUp3-2.png"
#define HP_2 "assets/img/char/LifeBar/LifeBarUp2.png"
#define HP_2_1 "assets/img/char/LifeBar/LifeBarUp2-1.png"
#define HP_1 "assets/img/char/LifeBar/LifeBarUp1.png"
#define HP_1_0 "assets/img/char/LifeBar/LifeBarUp1-0.png"
#define HP_0 "assets/img/char/LifeBar/LifeBarUp0.png"
#define HP_CHANGE_TIME 0.083333333

#include "Component.h"
#include "Sprite.h"

class LifeBar : public Component {
    int hp;
    Sprite* lifeBarSprite;
    Timer hpChangeTimer;
    bool switched;
    public:
        LifeBar(GameObject& associated);
        void Update(float dt);
        void Start();
        int HP();
        void LoseHP();
        void GetHP();
        void Render();
        bool Is(string type);
};


#endif //SOULBEATS_LIFEBAR_H
