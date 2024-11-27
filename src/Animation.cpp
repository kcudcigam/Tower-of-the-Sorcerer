#include "Animation.h"
//RectQueue
RectQueue :: RectQueue(const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size) {
    this -> startRect = sf :: IntRect(sf :: Vector2i(start.x * size.x, start.y * size.y), size);
    this ->   endRect = sf :: IntRect(sf :: Vector2i(  end.x * size.x,   end.y * size.y), size);
    this -> size = size; this -> reset();
}
RectQueue :: ~RectQueue() {

}
sf :: IntRect RectQueue :: next() {
    if(this -> end()) return this -> endRect;
    this -> currentRect.left += this -> size.x;
    return this -> currentRect;
}
bool RectQueue :: end() const {
    return this -> currentRect == this -> endRect;
}
void RectQueue :: reset() {
    this -> currentRect = this -> startRect;
    this -> currentRect.left -= this -> size.x;
}

//Animation
Animation :: Animation(sf :: Texture *sheet, const float &animationTime, const RectQueue &position)
: sprite(nullptr), sheet(sheet), animationTime(animationTime), position(position) {
    
}
Animation :: ~Animation() {

}
void Animation :: init(sf :: Sprite *sprite) {
    this -> sprite = sprite;
    this -> sprite -> setTexture(*this -> sheet);
    this -> reset();
}
bool Animation :: end() const {
    return this -> position.end();
}
bool Animation :: play(const float &deltaTime) {
    this -> currentTime += deltaTime;
    if(this -> currentTime > this -> animationTime) {
        if(this -> end()) return true;
        this -> currentTime = 0.f;
        this -> sprite -> setTextureRect(this -> position.next());
    }
    return false;
}
void Animation :: reset() {
    currentTime = 0.f;
    this -> position.reset();
    this -> sprite -> setTextureRect(this -> position.next());
}

//AnimationSet
AnimationSet :: AnimationSet(sf :: Sprite* sprite) : sprite(sprite) {
    
}
AnimationSet :: ~AnimationSet() {

}
void AnimationSet :: insert(const std :: string &key, const Animation &value) {
    this -> animation.emplace(key, value);
    this -> animation.at(key).init(this -> sprite);
}
void AnimationSet :: play(const std :: string &key, const float &deltaTime) {
    if(this -> animation.at(key).play(deltaTime))
        this -> animation.at(key).reset();
}

