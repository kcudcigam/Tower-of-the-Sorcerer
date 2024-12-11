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
    virtual void render(sf :: RenderTarget *target, const float &y, const bool &flag) const = 0;
};

class CollisionBox : public Entity {
private:
    sf :: FloatRect rect;
    std :: string playerBox;
public:
    CollisionBox(const sf :: FloatRect &rect, const std :: string &playerBox = "groundHitbox");
    virtual ~CollisionBox();
    sf :: Vector2f getCenter() const;
    const sf :: FloatRect& getBox() const;
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y, const bool &flag) const;
};

class Treasure : public Entity {
private:
    sf :: Sprite sprite;
    std :: vector<CollisionBox> boxList;
    Animation animation;
    float ysort;
    bool activate, opened, display;
public:
    Treasure(const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, const float &ysort);
    virtual ~Treasure();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y, const bool &flag) const;
};

class Door : public Entity {
private:
    sf :: Sprite sprite;
    std :: vector<CollisionBox> boxList;
    Animation animation;
    float ysort;
    bool activate, opened, display;
public:
    Door(const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, const float &ysort);
    virtual ~Door();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y, const bool &flag) const;
};

class MonsterLink : public Entity {
private:
    std :: string name;
    sf :: Sprite sprite;
    std :: vector<CollisionBox> boxList;
    Animation animation;
    float ysort;
    bool activate, challenged;
public:
    MonsterLink(const std :: string &name, const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, const float &ysort);
    virtual ~MonsterLink();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y, const bool &flag) const;
};