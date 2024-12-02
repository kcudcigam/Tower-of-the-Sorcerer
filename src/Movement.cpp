#include "Movement.h"
#include<iostream>

Movement :: Movement(sf :: Sprite *sprite, const float &maxVelocity, const float &acceleration, const float &deceleration, const unsigned &direction)
: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), velocity(sf :: Vector2f(0.f, 0.f)), direction(direction) {

}
Movement :: ~Movement() {

}

const unsigned& Movement :: getDirection() const {
    return this -> direction;
}
const float& Movement :: getMaxVelocity() const {
    return this -> maxVelocity;
}
const sf :: Vector2f& Movement :: getVelocity() const {
    return this -> velocity;
}

void Movement :: stopVelocity(const bool &x = true, const bool &y = true) {
    if(x) this -> velocity.x = 0.f; 
    if(y) this -> velocity.y = 0.f;
}

void Movement :: move(const float &x, const float &y, const float &deltaTime) {
    auto limit = [](float &u, const float &maxVelocity) {
        u = std :: min(u,  maxVelocity);
        u = std :: max(u, -maxVelocity);
    };
    if(x != 0) this -> direction = ((this -> direction >> 1 & 1) << 1) | ((x > 0) << 2);
    if(y != 0) this -> direction = ((this -> direction >> 2 & 1) << 2) | ((y > 0) << 1) | 1;
    limit(this -> velocity.x += this -> acceleration * x * deltaTime, this -> maxVelocity);
    limit(this -> velocity.y += this -> acceleration * y * deltaTime, this -> maxVelocity);
}

void Movement :: update(const float &deltaTime) {
    auto updateSpeed = [&deltaTime](float &x, const float &deceleration) {
        const int u = (x > 0.f ? 1 : x < 0.f ? -1 : 0); x *= u;
        x -= deltaTime * deceleration; x = std :: max(x, 0.f) * u;
    };
    updateSpeed(this -> velocity.x, this -> deceleration);
    updateSpeed(this -> velocity.y, this -> deceleration);
    this -> sprite -> move(this -> velocity * deltaTime);
    //std :: cerr << this -> velocity.x << ' ' << this -> velocity.y << std :: endl;
}