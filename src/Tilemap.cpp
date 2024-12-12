#include "Tilemap.h"
#include <iostream>
extern Resource resource;

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
void Layer :: render(sf :: RenderTarget* target, const float &y, const bool &flag) const {
    for(const auto &tile : this -> tiles)
        if((tile.getY() < y) ^ flag) tile.render(target);
}

//Tilemap
Tilemap :: Tilemap(const std :: string &file) : mapSize({0, 0}) {
    this -> loadFromFile(*resource.getMap(file));
    player.initAnimation();
}
Tilemap :: ~Tilemap() {
    for(const auto &entity : entities) delete entity;
}

std :: vector<Monster> Tilemap :: getMonsterList() const {
    std :: vector<Monster> mapMonster;
    for(const auto &monster : monsters)
        if(monster.second.any()) mapMonster.emplace_back(monster.second);
    return mapMonster;
}
Player& Tilemap :: playerReference() {
    return player;
}
Monster& Tilemap :: monsterReference(const std :: string &name) {
    return monsters.at(name);
}
void Tilemap :: loadFromFile(const json &map) {

    auto getFileName = [](const std :: string &path) {
        return path.substr(path.find_last_of("\\/") + 1);
    };
    auto to_wstring = [](const std :: string &s){
        setlocale(LC_ALL, "chs"); 
        const char* source = s.c_str();
        const size_t &size = MultiByteToWideChar(CP_UTF8, 0, source, strlen(source), NULL, 0);
        wchar_t *dest = new wchar_t[size + 1]; 
        MultiByteToWideChar(CP_UTF8, 0, source, strlen(source), dest, size);
        dest[size] = 0; std :: wstring result = dest; delete []dest;
        setlocale(LC_ALL, "C");
        return result;
    };

    const unsigned int bitmask = (1 << 29) - 1;
    std :: vector<Img> imgList; imgList.emplace_back();
    std :: unordered_map<unsigned int, std :: vector<sf :: FloatRect> > rectList;
    std :: unordered_map<unsigned int, std :: map<std :: string, const json&> > propertyList;
    
    for(const auto &tileset : map["tilesets"]) {
        assert(tileset["firstgid"].get<size_t>() == imgList.size());
        //std :: cerr << tileset["name"].get<std :: string>() << std :: endl;
        const int cnt = tileset["tilecount"].get<int>();
        if(tileset.contains("image")) {
            const auto texture = resource.getImg(getFileName(tileset["image"].get<std :: string>()));
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
                const auto texture = resource.getImg(getFileName(tile["image"].get<std :: string>()));
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
                imgList[tile["id"].get<int>() + tileset["firstgid"].get<int>()].origin = {list.back().left + list.back().width / 2.f, list.back().top + list.back().height};
            }
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("properties")) continue;
                auto &list = propertyList[tile["id"].get<int>() + tileset["firstgid"].get<int>()];
                for(const auto &property : tile["properties"])
                    list.emplace(property["name"].get<std :: string>(), property["value"]);
            }
        }
    }
    std :: vector<Animation> animationList(imgList.size());
    for(int i = 1; i < static_cast<int>(imgList.size()); i++)  animationList[i] = Animation((std :: vector<Img>){ imgList[i]});
    for(const auto &tileset : map["tilesets"]) {
        if(tileset.contains("tiles")) {
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("objectgroup")) continue;
            }
            for(const auto &tile : tileset["tiles"]) {
                if(!tile.contains("animation")) continue;
                std :: vector<Img> list; float duration = 0.f;
                const sf :: Vector2f &origin = imgList[tile["id"].get<int>() + tileset["firstgid"].get<int>()].origin;
                for(const auto &img : tile["animation"]) {
                    list.emplace_back(imgList[img["tileid"].get<int>() + tileset["firstgid"].get<int>()]);
                    list.back().origin = origin;
                    duration = img["duration"].get<int>() / 1000.f;
                }
                animationList[tile["id"].get<int>() + tileset["firstgid"].get<int>()] = Animation(list, duration, true);
            }
        }
    }
    
    for(const auto &tileset : map["tilesets"]) {
        if(!tileset.contains("tiles")) continue;
        for(const auto &tile : tileset["tiles"]) {
            const unsigned int &id = tile["id"].get<int>() + tileset["firstgid"].get<int>();
            if(!propertyList.contains(id)) continue;
            const auto &list = propertyList[id];
            if(!list.contains("type")) continue;
            Animation animation = animationList[id];
            if(!list.contains("loop")) animation.setLoop(false);
            if(list.at("type").get<std :: string>() == "monster") {
                const std :: string &name = list.at("name").get<std :: string>();
                if(!monsters.contains(name)) monsters.emplace(name, Monster(to_wstring(name)));
                monsters.at(name).insertAction(list.at("action").get<std :: string>(), animation);
                for(const std :: string &attribute : {"health", "attack", "defence"})
                    if(list.contains(attribute)) monsters.at(name).setAttribute(attribute, list.at(attribute).get<int>());
            }
            else if(list.at("type").get<std :: string>() == "player")
                player.insertAnimation(list.at("action").get<std :: string>(), animation);
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
                    const auto &origin = imgList[id & bitmask].origin;
                    const auto &position = sf :: Vector2f(j * size.x, i * size.y);
                    auto animation = animationList[id & bitmask]; if(id >> 31 & 1) animation.flip();
                    float ysort = 0; bool ground = false; std :: string tag = "";
                    if(propertyList.contains(id & bitmask) && propertyList[id & bitmask].contains("elevation"))
                        ysort = position.y + propertyList[id & bitmask].at("elevation").get<int>() * size.y;
                    if(propertyList.contains(id & bitmask) && propertyList[id & bitmask].contains("ground")) ground = true;
                    if(propertyList.contains(id & bitmask) && propertyList[id & bitmask].contains("tag")) tag = propertyList[id & bitmask].at("tag");
                    layers.back().insert(Tile(position + origin, animation, ysort));
                    if(rectList.contains(id & bitmask)) {
                        const auto tileRect = sf :: FloatRect(position, size);
                        const auto &rect = rectList[id & bitmask];
                        for(auto box : rect) {
                            entities.emplace_back(new CollisionBox(calcRect(tileRect, box, id >> 31 & 1), (ground ? "groundHitbox" : "bodyHitbox"), tag));
                        }
                    }
                    
                }
        }
        else if(layer["type"].get<std :: string>() == "objectgroup") {
            const bool interactive = (layer["name"].get<std :: string>() == "interactive");
            if(!interactive) layers.emplace_back();
            for(const auto &object : layer["objects"]) {
                if(!object.contains("gid")) continue;
                const unsigned int id = object["gid"].get<unsigned int>();
                const auto &origin = imgList[id & bitmask].origin;
                const auto &size = sf :: Vector2f(object["width"].get<float>(), object["height"].get<float>());
                const auto &position = sf :: Vector2f(object["x"].get<float>(), object["y"].get<float>() - size.y) + origin;
                auto animation = animationList[id & bitmask]; if(id >> 31 & 1) animation.flip();

                float ysort = position.y - origin.y + size.y; std :: vector<CollisionBox> boxList;
                bool ground = false; std :: string tag = "";
                if(propertyList.contains(id & bitmask) && propertyList[id & bitmask].contains("ground")) ground = true;
                if(propertyList.contains(id & bitmask) && propertyList[id & bitmask].contains("tag")) tag = propertyList[id & bitmask].at("tag");

                if(rectList.contains(id & bitmask)) {
                    const auto tileRect = sf :: FloatRect(position - origin, size);
                    const auto &rect = rectList[id & bitmask];
                    for(const auto &box : rect) {
                        const auto &tmp = calcRect(tileRect, box, id >> 31 & 1);
                        if(!interactive) entities.emplace_back(new CollisionBox(tmp, (ground ? "groundHitbox" : "bodyHitbox"), tag));
                        else boxList.emplace_back(CollisionBox(tmp, (ground ? "groundHitbox" : "bodyHitbox"), tag));
                        ysort = tmp.top + tmp.height;
                    }
                }

                if(!interactive) {
                    layers.back().insert(Tile(position, animation, ysort));
                    continue;
                }
    
                const std :: map<std :: string, const json&> &properties = propertyList.at(id & bitmask);
                if(!properties.contains("loop")) animation.setLoop(false);
                const std :: string &type = properties.at("type").get<std :: string>();
                if(type == "treasure") {
                    entities.emplace_back(new Treasure(position, animation, boxList, ysort));
                }
                else if(type == "door") {
                    entities.emplace_back(new Door(position, animation, boxList, ysort));
                }
                else if(type == "monster") {
                    monsters.at(properties.at("name").get<std :: string>()).add();
                    entities.emplace_back(new MonsterLink(properties.at("name").get<std :: string>(), position, animation, boxList, ysort));
                }
                else if(type == "player") {
                    player.setPosition(position);
                    player.setHitbox("groundHitbox", boxList.back().getBox().getPosition() - position, boxList.back().getBox().getSize()); boxList.pop_back();
                    player.setHitbox("bodyHitbox", boxList.back().getBox().getPosition() - position, boxList.back().getBox().getSize());
                }
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
    const auto originView = target -> getView();
    const float &zoom = 0.5f;
    sf :: Vector2f center = {std :: floor(player.getPosition().x + 0.5f), std :: floor(player.getPosition().y + 0.5f)};
    const sf :: Vector2f &size = {static_cast<float>(target -> getSize().x), static_cast<float>(target -> getSize().y)};
    center.x = std :: max(center.x, std :: ceil(size.x / 2.f * zoom));
    center.x = std :: min(center.x, std :: floor(static_cast<float>(mapSize.x) - size.x / 2.f * zoom));
    center.y = std :: max(center.y, std :: ceil(size.y / 2.f * zoom));
    center.y = std :: min(center.y, std :: floor(static_cast<float>(mapSize.y) - size.y / 2.f * zoom));
    auto view = sf :: View(center, size); view.zoom(zoom); target -> setView(view);

    const float &playerY = player.getPosition().y;
    for(const auto &layer : layers) layer.render(target, playerY, false);
    for(const auto &entity : entities) entity -> render(target, playerY, false);
    player.render(target);
    for(const auto &layer : layers) layer.render(target, playerY, true);
    for(const auto &entity : entities) entity -> render(target, playerY, true);
    target -> setView(originView);

    player.getAttribute().render(target, {10.f, 10.f}, {"health", "attack", "defence", "key"}, "green");
}