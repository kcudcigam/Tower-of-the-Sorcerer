#include "Attribute.h"
extern Resource resource;
extern Subtitle subtitle;
Attribute :: Attribute(const int &health, const int &attack, const int &defence, const int &key) {
    set("max_health", health), set("health", health);
    set("attack", attack), set("defence", defence), set("key", key);
}
Attribute :: ~Attribute() {

}
void Attribute :: set(const std :: string &type, const int &value) {
    attribute[type] = value;
}
void Attribute :: add(const std :: string &type, const int &value) {
    attribute[type] = std :: max(attribute[type] + value, 0);
    if(type == "health") attribute[type] = std :: min(attribute[type], attribute["max_health"]);
}
int Attribute :: get(const std :: string &type) const {
    return attribute.at(type);
}
void Attribute :: render(sf :: RenderTarget* target, sf :: Vector2f position, const std :: vector<std :: string> &types, const std :: string &color) const {
    for(const auto &type : types) {
        sf :: Sprite sprite; sf :: Text text;
        sprite.setTexture(*resource.getImg(type + "-" + color + ".png"));
        sprite.setPosition(position);
        sprite.setScale({2.f, 2.f});
        text.setFont(*resource.getFont("pixel.ttf"));
        text.setPosition(position + sf :: Vector2f(74.f, 10.f));
        text.setString(std :: to_string(get(type)) + (type == "health" ? "/" + std :: to_string(get("max_health")) : ""));
        target -> draw(sprite), target -> draw(text);
        position.y += 64.f;
    }
}