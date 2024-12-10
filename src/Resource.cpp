#include <iostream>
#include "Resource.h"

//Resource
Resource :: Resource() {

}
Resource :: ~Resource() {
    for(auto it : img) delete it.second;
    for(auto it : map) delete it.second;
    for(auto it : font) delete it.second;
}
void Resource :: loadFrom(const std :: filesystem :: path &directory) {
    loadImg(directory / "image");
    loadMap(directory / "tilemap");
    loadFont(directory / "font");
}
void Resource :: loadImg(const std :: filesystem :: path &directory) {
    for (const auto &img : std :: filesystem :: directory_iterator(directory)) {
        if(std :: filesystem :: is_directory(img)) loadImg(img.path());
        else {
            auto texture = new sf :: Texture(); texture -> loadFromFile(img.path().string());
            this -> img.emplace(img.path().filename().string(), texture);
            //std :: cerr << img.path().filename().string() << std :: endl;
        }
    }
}
void Resource :: loadMap(const std :: filesystem ::path &directory) {
    for (const auto &map : std :: filesystem :: directory_iterator(directory)) {
        auto mapjson = new json(json :: parse(std :: ifstream(map.path().string())));
        this -> map.emplace(map.path().filename().string(), mapjson);
    }
}
void Resource :: loadFont(const std :: filesystem ::path &directory) {
    for (const auto &file : std :: filesystem :: directory_iterator(directory)) {
        auto font = new sf :: Font(); font -> loadFromFile(file.path().string());
        this -> font.emplace(file.path().filename().string(), font);
    }
}
sf :: Texture* Resource :: getImg(const std :: string &file) const {
    return img.at(file);
}
json* Resource :: getMap(const std :: string &file) const {
    return map.at(file);
}
sf :: Font* Resource :: getFont(const std :: string &file) const {
    return font.at(file);
}