#ifndef LORE_STATE_H
#define LORE_STATE_H
#define LORE_BG "assets/img/background/SoulBeatsLore.png"
#include "State.h"

class LoreState : public State
{
private:
    string bgSpriteFile;
public:
    LoreState(string bgSpriteFile);
    void Pause() {};
    void Resume() {};
    void StartData() {};
    void LoadAssets();
    void Update(float dt);
};

#endif