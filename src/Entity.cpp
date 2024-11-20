#include "Entity.h"
#include <iostream>
//constructor & destructor
Entity :: Entity() {
    this -> shape.setSize(sf :: Vector2f(50.f, 50.f));
    this -> shape.setFillColor(sf :: Color :: Green);
    this -> movementSpeed = 600.f;
}
Entity :: ~Entity() {

}

//funtions
void Entity :: move(const float &deltaTime, const float& x, const float& y) {
    std :: cerr << "Move " << x * this -> movementSpeed * deltaTime << ' ' << y * this -> movementSpeed * deltaTime << std :: endl;
    this -> shape.move(x * this -> movementSpeed * deltaTime, y * this -> movementSpeed * deltaTime);
}
void Entity :: update(const float& deltaTime) {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: A) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left))
        this -> move(deltaTime, -1.f,  0.f);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: D) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right))
        this -> move(deltaTime,  1.f,  0.f);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: W) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Up))
        this -> move(deltaTime,  0.f, -1.f);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: S) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Down))
        this -> move(deltaTime,  0.f,  1.f);
}
void Entity :: render(sf :: RenderTarget* target) {
    target -> draw(this -> shape);
}