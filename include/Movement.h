#pragma once
#include <SFML/Graphics.hpp>
class Movement {
private:
    sf :: Sprite *sprite;
    sf :: Vector2f maxVelocity, acceleration, deceleration, velocity;
    unsigned direction;
public:
    Movement(sf :: Sprite *sprite, const sf :: Vector2f &maxVelocity, const sf :: Vector2f &acceleration, const sf :: Vector2f &deceleration, const unsigned &direction = 0);
    virtual ~Movement();  

    const unsigned& getDirection() const;
    const sf :: Vector2f& getVelocity() const;
    
    void stopVelocity(const bool &x, const bool &y);
    void move(const float &x, const float &y, const float &deltaTime);
    void update(const float &deltaTime);
};
