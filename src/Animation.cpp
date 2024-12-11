#include "Animation.h"

//Img
Img :: Img(sf :: Texture* texture, const sf :: IntRect &rect, const float &scale, const sf :: Vector2f &origin)
: texture(texture), rect(rect), scale(scale), origin(origin) {

}
void Img :: flip() {
    scale *= -1.f; origin.x *= -1.f;
    origin.x += rect.width;
}
std :: vector<Img> generateList(sf :: Texture* texture, const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size, const float &scale, const sf :: Vector2f &origin) {
    std :: vector<Img> imgList;
    auto startRect = sf :: IntRect(sf :: Vector2i(start.x * size.x, start.y * size.y), size);
    auto   endRect = sf :: IntRect(sf :: Vector2i(  end.x * size.x,   end.y * size.y), size);
    for(auto current = startRect; current.left <= endRect.left; current.left += size.x)
        imgList.emplace_back(texture, current, scale, origin);
    return imgList;
}
sf :: Vector2i Img :: getSize() const {
    return sf :: Vector2i(rect.width, rect.height);
}

//Animation
Animation flip(Animation animation) {
    animation.flip(); return animation;
};
Animation :: Animation(const std :: vector<Img> &list, const float &animationTime, bool loop)
: list(list), animationTime(animationTime), loop(loop), paused(false) {
    reset();
}
Animation :: ~Animation() {

}
void Animation :: setLoop(bool loop) {
    this -> loop = loop;
}
void Animation :: pause() {
    paused = true;
}
void Animation :: run() {
    paused = false;
}
void Animation :: flip() {
    for(auto &img : list) img.flip();
}
sf :: Vector2i Animation :: getSize() const {
    return list.back().getSize();
}
bool Animation :: end() const {
    return it == list.size();
}
void Animation :: play(sf :: Sprite *sprite, const float &deltaTime, const float &scale) {
    if(end()) return;
    if(!paused) currentTime += deltaTime;
    if(currentTime > animationTime) {
        currentTime = 0.f, it++;
    }
    if(end()) {
        if(loop) it = 0;
        else return;
    }
    sprite -> setTexture(*list[it].texture);
    sprite -> setTextureRect(list[it].rect);
    sprite -> setOrigin(list[it].origin);
    sprite -> setScale(list[it].scale * scale, std :: abs(list[it].scale) * scale);
}
void Animation :: reset() {
    currentTime = 0.f; it = 0;
}

//AnimationSet
AnimationSet :: AnimationSet() {
    
}
AnimationSet :: ~AnimationSet() {

}
void AnimationSet :: insert(const std :: string &key, const Animation &value) {
    animation.emplace(key, value);
    animation.at(key).reset();
}
bool AnimationSet :: hasPriority() const {
    return priority != "" && !animation.at(priority).end();
}
void AnimationSet :: updatePriority() {
    if(priority != "" && !hasPriority()) animation.at(priority).reset(), priority = "";
}
void AnimationSet :: play(sf :: Sprite *sprite, std :: string key, const float &deltaTime, const float &scale) {

    if(hasPriority()) key = priority;
    
    if(currentAnimation != key) {
        if(currentAnimation != "") animation.at(currentAnimation).reset();
        currentAnimation = key;
    }
    
    animation.at(key).play(sprite, deltaTime, scale);
    updatePriority();
}
void AnimationSet :: setPriority(const std :: string &key) {
    if(priority != "") animation.at(priority).reset();
    priority = key;
}
bool AnimationSet :: contains(const std :: string &key) const {
    return animation.contains(key);
}
Animation AnimationSet :: getAnimation(const std :: string &key) const {
    return animation.at(key);
}


