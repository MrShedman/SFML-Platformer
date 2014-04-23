#pragma once

#include <SFML/Window/Event.hpp>

#include <Sprite.h>
#include <State.hpp>
#include <Scoreboard.h>

class EnemySprite : public Sprite
{
public:
	EnemySprite(State::Context context, sf::Vector2f position, int ID);
	virtual ~EnemySprite();
	void handleEvent(const sf::Event &event);

	sf::Time lifeTime;

	void reset();
};