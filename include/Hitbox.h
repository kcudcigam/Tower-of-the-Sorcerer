#pragma once
#include <SFML/Graphics.hpp>
class Hitbox {
private:
	sf :: Sprite* sprite;
	sf :: FloatRect box;
	sf :: Vector2f offset;

public:
	Hitbox(sf::Sprite *sprite, const sf :: Vector2f &offset = sf :: Vector2f(0.f, 0.f), const sf :: Vector2f &size = sf :: Vector2f(0.f, 0.f));
	virtual ~Hitbox();

	sf :: Vector2f getPosition() const;
	sf :: Vector2f getOffset() const;
	sf :: Vector2f getSize() const;
	void render(sf :: RenderTarget *target) const;
};