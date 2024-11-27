#pragma once
#include <SFML/Graphics.hpp>
#include "Movement.h"
#include "Animation.h"
class Entity {
private:
    //Variables
    sf :: Texture* texture;
    sf :: Sprite* sprite;
    Movement* position;
    AnimationSet* animation;
public:
    //constructor & destructor
    Entity();
    virtual ~Entity();
    //funtions
    virtual void update(const float& deltaTime);
    virtual void render(sf :: RenderTarget* target);
};