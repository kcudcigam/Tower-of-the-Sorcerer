#include "Tilemap.h"
#include <iostream>
//Tile
Tile :: Tile(const sf :: Vector2f &position, const Animation &animation, const float &ysort) : ysort(ysort) {
    this -> setPosition(position), this -> setAnimation(animation);
}
Tile :: ~Tile() {

}
const float& Tile :: getY() const {
    return this -> ysort;
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
    return sprite.getTexture() == nullptr;
}
void Tile :: render(sf :: RenderTarget* target) const {
    if(!this -> empty()) target -> draw(this -> sprite);
}

//Layer
Layer :: Layer() {
    
}
Layer :: ~Layer() {

}
void Layer :: ysort() {
    sort(tiles.begin(), tiles.end(), [](const Tile &u, const Tile &v) {return u.getY() < v.getY();});
}
void Layer :: insert(const Tile &tile) {
    this -> tiles.emplace_back(tile);
}
void Layer :: update(const float& deltaTime) {
    for(auto &tile : this -> tiles) tile.update(deltaTime);
}
void Layer :: beforeRender(sf :: RenderTarget* target, const float &playerY) const {
    for(const auto &tile : this -> tiles)
        if(tile.getY() < playerY) tile.render(target);
}
void Layer :: afterRender(sf :: RenderTarget* target, const float &playerY) const {
    for(const auto &tile : this -> tiles)
        if(!(tile.getY() < playerY)) tile.render(target);
}

Tilemap :: Tilemap(Resource *resource, const std :: string &file) : player(resource), mapSize({0, 0}) {
    this -> loadFromFile(*resource -> getMap(file), *resource);
}
Tilemap :: ~Tilemap() {
    for(const auto &entity : entities) delete entity;
}
void Tilemap :: loadFromFile(const json &map, const Resource &Resource) {

    auto getFileName = [](const std :: string &path) {
        return path.substr(path.find_last_of("\\/") + 1);
    };

    const unsigned int bitmask = (1 << 29) - 1;
    std :: vector<Img> imgList; imgList.emplace_back();
    std :: unordered_map<int, std :: vector<sf :: FloatRect> > rectList;
    std :: unordered_map<unsigned int, int> heightList; 

    for(const auto &tileset : map["tilesets"]) {
        assert(tileset["firstgid"].get<size_t>() == imgList.size());
        //std :: cerr << tileset["name"].get<std :: string>() << std :: endl;
        const int cnt = tileset["tilecount"].get<int>();
        if(tileset.contains("image")) {
            const auto texture = Resource.getImg(getFileName(tileset["image"].get<std :: string>()));
            const int column = tileset["columns"].get<int>(), row = cnt / column;
            sf :: Vector2i size(tileset["tilewidth"], tileset["tileheight"]);
            for(int i = 0; i < row; i++) {
                const auto list = generateList(texture, {0, i}, {column - 1, i}, size);
                imgList.insert(imgList.end(), list.begin(), list.end());
            }
        }
        if(tileset.contains("tiles")) {
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("image")) continue;
                const auto texture = Resource.getImg(getFileName(tile["image"].get<std :: string>()));
                const int x = tile["imagewidth"].get<int>(), y = tile["imageheight"].get<int>();
                const int id = tile["id"].get<int>() + tileset["firstgid"].get<int>();
                assert((int)imgList.size() <= id); 
                imgList.resize(id + 1); imgList[id] = Img(texture, sf :: IntRect({0, 0}, {x, y}));
            }
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("objectgroup")) continue;
                auto &list = rectList[tile["id"].get<int>() + tileset["firstgid"].get<int>()];
                for(const auto &rect : tile["objectgroup"]["objects"])
                    list.emplace_back(rect["x"].get<float>(), rect["y"].get<float>(), rect["width"].get<float>(), rect["height"].get<float>());
                //if(!list.empty()) heightList[tile["id"].get<int>() + tileset["firstgid"].get<int>()] = 1;
            }
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("properties")) continue;
                auto &list = rectList[tile["id"].get<int>() + tileset["firstgid"].get<int>()];
                for(const auto &property : tile["properties"])
                    if(property["name"].get<std :: string>() == "elevation")
                        heightList[tile["id"].get<int>() + tileset["firstgid"].get<int>()] = property["value"].get<int>();
            }
        }
    }
    std :: vector<Animation> animationList(imgList.size());

    for(int i = 1; i < static_cast<int>(imgList.size()); i++)  animationList[i] = Animation((std :: vector<Img>){ imgList[i]});
    for(const auto &tileset : map["tilesets"]) {
        if(tileset.contains("tiles")) {
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("animation")) continue;
                std :: vector<Img> list; float duration = 0.f;
                for(const auto &img : tile["animation"]) {
                    list.emplace_back(imgList[img["tileid"].get<int>() + tileset["firstgid"].get<int>()]);
                    duration = img["duration"].get<int>() / 1000.f;
                }
                animationList[tile["id"].get<int>() + tileset["firstgid"].get<int>()] = Animation(list, duration, true);
            }
        }
    }

    auto calcRect = [](const sf :: FloatRect &position, const sf :: FloatRect &box, bool flip) {
        return sf :: FloatRect(position.left + (flip ? position.width - box.width - box.left : box.left), position.top + box.top, box.width, box.height);
    };
    
    for(const auto &layer : map["layers"]) {
        if(layer["type"].get<std :: string>() == "tilelayer") {
            const int x = layer["height"].get<int>(), y = layer["width"].get<int>(); layers.emplace_back();
            mapSize.x = std :: max(mapSize.x, y * map["tilewidth"].get<int>());
            mapSize.y = std :: max(mapSize.y, x * map["tileheight"].get<int>());
            const auto &size = sf :: Vector2f(map["tilewidth"].get<float>(), map["tileheight"].get<float>());
            for(int i = 0; i < x; i++)
                for(int j = 0; j < y; j++) {
                    const unsigned int id = layer["data"][i * y + j].get<int>();
                    const auto &position = sf :: Vector2f(j * size.x, i * size.y);
                    auto animation = animationList[id & bitmask]; if(id >> 31 & 1) animation.flip();
                    float ysort = 0;
                    if(heightList.contains(id & bitmask)) ysort = position.y + heightList.at(id & bitmask) * size.y;
                    layers.back().insert(Tile(position, animation, ysort));
                    if(rectList.contains(id & bitmask)) {
                        const auto tileRect = sf :: FloatRect(position, size);
                        const auto &rect = rectList[id & bitmask];
                        for(const auto &box : rect)
                            entities.emplace_back(new Collisionbox(calcRect(tileRect, box, id >> 31 & 1)));
                    }
                    
                }
        }
        else if(layer["type"].get<std :: string>() == "objectgroup") {
            //std :: cerr << layer["name"].get<std :: string>() << std :: endl;
            layers.emplace_back();
            for(const auto &object : layer["objects"]) {
                if(!object.contains("gid")) continue;
                const unsigned int id = object["gid"].get<unsigned int>();
                const auto &size = sf :: Vector2f(object["width"].get<float>(), object["height"].get<float>());
                const auto &position = sf :: Vector2f(object["x"].get<float>(), object["y"].get<float>() - size.y);
                auto animation = animationList[id & bitmask]; if(id >> 31 & 1) animation.flip();
                float ysort = position.y + size.y;
                if(rectList.contains(id & bitmask)) {
                    const auto tileRect = sf :: FloatRect(position, size);
                    const auto &rect = rectList[id & bitmask];
                    for(const auto &box : rect) {
                        const auto &tmp = calcRect(tileRect, box, id >> 31 & 1);
                        entities.emplace_back(new Collisionbox(tmp));
                        ysort = std :: max(ysort, tmp.top + tmp.height);
                    }
                }
                layers.back().insert(Tile(position, animation, ysort));
            }
        }
    }
    for(auto &layer : layers) layer.ysort();
    //std :: cerr << mapSize.x << ' ' << mapSize.y << std :: endl;
}

