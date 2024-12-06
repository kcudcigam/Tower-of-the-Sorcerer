#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
class Movement {
private:
    sf :: Sprite *sprite;
    sf :: Vector2f velocity;
    float maxVelocity, acceleration, deceleration;
    unsigned direction;
public:
    Movement(sf :: Sprite *sprite, const float &maxVelocity, const float &acceleration, const float &deceleration, const unsigned &direction = 0);
    virtual ~Movement();  

    const unsigned& getDirection() const;
    const sf :: Vector2f& getVelocity() const;
    
    void stopVelocity(const bool &x, const bool &y);
    void move(const float &x, const float &y, const float &deltaTime);
    void update(const float &deltaTime);
};
