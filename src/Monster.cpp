#include "Monster.h"
//Monster
Monster :: Monster(const std :: wstring &name) : name(name) {

}
Monster :: ~Monster() {

}
bool Monster :: any() const {
    return cnt.first > 0;
}
const std :: wstring& Monster :: getName() const {
    return name;
}
const Attribute& Monster :: getAttribute() const {
    return attribute;
}
const AnimationSet& Monster :: getAnimation() const {
    return animation;
}
void Monster :: insertAction(const std :: string &key, const Animation &action) {
    animation.insert(key, action);
}
void Monster :: setAttribute(const std :: string &key, const int &value) {
    attribute.set(key, value);
    if(key == "health") attribute.set("max_health", value);
}
void Monster :: add() {
    cnt.first++, cnt.second++;
}
void Monster :: del() {
    assert(any()); cnt.first--;
}