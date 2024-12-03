#include "Entity.h"
#include <iostream>
//constructor & destructor
Entity :: Entity(Resource* resource) : resource(resource) {
    this -> sprite = new sf :: Sprite();
    this -> movement = new Movement(this -> sprite, 400.f, 2000.f, 1000.f);
    this -> animation = new AnimationSet;
    this -> animation -> insert("IDLE_LEFT"   , Animation(generateList(this -> resource -> getImg("PLAYER_SHEET.png"), {0, 0}, {13, 0}, {192, 192}), 0.05f, true));
    this -> animation -> insert("IDLE_RIGHT"  , Animation(generateList(this -> resource -> getImg("PLAYER_SHEET.png"), {0, 0}, {13, 0}, {192, 192}, -1.f, {258.f, 0.f}), 0.05f, true));
    this -> animation -> insert("WALK_LEFT"   , Animation(generateList(this -> resource -> getImg("PLAYER_SHEET.png"), {0, 1}, {11, 1}, {192, 192}), 0.05f, true));
    this -> animation -> insert("WALK_RIGHT"  , Animation(generateList(this -> resource -> getImg("PLAYER_SHEET.png"), {0, 1}, {11, 1}, {192, 192}, -1.f, {258.f, 0.f}), 0.05f, true));
    this -> animation -> insert("ATTACK_LEFT" , Animation(generateList(this -> resource -> getImg("PLAYER_SHEET.png"), {0, 2}, {14, 2}, {384, 192},  1.f, { 88.f, 0.f}), 0.05f, false));
    this -> animation -> insert("ATTACK_RIGHT", Animation(generateList(this -> resource -> getImg("PLAYER_SHEET.png"), {0, 2}, {14, 2}, {384, 192}, -1.f, {348.f, 0.f}), 0.05f, false));
    this -> hitbox = new Hitbox(this -> sprite, sf :: Vector2f(86.f, 61.f), sf :: Vector2f(86.f, 111.f));
}
Entity :: ~Entity() {
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

    //std :: cerr << (this -> movement -> getVelocity().x) << ' ' << (this -> movement -> getVelocity().y) << std :: endl;
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: J)) {
        if(this -> movement -> getDirection() >> 2 & 1)
            this -> animation -> setPriority("ATTACK_RIGHT");
        else this -> animation -> setPriority("ATTACK_LEFT");
    }
    if(this -> movement -> getVelocity() != sf :: Vector2f(0.f, 0.f)) {
        if(this -> movement -> getDirection() >> 2 & 1)
            this -> animation -> play(this -> sprite, "WALK_RIGHT", deltaTime);
        else this -> animation -> play(this -> sprite, "WALK_LEFT", deltaTime);
    }
    else {
        if(this -> movement -> getDirection() >> 2 & 1)
            this -> animation -> play(this -> sprite, "IDLE_RIGHT", deltaTime);
        else this -> animation -> play(this -> sprite, "IDLE_LEFT", deltaTime);
    }

    this -> hitbox -> update();
}
void Entity :: render(sf :: RenderTarget* target) {
    target -> draw(*this -> sprite);
    this -> hitbox -> render(target);
}