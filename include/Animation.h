#pragma once
#include <SFML/Graphics.hpp>
class RectQueue {
private:
    sf::IntRect startRect, currentRect, endRect;
    sf :: Vector2i size;
public:
    RectQueue();
    virtual ~RectQueue();
    
    sf::IntRect next();
    const sf :: Vector2i getSize();
    const bool& end() const;
    void reset();
};
class Animation {
private:
    sf :: Sprite &sprite;
    sf :: Texture &sheet;
    float currentTime, animationTime;
    RectQueue position;
    bool isEnd;
public:
    Animation(sf :: Sprite &sprite, sf :: Texture &sheet, const float &animationTime, const RectQueue &position);
    virtual ~Animation();
    const bool& end() const;
    const bool& play(const float &deltaTime);
    void reset();
};
class AnimationSet {
private:
    std :: map<std :: string, sf :: Texture> animation;
};
