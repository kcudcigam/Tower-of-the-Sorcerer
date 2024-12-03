#include "Hitbox.h"

Hitbox :: Hitbox(sf::Sprite *sprite, const sf :: Vector2f &offset, const sf :: Vector2f &size) : sprite(sprite), offset(offset) {
    this -> outline.setPosition(this -> sprite -> getPosition() + offset);
    this -> outline.setSize(size);
    this -> outline.setFillColor(sf :: Color :: Transparent);
    this -> outline.setOutlineThickness(-1.f);
    this -> outline.setOutlineColor(sf :: Color :: Green);
}
Hitbox :: ~Hitbox() {

}

const sf :: Vector2f& Hitbox :: getPosition() const {
	return this -> outline.getPosition();
}
/*
const sf::FloatRect HitboxComponent::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}*/


void Hitbox :: setPosition(const sf::Vector2f &position) {
	this -> outline.setPosition(position);
	this -> sprite -> setPosition(position - offset);
}


bool Hitbox :: intersects(const sf :: FloatRect &rect) {
    if(this -> outline.getSize() == sf :: Vector2f(0.f, 0.f)) return false;
	return this -> outline.getGlobalBounds().intersects(rect);
}
void Hitbox :: update() {
	this -> outline.setPosition(this -> sprite -> getPosition() + offset);
}
void Hitbox :: render(sf :: RenderTarget *target) {
    if(target != nullptr && this -> outline.getSize() != sf :: Vector2f(0.f, 0.f)) target -> draw(this -> outline);
}
