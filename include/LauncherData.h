#ifndef LAUNCHER_DATA_H
#define LAUNCHER_DATA_H
#include "Vect2.h"
#include "Launcher.h"

class LauncherData
{
    private:
        Vect2 launcherPos;
        Launcher::LauncherType type;
    public:
        Launcher::LauncherType GetLauncherType() { return type; }
        Vect2 GetLauncherPos() { return launcherPos; }
        LauncherData(Launcher::LauncherType type, Vect2 launcherPos) {
            this->type = type;
            this->launcherPos = launcherPos;
        }};

#endif