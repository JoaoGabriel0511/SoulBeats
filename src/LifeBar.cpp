//
// Created by joao on 30/06/19.
//

#include "../include/LifeBar.h"


LifeBar::LifeBar(GameObject &associated) : Component(associated){
}

bool LifeBar::Is(string type) {
    bool result = false;
    if(type == "LifeBar") {
        result = true;
    }
    return result;
}

void  LifeBar::Start() {
    lifeBarSprite = new Sprite(associated, HP_5);
    lifeBarSprite->SetScale({2,2});
    hp = 5;
    switched = false;
}

void LifeBar::GetHP() {
    if(hp < 5) {
        hp++;
        switched = true;
        switch(hp){
            case 5:
                lifeBarSprite->SwitchSprite(HP_5_4, 1, 0);
                break;
            case 4:
                lifeBarSprite->SwitchSprite(HP_4_3, 1, 0);
                break;
            case 3:
                lifeBarSprite->SwitchSprite(HP_3_2, 1, 0);
                break;
            case 2:
                lifeBarSprite->SwitchSprite(HP_2_1, 1, 0);
                break;
            default:
                break;
        }
        hpChangeTimer.Restart();
    }
}

void LifeBar::LoseHP() {
    if(hp > 0) {
        hp--;
    }
    switched = true;
    switch(hp){
        case 4:
            lifeBarSprite->SwitchSprite(HP_5_4, 1, 0);
            break;
        case 3:
            lifeBarSprite->SwitchSprite(HP_4_3, 1, 0);
            break;
        case 2:
            lifeBarSprite->SwitchSprite(HP_3_2, 1, 0);
            break;
        case 1:
            lifeBarSprite->SwitchSprite(HP_2_1, 1, 0);
            break;
        case 0:
            lifeBarSprite->SwitchSprite(HP_1_0, 1, 0);
        default:
            break;
    }
    hpChangeTimer.Restart();
}

void LifeBar::Update(float dt) {
    associated.box.x = 1 - Camera::pos.x;
    associated.box.y = 1 - Camera::pos.y;
    if (switched) {
        hpChangeTimer.Update(dt);
        if(hpChangeTimer.Get() >= HP_CHANGE_TIME) {
            switch(hp){
                case 5:
                    lifeBarSprite->SwitchSprite(HP_5, 1, 0);
                    break;
                case 4:
                    lifeBarSprite->SwitchSprite(HP_4, 1, 0);
                    break;
                case 3:
                    lifeBarSprite->SwitchSprite(HP_3, 1, 0);
                    break;
                case 2:
                    lifeBarSprite->SwitchSprite(HP_2, 1, 0);
                    break;
                case 1:
                    lifeBarSprite->SwitchSprite(HP_1, 1, 0);
                    break;
                case 0:
                    lifeBarSprite->SwitchSprite(HP_0, 1, 0);
                default:
                    break;
            }
            switched = false;
        }
    }
}

void LifeBar::Render() {}

int LifeBar::HP() {
    return hp;
}