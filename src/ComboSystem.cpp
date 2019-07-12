#include "../include/ComboSystem.h"
#include "../include/Sprite.h"

ComboSystem::ComboSystem(GameObject& associated) : Component(associated){
}

void ComboSystem::Start(){
    comboFlag = false;
    comboLevel = NONE;

    comboLevelSprite = new Sprite(associated, 8, MESSAGE_TIME);
    comboLevelSprite->SetScale({2, 2});

    comboBarGo = new GameObject();
    comboBarGo->box.z = 7;
    comboBarSprite = new Sprite(*comboBarGo);
    //, COMBO_BAR_SPRITE, 21, 0.05, 0

    comboBarSprite->SetScale({1.5, 1.5});
    Game::GetInstance().GetCurrentStatePointer()->AddObject(comboBarGo);

}


void ComboSystem::RestartComboTimer(){
    if(comboFlag){
        comboTimer.Restart();
        if(comboLevel == NICE){
            comboBarSprite->SwitchSprite(NICE_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        }
        if(comboLevel == GREAT){
            comboBarSprite->SwitchSprite(GREAT_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        }
        if(comboLevel == BRAVO){
            comboBarSprite->SwitchSprite(BRAVO_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        }    
    }
}

void ComboSystem::Update(float dt){
    associated.box.x = 600 - Camera::pos.x;
    associated.box.y = 250 - Camera::pos.y;

    comboBarGo->box.x = 350 - Camera::pos.x;
    comboBarGo->box.y = 1 - Camera::pos.y;
   
    if(comboFlag){
        if(playMessage){
            messageTimer.Update(dt);
            if(messageTimer.Get() > MESSAGE_TIME){
                comboLevelSprite->isBlinking = true;
                // comboLevelSprite->SwitchSprite("", 8, MESSAGE_FRAME_TIME);
                messageTimer.Restart();
                playMessage = false;
            }
        }

        comboTimer.Update(dt);
        if(comboTimer.Get() >= COMBO_INTERVAL){
            ComboLevel currentCombo = comboLevel;

            if(currentCombo == BRAVO){
                comboLevel = GREAT;
                comboBarSprite->SwitchSprite(GREAT_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
                comboTimer.Restart();
            }

            if(currentCombo == GREAT){
                comboLevel = NICE;
                comboBarSprite->SwitchSprite(NICE_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
                comboTimer.Restart();
            }
            
            if(currentCombo == NICE){
                comboLevel = NONE;
                comboFlag = false;
                comboTimer.Restart();
                playMessage = false;
                comboBarSprite->isBlinking = true;
                // comboBarSprite->SwitchSprite("", 0, 0);
            }
        }
    }

    // cout << "COMBO SPRITE is on (" << associated.box.x << " , " << associated.box.y << ")\n";

}


void ComboSystem::Render(){}

int ComboSystem::ComboMultiplicator() {
    int multiplicator;
    switch (comboLevel)
    {
    case BRAVO:
        multiplicator = 4;
        break;
    case GREAT:
        multiplicator = 3;
        break;
    case NICE:
        multiplicator = 2;
        break;
    default:
        multiplicator = 1;
        break;
    }

    return multiplicator;
}


bool ComboSystem::Is(string type){
    return (type == "ComboSystem") ? true : false;
}

void ComboSystem::UpdateKilledEnemy(){
    comboFlag = true;
    ComboLevel currentCombo = comboLevel;
    comboLevelSprite->isBlinking = false;
    if(currentCombo == NONE){
        comboLevel = NICE;
        comboBarSprite->SwitchSprite(NICE_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        comboBarSprite->isBlinking = false;
        playMessage = true;
        comboLevelSprite->isBlinking = false;
        comboLevelSprite->SwitchSprite(NICE_SPRITE, 8, MESSAGE_FRAME_TIME);
    }
    if(currentCombo == NICE){
        comboLevel = GREAT;
        comboBarSprite->SwitchSprite(GREAT_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        comboBarSprite->isBlinking = false;
        playMessage = true;
        comboLevelSprite->isBlinking = false;
        comboLevelSprite->SwitchSprite(GREAT_SPRITE, 8, MESSAGE_FRAME_TIME);

    }
     if(currentCombo == GREAT){
        comboLevel = BRAVO;
        comboBarSprite->SwitchSprite(BRAVO_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        comboBarSprite->isBlinking = false;
        comboLevelSprite->isBlinking = false;
        playMessage = true;
        comboLevelSprite->SwitchSprite(BRAVO_SPRITE, 8, MESSAGE_FRAME_TIME);

    }
    comboBarSprite->isBlinking = false;
}