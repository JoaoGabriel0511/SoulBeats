#include "../include/ComboSystem.h"
#include "../include/Sprite.h"

ComboSystem::ComboSystem(GameObject& associated) : Component(associated){
}

void ComboSystem::Start(){
    comboFlag = false;
    comboLevel = NONE;

    comboLevelSprite = new Sprite(associated, 8, MESSAGE_TIME);
    comboLevelSprite->SetScale({1.5, 1.5});

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
        comboBarSprite->SwitchSprite(COMBO_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
    }
}

void ComboSystem::Update(float dt){
    associated.box.x = 700 - Camera::pos.x;
    associated.box.y = 250 - Camera::pos.y;

    comboBarGo->box.x = 350 - Camera::pos.x;
    comboBarGo->box.y = 1 - Camera::pos.y;
   
    if(comboFlag){

        if(playMessage){
            messageTimer.Update(dt);
            if(messageTimer.Get() > MESSAGE_TIME){
                comboLevelSprite->SwitchSprite("", 8, MESSAGE_FRAME_TIME);
                messageTimer.Restart();
                playMessage = false;
            }
        }   

        comboTimer.Update(dt);
        if(comboTimer.Get() >= COMBO_INTERVAL){
            ComboLevel currentCombo = comboLevel;

            if(currentCombo == BRAVO){
                comboLevel = GREAT;
                comboTimer.Restart();
            }

            if(currentCombo == GREAT){
                comboLevel = NICE;
                comboTimer.Restart();
            }
            
            if(currentCombo == NICE){
                comboLevel = NONE;
                comboFlag = false;
                comboTimer.Restart();
                comboBarSprite->SwitchSprite("", 0, 0);
            }
        }
    }

    cout << "COMBO SPRITE is on (" << associated.box.x << " , " << associated.box.y << ")\n";

}


void ComboSystem::Render(){}


bool ComboSystem::Is(string type){
    return (type == "ComboSystem") ? true : false;
}

void ComboSystem::UpdateKilledEnemy(){
    comboFlag = true;
    ComboLevel currentCombo = comboLevel;

    if(currentCombo == NONE){
        cout << "Combo is now " << comboLevel << endl;
        comboLevel = NICE;
        comboBarSprite->SwitchSprite( COMBO_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        playMessage = true;
        comboLevelSprite->SwitchSprite(NICE_SPRITE, 8, MESSAGE_FRAME_TIME);
    }
    if(currentCombo == NICE){
        cout << "Combo is now " << comboLevel << endl;
        comboLevel = GREAT;
        comboBarSprite->SwitchSprite( COMBO_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        // comboLevelSprite->SwitchSprite(GREAT_SPRITE, 8, MESSAGE_FRAME_TIME);

    }
     if(currentCombo == GREAT){
        cout << "Combo is now " << comboLevel << endl;
        comboLevel = BRAVO;
        comboBarSprite->SwitchSprite( COMBO_BAR_SPRITE, 21, COMBO_BAR_DECREASE_TIME);
        // comboLevelSprite->SwitchSprite(BRAVO_SPRITE, 8, MESSAGE_FRAME_TIME);

    }
}