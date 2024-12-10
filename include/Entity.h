#pragma once
#include "SFML/Graphics.hpp"
#include "Resource.h"
#include "Subtitle.h"
#include "Player.h"

class Entity {
public:
    Entity();
    virtual ~Entity();
    virtual void update(Player &player, const float &deltaTime) = 0;
    virtual void render(sf :: RenderTarget *target, const float &y) const = 0;
};

class CollisionBox : public Entity {
private:
    sf :: FloatRect rect;
public:
    CollisionBox(const sf :: FloatRect &rect);
    virtual ~CollisionBox();
    sf :: Vector2f getCenter() const;
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y) const;
};

class Treasure : public Entity {
private:
    sf :: Sprite sprite;
    std :: vector<CollisionBox*> boxList;
    Animation animation;
    float ysort;
    bool activate, opened, display;
public:
    Treasure(const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox*> &boxList, const float &ysort);
    virtual ~Treasure();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y) const;
};

class Door : public Entity {
private:
    sf :: Sprite sprite;
    std :: vector<CollisionBox*> boxList;
    Animation animation;
    float ysort;
    bool activate, opened, display;
public:
    Door(const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox*> &boxList, const float &ysort);
    virtual ~Door();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y) const;
};

class MonsterLink : public Entity {
private:
    std :: string name;
    sf :: Sprite sprite;
    std :: vector<CollisionBox*> boxList;
    Animation animation;
    float ysort;
    bool activate, challenged;
public:
    MonsterLink(const std :: string &name, const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox*> &boxList, const float &ysort);
    virtual ~MonsterLink();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y) const;
};