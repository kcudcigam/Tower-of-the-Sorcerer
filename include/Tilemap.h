#pragma once
#include <SFML/Graphics.hpp>
#include "Hitbox.h"
#include "Animation.h"

class Tile {
private:
    sf :: Sprite sprite;
    Animation animation;
    Hitbox hitbox;
public:
    Tile(const sf :: Vector2f &position, const Animation &animation, const Hitbox &hitbox);
    virtual ~Tile();
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target);
};

/*
class Tilemap {
private:
    //Variables
    std :: vector<sf :: Texture*> texture;
    std :: vector<Tile> tiles;
public:
    //constructor & destructor
    Tilemap();
    virtual ~Tilemap();
    //funtions
    virtual void update(const float& deltaTime);
    virtual void render(sf :: RenderTarget* target);
};
*/