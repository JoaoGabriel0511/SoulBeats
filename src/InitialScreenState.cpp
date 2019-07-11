#include "../include/InitialScreenState.h"
#include "../include/LevelState.h"

InitialScreenState::InitialScreenState() : State() {
}


void InitialScreenState::Start() {
    floorOnInitialState = true;
    selectedOption = START;
    State::Start();
}

void InitialScreenState::LoadAssets() {
    // Background
    backgroundGo = new GameObject();
    backgroundGo->box.w = GameInfo::GetInstance().WIDTH;
    backgroundGo->box.h = GameInfo::GetInstance().HEIGHT;
    backgroundGo->box.x = Camera::pos.x;
    backgroundGo->box.y = Camera::pos.y;
    Sprite* backgroungSprite = new Sprite(*backgroundGo, INITIAL_SCREEN_BACKGROUND_SPRITE);
    backgroungSprite->SetScale({2.1,2.1});

    Music * menuMusic = new Music(*backgroundGo, INTIAL_SCREEN_MUSIC);
    // menuMusic->Play(1);

    // Floor
    floorGo = new GameObject();
    floorGo->box.x = Camera::pos.x;
    floorGo->box.y = Camera::pos.y;
    floorSprite = new Sprite(*floorGo, INITIAL_SCREEN_FLOOR_1_SPRITE);
    floorSprite->SetScale({2.1, 2.1});

    // Heart
    heartGo = new GameObject();
    heartGo->box.x = Camera::pos.x + 230;
    heartGo->box.y = Camera::pos.y + 120;
    Sprite * heartSprite = new Sprite(*heartGo, MENU_HEART_SPRITE);
    heartSprite->SetScale({1.2, 1.2});

    // Aria
    characterGo = new GameObject();
    characterGo->box.x = Camera::pos.x + 440;
    characterGo->box.y = Camera::pos.y + 360;
    characterGo->box.z = 3;
    characterSprite = new Sprite(*characterGo, MENU_CHARACTER_SPRITE_SHEET, 4, MENU_CHARACTER_FRAME_TIME, 0);
    characterSprite->SetScale({1.4, 1.4});


    // Highlight
    highlightGo = new GameObject();
    highlightGo->box.x = Camera::pos.x + 185;
    highlightGo->box.y = Camera::pos.y + 140;
    highlightGo->box.z = 2;
    highlightSprite = new Sprite(*highlightGo, MENU_HIGHLIGHT_SPRITE_1);
    highlightSprite->SetScale({1.4, 1.4});

    // Menu Options
    startOptionGo = new GameObject();
    creditsOptionGo = new GameObject();
    exitOptionGo = new GameObject();
    loreOptionGo = new GameObject();
    
    startSprite = new Sprite(*startOptionGo, OPTION_START_1);
    startOptionGo->box.x = Camera::pos.x + 455;
    startOptionGo->box.y = Camera::pos.y + 330;
    startSprite->SetScale({1.2, 1.2});

    creditsSprite = new Sprite(*creditsOptionGo, OPTION_CREDITS_0);
    creditsOptionGo->box.x = Camera::pos.x + 150;
    creditsOptionGo->box.y = Camera::pos.y + 570;
    creditsSprite->SetScale({1.2, 1.2});

    exitSprite = new Sprite(*exitOptionGo, OPTION_QUIT_0);
    exitOptionGo->box.x = Camera::pos.x + 510;
    exitOptionGo->box.y = Camera::pos.y + 570;
    exitSprite->SetScale({1.2, 1.2});

    loreSprite = new Sprite(*loreOptionGo, OPTION_LORE_0);
    loreOptionGo->box.x = Camera::pos.x + 800;
    loreOptionGo->box.y = Camera::pos.y + 570;
    loreSprite->SetScale({1.2, 1.2});


    ///


    objectArray.emplace_back(backgroundGo);
    objectArray.emplace_back(floorGo);
    objectArray.emplace_back(heartGo);
    objectArray.emplace_back(characterGo); 
    objectArray.emplace_back(highlightGo);
    objectArray.emplace_back(startOptionGo);
    objectArray.emplace_back(creditsOptionGo);
    objectArray.emplace_back(exitOptionGo);
    objectArray.emplace_back(loreOptionGo);

}

