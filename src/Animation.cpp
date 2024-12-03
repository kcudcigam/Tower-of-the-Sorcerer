#include <cmath>
#include "Animation.h"
#include<iostream>
//Img
Img :: Img(sf :: Texture* texture, const sf :: IntRect &rect, const float &scale, const sf :: Vector2f &origin)
: texture(texture), rect(rect), scale(scale), origin(origin) {

}
std :: vector<Img> generateList(sf :: Texture* texture, const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size, const float &scale, const sf :: Vector2f &origin) {
    std :: vector<Img> imgList;
    auto startRect = sf :: IntRect(sf :: Vector2i(start.x * size.x, start.y * size.y), size);
    auto   endRect = sf :: IntRect(sf :: Vector2i(  end.x * size.x,   end.y * size.y), size);
    for(auto current = startRect; current.left <= endRect.left; current.left += size.x)
        imgList.emplace_back(texture, current, scale, origin);
    return imgList;
}

//Animation
Animation :: Animation(const std :: vector<Img> &list, const float &animationTime, bool loop)
: list(list), animationTime(animationTime), loop(loop) {
    this -> reset();
}
Animation :: ~Animation() {

}
bool Animation :: end() const {
    return this -> position == this -> list.end();
}

void Animation :: play(sf :: Sprite *sprite, const float &deltaTime) {
    if(this -> end()) return;
    this -> currentTime += deltaTime;
    if(this -> currentTime > this -> animationTime) {
        this -> currentTime = 0.f;
        this -> position = next(this -> position);
    }
    if(this -> end()) {
        if(this -> loop) this -> position = this -> list.begin();
        else return;
    }
    sprite -> setTexture(*this -> position -> texture);
    sprite -> setTextureRect(this -> position -> rect);
    sprite -> setOrigin(this -> position -> origin);
    sprite -> setScale(this -> position -> scale, fabs(this -> position -> scale));
}
void Animation :: reset() {
    currentTime = 0.f;
    this -> position = this -> list.begin();
}

//AnimationSet
AnimationSet :: AnimationSet() {
    
}
AnimationSet :: ~AnimationSet() {

}
void AnimationSet :: insert(const std :: string &key, const Animation &value) {
    this -> animation.emplace(key, value);
    this -> animation.at(key).reset();
}
bool AnimationSet :: hasPriority() {
    return this -> priority != "" && !this -> animation.at(priority).end();
}
void AnimationSet :: updatePriority() {
    if(this -> priority != "" && !this -> hasPriority()) this -> animation.at(this -> priority).reset(), this -> priority = "";
}
void AnimationSet :: play(sf :: Sprite *sprite, std :: string key, const float &deltaTime) {

    if(hasPriority()) key = priority;
    
    if(currentAnimation != key) {
        if(currentAnimation != "") this -> animation.at(currentAnimation).reset();
        currentAnimation = key;
    }
    
    this -> animation.at(key).play(sprite, deltaTime);
    updatePriority();
}
void AnimationSet :: setPriority(const std :: string &key) {
    this -> priority = key;
}

