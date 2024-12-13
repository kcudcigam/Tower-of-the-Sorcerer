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
    std :: string playerBox, tag;
public:
    CollisionBox(const sf :: FloatRect &rect, const std :: string &playerBox, const std :: string &tag);
    virtual ~CollisionBox();
    sf :: Vector2f getCenter() const;
    const std :: string& getTag() const;
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

class Reward : public Entity {
private:
std :: string name;
    sf :: Sprite sprite;
    Animation animation;
    sf :: Vector2f position;
    float ysort, offset, dOffset;
    bool activate, opened;
public:
    Reward(const std :: string &name, const sf :: Vector2f &position, const Animation &animation, const float &ysort);
    virtual ~Reward();
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
    bool activate, challenged, beaten;
public:
    MonsterLink(const std :: string &name, const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, const float &ysort);
    virtual ~MonsterLink();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y, const bool &flag) const;
};

class Entrance : public Entity {
private:
    sf :: Sprite sprite;
    std :: vector<CollisionBox> boxList;
    Animation animation;
    float ysort;
    bool opened, forward, activate, opening;
public:
    Entrance(const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, bool forward);
    virtual ~Entrance();
    void update(Player &player, const float &deltaTime);
    void render(sf :: RenderTarget *target, const float &y, const bool &flag) const;
};