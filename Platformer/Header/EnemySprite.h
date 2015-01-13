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

	sf::RectangleShape outline;
	sf::RectangleShape health;

	void updateLife(sf::Time dt)
	{
		lifeTime -= dt;

		float percent = 1.f / life.asSeconds() * lifeTime.asSeconds();

		float size = percent * 70.f;

		health.setSize(sf::Vector2f(size, 14.f - 2.f * 2.f));
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Time life;
	sf::Time lifeTime;

	void reset();
};