#include "Player.h"
#include <iostream>
//constructor & destructor
Player :: Player(Resource* resource) : resource(resource), movement(&sprite, 160.f, 600.f, 300.f), hitbox(&sprite, sf :: Vector2f(54.f, 70.f), sf :: Vector2f(30.f, 2.f)) {
    animation.insert("IDLE_LEFT"   , Animation(generateList(this -> resource -> getImg("warrior.png"), {0, 0}, {15, 0}, {144, 96}, -1.f, {140.f, 0.f}), 0.08f, true));
    animation.insert("IDLE_RIGHT"  , Animation(generateList(this -> resource -> getImg("warrior.png"), {0, 0}, {15, 0}, {144, 96},  1.f, {0.f, 0.f}), 0.08f, true));
    animation.insert("WALK_LEFT"   , Animation(generateList(this -> resource -> getImg("warrior.png"), {0, 1}, { 7, 1}, {144, 96}, -1.f, {140.f, 0.f}), 0.08f, true));
    animation.insert("WALK_RIGHT"  , Animation(generateList(this -> resource -> getImg("warrior.png"), {0, 1}, { 7, 1}, {144, 96},  1.f, {0.f, 0.f}), 0.08f, true));
    animation.insert("ATTACK_LEFT" , Animation(generateList(this -> resource -> getImg("warrior.png"), {0, 2}, {10, 3}, {144, 96}, -1.f, {140.f, 0.f}), 0.1f, false));
    animation.insert("ATTACK_RIGHT", Animation(generateList(this -> resource -> getImg("warrior.png"), {0, 2}, {10, 3}, {144, 96},  1.f, {0.f, 0.f}), 0.1f, false));
    sprite.setPosition({192.f, 192.f});
}
Player :: ~Player() {
}
//funtions
sf :: FloatRect Player :: getPosition() const {
    return sf :: FloatRect(hitbox.getPosition(), hitbox.getSize());
}
void Player :: setPosition(const sf :: Vector2f &position) {
    sprite.setPosition(position - hitbox.getOffset());
}
void Player :: stopVelocity(const bool &x, const bool &y) {
    movement.stopVelocity(x, y);
}
void Player :: update(const float& deltaTime) {

    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: A) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Left))
        movement.move(-1.f,  0.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: D) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Right))
        movement.move(1.f,  0.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: W) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Up))
        movement.move(0.f, -1.f, deltaTime);
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: S) || sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: Down))
        movement.move(0.f,  1.f, deltaTime);
    movement.update(deltaTime);

    //std :: cerr << (this -> movement -> getVelocity().x) << ' ' << (this -> movement -> getVelocity().y) << std :: endl;
    if(sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: J)) {
        if(movement.getDirection() >> 2 & 1)
            animation.setPriority("ATTACK_RIGHT");
        else animation.setPriority("ATTACK_LEFT");
    }
    if(movement.getVelocity() != sf :: Vector2f(0.f, 0.f)) {
        if(movement.getDirection() >> 2 & 1)
            animation.play(&sprite, "WALK_RIGHT", deltaTime);
        else  animation.play(&sprite, "WALK_LEFT", deltaTime);
    }
    else {
        if(movement.getDirection() >> 2 & 1)
            animation.play(&sprite, "IDLE_RIGHT", deltaTime);
        else animation.play(&sprite, "IDLE_LEFT", deltaTime);
    }
}
void Player :: render(sf :: RenderTarget* target) const {
    target -> draw(this -> sprite);
    hitbox.render(target);
}