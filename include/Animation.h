#pragma once
#include <SFML/Graphics.hpp>

class RectQueue {
private:
    sf :: IntRect startRect, currentRect, endRect; sf :: Vector2i size;
public:
    RectQueue(const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size);
    virtual ~RectQueue();
    
    sf :: IntRect next();
    bool end() const;
    void reset();
};

class Animation {
private:
    sf :: Sprite *sprite;
    sf :: Texture *sheet;
    float currentTime, animationTime;
    RectQueue position;
public:
    Animation(sf :: Texture *sheet, const float &animationTime, const RectQueue &position);
    virtual ~Animation();
    void init(sf :: Sprite *sprite);
    bool end() const;
    bool play(const float &deltaTime);
    void reset();
};

class AnimationSet {
private:
    sf :: Sprite* sprite;
    std :: map<std :: string, Animation> animation;
public:
    AnimationSet(sf :: Sprite* sprite);
    virtual ~AnimationSet();
    void insert(const std :: string &key, const Animation &value);
    void play(const std :: string &key, const float &deltaTime);
};
