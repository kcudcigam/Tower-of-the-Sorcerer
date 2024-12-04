#include "Tilemap.h"
#include "iostream"
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
void Tile :: render(sf :: RenderTarget* target) const {
    target -> draw(this -> sprite);
}

//Layer
Layer :: Layer(const sf :: Vector2i &size) : tiles(size.x, std :: vector<Tile>(size.y)) {
    
}
Layer :: ~Layer() {

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
    this -> loadFromFile(*resource -> getMap(file), *resource);
}
Tilemap :: ~Tilemap() {

}
void Tilemap :: loadFromFile(const json &map, const Resource &Resource) {
    const auto &tilesets = map["tilesets"];
    auto getFileName = [](const std :: string &path) {
        return path.substr(path.find_last_of("\\/") + 1);
    };
    for(const auto &tileset : tilesets) {
        std :: cerr << getFileName(tileset["image"].get<std :: string>()) << std :: endl;
    }

}
void Tilemap :: update(const float& deltaTime) {
    for(auto &layer : layers) layer.update(deltaTime);
}
void Tilemap :: render(sf :: RenderTarget* target) const {
    for(const auto &layer : layers) layer.render(target);
}