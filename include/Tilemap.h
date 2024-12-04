#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Animation.h"
#include "Resource.h"
#include <json.hpp>

class Tile {
private:
    sf :: Sprite sprite;
    Animation animation;
public:
    Tile(const sf :: Vector2f &position = sf :: Vector2f(0.f, 0.f), const Animation &animation = Animation());
    virtual ~Tile();
    bool empty() const;
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
    void insert(const sf :: Vector2f &position, const Animation &animation);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target) const;
};

class Tilemap {
private:
    //Variables
    std :: vector<Img> imgList;
    std :: vector<Animation> animationList;
    std :: vector<Layer> layers;
public:
    //constructor & destructor
    Tilemap(Resource* resource, const std :: string &file);
    virtual ~Tilemap();
    //funtions
    void loadFromFile(const json &map, const Resource &Resource);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target) const;
};