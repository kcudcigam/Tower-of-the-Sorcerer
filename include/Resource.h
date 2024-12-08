#pragma once
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Json.hpp"
using json = nlohmann :: json;

class Resource {
private:
    std :: map <std :: string, sf :: Texture*> img;
    std :: map <std :: string, json*> map;
    std :: map <std :: string, sf :: Font*> font;
    void loadImg(const std :: filesystem :: path &directory);
    void loadMap(const std :: filesystem :: path &directory);
    void loadFont(const std :: filesystem :: path &directory);
public:
    Resource(const std :: filesystem :: path &directory);
    virtual ~Resource();
    sf :: Texture* getImg(const std :: string &file) const;
    json* getMap(const std :: string &file) const;
    sf :: Font* getFont(const std :: string &file) const;
};