#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
class Entity {
public:
    Entity();
    virtual ~Entity();
    virtual void update(Player &player, const float &deltaTime) = 0;
    virtual void render(sf :: RenderTarget *target) const = 0;
};
class Collisionbox : public Entity {
private:
    sf :: FloatRect rect;
public:
    Collisionbox(const sf :: FloatRect &rect);
    virtual ~Collisionbox();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target) const;
};