#ifndef RECT_H
#define RECT_H
#include "Vect2.h"
class Vect2;
class Rect {
    public:
        Rect();
        ~Rect();
        Rect operator+(Vect2 vect);
        Rect operator-(Vect2 vect);
        void operator+=(Vect2 vect);
        void operator-=(Vect2 vect);
        int x;
        int y;
        int z;
        int w;
        int h;
        bool Contains(float mouseX, float mouseY);
        Vect2 GetCenter();
};
#endif

