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

const sf :: Vector2f& Movement :: getVelocity() const {
    return this -> velocity;
}

void Movement :: stopVelocity(const bool &x = true, const bool &y = true) {
    if(x) this -> velocity.x = 0.f; 
    if(y) this -> velocity.y = 0.f;
}

void Movement :: move(const float &x, const float &y, const float &deltaTime) {
    auto limit = [](float &u, float &v, const float &maxVelocity) {
        u = std :: min(u,  maxVelocity); u = std :: max(u, -maxVelocity);
        const float &w = std :: sqrt(maxVelocity * maxVelocity - u * u);
        v = std :: min(v, w); v = std :: max(v, -w);
    };
    if(x != 0) direction = ((this -> direction >> 1 & 1) << 1) | ((x > 0) << 2);
    if(y != 0) direction = ((this -> direction >> 2 & 1) << 2) | ((y > 0) << 1) | 1;
    velocity.x += acceleration * x * deltaTime;
    velocity.y += acceleration * y * deltaTime;
}

void Movement :: update(const float &deltaTime) {
    const float &d = std :: sqrt(velocity.x * velocity.x + velocity.y * velocity.y) / maxVelocity;
    if(d > 1.f) velocity /= d;  
    auto updateSpeed = [&deltaTime](float &x, const float &deceleration) {
        const int u = (x > 0.f ? 1 : x < 0.f ? -1 : 0); x *= u;
        x -= deltaTime * deceleration; x = std :: max(x, 0.f) * u;
    };
    updateSpeed(this -> velocity.x, this -> deceleration);
    updateSpeed(this -> velocity.y, this -> deceleration);
    this -> sprite -> move(this -> velocity * deltaTime);
    //std :: cerr << this -> velocity.x << ' ' << this -> velocity.y << std :: endl;
}