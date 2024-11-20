#pragma once
#include <SFML/Graphics.hpp>
class Entity {
protected:
    //Variables
    sf :: RectangleShape shape;
    float movementSpeed;
public:
    //constructor & destructor
    Entity();
    virtual ~Entity();
    //funtions
    virtual void move(const float &deltaTime, const float& x, const float& y);
    virtual void update(const float& deltaTime);
    virtual void render(sf :: RenderTarget* target);
};