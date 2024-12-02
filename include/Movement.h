#pragma once
#include <SFML/Graphics.hpp>
class Movement {
private:
    sf :: Sprite *sprite;
    float maxVelocity, acceleration, deceleration;
    sf :: Vector2f velocity;
    unsigned direction;
public:
    Movement(sf :: Sprite *sprite, const float &maxVelocity, const float &acceleration, const float &deceleration, const unsigned &direction = 0);
    virtual ~Movement();  

    const unsigned& getDirection() const;
    const float& getMaxVelocity() const;
    const sf :: Vector2f& getVelocity() const;
    
    void stopVelocity(const bool &x, const bool &y);
    void move(const float &x, const float &y, const float &deltaTime);
    void update(const float &deltaTime);
};
