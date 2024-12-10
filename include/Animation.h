#pragma once
#include "SFML/Graphics.hpp"

struct Img {
    sf :: Texture* texture;
    sf :: IntRect rect;
    sf :: Vector2f origin;
    float scale;
    Img(sf :: Texture* texture = nullptr, const sf :: IntRect &rect = sf :: IntRect(), const float &scale = 1.f, const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));
    sf :: Vector2i getSize() const;
    void flip();
};
std :: vector<Img> generateList(sf :: Texture* texture, const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size, const float &scale = 1.f, const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));

class Animation {
private:
    float currentTime, animationTime;
    std :: vector<Img> list;
    size_t it;
    bool loop, paused;
public:
    Animation(const std :: vector<Img> &list = (std :: vector<Img>){}, const float &animationTime = 0, bool loop = true);
    virtual ~Animation();
    void setLoop(bool loop = true);
    void flip();
    void pause();
    void run();
    sf :: Vector2i getSize() const;
    bool end() const;
    void play(sf :: Sprite *sprite, const float &deltaTime, const float &scale = 1.f);
    void reset();
};

class AnimationSet {
private:
    std :: map<std :: string, Animation> animation;
    std :: string priority, currentAnimation;
public:
    AnimationSet();
    virtual ~AnimationSet();
    void insert(const std :: string &key, const Animation &value);
    void play(sf :: Sprite *sprite, std :: string key, const float &deltaTime, const float &scale = 1.f);
    bool hasPriority() const;
    void updatePriority();
    void setPriority(const std :: string &key);
    bool contains(const std :: string &key) const;
    Animation getAnimation(const std :: string &key) const;
};
