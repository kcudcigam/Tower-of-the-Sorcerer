#pragma once
#include "SFML/Graphics.hpp"
#include "Json.hpp"
#include "Resource.h"
#include "Player.h"
#include "Entity.h"

class Tile {
private:
    sf :: Sprite sprite;
    Animation animation;
    float ysort;
public:
    Tile(const sf :: Vector2f &position = sf :: Vector2f(0.f, 0.f), const Animation &animation = Animation(), const float &ysort = 0.f);
    virtual ~Tile();
    bool empty() const;
    const float& getY() const;
    void setPosition(const sf :: Vector2f &position);
    void setAnimation(const Animation &animation);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target) const;
};

class Layer {
private:
    std :: vector<Tile> tiles;
public:
    Layer();
    virtual ~Layer();
    void ysort();
    void insert(const Tile &tile);
    void update(const float& deltaTime);
    void beforeRender(sf :: RenderTarget* target, const float &playerY) const;
    void afterRender(sf :: RenderTarget* target, const float &playerY) const;
};

class Tilemap {
private:
    Player player;
    sf :: Vector2i mapSize;
    std :: vector<Layer> layers;
    std :: vector<Entity*> entities;
public:
    Tilemap(const std :: string &file);
    virtual ~Tilemap();
    void loadFromFile(const json &map);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target) const;
};