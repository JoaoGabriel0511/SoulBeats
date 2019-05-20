#include "Rect.h"
#include "Vect2.h"

#include <algorithm>
#include <cmath>

class Collision {

	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
			Vect2 A[] = { Vect2( a.x, a.y + a.h ),
						  Vect2( a.x + a.w, a.y + a.h ),
						  Vect2( a.x + a.w, a.y ),
						  Vect2( a.x, a.y )
						};
			Vect2 B[] = { Vect2( b.x, b.y + b.h ),
						  Vect2( b.x + b.w, b.y + b.h ),
						  Vect2( b.x + b.w, b.y ),
						  Vect2( b.x, b.y )
						};

			for (auto& v : A) {
				v = Rotate(v - a.GetCenter(), angleOfA) + a.GetCenter();
			}

			for (auto& v : B) {
				v = Rotate(v - b.GetCenter(), angleOfB) + b.GetCenter();
			}

			Vect2 axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB) {
					return false;
				}
			}
			return true;
		}

	private:
		static inline float Mag(const Vect2& p) {
			return std::sqrt(p.x * p.x + p.y * p.y);
		}

		static inline Vect2 Norm(const Vect2& p) {
			return p * (1.f / Mag(p));
		}

		static inline float Dot(const Vect2& a, const Vect2& b) {
			return a.x * b.x + a.y * b.y;
		}

		static inline Vect2 Rotate(const Vect2& p, float angle) {
			float cs = std::cos(angle), sn = std::sin(angle);
			return Vect2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
		}
};

// Aqui estão três operadores que sua classe Vec2 deve precisar, se já não tiver. 
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }