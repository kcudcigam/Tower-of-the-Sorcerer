#include "Hitbox.h"

Hitbox :: Hitbox(sf::Sprite *sprite, const sf :: Vector2f &offset, const sf :: Vector2f &size) : sprite(sprite), box(offset, size) {
    
}
Hitbox :: ~Hitbox() {

}

sf :: Vector2f Hitbox :: getPosition() const {
	return box.getPosition() + sprite -> getPosition();
}
sf :: Vector2f Hitbox :: getOffset() const {
	return box.getPosition();
}
sf :: Vector2f Hitbox :: getSize() const {
	return box.getSize();
}

void Hitbox :: render(sf :: RenderTarget *target) const {
    sf :: RectangleShape outline;
    outline.setPosition(this -> getPosition());
    outline.setSize(this -> getSize());
    outline.setFillColor(sf :: Color :: Transparent);
    outline.setOutlineThickness(-1.f);
    outline.setOutlineColor(sf :: Color :: Green);
    //target -> draw(outline);
}
