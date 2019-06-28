// #include "../include/UserInterface.h"

// UserInterface::UserInterface(GameObject& associated) : Component(associated){
//     Start();
// }

// void UserInterface::Start(){
//     heartSprite = new Sprite(associated, HP_HEART_SPRITE);
//     // hp.reserve(3);
//     // for(int i = 0; i < 3; i++){
//     //     Sprite* sprite = new Sprite(associated, HEART_SPRITE);
//     //     hp.push_back(sprite);
//     //cout<<"falha ao carregar tile pos("<<posx<<","<<posy<<") index: "<<tileMatrix[i]<<endl;
//      // }
// }

// void UserInterface::Update(float dt){
//     Render();
// }

// void UserInterface::Render(){
//     cout << "[UserInterface] render\n";
//     int player_hp = 3; 
//     for(int i = 0; i < player_hp; i++) {
//         int pos_x = Camera::pos.x + 50;
//         int pos_y = Camera::pos.y + 50;
//         cout << "Trying to render interface heart at ("  << pos_x << ", " << pos_y << ")" << endl;
//         // cout << "Sprite width: " <<  heartSprite->GetWidth() << endl;
//         // cout << "Sprite Height: " <<  heartSprite->GetHeight() << endl;
//         heartSprite->Render(pos_x, pos_y, heartSprite->GetWidth(), heartSprite->GetHeight());

//     }
// }


// bool UserInterface::Is(string type){
//     return (type == "UserInterface") ? true : false;
// }
