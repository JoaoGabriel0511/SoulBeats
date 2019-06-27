#include "../include/Collider.h"
#define PI 3.14159265
// Adicione o trecho abaixo no começo do seu Collider.cpp,
// logo após os seus includes e antes de qualquer função.

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject& associated, Vect2 scale, Vect2 offset, Vect2 posOffset) : Component(associated) {
    this->scale = scale;
    this->offset = offset;
    this->posOffset = posOffset;
}

Collider::Collider(GameObject& associated, Vect2 scale, Vect2 offset) : Component(associated) {
    this->scale = scale;
    this->offset = offset;
    this->posOffset.x = 0;
    this->posOffset.y = 0;
}

Collider::Collider(GameObject& associated) : Component(associated) {
    this->scale.x = 1;
    this->scale.y = 1;
    this->offset.x = 0;
    this->offset.y = 0;
    this->posOffset.x = 0;
    this->posOffset.y = 0;
}

void Collider::Update(float dt) {
    box = associated.box;
    box.h = box.h * scale.y;
    box.w = box.w * scale.x;
    box.w = box.w + offset.x;
    box.h = box.h + offset.y;
    box.x = (box.x - offset.x/2) + posOffset.x;
    box.y = (box.y - offset.y/2) + posOffset.y;
}

// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render() {
#ifdef DEBUG
	Vect2 center( box.GetCenter() );
	SDL_Point points[5];

	Vect2 point = (Vect2(box.x, box.y) - center) + center + Camera::pos;
	points[0].x = (int) point.x;
    points[0].y = (int) point.y;
	points[4].x = (int) point.x;
    points[4].y = (int) point.y;

	point = (Vect2(box.x + box.w, box.y) - center) + center + Camera::pos;
	points[1].x = (int) point.x;
    points[1].y = (int) point.y;

	point = (Vect2(box.x + box.w, box.y + box.h) - center) + center + Camera::pos;
	points[2].x = (int) point.x;
    points[2].y = (int) point.y;

	point = (Vect2(box.x, box.y + box.h) - center) + center + Camera::pos;
	points[3].x = (int) point.x;
    points[3].y = (int) point.y;

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(string type) {
    bool result = false;
    if(type == "Collider") {
        result = true;
    }
    return result;
}

void Collider::SetScale(Vect2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vect2 scale) {
    this->offset = offset;
}