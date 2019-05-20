#include "../include/TitleState.h"

TitleState::TitleState() {
    Start();
}

void TitleState::Update(float dt) {
    StageState *stage;
    Game& instance = Game::GetInstance();
    InputManager inputManager = InputManager::GetInstance();
    if(inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested()){
		quitRequested = true;
	} else {
        if(inputManager.KeyPress(SPACE_KEY)) {
            stage = new StageState();
            Pause();
            instance.Push(stage);
        }
    }
    UpdateArray(dt);
}

TitleState::~TitleState(){}

void TitleState::LoadAssets() {
    Sprite *sprite;
    Text *text;
    CameraFollower * cameraFollower;
    bg = new GameObject();
    textGO = new GameObject();
    text = new Text(*textGO, "assets/font/superFont.ttf", 50, Text::SOLID, "Aperte espaco para proceguir", {0,0,0}, 0.7);
    cameraFollower = new CameraFollower(*bg);
    sprite = new Sprite(*bg, "assets/img/title.jpg");
    bgSprite = shared_ptr<Sprite>(sprite);
    bg->AddComponent(shared_ptr<Component> (bgSprite));
    bg->AddComponent(shared_ptr<Component> (cameraFollower));
    textGO->AddComponent(shared_ptr<Component> (text));
    textGO->box.x = 200;
    textGO->box.y = 450;
    textGO->box.z = 1;
    AddObject(bg);
    AddObject(textGO);
}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    LoadAssets();
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

void TitleState::Pause() {}

void TitleState::Resume() {
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}