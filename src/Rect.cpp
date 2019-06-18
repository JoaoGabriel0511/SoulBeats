#include "../include/Rect.h"
#include <iostream>
using namespace std;

bool Rect::Contains(float mouseX, float mouseY) {
    bool result = true;
    if((mouseX > x + w) || (mouseX < x) || (mouseY > y + h) || (mouseY < y)) {
        result = false;
    }
    return result;
}

Rect::Rect(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect::Rect() {
    x=0;
    y=0;
    h=0;
    w=0;
    z=0;
}

Rect::~Rect() {}

Vect2 Rect::GetCenter() {
    Vect2 result;
    result.x = x + w/2;
    result.y = y + h/2;
    return result;
}

Rect Rect::operator+(Vect2 vect) {
    Rect result;
    result.x = this->x + vect.x;
    result.y = this->y + vect.y;
    result.w = this->w;
    result.h = this->h;
    result.z = this->z;
    return result;
}

Rect Rect::operator-(Vect2 vect) {
    Rect result;
    result.x = this->x - vect.x;
    result.y = this->y - vect.y;
    result.w = this->w;
    result.h = this->h;
    result.z = this->z;
    return result;
}

Rect Rect::operator+(Rect rect) {
    Rect result;
    result.x = this->x + rect.x;
    result.y = this->y + rect.y;
    result.w = this->w;
    result.h = this->h;
    result.z = this->z;
    return result;
}

Rect Rect::operator-(Rect rect) {
    Rect result;
    result.x = this->x - rect.x;
    result.y = this->y - rect.y;
    result.w = this->w;
    result.h = this->h;
    result.z = this->z;
    return result;
}

void Rect::operator+=(Vect2 vect) {
    *this = operator+(vect);
}

void Rect::operator-=(Vect2 vect) {
    *this = operator-(vect);
}
