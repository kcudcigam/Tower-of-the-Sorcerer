#include "Entity.h"
extern Resource resource;
extern Subtitle subtitle;

float len(const sf :: Vector2f &u) {
    return std :: sqrt(u.x * u.x + u.y * u.y);
}

//Entity
Entity :: Entity() {

}
Entity :: ~Entity() {

}

//CollisionBox
CollisionBox :: CollisionBox(const sf :: FloatRect &rect, const std :: string &playerBox, const std :: string &tag) : rect(rect), playerBox(playerBox), tag(tag) {

}
CollisionBox :: ~CollisionBox() {

}
const std :: string& CollisionBox :: getTag() const {
    return tag;
}
const sf :: FloatRect& CollisionBox :: getBox() const {
    return rect;
}
sf :: Vector2f CollisionBox :: getCenter() const {
    return sf :: Vector2f(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
}
void CollisionBox :: update(Player &player, const float &deltaTime) {
    const auto &hitbox = player.getHitbox(playerBox);
    if(!hitbox.intersects(rect)) return;
    if(tag != "") {player.addTag(tag, 0.3f); return;}
    const std :: pair<float, float> dx = {hitbox.left + hitbox.width - rect.left, rect.left + rect.width - hitbox.left};
    const std :: pair<float, float> dy = {hitbox.top + hitbox.height - rect.top, rect.top + rect.height - hitbox.top};
    if(std :: min(dx.first, dx.second) < std :: min(dy.first, dy.second)) {
        if(dx.first < dx.second) player.setHitboxPosition(playerBox, {rect.left - hitbox.width, hitbox.top});
        else player.setHitboxPosition(playerBox, {rect.left + rect.width, hitbox.top});
        player.stopVelocity(true, false);
    }
    else {
        if(dy.first < dy.second) player.setHitboxPosition(playerBox, {hitbox.left, rect.top - hitbox.height});
        else player.setHitboxPosition(playerBox, {hitbox.left, rect.top + rect.height});
        player.stopVelocity(false, true);
    }
    //if(tag != "") player.addTag(tag, 0.1f);
}
void CollisionBox :: render(sf :: RenderTarget *target, const float &y, const bool &flag) const {
    
    sf :: RectangleShape outline;
    outline.setPosition({rect.left, rect.top});
    outline.setSize({rect.width, rect.height});
    outline.setFillColor(sf :: Color :: Transparent);
    outline.setOutlineThickness(-1.f);
    outline.setOutlineColor(sf :: Color :: Green);
    target -> draw(outline);
    
    
}

//Treasure
const float dTreasure = 35.f;
Treasure :: Treasure(const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, const float &ysort)
 : animation(animation), boxList(boxList), activate(false), opened(false), display(false), ysort(ysort) {
    sprite.setPosition(position);
    this -> animation.pause();
}
Treasure :: ~Treasure() {

}
void Treasure :: update(Player &player, const float &deltaTime) {
    for(auto box : boxList) box.update(player, deltaTime);
    if(!opened) {
        const sf :: Vector2f &position = boxList.back().getCenter();
        
        if(len(position - player.getPosition()) < dTreasure) {
            subtitle.display(L"按F键打开宝箱", 0.1f);
            activate = true;
        }
        else activate = false;
        if(activate && sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: F))
            animation.run(), opened = true;
    }
    if(animation.end() && !display) {
        subtitle.display(L"获得一把宝剑, 攻击力得到大幅提升", 1.5f);
        display = true;
    }
    animation.play(&sprite, deltaTime);
}
void Treasure :: render(sf :: RenderTarget *target, const float &y, const bool &flag) const {
    if((y < ysort) ^ flag) return;
    target -> draw(sprite);
}

const float dDoor = 35.f;
Door :: Door(const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, const float &ysort)
 : animation(animation), boxList(boxList), activate(false), opened(false), display(false), ysort(ysort) {
    sprite.setPosition(position); this -> animation.pause();
}
Door :: ~Door() {

}
void Door :: update(Player &player, const float &deltaTime) {
    for(auto box : boxList) box.update(player, deltaTime);
    if(!opened) {
        const sf :: Vector2f &position = boxList.back().getCenter();
        if(len(position - player.getPosition()) < dDoor) {
            subtitle.display(L"按F键消耗一把钥匙打开门", 0.1f);
            activate = true;
        }
        else activate = false;
        if(activate && sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: F)) {
            animation.run(), opened = true, boxList.pop_back();
        }
    }
    if(animation.end() && !display) {
        subtitle.display(L"门已打开", 1.5f);
        display = true;
    }
    animation.play(&sprite, deltaTime);
}
void Door :: render(sf :: RenderTarget *target, const float &y, const bool &flag) const {
    //for(auto box : boxList) box -> render(target, y);
    if((y < ysort) ^ flag) return;
    target -> draw(sprite);
}


const float dMonster = 40.f;
MonsterLink :: MonsterLink(const std :: string &name, const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, const float &ysort)
 : name(name), animation(animation), boxList(boxList), activate(false), challenged(false), ysort(ysort) {
    sprite.setPosition(position);
}
MonsterLink :: ~MonsterLink() {

}
void MonsterLink :: update(Player &player, const float &deltaTime) {
    if(challenged) return;
    for(auto box : boxList) box.update(player, deltaTime);
    const sf :: Vector2f &position = boxList.back().getCenter();
    if(len(position - player.getPosition()) < dMonster) {
        subtitle.display(L"按F键开启挑战", 0.1f);
        activate = true;
    }
    else activate = false;
    if(activate && sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: F)) {
        subtitle.display(L"加载竞技场", 2.f);
        challenged = true;
    }
    animation.play(&sprite, deltaTime);
}
void MonsterLink :: render(sf :: RenderTarget *target, const float &y, const bool &flag) const {
    //for(auto box : boxList) box -> render(target, y);
    if(((y < ysort) ^ flag) || challenged) return;
    target -> draw(sprite);
}