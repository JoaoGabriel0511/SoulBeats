#include "../include/Vect2.h"

Vect2::Vect2(float x, float y) {
    this->x = x;
    this->y = y;
}

Vect2::Vect2() {
    this->x = 0;
    this->y = 0;
}

Vect2::~Vect2() {}

Vect2 Vect2::GetRotated(float angle){
    int value_x = this->x;
    int value_y = this->y;
    x = value_x * cos(angle) - value_y * sin(angle);
    y = value_y * cos(angle) + value_x * sin(angle);
    return Vect2(x,y);
}

Vect2 Vect2::operator+(Vect2 vet) {
    Vect2 result;
    result.x = this->x + vet.x;
    result.y = this->y + vet.y;
    return result;
}

Vect2 Vect2::operator-(Vect2 vet) {
    Vect2 result;
    result.x = this->x - vet.x;
    result.y = this->y - vet.y;
    return result;
}

Vect2 Vect2::operator*(float nro) {
    Vect2 result;
    result.x = this->x * nro;
    result.y = this->y * nro;
    return result;
}

Vect2 Vect2::operator*(const float &right) const {
    Vect2 result;
    result.x = this->x * right;
    result.y = this->y * right;
    return result;
}

float Vect2::Length() {
    float result;
    result = sqrt(this->x * this->x + this->y * this->y);
    return result;
}

float Vect2::DistanceTo(Vect2 vect) {
    float result;
    Vect2 aux;
    aux = vect - *this;
    result = aux.Length();
    return result;
}

bool Vect2::operator==(Vect2 vet) {
    bool result = false;
    if(this->x == vet.x && this->y == vet.y) {
        result = true;
    }
    return result;
}

Vect2 Vect2::Normalize() {
    Vect2 result;
    result.x = this->x / this->Length();
    result.y = this->y / this->Length();
    return result;
}

Vect2 Vect2::Rotate(float angle){
    Vect2 result;
    result.x = this->x + this->x * cos(angle);
    result.y = this->y + this->y * sin(angle);
}

Rect Vect2::operator+(Rect rect) {
    Rect result;
    result.x = this->x + rect.x;
    result.y = this->y + rect.y;
    result.w = rect.w;
    result.h = rect.h;
    result.z = rect.z;
    return result;
}

Rect Vect2::operator-(Rect rect) {
    Rect result;
    result.x = this->x - rect.x;
    result.y = this->y - rect.y;
    result.w = rect.w;
    result.h = rect.h;
    result.z = rect.z;
    return result;
}