void Tilemap :: update(const float& deltaTime) {
    player.update(deltaTime);
    for(const auto &entity : entities) entity -> update(player, deltaTime);
    for(auto &layer : layers) layer.update(deltaTime);
}
void Tilemap :: render(sf :: RenderTarget* target) const {
    auto tmpview = target -> getView();
    const double &zoom = 0.5f;
    const auto &position = player.getPosition();
    sf :: Vector2f center = {floorf(position.left + position.width / 2.f + 0.5f), floorf(position.top + 0.5f)};
    const sf :: Vector2f &size = {static_cast<float>(target -> getSize().x), static_cast<float>(target -> getSize().y)};
    center.x = std :: max(center.x, ceilf(size.x / 2.f * zoom));
    center.x = std :: min(center.x, floorf(static_cast<float>(mapSize.x) - size.x / 2.f * zoom));
    center.y = std :: max(center.y, ceilf(size.y / 2.f * zoom));
    center.y = std :: min(center.y, floorf(static_cast<float>(mapSize.y) - size.y / 2.f * zoom));
    auto view = sf :: View(center, size); view.zoom(zoom); target -> setView(view);

    const float &playerY = player.getPosition().top + player.getPosition().height;
    for(const auto &layer : layers) layer.beforeRender(target, playerY);
    player.render(target);
    for(const auto &layer : layers) layer.afterRender(target, playerY);
    for(const auto &entity : entities) entity -> render(target);
    target -> setView(tmpview);
}