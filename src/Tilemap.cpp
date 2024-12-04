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
    this -> animation.play(&this -> sprite, deltaTime);
}
bool Tile :: empty () const {
    return this -> animation.empty();
}
void Tile :: render(sf :: RenderTarget* target) const {
    if(!this -> empty()) target -> draw(this -> sprite);
}

//Layer
Layer :: Layer() {
    
}
Layer :: ~Layer() {

}
void Layer :: insert(const sf :: Vector2f &position, const Animation &animation) {
    this -> tiles.emplace_back(position, animation);
}
void Layer :: update(const float& deltaTime) {
    for(auto &tile : this -> tiles) tile.update(deltaTime);
}
void Layer :: render(sf :: RenderTarget* target) const {
    for(const auto &tile : this -> tiles) tile.render(target);
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
    const unsigned int bitmask = (1 << 29) - 1;
    for(const auto &tileset : map["tilesets"]) {
        assert(tileset["firstgid"].get<size_t>() == this -> imgList.size());
        //std :: cerr << tileset["name"].get<std :: string>() << std :: endl;
        const int cnt = tileset["tilecount"].get<int>();
        if(tileset.contains("image")) {
            const auto texture = Resource.getImg(getFileName(tileset["image"].get<std :: string>()));
            const int column = tileset["columns"].get<int>(), row = cnt / column;
            sf :: Vector2i size(tileset["tilewidth"], tileset["tileheight"]);
            for(int i = 0; i < row; i++) {
                const auto list = generateList(texture, {0, i}, {column - 1, i}, size);
                this -> imgList.insert(this -> imgList.end(), list.begin(), list.end());
            }
        }
        if(tileset.contains("tiles")) {
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("image")) continue;
                const auto texture = Resource.getImg(getFileName(tile["image"].get<std :: string>()));
                const int x = tile["imagewidth"].get<int>(), y = tile["imageheight"].get<int>();
                size_t id = tile["id"].get<int>() + tileset["firstgid"].get<int>();
                if(this -> imgList.size() <= id) this -> imgList.resize(id + 1);
                this -> imgList[id] = Img(texture, sf :: IntRect({0, 0}, {x, y}));
            }
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
        if(layer["type"].get<std :: string>() == "tilelayer") {
            const int x = layer["height"].get<int>(), y = layer["width"].get<int>();
            this -> layers.emplace_back();
            for(int i = 0; i < x; i++)
                for(int j = 0; j < y; j++) {
                    const unsigned int id = layer["data"][i * y + j].get<int>();
                    this -> layers.back().insert(sf :: Vector2f(j * map["tilewidth"].get<int>(), i * map["tileheight"].get<int>()), animationList[id & bitmask].flip(id >> 31 & 1));
                }
        }
        else if(layer["type"].get<std :: string>() == "objectgroup") {
            std :: cerr << layer["name"].get<std :: string>() << std :: endl;
            layers.emplace_back();
            for(const auto &object : layer["objects"]) {
                if(!object.contains("gid")) continue;
                std :: cerr << object["x"].get<float>() << ' ' << object["y"].get<float>() << std :: endl;
                const unsigned int id = object["gid"].get<unsigned int>();
                const float x = object["x"].get<float>() + object["width"].get<float>();
                const float y = object["y"].get<float>() - object["height"].get<float>();
                if(!(id >> 31 & 1)) layers.back().insert(sf :: Vector2f(x, y), animationList[id & bitmask].flip(id >> 31 & 1));
            }
        }
    }
}

void Tilemap :: update(const float& deltaTime) {
    for(auto &layer : layers) layer.update(deltaTime);
}
void Tilemap :: render(sf :: RenderTarget* target) const {
    for(const auto &layer : layers) layer.render(target);
}