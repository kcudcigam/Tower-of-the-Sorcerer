#pragma once
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Json.hpp"
#include "Animation.h"
using json = nlohmann :: json;

class Resource {
private:
    std :: map <std :: string, sf :: Texture*> img;
    std :: map <std :: string, json*> map;
    std :: map <std :: string, sf :: Font*> font;
    std :: map <std :: string, AnimationSet> entity;
    void loadImg(const std :: filesystem :: path &directory);
    void loadMap(const std :: filesystem :: path &directory);
    void loadFont(const std :: filesystem :: path &directory);
public:
    Resource();
    virtual ~Resource();
    void loadFrom(const std :: filesystem :: path &directory);
    void addAction(const std :: string &name, const std :: string &action, const Animation &animation);
    sf :: Texture* getImg(const std :: string &file) const;
    json* getMap(const std :: string &file) const;
    sf :: Font* getFont(const std :: string &file) const;
    AnimationSet getEntity(const std :: string &name) const;
    
};