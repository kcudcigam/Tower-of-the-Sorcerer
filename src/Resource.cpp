#include "Resource.h"
#include <iostream>
Resource :: Resource(const std :: filesystem ::path &directory) {
    this -> loadImg(directory / "image");
    this -> loadMap(directory / "tilemap");
}
Resource :: ~Resource() {
    for(auto it : this -> img) delete it.second;
    for(auto it : this -> map) delete it.second;
}
void Resource :: loadImg(const std :: filesystem :: path &directory) {
    for (const auto &img : std :: filesystem :: directory_iterator(directory)) {
        if(std :: filesystem :: is_directory(img)) this -> loadImg(img.path());
        else {
            auto texture = new sf :: Texture(); texture -> loadFromFile(img.path().string());
            this -> img.emplace(img.path().filename().string(), texture);
        }
    }
}
void Resource :: loadMap(const std :: filesystem ::path &directory) {
    for (const auto &map : std :: filesystem :: directory_iterator(directory)) {
        auto mapjson = new json(json :: parse(std :: ifstream(map.path().string())));
        this -> map.emplace(map.path().filename().string(), mapjson);
    }
}
sf :: Texture* Resource :: getImg(const std :: string &file) const {
    return this -> img.at(file);
}
json* Resource :: getMap(const std :: string &file) const {
    return this -> map.at(file);
}