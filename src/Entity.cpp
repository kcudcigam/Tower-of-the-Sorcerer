#include "Entity.h"
//Entity
Entity :: Entity() {

}
Entity :: ~Entity() {

}

//Collisionbox
Collisionbox :: Collisionbox(const sf :: FloatRect &rect) : rect(rect) {

}
Collisionbox :: ~Collisionbox() {

}
void Collisionbox :: update(Player &player, const float &deltaTime) {
    const auto &position = player.getPosition();
    if(!position.intersects(rect)) return;
    const std :: pair<float, float> dx = {position.left + position.width - rect.left, rect.left + rect.width - position.left};
    const std :: pair<float, float> dy = {position.top + position.height - rect.top, rect.top + rect.height - position.top};
    if(std :: min(dx.first, dx.second) < std :: min(dy.first, dy.second)) {
        if(dx.first < dx.second) player.setPosition({rect.left - position.width, position.top});
        else player.setPosition({rect.left + rect.width, position.top});
        player.stopVelocity(true, false);
    }
    else {
        if(dy.first < dy.second) player.setPosition({position.left, rect.top - position.height});
        else player.setPosition({position.left, rect.top + rect.height});
        player.stopVelocity(false, true);
    }
}
void Collisionbox :: render(sf :: RenderTarget *target) const {
    sf :: RectangleShape outline;
    outline.setPosition({rect.left, rect.top});
    outline.setSize({rect.width, rect.height});
    outline.setFillColor(sf :: Color :: Transparent);
    outline.setOutlineThickness(-1.f);
    outline.setOutlineColor(sf :: Color :: Green);
    //target -> draw(outline);
}