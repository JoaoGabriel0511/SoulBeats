#include "../include/Text.h"

Text::Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, float blinkTime) : Component(associated) {
    this->fontFile = fontFile;
    this->fontSize = fontSize;
    this->style = style;
    this->text = text;
    this->color = color;
    this->blinkTime = blinkTime;
    isBlink = false;
    texture = NULL;
    RemakeTexture();
}

Text::~Text() {
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt) {
    if(blinkTime > 0) {
        blinkTimer.Update(dt);
        if(blinkTimer.Get() >= blinkTime) {
            if(isBlink) {
                isBlink = false;
            } else {
                isBlink = true;
            }
            blinkTimer.Restart();
        }
    }
}

void Text::Render() {
    if(!isBlink) {
        SDL_Rect srcRect{ 0, 0, associated.box.w, associated.box.h };
        SDL_Rect dstRect{ associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y, srcRect.w, srcRect.h };
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &srcRect, &dstRect, associated.angleDeg, NULL, SDL_FLIP_NONE);
    }
}

void  Text::SetText (string text) {
    this->text = text;
}

void Text::SetColor (SDL_Color color) {
    this->color = color;
}

void Text::SetStyle (TextStyle style) {
    this->style = style;
}

void Text::SetFontSize (int fontSize) {
    this->fontSize = fontSize;
}

bool Text::Is(string type) {
    bool result = false;
    if(type == "Text") {
        result = true;
    }
    return result;
}

void Text::RemakeTexture() {
    SDL_Surface* surface;
    if(texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    font = Resources::GetFont(fontFile, fontSize);
    cout<<"->>>> "<<font<<endl;
    if(font != NULL) {
        switch (style) {
            case SOLID:
                surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
                break;
            case SHADED:
                surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
                break;
            case BLENDED:
                surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
                break;
            default:
                break;
        }
        associated.box.h = surface->h;
        associated.box.w = surface->w;
        texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
        SDL_FreeSurface(surface);
    }
}

