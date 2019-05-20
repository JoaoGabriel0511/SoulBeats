#ifndef RECT_H
#define RECT_H
#include "Vect2.h"
class Rect {
    public:
        Rect();
        ~Rect();
        int x;
        int y;
        int z;
        int w;
        int h;
        bool Contains(float mouseX, float mouseY);
        Vect2 GetCenter();
};
#endif

