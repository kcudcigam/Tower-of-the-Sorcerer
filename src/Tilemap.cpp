#include "Tilemap.h"
//Tile
Tile :: Tile(const sf :: Vector2f &position, const Animation &animation, const Hitbox &hitbox) : animation(animation), hitbox(hitbox) {
    this -> sprite.setPosition(position);
}
Tile :: ~Tile() {
    
}
void Tile :: update(const float& deltaTime) {
    this -> animation.play(&this -> sprite, deltaTime);
}
void Tile :: render(sf :: RenderTarget* target) {
    target -> draw(this -> sprite);
}