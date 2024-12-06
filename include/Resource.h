#pragma once
#include <fstream>
#include <SFML/Graphics.hpp>
#include "json.hpp"
using json = nlohmann :: json;
class  Resource {
private:
    //Variables
    std :: map <std :: string, sf :: Texture*> img;
    std :: map <std :: string, json*> map;
    std :: map <std :: string, sf :: Font*> font;
    void loadImg(const std :: filesystem :: path &directory);
    void loadMap(const std :: filesystem :: path &directory);
    void loadFont(const std :: filesystem :: path &directory);
public:
    //constructor & destructor
    Resource(const std :: filesystem :: path &directory);
    virtual ~Resource();
    //funtions
    sf :: Texture* getImg(const std :: string &file) const;
    json* getMap(const std :: string &file) const;
    sf :: Font* getFont(const std :: string &file) const;
    
};