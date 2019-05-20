#include "../include/EndState.h"


EndState::EndState() {
    Start();
}

EndState::~EndState() {

}

void EndState::LoadAssets() {
    bg = new GameObject();
    GameObject *textGO = new GameObject();
    Text *text;
    Sprite *sprite;
    Music *music;
    CameraFollower * cameraFollower;
    cameraFollower = new CameraFollower(*bg);
    if(GameData::playerVictory == true) {
        sprite = new Sprite(*bg, "assets/img/win.jpg");
        music = new Music(*bg, "assets/audio/endStateWin.ogg");
        text = new Text(*textGO, "assets/font/superFont.ttf", 50, Text::SOLID, "Victory", {123,104,238}, 0);
        textGO->box.x = 450;
        textGO->box.y = 450;
        textGO->box.z = 1;
    } else {
        sprite = new Sprite(*bg, "assets/img/lose.jpg");
        music = new Music(*bg, "assets/audio/endStateLose.ogg");
        text = new Text(*textGO, "assets/font/superFont.ttf", 50, Text::SOLID, "Game Over", {255,0,0}, 0);
        textGO->box.x = 410;
        textGO->box.y = 450;
        textGO->box.z = 1;
    }
    bg->AddComponent(shared_ptr<Component> (cameraFollower));
    bg->AddComponent(shared_ptr<Component> (sprite));
    bg->AddComponent(shared_ptr<Component> (music));
    textGO->AddComponent(shared_ptr<Component> (text));
    AddObject(bg);
    AddObject(textGO);
}

void EndState::Update(float dt) {
    TitleState *title;
    InputManager& input = InputManager::GetInstance();
    if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)){
		quitRequested = true;
	}
    if(input.KeyPress(SPACE_KEY)) {
        popRequested = true;
        ((Music*) bg->GetComponent("Music").get())->Stop(0);
        title = new TitleState();
        Game::GetInstance().Push(title);
    }
    UpdateArray(dt);
}

void EndState::Render() {
    RenderArray();
}

void EndState::Start() {
    LoadAssets();
    ((Music*) bg->GetComponent("Music").get())->Play(-1);
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

void EndState::Resume() {

}

void EndState::Pause() {

}

