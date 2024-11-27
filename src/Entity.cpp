#include "Entity.h"
#include <iostream>
//constructor & destructor
Entity :: Entity() {
    this -> texture = new sf :: Texture();
    this -> texture -> loadFromFile("../res/PLAYER_SHEET.png");
    this -> sprite = new sf :: Sprite();
    this -> position = new Movement(this -> sprite, 400.f, 2000.f, 1000.f);
    this -> animation = new AnimationSet(this -> sprite);
    this -> animation -> insert("IDLE", Animation(this -> texture, 0.05f, RectQueue(sf :: Vector2i(0, 0), sf :: Vector2i(13, 0), sf :: Vector2i(192, 192))));
}
Entity :: ~Entity() {
    delete this -> texture;
    delete this -> sprite;
    delete this -> position;
    delete this -> animation;
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
    
    this -> animation -> play("IDLE", deltaTime);
}
void Entity :: render(sf :: RenderTarget* target) {
    target -> draw(*this -> sprite);
}