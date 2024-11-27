#include "Entity.h"
#include <iostream>
//constructor & destructor
Entity :: Entity() {
    this -> texture = new sf :: Texture();
    this -> texture -> loadFromFile("../res/background.png");
    this -> sprite = new sf :: Sprite(*this -> texture);
    this -> sprite -> setScale(sf :: Vector2f(0.1f, 0.1f));
    this -> position = new Movement(*this -> sprite, 420.f, 4200.f, 3000.f);
}
Entity :: ~Entity() {

}

//funtionss
void Entity :: update(const float& deltaTime) {
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: A) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left))
        this -> position -> move(-1.f,  0.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: D) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right))
        this -> position -> move(1.f,  0.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: W) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Up))
        this -> position -> move(0.f, -1.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: S) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Down))
        this -> position -> move(0.f,  1.f, deltaTime);
    this -> position -> update(deltaTime);
}
void Entity :: render(sf :: RenderTarget* target) {
    target -> draw(*this -> sprite);
}