#include "Entity.h"
extern Resource resource;
extern Subtitle subtitle;

//Entity
Entity :: Entity() {

}
Entity :: ~Entity() {

}

//CollisionBox
CollisionBox :: CollisionBox(const sf :: FloatRect &rect) : rect(rect) {

}
CollisionBox :: ~CollisionBox() {

}
sf :: Vector2f CollisionBox :: getCenter() const {
    return sf :: Vector2f(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
}
void CollisionBox :: update(Player &player, const float &deltaTime) {
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
void CollisionBox :: render(sf :: RenderTarget *target, const float &y) const {
    /*
    sf :: RectangleShape outline;
    outline.setPosition({rect.left, rect.top});
    outline.setSize({rect.width, rect.height});
    outline.setFillColor(sf :: Color :: Transparent);
    outline.setOutlineThickness(-1.f);
    outline.setOutlineColor(sf :: Color :: Green);
    target -> draw(outline);
    */
}

//Treasure
const float dTreasure = 35.f;
Treasure :: Treasure(const sf :: Vector2f &position, const std :: vector<CollisionBox*> &boxList, const float &ysort)
 : boxList(boxList), activate(false), opened(false), display(false), ysort(ysort) {
    sprite.setPosition(position);
    animation = resource.getEntity("treasure").getAnimation("open");
    animation.pause();
}
Treasure :: ~Treasure() {

}
void Treasure :: update(Player &player, const float &deltaTime) {
    for(auto box : boxList) box -> update(player, deltaTime);
    if(!opened) {
        const sf :: Vector2f &position = boxList.back() -> getCenter();
        auto len = [](const sf :: Vector2f &u) {
            return sqrtf(u.x * u.x + u.y * u.y);
        };
        if(len(position - player.getCenter()) < dTreasure) {
            subtitle.display(L"按F键打开宝箱", 0.1f);
            activate = true;
        }
        else activate = false;
        if(activate && sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: F))
            animation.run(), opened = true;
    }
    if(animation.end() && !display) {
        subtitle.display(L"获得一把宝剑, 攻击力大幅提升", 1.6f);
        display = true;
    }
    animation.play(&sprite, deltaTime);
}
void Treasure :: render(sf :: RenderTarget *target, const float &y) const {
    if(ysort < y) return;
    target -> draw(sprite);
}