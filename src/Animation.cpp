#include "Animation.h"
//RectQueue
RectQueue :: RectQueue(const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size) {
    this -> startRect = sf :: IntRect(sf :: Vector2i(start.x * size.x, start.y * size.y), size);
    this ->   endRect = sf :: IntRect(sf :: Vector2i(  end.x * size.x,   end.y * size.y), size);
    this -> size = size; this -> reset();
}
RectQueue :: ~RectQueue() {

}
void RectQueue :: next() {
    this -> currentRect.left = std :: min(this -> currentRect.left, this -> endRect.left) + this -> size.x;
}
sf :: IntRect RectQueue :: now() const {
    if(this -> end()) return this -> startRect;
    return this -> currentRect;
}
bool RectQueue :: end() const {
    return this -> currentRect.left > this -> endRect.left;
}
void RectQueue :: reset() {
    this -> currentRect = this -> startRect;
}

//Animation
Animation :: Animation(sf :: Texture *sheet, const float &animationTime, const RectQueue &position, bool loop)
: sprite(nullptr), sheet(sheet), animationTime(animationTime), position(position), loop(loop) {
    
}
Animation :: ~Animation() {

}
void Animation :: init(sf :: Sprite *sprite) {
    this -> sprite = sprite;
    this -> reset();
}
bool Animation :: end() const {
    return this -> position.end();
}
void Animation :: play(const float &deltaTime) {
    this -> currentTime += deltaTime;
    if(this -> currentTime > this -> animationTime) {
        this -> currentTime = 0.f;
        position.next();
    }
    this -> sprite -> setTexture(*this -> sheet);
    this -> sprite -> setTextureRect(this -> position.now());
    if(this -> end()) {
        if(this -> loop) this -> position.reset();
        else currentTime = 0.f;
    }
}
void Animation :: reset() {
    currentTime = 0.f;
    this -> position.reset();
}

//AnimationSet
AnimationSet :: AnimationSet(sf :: Sprite* sprite) : sprite(sprite), currentAnimation(""), priority({"", 0}) {
    
}
AnimationSet :: ~AnimationSet() {

}
void AnimationSet :: insert(const std :: string &key, const Animation &value, const sf :: Vector2f &offset, bool reversed) {
    this -> animation.emplace(key, value), this -> offset.emplace(key, offset);
    this -> animation.at(key).init(this -> sprite);
}
void AnimationSet :: reverse(const bool &reversed, const sf :: Vector2f &offset) {
    this -> sprite -> setOrigin(reversed ? offset.y : offset.x, 1.f);
    this -> sprite -> setScale(reversed ? -1.f : 1.f, 1.f);
}
bool AnimationSet :: hasPriority() {
    return this -> priority.first != "" && !this -> animation.at(priority.first).end();
}
void AnimationSet ::delPriority() {
    if(this -> priority.first != "") this -> animation.at(this -> priority.first).reset();
    this -> priority = {"", false};
}
void AnimationSet :: play(std :: string key, const float &deltaTime, bool reversed) {
    if(hasPriority()) key = priority.first, reversed = priority.second;
    if(currentAnimation != key) {
        if(currentAnimation != "") this -> animation.at(currentAnimation).reset();
        currentAnimation = key;
    }
    
    this -> animation.at(key).play(deltaTime);
    this -> reverse(reversed, this -> offset.at(key));
    if(!hasPriority()) delPriority();
}

void AnimationSet :: setPriority(const std :: string &key, bool reversed) {
    this -> priority = make_pair(key, reversed);
}