void InitialScreenState::Update(float dt) {
    State::Update(dt);
    floorChangeTimer.Update(dt);
    if(floorChangeTimer.Get() > FLOOR_CHANGE_INTERVAL){
        if(floorOnInitialState){
            floorSprite->SwitchSprite(INITIAL_SCREEN_FLOOR_2_SPRITE, 1, 0);
            highlightSprite->SwitchSprite(MENU_HIGHLIGHT_SPRITE_2, 1, 0);
            floorOnInitialState = false;
        } 
        else {
            floorSprite->SwitchSprite(INITIAL_SCREEN_FLOOR_1_SPRITE, 1, 0);
            highlightSprite->SwitchSprite(MENU_HIGHLIGHT_SPRITE_1, 1, 0);
            floorOnInitialState = true;
        }
        floorChangeTimer.Restart();
    }

    UpdateMenuInput(dt);
}

void InitialScreenState::Pause() {}

void InitialScreenState::Resume() {}

void InitialScreenState::StartData() {}

void InitialScreenState::UpdateMenuInput(float dt){
    Options currentOption = selectedOption;

    if(currentOption == START){
        // cout << "[START] selected\n";
        
        if (InputManager::GetInstance().KeyPress(D_KEY) or  InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)) {
            // cout << "Go right";
            selectedOption = CREDITS;
            startSprite->SwitchSprite(OPTION_START_0, 1, 0);
            creditsSprite->SwitchSprite(OPTION_CREDITS_1, 1, 0);
        }

        if (InputManager::GetInstance().KeyPress(A_KEY) or  InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)) {
            selectedOption = LORE;
            startSprite->SwitchSprite(OPTION_START_0, 1, 0);
            loreSprite->SwitchSprite(OPTION_LORE_1, 1, 0);
        }   

        if (InputManager::GetInstance().KeyPress(SDLK_RETURN)){
            LevelState* levelState;
            levelState = new LevelState();
            Game::GetInstance().Push(levelState);

        }
    }

    if(currentOption == CREDITS){
        if (InputManager::GetInstance().KeyPress(D_KEY) or  InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)) {
            selectedOption = QUIT;
            creditsSprite->SwitchSprite(OPTION_CREDITS_0, 1, 0);
            exitSprite->SwitchSprite(OPTION_QUIT_1, 1, 0);
        }

        if (InputManager::GetInstance().KeyPress(A_KEY) or  InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)) {
            selectedOption = START;
            creditsSprite->SwitchSprite(OPTION_CREDITS_0, 1, 0);
            startSprite->SwitchSprite(OPTION_START_1, 1, 0);
        }   
    }

    if(currentOption == QUIT){
        if (InputManager::GetInstance().KeyPress(D_KEY) or  InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)) {
            selectedOption = LORE;
            exitSprite->SwitchSprite(OPTION_QUIT_0, 1, 0);
            loreSprite->SwitchSprite(OPTION_LORE_1, 1, 0);
        }

        if (InputManager::GetInstance().KeyPress(A_KEY) or  InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)) {
            selectedOption = CREDITS;
            exitSprite->SwitchSprite(OPTION_QUIT_0, 1, 0);
            creditsSprite->SwitchSprite(OPTION_CREDITS_1, 1, 0);
        }   

         if (InputManager::GetInstance().KeyPress(SDLK_RETURN)){
            quitRequested = true;
            // Game::GetInstance().GetCurrentState().
        }
    }

    if(currentOption == LORE){
        if (InputManager::GetInstance().KeyPress(D_KEY) or  InputManager::GetInstance().KeyPress(RIGHT_ARROW_KEY)) {
            selectedOption = START;
            loreSprite->SwitchSprite(OPTION_LORE_0, 1, 0);
            startSprite->SwitchSprite(OPTION_START_1, 1, 0);
        }

        if (InputManager::GetInstance().KeyPress(A_KEY) or  InputManager::GetInstance().KeyPress(LEFT_ARROW_KEY)) {
            selectedOption = QUIT;
            loreSprite->SwitchSprite(OPTION_LORE_0, 1, 0);
            exitSprite->SwitchSprite(OPTION_QUIT_1, 1, 0);
        }   
    }


}