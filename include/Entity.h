#pragma once
#include <SFML/Graphics.hpp>
#include "Movement.h"
#include "Animation.h"
#include "Hitbox.h"
#include "Resource.h"

class Entity {
private:
    //Variables
    sf :: Sprite* sprite;
    Movement* movement;
    AnimationSet* animation;
    Hitbox* hitbox;
    Resource* resource;
public:
    //constructor & destructor
    Entity(Resource* resource);
    virtual ~Entity();
    //funtions
    virtual void update(const float& deltaTime);
    virtual void render(sf :: RenderTarget* target);
};