#ifndef TEXT_H
#define TEXT_H
#include "Component.h"
#include "Game.h"
#include "Timer.h"
#include "Resources.h"
#include "SDL2/SDL_ttf.h"
using namespace std;

class Text : public Component{
    public:
        enum TextStyle { SOLID, SHADED, BLENDED };
        Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, float blinkTime);
        ~Text();
        void Update(float dt);
        void Render();
        bool Is(string type);
        void SetText(string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(string fontFile);
        void SetFontSize(int fontSize);
        Timer blinkTimer;
        float blinkTime;
        bool isBlink;
    private:
        void RemakeTexture();
        shared_ptr<TTF_Font> font;
        SDL_Texture* texture;
        string text;
        TextStyle style;
        string fontFile;
        int fontSize;
        SDL_Color color;
};

#endif