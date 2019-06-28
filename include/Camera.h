#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include "GameInfo.h"
#include "Vect2.h"
class GameObject;
class Camera {
    static GameObject * focus;
    public:
        static void Follow(GameObject * newFocus);
        static void UnFollow();
        static void Update(float dt);
        static bool IsOnCamera(Rect box);
        static bool IsOnCamera(Rect box, float paralaxX, float paralaxY);
        static Vect2 pos;
        static Vect2 speed;
        static bool debug;
        static bool followX;
        static bool followY;
};

#endif