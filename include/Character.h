#ifndef CHARACTER_H
#define CHARACTER_H
#define IDLE_SPRITE_RIGHT "assets/img/char/SoulBeatsCharIdleR.png"
#define IDLE_SPRITE_LEFT "assets/img/char/SoulBeatsCharIdleL.png"
#define WALKING_SPRITE_RIGHT "assets/img/char/SoulBeatsCharWalkR.png"
#define WALKING_SPRITE_LEFT "assets/img/char/SoulBeatsCharWalkCycleL.png"
#define WALKING_FRAME_COUNT 8
#define WALKING_FRAME_TIME 0.08333
#define IDLE_RIGHT_FRAME_COUNT 8
#define IDLE_LEFT_FRAME_COUNT 7
#define IDLE_FRAME_TIME 0.08333
#define RISING_RIGHT_SPRITE "assets/img/char/SoulBeatsCharRiseR.png"
#define RISING_LEFT_SPRITE "assets/img/char/SoulBeatsCharRiseL.png"
#define RISING_FRAME_COUNT 3
#define RISING_FRAME_TIME 0.08333
#define BEFORE_RISE_RIGHT_SPRITE "assets/img/char/SoulBeatsCharBeforeRiseR.png"
#define BEFORE_RISE_LEFT_SPRITE "assets/img/char/SoulBeatsCharBeforeJumpL.png"
#define BEFORE_RISE_RIGHT_SPRITE_ON_BEAT "assets/img/char/SoulBeatsCharBeforeJumpBEAT.png"
#define BEFORE_RISE_LEFT_SPRITE_ON_BEAT "assets/img/char/SoulBeatsCharBeforeJumpLBEAT.png"
#define BEFORE_RISE_FRAME_COUNT 2
#define BEFORE_RISE_FRAME_TIME 0.0833
#define PEAK_RIGHT_SPRITE "assets/img/char/SoulBeatsCharPeakR.png"
#define PEAK_LEFT_SPRITE "assets/img/char/SoulBeatsCharPeakL.png"
#define PEAK_FRAME_COUNT 1
#define PEAK_FRAME_TIME 0
#define FALLING_RIGHT_SPRITE "assets/img/char/SoulBeatsCharFallR.png"
#define FALLING_LEFT_SPRITE "assets/img/char/SoulBeatsCharFallL.png"
#define FALLING_FRAME_COUNT 4
#define FALLING_FRAME_TIME 0.08333
//#define LANDING_SPRITE "assets/img/char/SoulBeatsCharLandlR.png"
//#define LANDING_FRAME_COUNT 2
#define LANDING_FRAME_TIME 0.08333
#define BEFORE_RISE_DURATION_ON_BEAT 0.5
#define BEFORE_RISE_DURATION 0.2
#define PEAK_DURATION 0.4
#define WALKING_SPEED 400
#define WALKING_SOUND "assets/audio/SFX/Passo1.wav"
#define ON_BEAT_ATTACKING_SPEED 800
#define ATTACKING_SPEED 600
#define JUMPING_SOUND "assets/audio/SFX/PuloForte1.wav"
#define JUMPING_SOUND_ON_BEAT "assets/audio/SFX/PuloFraco1.wav"
#define JUMPING_SPEED -1130
#define JUMPING_SPEED_ON_BEAT -1380
#define GRAVITY_RISING 25
#define GRAVITY_PEAK 8
#define GRAVITY_FALLING 25
#define MAX_FALL_SPEED 1500
#define LANDING_DURATION 0.08333
#define HURT_SPRITE_RIGHT "assets/img/char/SoulBeatsCharHurtR.png"
#define HURT_SPRITE_LEFT "assets/img/char/SoulBeatsCharHurtL.png"
#define HURT_FRAME_COUNT 2
#define HURT_FRAME_TIME 0.08333
#define HURT_DURATION 0.16666
#define HURT_GRAVITY 20
#define HURT_BOUNCING_SPEED -50
#define HURT_DEFLECT_SPEED 500
#define INVINCIBILITY_DURATION 0.7
#define ENDING_INVINCIBILITY_DURATION 0.15
#define BLINKING_DURATION 0.05
#define ATTACK_SOUND "assets/audio/SFX/GolpeFraco1.wav"
#define ATTACK_SOUND_ON_BEAT "assets/audio/SFX/GolpeForte1.wav"
#define ATTACK_RIGHT_SPRITE "assets/img/char/SoulBeatsCharAttack.png"
#define ATTACK_RIGHT_SPRITE_ON_BEAT "assets/img/char/SoulBeatsCharAttackBEAT.png"
#define ATTACK_LEFT_SPRITE "assets/img/char/SoulBeatsCharAttackL.png"
#define ATTACK_LEFT_SPRITE_ON_BEAT "assets/img/char/SoulBeatsCharAttackLBEAT.png"
#define ATTACK_AIR_RIGHT_SPRITE "assets/img/char/SoulBeatsCharAttackAir.png"
#define ATTACK_AIR_RIGHT_SPRITE_ON_BEAT "assets/img/char/SoulBeatsCharAttackAirBEAT.png"
#define ATTACK_AIR_LEFT_SPRITE "assets/img/char/SoulBeatsCharAttackAirL.png"
#define ATTACK_AIR_LEFT_SPRITE_ON_BEAT "assets/img/char/SoulBeatsCharAttackAirLBEAT.png"
#define ATTACK_FRAME_COUNT 5
#define ATTACK_DURATION 0.3
#define LITSEN_TO_MUSIC_RIGHT_SPRITE "assets/img/char/SoulBeatsCharHeadbangSwordless.png"
#define LITSEN_TO_MUSIC_LEFT_SPRITE "assets/img/char/SoulBeatsCharHeadbangSwordlessLeft.png"
#define LITSEN_TO_MUSIC_FRAME_COUNT 8
#define LISTEN_TO_MUSIC_FRAME_TIME 0.08333
#define IDLE_DURATION 10
#define HIT_RECOVER_TIME 0.2
#define MAX_CHARACTER_HEIGHT 3700.00
#define DEATH_SCREEN_TIME 0.5
#define RECOVER_SPRITE_RIGHT "assets/img/char/SoulBeatsCharBounce.png"
#define RECOVER_SPRITE_RIGHT_ON_BEAT "assets/img/char/SoulBeatsCharBounceBEAT.png"
#define RECOVER_SPRITE_LEFT_ON_BEAT "assets/img/char/SoulBeatsCharBounceLeftBEAT.png"
#define RECOVER_SPRITE_LEFT "assets/img/char/SoulBeatsCharBounceL.png"
#define RECOVER_FRAME_COUNT 6
#define HIT_DEFLECT_SPEED 250
#define RECOVER_DURATION 0.5
#define WALKING_SOUND_TIMER 0.3
#include "Component.h"
#include "Sprite.h"
#include "Attack.h"
#include "LifeBar.h"

