#ifndef GAME_INFO_H
#define GAME_INFO_H

class GameInfo {
    public:
        float HEIGHT;
        float WIDTH;
        GameInfo(){
            this->HEIGHT = 600;
            this->WIDTH = 1024;
        }
        static GameInfo& GetInstance() {
            static  GameInfo gameInfo;
            return gameInfo;
        }
};

#endif