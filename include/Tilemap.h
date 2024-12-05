#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Animation.h"
#include "Resource.h"
#include "Entity.h"
#include "json.hpp"

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
    void  afterRender(sf :: RenderTarget* target, const float &playerY) const;
};

class Tilemap {
private:
    //Variables
    Player player;
    std :: vector<Layer> layers;
    std :: vector<Entity*> entities;

public:
    //constructor & destructor
    Tilemap(Resource* resource, const std :: string &file);
    virtual ~Tilemap();
    //funtions
    void loadFromFile(const json &map, const Resource &Resource);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target) const;
};