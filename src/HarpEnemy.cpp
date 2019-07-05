#include "../include/HarpEnemy.h"

HarpEnemy::HarpEnemy(GameObject &associated, int movingDistance, int movingSpeed, GameObject *character, int index, bool moveX,
                     bool moveY) : Component(associated)
{
    this->character = character;
    Collider *collider;
    this->index = index;
    this->moveX = moveX;
    this->moveY = moveY;
    //initalPos = associated.box;
    collider = new Collider(associated, {2, 2}, {-70, -80});
}

bool HarpEnemy::Is(string type)
{
    bool result = false;
    if (type == "HarpEnemy")
    {
        result = true;
    }
    return result;
}

void HarpEnemy::Start()
{
    state = LOOKING_UP;
    hp = 3;
    switchSides.Restart();
    sound = new Sound(associated, HARP_SOUND);
    harpEnemySprite = new Sprite(associated, ENEMY_IDLE_SPRITE, ENEMY_IDLE_FRAME_COUNT, ENEMY_IDLE_DURATION / ENEMY_IDLE_FRAME_COUNT);
    harpEnemySprite->SetScale({2, 2});
    velocity = {-1 * ENEMY_VELOCITY_X, -1 * ENEMY_VELOCITY_Y};
    lifeBar = new GameObject();
    lifeBarSprite = new Sprite(*lifeBar, FULL_LIFE_BAR);
    lifeBarSprite->SetScale({2,2});
    lifeBar->box.x = associated.box.x + 35;
    lifeBar->box.y = associated.box.y - 20;
    lifeBar->box.z = 5;
    Game::GetInstance().GetCurrentStatePointer()->AddObject(lifeBar);
}

void HarpEnemy::Update(float dt)
{
	if(moveY) {
		switch (state) {
			case LOOKING_DOWN:
				lookDown.Update(dt);
				if (lookDown.Get() >= ENEMY_LOOKING_DOWN_DURATION) {
					velocity.y = -1 * ENEMY_VELOCITY_Y;
					if (Camera::IsOnCamera(associated.box)) {
						sound->Play(1);
					}
					SwitchHarpEnemyState(LOOKING_UP, ENEMY_LOOKING_UP_SPRITE, ENEMY_LOOKING_UP_FRAME_COUNT,
					                     ENEMY_LOOKING_UP_FRAME_TIME, &lookUp);
				}
				break;
			case LOOKING_UP:
				lookUp.Update(dt);
				if (lookUp.Get() >= ENEMY_LOOKING_UP_DURATION) {
					velocity.y = ENEMY_VELOCITY_Y;
					if (Camera::IsOnCamera(associated.box)) {
						sound->Play(1);
					}
					SwitchHarpEnemyState(LOOKING_DOWN, ENEMY_LOOKING_DOWN_SPRITE, ENEMY_LOOKING_DOWN_FRAME_COUNT,
					                     ENEMY_LOOKING_UP_FRAME_TIME, &lookDown);
				}
				break;
			default:
				break;
		}
	}
    if(moveX) {
	    switchSides.Update(dt);
	    if (switchSides.Get() >= ENEMY_SWITCH_SIDES_TIME) {
		    if (Camera::IsOnCamera(associated.box)) {
			    sound->Play(1);
		    }
		    switchSides.Restart();
		    if (harpEnemySprite->flip) {
			    harpEnemySprite->flip = false;
			    velocity.x = -1 * ENEMY_VELOCITY_X;
		    } else {
			    harpEnemySprite->flip = true;
			    velocity.x = ENEMY_VELOCITY_X;
		    }
	    }
    }
    lifeBar->box.x = associated.box.x + 35;
    lifeBar->box.y = associated.box.y - 20;
    if(moveX) {
	    associated.box.x += velocity.x;
    }
    if(moveY) {
	    associated.box.y += velocity.y;
    }
}

void HarpEnemy::SwitchHarpEnemyState(HarpEnemyState state, string sprite, int frameCount, float frameTime, Timer *timer)
{
    harpEnemySprite->SwitchSprite(sprite, frameCount, frameTime);
    timer->Restart();
    this->state = state;
}

void HarpEnemy::Render() {}

void HarpEnemy::NotifyCollision(GameObject &other)
{
    if (other.GetComponent("Attack") != NULL)
    {
        sound->Open(ENEMY_HIT_SOUND);
        sound->Play(1);
        if(((Character*) character->GetComponent("Character").get())->AttackOnBeat()) {
            hp=0;
        } else {
            hp--;
        }
        if(hp == 1) {
            lifeBarSprite->SwitchSprite(ONE_THIRD_LIFE_BAR, 1, 0);
        }
        if(hp == 2) {
            lifeBarSprite->SwitchSprite(TWO_THIRDS_LIFE_BAR, 1, 0);
        }
        if(hp <= 0) {
            LevelData::GetInstance().enemyData[index]->wasKilled = true;
            associated.RequestedDelete();
        }
        if(hp > 0) {
            ((Character*) character->GetComponent("Character").get())->HitKnockBack();
        }
        sound->Open(HARP_SOUND);
    }
}

HarpEnemy::~HarpEnemy()
{
    lifeBar->RequestedDelete();
    character = NULL;
}