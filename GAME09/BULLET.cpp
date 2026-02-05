#include "BULLET.h"
#include "../../libOne/inc/graphic.h"


BULLET::BULLET(float x, float y) : x(x), y(y), dead(false) {}

void BULLET::update() {
    y -= 10;
    if (y < 0) dead = true;
}

void BULLET::draw() {
    fill(255, 255, 0);
    rect(x, y, 4, 10);
}

bool BULLET::isOut() const {
    return dead;
} 

float BULLET::getX() const { return x; }
float BULLET::getY() const { return y; }

void BULLET::setDead() { dead = true; }
bool BULLET::isDead() const { return dead; }
