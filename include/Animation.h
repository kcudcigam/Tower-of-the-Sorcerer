#pragma once
#include <SFML/Graphics.hpp>

class RectQueue {
private:
    sf :: IntRect startRect, currentRect, endRect; sf :: Vector2i size;
public:
    RectQueue(const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size);
    virtual ~RectQueue();
    
    void next();
    sf :: IntRect now() const;
    bool end() const;
    void reset();
};

class Animation {
private:
    sf :: Sprite *sprite;
    sf :: Texture *sheet;
    float currentTime, animationTime;
    RectQueue position;
    bool loop;
public:
    Animation(sf :: Texture *sheet, const float &animationTime, const RectQueue &position, bool loop = false);
    virtual ~Animation();
    bool end() const;
    void init(sf :: Sprite *sprite);
    void play(const float &deltaTime);
    void reset();
};

class AnimationSet {
private:
    sf :: Sprite* sprite;
    std :: map<std :: string, Animation> animation;
    std :: map<std :: string, sf :: Vector2f> offset;
    std :: pair<std :: string, bool> priority;
    std :: string currentAnimation;

    //std :: vector<Animation> playlist;
public:
    AnimationSet(sf :: Sprite* sprite);
    virtual ~AnimationSet();
    void insert(const std :: string &key, const Animation &value, const sf :: Vector2f &offset = sf :: Vector2f(0, 0), bool reversed = false);
    void reverse(const bool &reversed, const sf :: Vector2f &offset);
    void play(std :: string key, const float &deltaTime, bool reversed = false);
    bool hasPriority();
    void delPriority();
    void setPriority(const std :: string &key, bool reversed = false);
};
