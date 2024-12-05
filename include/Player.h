#pragma once
#include <SFML/Graphics.hpp>
#include "Movement.h"
#include "Animation.h"
#include "Hitbox.h"
#include "Resource.h"

class Player {
private:
    //Variables
    sf :: Sprite sprite;
    Movement movement;
    AnimationSet animation;
    Hitbox hitbox;
    Resource* resource;
public:
    //constructor & destructor
    Player(Resource* resource);
    virtual ~Player();
    //funtions

    Hitbox& getHitbox();
    sf :: FloatRect getPosition() const;
    void setPosition(const sf :: Vector2f &position);
    void stopVelocity(const bool &x = true, const bool &y = true);
    void update(const float& deltaTime);
    void render(sf :: RenderTarget* target) const;
};