#include "Entity.h"
extern Resource resource;
extern Subtitle subtitle;
extern std :: mt19937 rnd;

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
        const int id = rnd() % 6;
        subtitle.display(L"你获得了" + getEquipment(id).description, 1.f);
        player.attributeReference().add(getEquipment(id).attribute, getEquipment(id).value);
        display = true;
    }
    animation.play(&sprite, deltaTime);
}
void Treasure :: render(sf :: RenderTarget *target, const float &y, const bool &flag) const {
    if((y < ysort) ^ flag) return;
    target -> draw(sprite);
}

//Reward
const float dReward = 40.f, maxOffset = 5.f;
Reward :: Reward(const int &id, const sf :: Vector2f &position, const Animation &animation, const float &ysort)
: id(id), position(position), animation(animation), ysort(ysort), offset(0.f), dOffset(10.f), activate(false), opened(false) {
    this -> animation.pause();
}
Reward :: ~Reward() {

}
void Reward :: update(Player &player, const float &deltaTime) {
    if(opened) return;
    offset += dOffset * deltaTime;
    if(offset > maxOffset || offset < 0.f) dOffset *= -1;
    offset = std :: max(offset, 0.f);
    offset = std :: min(offset, maxOffset);
    sprite.setPosition(position - sf :: Vector2f(0.f, offset));
    animation.play(&sprite, deltaTime);
    if(len(position + sf :: Vector2f() - player.getPosition()) < dReward) {
        subtitle.display(L"按F键拾取" + getEquipment(id).name, 0.1f);
        activate = true;
    }
    else activate = false;
    if(activate && sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: F)) {
        opened = true;
        subtitle.display(L"你获得了" + getEquipment(id).description, 1.f);
        player.attributeReference().add(getEquipment(id).attribute, getEquipment(id).value);
    }
}
void Reward :: render(sf :: RenderTarget *target, const float &y, const bool &flag) const {
    if((y < ysort) ^ flag || opened) return;
    target -> draw(sprite);
}

//Door
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
            subtitle.display(L"门被锁上, 按F键消耗一把钥匙打开", 0.1f);
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

//MonsterLink
const float dMonster = 40.f;
MonsterLink :: MonsterLink(const std :: string &name, const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, const float &ysort)
 : name(name), animation(animation), boxList(boxList), activate(false), challenged(false), beaten(false), ysort(ysort) {
    sprite.setPosition(position);
}
MonsterLink :: ~MonsterLink() {

}
void MonsterLink :: update(Player &player, const float &deltaTime) {
    if(beaten) return;
    if(challenged) {
        if(player.getBattle() == "") beaten = true;
        return;
    }
    for(auto box : boxList) box.update(player, deltaTime);
    const sf :: Vector2f &position = boxList.back().getCenter();
    if(len(position - player.getPosition()) < dMonster) {
        subtitle.display(L"按F键进行战斗", 0.1f);
        activate = true;
    }
    else activate = false;
    if(activate && sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: F)) {
        player.setBattle(name);
        challenged = true;
    }
    animation.play(&sprite, deltaTime);
}
void MonsterLink :: render(sf :: RenderTarget *target, const float &y, const bool &flag) const {
    //for(auto box : boxList) box -> render(target, y);
    if(((y < ysort) ^ flag) || beaten) return;
    target -> draw(sprite);
}


//Entrance
const float dEntrance = 50.f;
Entrance :: Entrance(const sf :: Vector2f &position, const Animation &animation, const std :: vector<CollisionBox> &boxList, bool forward)
: animation(animation), boxList(boxList), forward(forward), activate(false), opening(false), opened(false) {
    sprite.setPosition(position);
    ysort = this -> boxList.back().getBox().top + this -> boxList.back().getBox().height;
    if(forward) this -> animation.pause();
    else this -> animation.run(), opening = true;
}
Entrance :: ~Entrance() {

}
void Entrance :: update(Player &player, const float &deltaTime) {
    animation.play(&sprite, deltaTime);
    if(animation.end() && !opened) {
        opened = true, boxList.pop_back();
    }
    if(opened) {
        if(boxList[0].getBox().intersects(player.getHitbox("bodyHitbox"))) {
            player.setPosition(boxList[0].getCenter() + sf :: Vector2f(0.f, 60.f));
            player.setLocation(forward ? "forward" : "backward");
            player.setHidden(true), player.setDirection(true), player.stopVelocity(true, true);
            subtitle.clear();
            return;
        }
        for(auto &box : boxList) box.update(player, deltaTime);
        const sf :: Vector2f &position = boxList[0].getCenter();
        if(len(position - player.getPosition()) < dEntrance) subtitle.display(forward ? L"进入下一层" : L"回到上一层", 0.1f);
    }
    else {
        boxList.back().update(player, deltaTime);
        if(opening) return;
        const sf :: Vector2f &position = boxList.back().getCenter();
        if(len(position - player.getPosition()) < dEntrance) {
            subtitle.display(L"按F键打开通往下一层大门", 0.1f);
            activate = true;
        }
        else activate = false;
        if(activate && sf :: Keyboard :: isKeyPressed(sf :: Keyboard :: F)) {
            animation.run(), opening = true;
        }
    }
}
void Entrance :: render(sf :: RenderTarget *target, const float &y, const bool &flag) const {
    if((y < ysort) ^ flag) return;
    target -> draw(sprite);
}