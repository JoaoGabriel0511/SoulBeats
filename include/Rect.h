#ifndef RECT_H
#define RECT_H
#include "Vect2.h"
class Vect2;
class Rect {
    public:
        Rect();
        Rect(int x, int y, int w, int h);
        ~Rect();
        Rect operator+(Vect2 vect);
        Rect operator-(Vect2 vect);
        Rect operator+(Rect rect);
        Rect operator-(Rect rect);
        void operator+=(Vect2 vect);
        void operator-=(Vect2 vect);
        float x;
        float y;
        int z;
        int w;
        int h;
        bool Contains(float mouseX, float mouseY);
        Vect2 GetCenter();
};
#endif

