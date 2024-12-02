#pragma once
#include <SFML/Graphics.hpp>
class Hitbox {
private:
	sf :: Sprite* sprite;
	sf :: RectangleShape outline;
	sf :: Vector2f offset;

public:
	Hitbox(sf::Sprite *sprite, const sf :: Vector2f &offset, const sf :: Vector2f &size);
	virtual ~Hitbox();

	const sf :: Vector2f& getPosition() const;
	//const sf :: FloatRect getGlobalBounds() const;
	//const sf :: FloatRect& getNextPosition(const sf::Vector2f& velocity) const;

	void setPosition(const sf :: Vector2f &position);
	bool intersects(const sf::FloatRect &rect);

	void update();
	void render(sf :: RenderTarget *target = nullptr);
};