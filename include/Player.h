#pragma once
#include "SFML/Graphics.hpp"
#include "Resource.h"
#include "Animation.h"
#include "Attribute.h"

class Movement {
private:
    sf :: Sprite *sprite;
    sf :: Vector2f velocity;
    float maxVelocity, acceleration, deceleration;
    bool direction, paused;
public:
    Movement(sf :: Sprite *sprite, const float &maxVelocity, const float &acceleration, const float &deceleration, const bool &direction = false);
    virtual ~Movement();  
    void setPause(bool flag);
    const bool& getDirection() const;
    const sf :: Vector2f& getVelocity() const;
    void stopVelocity(const bool &x, const bool &y);
    void move(const float &x, const float &y, const float &deltaTime);
    void update(const float &deltaTime);
};

class Player {
private:
    sf :: Sprite sprite;
    Movement movement;
    AnimationSet animation;
    Attribute attribute;
    std :: map<std :: string, float> tags;
    std :: map<std :: string, sf :: FloatRect> hitbox;
    std :: string battle;
    void updateTag(const float &deltaTime);
    void addEffect(const std :: string &tag);
    void delEffect(const std :: string &tag);
public:
    Player(const Attribute &attribute);
    virtual ~Player();
    sf :: FloatRect getHitbox(const std :: string &type) const;
    const Attribute& getAttribute() const;
    const sf :: Vector2f& getPosition() const;
    const std :: string& getBattle() const;
    Attribute& attributeReference();
    Animation getAnimation(const std :: string &key) const;
    void setBattle(const std :: string &monster);
    void initAnimation();
    void addTag(const std :: string &tag, const float &duration);
    void insertAnimation(const std :: string &key, const Animation &animation);
    void setHitbox(const std :: string &type, const sf :: Vector2f &position, const sf :: Vector2f &size);
    void setPosition(const sf :: Vector2f &position);
    void setHitboxPosition(const std :: string &type, const sf :: Vector2f &position);
    void stopVelocity(const bool &x = true, const bool &y = true);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target) const;
};