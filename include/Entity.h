#pragma once
#include <SFML/Graphics.hpp>
#include "Movement.h"
#include "Animation.h"
#include "Hitbox.h"

class Entity {
private:
    //Variables
    sf :: Texture* texture;
    sf :: Sprite* sprite;
    Movement* movement;
    AnimationSet* animation;
    Hitbox* hitbox;
public:
    //constructor & destructor
    Entity();
    virtual ~Entity();
    //funtions
    virtual void update(const float& deltaTime);
    virtual void render(sf :: RenderTarget* target);
};