#include "Tilemap.h"
#include <iostream>
//Tile
Tile :: Tile(const sf :: Vector2f &position, const Animation &animation) {
    this -> setPosition(position), this -> setAnimation(animation);
}
Tile :: ~Tile() {

}
void Tile :: setPosition(const sf :: Vector2f &position) {
    this -> sprite.setPosition(position);
}
void Tile :: setAnimation(const Animation &animation) {
    this -> animation = animation;
    this -> animation.reset();
}
void Tile :: update(const float& deltaTime) {
    //std :: cerr << (this -> animation.empty()) << std :: endl;
    this -> animation.play(&this -> sprite, deltaTime);
}
bool Tile :: empty () const {
    return this -> animation.empty();
}
void Tile :: render(sf :: RenderTarget* target) const {
    if(!this -> empty()) target -> draw(this -> sprite);
}

//Layer
Layer :: Layer(const sf :: Vector2i &size) : tiles(size.x, std :: vector<Tile>(size.y)) {
    
}
Layer :: ~Layer() {

}
void Layer :: insert(int x, int y, const sf :: Vector2f &position, const Animation &animation) {
    this -> tiles[x][y].setPosition(position);
    this -> tiles[x][y].setAnimation(animation);
}
void Layer :: update(const float& deltaTime) {
    for(auto &raw : this -> tiles)
        for(auto &tile : raw) tile.update(deltaTime);
}
void Layer :: render(sf :: RenderTarget* target) const {
    for(const auto &raw : this -> tiles)
        for(const auto &tile : raw) tile.render(target);
}

Tilemap :: Tilemap(Resource *resource, const std :: string &file) {
    this -> imgList.emplace_back();
    this -> loadFromFile(*resource -> getMap(file), *resource);
}
Tilemap :: ~Tilemap() {

}
void Tilemap :: loadFromFile(const json &map, const Resource &Resource) {
    auto getFileName = [](const std :: string &path) {
        return path.substr(path.find_last_of("\\/") + 1);
    };
    for(const auto &tileset : map["tilesets"]) {
        assert(tileset["firstgid"].get<size_t>() == this -> imgList.size());
        const auto texture = Resource.getImg(getFileName(tileset["image"].get<std :: string>()));
        const int column = tileset["columns"].get<int>(), row = tileset["tilecount"].get<int>() / column;
        sf :: Vector2i size(tileset["tilewidth"], tileset["tileheight"]);
        for(int i = 0; i < row; i++) {
            const auto list = generateList(texture, {0, i}, {column - 1, i}, size);
            this -> imgList.insert(this -> imgList.end(), list.begin(), list.end());
        }
    }
    this -> animationList.resize(imgList.size());
    for(int i = 1; i < static_cast<int>(imgList.size()); i++) this -> animationList[i] = Animation((std :: vector<Img>){this -> imgList[i]});
    for(const auto &tileset : map["tilesets"]) {
        if(tileset.contains("tiles")) {
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("animation")) continue;
                std :: vector<Img> list; float duration = 0.f;
                for(const auto &img : tile["animation"]) {
                    list.emplace_back(imgList[img["tileid"].get<int>() + tileset["firstgid"].get<int>()]);
                    duration = img["duration"].get<int>() / 1000.f;
                }
                this -> animationList[tile["id"].get<int>() + tileset["firstgid"].get<int>()] = Animation(list, duration, true);
            }
        }
    }
    
    for(const auto &layer : map["layers"]) {
        if(layer["type"].get<std :: string>() != "tilelayer") continue;
        
        const int x = layer["height"].get<int>(), y = layer["width"].get<int>();
        this -> layers.emplace_back(sf :: Vector2i(x, y));
        for(int i = 0; i < x; i++)
            for(int j = 0; j < y; j++) {
                const int id = layer["data"][i * x + j].get<int>();
                this -> layers.back().insert(i, j, sf :: Vector2f(i * map["tilewidth"].get<int>(), j * map["tileheight"].get<int>()), animationList[id]);
            }
    }
}

void Tilemap :: update(const float& deltaTime) {
    for(auto &layer : layers) layer.update(deltaTime);
}
void Tilemap :: render(sf :: RenderTarget* target) const {
    for(const auto &layer : layers) layer.render(target);
}