class Character : public Component {
  Vect2 velocity;
  Vect2 oldVelocity;
  Rect oldPosition;
  Sprite *charSprite;
  bool isOnGround;
  bool wasOnGround;
  bool isStill;
  bool isRising;
  bool isFalling;
  bool beforeRisingDone;
  bool peakDone;
  bool isLanding;
  bool gotHit;
  bool finishIdle;
  bool landingDone;
  bool attackOnBeat;
  bool canCancelKnockBack;
  bool isInvincible;
  bool isAttacking;
  bool hasChanged;
  bool canAttack;
  bool jumpedOnBeat;
  bool playingWalkingSound;
  bool recoveringFromHitKnockback;
  bool isDead;
  bool isLaunching;

  Timer beforeRiseTimer;
  Timer walkingSoundTimer;
  Timer recoverFromHitTimer;
  Timer peakTimer;
  Timer blinkTimer;
  Timer attackTimer;
  Timer landingTimer;
  Timer idleTimer;
  Timer invincibilityTimer;
  Timer endingInvincibilityTimer;
  Timer hitRecoverTimer;
  Timer deathTimer;

  Sound *sound;
  float gravity;
  GameObject *attackGO;
  bool isLeftSide;
  bool wasLeftSide;
  bool isOnSlope;
  void LandOnground();
  void BangUpdate(float dt);
  void IsInvincibleUpdate(float dt);
  void GotHit(float dt);
  void RecoverFromHitKnockback(float dt);
  void AttackUpdate(float dt);
  void MoveSideWays(float dt);
  void Jump(float dt);
  void DoAttack(float dt);
  void ApplyPhysics(float dt);
  void StopMovingSideWays(float dt);
  void SolidGroundCollision(Rect tileBox);
  void SolidSlope1Collision(Rect tileBox);
  void SolidSlope2Collision(Rect tileBox);
  void LightSlope1Collision(Rect tileBox);
  void LightSlope2Collision(Rect tileBox);
  void LightGroundCollision(Rect tileBox);
  int hp;
  GameObject *lifeBarGO;
  LifeBar* lifeBar;
  public:
    Character(GameObject &associated);
    void Update(float dt);
    void Start();
    bool AttackOnBeat();
    void HitKnockBack();
    void LaunchCharacter(Vect2 velocity, bool isLeftSide);
    bool Is(string type);
    void NotifyCollision(GameObject &other);
    void NotifYCollisionWithMap(Rect Tilebox);
    bool WasNotCollinding(Rect Tilebox, Rect pastPosition);
};

#endif