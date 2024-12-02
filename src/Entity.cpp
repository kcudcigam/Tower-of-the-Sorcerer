#include "Entity.h"
#include <iostream>
//constructor & destructor
Entity :: Entity() {
    this -> texture = new sf :: Texture();
    this -> texture -> loadFromFile("../res/PLAYER_SHEET.png");
    this -> sprite = new sf :: Sprite();
    this -> movement = new Movement(this -> sprite, 400.f, 2000.f, 1000.f);
    this -> animation = new AnimationSet(this -> sprite);
    this -> animation -> insert("IDLE", Animation(this -> texture, 0.05f, RectQueue(sf :: Vector2i(0, 0), sf :: Vector2i(13, 0), sf :: Vector2i(192, 192)), true), sf :: Vector2f(0.f, 258.f));
    this -> animation -> insert("WALK", Animation(this -> texture, 0.05f, RectQueue(sf :: Vector2i(0, 1), sf :: Vector2i(11, 1), sf :: Vector2i(192, 192)), true), sf :: Vector2f(0.f, 258.f));
    this -> animation -> insert("ATTACK", Animation(this -> texture, 0.05f, RectQueue(sf :: Vector2i(0, 2), sf :: Vector2i(14, 2), sf :: Vector2i(384, 192)), false), sf :: Vector2f(88.f, 348.f));
    this -> hitbox = new Hitbox(this -> sprite, sf :: Vector2f(86.f, 61.f), sf :: Vector2f(86.f, 111.f));
}
Entity :: ~Entity() {
    delete this -> texture;
    delete this -> sprite;
    delete this -> movement;
    delete this -> animation;
}

//funtionss
void Entity :: update(const float& deltaTime) {

    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: A) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left))
        this -> movement -> move(-1.f,  0.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: D) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right))
        this -> movement -> move(1.f,  0.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: W) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Up))
        this -> movement -> move(0.f, -1.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: S) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Down))
        this -> movement -> move(0.f,  1.f, deltaTime);
    this -> movement -> update(deltaTime);

    //std :: cerr << (this -> movement -> getDirection() >> 2 & 1) << ' ' << (this -> movement -> getDirection() >> 1 & 1) << std :: endl;
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: J))
        this -> animation -> setPriority("ATTACK", this -> movement -> getDirection() >> 2 & 1);
    if(this -> movement -> getVelocity() != sf :: Vector2f(0.f, 0.f))
        this -> animation -> play("WALK", deltaTime, this -> movement -> getDirection() >> 2 & 1);
    else this -> animation -> play("IDLE", deltaTime, this -> movement -> getDirection() >> 2 & 1);

    this -> hitbox -> update();
}
void Entity :: render(sf :: RenderTarget* target) {
    target -> draw(*this -> sprite);
    this -> hitbox -> render(target);
}