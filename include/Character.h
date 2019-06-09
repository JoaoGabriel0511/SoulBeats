#ifndef CHARACTER_H
#define CHARACTER_H
#define IDLE_SPRITE "assets/img/char/SoulBeatsCharIdleR.png"
#define WALKING_SPRITE "assets/img/char/SoulBeatsCharWalkR.png"
#define WALKING_FRAME_COUNT 8
#define WALKING_FRAME_TIME 0.08333
#define IDLE_FRAME_COUNT 8
#define IDLE_FRAME_TIME 0.08333
#define RISING_SPRITE "assets/img/char/SoulBeatsCharRiseR.png"
#define RISING_FRAME_COUNT 3
#define RISING_FRAME_TIME 0.08333
#define BEFORE_RISE_SPRITE "assets/img/char/SoulBeatsCharBeforeRiseR.png"
#define BEFORE_RISE_FRAME_COUNT 2
#define BEFORE_RISE_FRAME_TIME 0.0833
#define PEAK_SPRITE "assets/img/char/SoulBeatsCharPeakR.png"
#define PEAK_FRAME_COUNT 1
#define PEAK_FRAME_TIME 0
#define FALLING_SPRITE "assets/img/char/SoulBeatsCharFallR.png"
#define FALLING_FRAME_COUNT 4
#define FALLING_FRAME_TIME 0.08333
//#define LANDING_SPRITE "assets/img/char/SoulBeatsCharLandlR.png"
//#define LANDING_FRAME_COUNT 2
#define LANDING_FRAME_TIME 0.08333
#define BEFORE_RISE_DURATION 0.2
#define PEAK_DURATION 0.4
#define WALKING_SPEED 300
#define ATTACKING_SPEED 600
#define JUMPING_SPEED -1100
#define GRAVITY_RISING 50
#define GRAVITY_PEAK 8
#define GRAVITY_FALLING 50
#define MAX_FALL_SPEED 1500
#define LANDING_DURATION 0.08333
#define HURT_SPRITE "assets/img/char/SoulBeatsCharHurtR.png"
#define HURT_FRAME_COUNT 2
#define HURT_FRAME_TIME 0.08333
#define HURT_DURATION 0.16666
#define HURT_GRAVITY 20
#define HURT_BOUNCING_SPEED -50
#define HURT_DEFLECT_SPEED 500
#define INVINCIBILITY_DURATION 0.7
#define ENDING_INVINCIBILITY_DURATION 0.15
#define BLINKING_DURATION 0.05
#define BEFORE_ATTACK_DURATION 0.5
#define BEFORE_ATTACK_SPRITE "assets/img/char/SoulBeatsCharBeforeAttackR.png"
#define ATTACKING_SPRITE "assets/img/char/SoulBeatsCharAttackR.png"
#define ATTACKING_FRAME_COUNT 1
#define BEFORE_ATTACK_FRAME_COUNT 6
#define ATTACKING_FRAME_TIME 0.08333
#define ATTACK_DURATION 0.6
#include "Component.h"
#include "Sprite.h"
#include "Attack.h"

class Character : public Component {
  Vect2 velocity;
  Vect2 oldVelocity;
  Rect oldPosition;
  Sprite *charSprite;
  bool isOnGround;
  bool isStill;
  bool isRising;
  bool isFalling;
  bool beforeRisingDone;
  bool peakDone;
  bool isLanding;
  bool gotHit;
  bool landingDone;
  bool isInvincible;
  bool isAttacking;
  bool canAttack;
  Timer beforeRiseTimer;
  Timer recoverFromHitTimer;
  Timer peakTimer;
  Timer blinkTimer;
  Timer beforeAttackTimer;
  Timer attackTimer;
  Timer landingTimer;
  Timer invincibilityTimer;
  Timer endingInvincibilityTimer;
  float gravity;
  GameObject *attackGO;
  bool isLeftSide;
  public:
    Character(GameObject &associated);
    void Update(float dt);
    void Start();
    bool Is(string type);
    void NotifyCollision(GameObject &other);
    void NotifYCollisionWithMap(Rect Tilebox);
    bool WasNotCollinding(Rect Tilebox, Rect pastPosition);
};

#endif