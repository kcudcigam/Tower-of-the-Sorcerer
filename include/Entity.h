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
bool checkCollision(Player &player, const sf :: FloatRect &rect);
class Tilebox : public Entity {
private:
    sf :: FloatRect rect;
public:
    Tilebox(const sf :: FloatRect &rect);
    virtual ~Tilebox();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target) const;
};