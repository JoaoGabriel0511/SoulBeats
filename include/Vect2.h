#ifndef VECT2_H
#define VECT2_H
#include <math.h>
#include <iostream>
#include "Rect.h"
using namespace std;
class Rect;
class Vect2{
    public:
        Vect2();
        Vect2(float x, float y);
        ~Vect2();
        Vect2 GetRotated(float nro);
        float x;
        float y;
        float Length();
        float DistanceTo(Vect2 vect);
        Vect2 Normalize();
        Vect2 Rotate(float angle);
        Rect operator+(Rect rect);
        Rect operator-(Rect rect);
        Vect2 operator+(Vect2 vet);
        Vect2 operator-(Vect2 vet);
        Vect2 operator*(const float &right) const;
        Vect2 operator*(float nro);
        bool operator==(Vect2 vet);
        static inline Vect2 Rotate(const Vect2& p, float angle) {
			float cs = cos(angle);
            float sn = sin(angle);
			return Vect2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
		}
};
#endif