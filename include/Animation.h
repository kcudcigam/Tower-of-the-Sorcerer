#pragma once
#include <SFML/Graphics.hpp>
struct Img {
    sf :: Texture* texture;
    sf :: IntRect rect;
    sf :: Vector2f origin;
    float scale;
    Img(sf :: Texture* texture = nullptr, const sf :: IntRect &rect = sf :: IntRect(), const float &scale = 1.f, const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));
    void flip();
};
std :: vector<Img> generateList(sf :: Texture* texture, const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size, const float &scale = 1.f, const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));

class Animation {
private:
    float currentTime, animationTime;
    std :: vector<Img> list;
    size_t position;
    bool loop;
public:
    Animation(const std :: vector<Img> &list = (std :: vector<Img>){}, const float &animationTime = 0, bool loop = true);
    virtual ~Animation();
    Animation flip(bool flip) const;
    bool empty() const;
    bool end() const;
    void play(sf :: Sprite *sprite, const float &deltaTime);
    void reset();
};

class AnimationSet {
private:
    std :: map<std :: string, Animation> animation;
    std :: string priority, currentAnimation;

    //std :: vector<Animation> playlist;
public:
    AnimationSet();
    virtual ~AnimationSet();
    void insert(const std :: string &key, const Animation &value);
    void play(sf :: Sprite *sprite, std :: string key, const float &deltaTime);
    bool hasPriority();
    void updatePriority();
    void setPriority(const std :: string &key);
};
