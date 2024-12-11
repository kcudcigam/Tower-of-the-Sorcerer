#include "Player.h"
extern Resource resource;

//Movement
Movement :: Movement(sf :: Sprite *sprite, const float &maxVelocity, const float &acceleration, const float &deceleration, const bool &direction)
: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), velocity(sf :: Vector2f(0.f, 0.f)), direction(direction), paused(false) {

}
Movement :: ~Movement() {

}
void Movement :: setPause(bool flag) {
    paused = flag;
}
const bool& Movement :: getDirection() const {
    return direction;
}
const sf :: Vector2f& Movement :: getVelocity() const {
    return velocity;
}
void Movement :: stopVelocity(const bool &x = true, const bool &y = true) {
    if(x) velocity.x = 0.f; 
    if(y) velocity.y = 0.f;
}
void Movement :: move(const float &x, const float &y, const float &deltaTime) {
    if(paused) return;
    auto limit = [](float &u, float &v, const float &maxVelocity) {
        u = std :: min(u,  maxVelocity); u = std :: max(u, -maxVelocity);
        const float &w = std :: sqrt(maxVelocity * maxVelocity - u * u);
        v = std :: min(v, w); v = std :: max(v, -w);
    };
    if(x != 0) direction = (x > 0);
    velocity.x += acceleration * x * deltaTime;
    velocity.y += acceleration * y * deltaTime;
}
void Movement :: update(const float &deltaTime) {
    const float &d = std :: sqrt(velocity.x * velocity.x + velocity.y * velocity.y) / maxVelocity;
    if(d > 1.f) velocity /= d;  
    auto updateSpeed = [&deltaTime](float &x, const float &deceleration) {
        const int u = (x > 0.f ? 1 : x < 0.f ? -1 : 0); x *= u;
        x -= deltaTime * deceleration; x = std :: max(x, 0.f) * u;
    };
    updateSpeed(velocity.x, deceleration);
    updateSpeed(velocity.y, deceleration);
    sprite -> move(velocity * deltaTime);
}


//Player
Player :: Player(const Attribute &attribute) : attribute(attribute), movement(&sprite, 160.f, 600.f, 300.f) {

}
Player :: ~Player() {

}
Attribute& Player :: attributeReference() {
    return attribute;
}
const Attribute& Player :: getAttribute() const {
    return attribute;
}
sf :: FloatRect Player :: getHitbox(const std :: string &type) const {
	return sf :: FloatRect(hitbox.at(type).getPosition() + sprite.getPosition(), hitbox.at(type).getSize());
}
const sf :: Vector2f& Player :: getPosition() const {
    return sprite.getPosition();
}
void Player :: setHitbox(const std :: string &type, const sf :: Vector2f &position, const sf :: Vector2f &size) {
    hitbox[type] = sf :: FloatRect(position, size);
}
void Player :: setPosition(const sf :: Vector2f &position) {
    sprite.setPosition(position);
}
void Player :: setHitboxPosition(const std :: string &type, const sf :: Vector2f &position) {
    sprite.setPosition(position - hitbox[type].getPosition());
}
const std :: string& Player :: getBattle() const {
    return battle;
}
void Player :: setBattle(const std :: string &monster) {
    battle = monster;
}
Animation Player :: getAnimation(const std :: string &key) const {
    return animation.getAnimation(key);
}
void Player :: stopVelocity(const bool &x, const bool &y) {
    movement.stopVelocity(x, y);
}
void Player :: initAnimation() {
    animation.insert("walk_left", flip(animation.getAnimation("walk_right")));
    animation.insert("idle_left", flip(animation.getAnimation("idle_right")));
    animation.insert("hurt_left", flip(animation.getAnimation("hurt_right")));
    animation.insert("attack_left", flip(animation.getAnimation("attack_right")));
    animation.insert("dead_left", flip(animation.getAnimation("dead_right")));
}
void Player :: addTag(const std :: string &tag, const float &duration) {
    if(!tags.contains(tag)) {
        tags.emplace(tag, duration);
        addEffect(tag);
    }
}
void Player :: updateTag(const float &deltaTime) {
    std :: map<std :: string, float> tmp;
    for(auto tag : tags) {
        tag.second -= deltaTime;
        if(tag.second > 0.f) tmp.emplace(tag.first, tag.second);
        else delEffect(tag.first);
    }
    swap(tmp, tags);
}
void Player :: addEffect(const std :: string &tag) {
    if(tag == "lava") {
        animation.setPriority(movement.getDirection() ? "hurt_right" : "hurt_left");
        attribute.add("health", -10);
        addTag("busy", 0.4f);
    }
    else if(tag == "busy") movement.setPause(true);
}
void Player :: delEffect(const std :: string &tag) {
    if(tag == "busy") movement.setPause(false);
}
void Player :: insertAnimation(const std :: string &key, const Animation &animation) {
    this -> animation.insert(key, animation);
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

    //std :: cerr << (movement -> getVelocity().x) << ' ' << (movement -> getVelocity().y) << std :: endl;
    if(movement.getVelocity() != sf :: Vector2f(0.f, 0.f)) {
        if(movement.getDirection())
            animation.play(&sprite, "walk_right", deltaTime);
        else animation.play(&sprite, "walk_left", deltaTime);
    }
    else {
        if(movement.getDirection())
            animation.play(&sprite, "idle_right", deltaTime);
        else animation.play(&sprite, "idle_left", deltaTime);
    }
    updateTag(deltaTime);
}
void Player :: render(sf :: RenderTarget* target) const {
    target -> draw(sprite);
    /*
    sf :: RectangleShape outline;
    outline.setPosition(getHitbox().getPosition());
    outline.setSize(hitbox.getSize());
    outline.setFillColor(sf :: Color :: Transparent);
    outline.setOutlineThickness(-1.f);
    outline.setOutlineColor(sf :: Color :: Green);
    target -> draw(outline);*/
}