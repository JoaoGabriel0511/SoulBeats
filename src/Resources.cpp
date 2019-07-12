#include "../include/Resources.h"
using namespace std;
unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string, shared_ptr<TTF_Font>> Resources::fontTable;
int countScore = 0;


shared_ptr<SDL_Texture> Resources::GetImage(string file) {
    shared_ptr<SDL_Texture> texture;
    if(imageTable.find(file) == imageTable.end()) {
        texture = shared_ptr<SDL_Texture>(IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str()), [=](SDL_Texture *texture){SDL_DestroyTexture(texture);});
        if(texture == NULL){
            cout<<"Falha ao carregar imagem "<<file<<" no hash de imagens"<<endl;
        } else {
            pair<string, shared_ptr<SDL_Texture>> newTexture(file, texture);
            imageTable.insert(newTexture);
            return texture;
        }
    } else {
        return imageTable[file];
    }
}

void Resources::ClearImages() {
    for(auto texture = imageTable.begin(); texture != imageTable.end(); texture++) {
        if(texture->second.unique()) {
            SDL_DestroyTexture(texture->second.get());
        }
    }
    imageTable.clear();
}

shared_ptr<Mix_Music> Resources::GetMusic(string file) {
    shared_ptr<Mix_Music> music;
    if(musicTable.find(file) == musicTable.end()){
        music = shared_ptr<Mix_Music>(Mix_LoadMUS(file.c_str()), [=](Mix_Music *music){Mix_FreeMusic(music);});
        if(music == NULL){
            cout<<"Falha ao carregar musica "<<file<<" no hash de musicas"<<endl;
        } else {
            pair<string, shared_ptr<Mix_Music>> newMusic(file, music);
            musicTable.insert(newMusic);
            return music;
        }
    } else {
        return musicTable[file];
    }
}

void Resources::ClearMusics() {
    for(auto music = musicTable.begin(); music != musicTable.end(); music++) {
        if(music->second.unique()) {
            Mix_FreeMusic(music->second.get());
        }
    }
    //musicTable.clear();
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file) {
    shared_ptr<Mix_Chunk> sound;
    if(soundTable.find(file) == soundTable.end()){
        sound = shared_ptr<Mix_Chunk>(Mix_LoadWAV(file.c_str()), [=](Mix_Chunk *sound){Mix_FreeChunk(sound);});
        if(sound == NULL){
            cout<<"Falha ao carregar som "<<file<<" no hash de sons"<<endl;
        } else {
            pair<string, shared_ptr<Mix_Chunk>> newsound(file, sound);
            soundTable.insert(newsound);
            return sound;
        }
    } else {
        return soundTable[file];
    }
}

void Resources::ClearSounds() {
    for(auto sound = soundTable.begin(); sound != soundTable.end(); sound++) {
        if(sound->second.get() != NULL) {
            if(sound->second.unique()) {
                //Mix_FreeChunk(sound->second.get());
            }
        }

    }
    // soundTable.clear();
}

shared_ptr<TTF_Font> Resources::GetFont(string file, int fontSize) {
    shared_ptr<TTF_Font> font;
    TTF_Init();
    if(fontTable.find(file) == fontTable.end()) {
        font = shared_ptr<TTF_Font>(TTF_OpenFont(file.c_str(), fontSize), [=](TTF_Font *font){TTF_CloseFont(font);});
        if(font == NULL){
            cout<<"Falha ao carregar fonte "<<file<<" no hash de fontes"<<endl;
            return NULL;
        } else {
            pair<string, shared_ptr<TTF_Font>> newFont(file + to_string(fontSize), font);
            fontTable.insert(newFont);
            return font;
        }
    } else {
        return fontTable[file + to_string(fontSize)];
    }
}

void Resources::ClearFonts() {
    for(auto font = fontTable.begin(); font != fontTable.end(); font++) {
        if(font->second.unique()) {
            TTF_CloseFont(font->second.get());
        }
    }
    fontTable.clear();
}

/*void Resources::updateScore(int value) {
   countScore = countScore + value;
}

int Resources::getScore() {
    return countScore;
}*/