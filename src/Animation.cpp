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
Animation :: Animation(sf :: Texture *sheet, const float &animationTime, const RectQueue &position, bool loop)
: sprite(nullptr), sheet(sheet), animationTime(animationTime), position(position), loop(loop) {
    
}
Animation :: ~Animation() {

}
void Animation :: init(sf :: Sprite *sprite) {
    this -> sprite = sprite;
    this -> reset();
}
const bool& Animation :: end() const {
    return this -> isEnd;
}
void Animation :: play(const float &deltaTime) {
    this -> currentTime += deltaTime;
    
    if(this -> currentTime > this -> animationTime) {
        if(this -> position.end()) {
            if(this -> loop) this -> reset(); 
            else {this -> isEnd = true; return;}
        }
        this -> currentTime = 0.f;
        this -> sprite -> setTexture(*this -> sheet);
        this -> sprite -> setTextureRect(this -> position.next());
    }
}
void Animation :: reset() {
    currentTime = 0.f; this -> isEnd = false;
    this -> position.reset();
    this -> sprite -> setTextureRect(this -> position.next());
}

//AnimationSet
AnimationSet :: AnimationSet(sf :: Sprite* sprite) : sprite(sprite), currentAnimation({"", 0}) {
    
}
AnimationSet :: ~AnimationSet() {

}
void AnimationSet :: insert(const std :: string &key, const Animation &value, const float &offset, bool reversed) {
    this -> animation.emplace(key, value), this -> offset.emplace(key, offset);
    this -> animation.at(key).init(this -> sprite);
}
void AnimationSet :: reverse(const bool &reversed, const float &offset) {
    this -> sprite -> setOrigin(reversed ? offset : 0.f, 1.f);
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
    if(!hasPriority()) delPriority();
    this -> reverse(reversed, this -> offset.at(key));
}

void AnimationSet :: setPriority(const std :: string &key, bool reversed) {
    this -> priority = make_pair(key, true);
}

