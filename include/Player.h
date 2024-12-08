#pragma once
#include <cmath>
#include "SFML/Graphics.hpp"
#include "Resource.h"
#include "Animation.h"

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

class Hitbox {
private:
	sf :: Sprite* sprite;
	sf :: FloatRect box;
	sf :: Vector2f offset;
public:
	Hitbox(sf::Sprite *sprite, const sf :: Vector2f &offset = sf :: Vector2f(0.f, 0.f), const sf :: Vector2f &size = sf :: Vector2f(0.f, 0.f));
	virtual ~Hitbox();
	sf :: Vector2f getPosition() const;
	sf :: Vector2f getOffset() const;
	sf :: Vector2f getSize() const;
	void render(sf :: RenderTarget *target) const;
};

class Player {
private:
    sf :: Sprite sprite;
    Movement movement;
    AnimationSet animation;
    Hitbox hitbox;
public:
    Player();
    virtual ~Player();
    Hitbox& getHitbox();
    sf :: FloatRect getPosition() const;
    void setPosition(const sf :: Vector2f &position);
    void stopVelocity(const bool &x = true, const bool &y = true);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target) const;
};