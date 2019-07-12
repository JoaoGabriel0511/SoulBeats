#ifndef UI_TEXT_H
#define UI_TEXT_H
#define FONT "assets/font/editundo.ttf"
#include "Component.h"
#include "Text.h"

class UIText : public Component
{
private:
    int value;
    Vect2 pos;
    Text* text;
    GameObject *iconGO;
    Sprite *iconSprite;
public:
    UIText(GameObject& associated, Vect2 pos, string iconFile);
    ~UIText();
    bool Is(string type);
    void Update(float dt);
    void UpdateText(string value);
    void Start();
};


#endif