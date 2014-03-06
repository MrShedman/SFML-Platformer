#pragma once

#include <State.hpp>
#include <SFML/Graphics.hpp>
#include <Utility.h>

class HealthBar : public sf::Drawable
{
public:
	HealthBar(State::Context context)
	{
		texture = context.textures->get(Textures::ID::HealthBar);
		texture.setSmooth(false);

		health.resize(40);

		d = sf::Vector2f(30, 30);
		s = sf::Vector2f(9, 9);

		update(20);
	}

	void update(int hitPoints)
	{
		clamp(hitPoints, 0, 20);

		int half = hitPoints % 2;
		int full = hitPoints - half;
		full /= 2;

		int position = 0;

		while (position < full)
		{
			createHeart(position, sf::Vector2f(9, 0));
			position++;
		}
		while (position < full + half)
		{
			createHeart(position, sf::Vector2f(18, 0));
			position++;
		}
		while (position < 10)
		{
			createHeart(position, sf::Vector2f(0, 0));
			position++;
		}
	}

	void createHeart(int position, sf::Vector2f texCoords)
	{
		int id = position * 4;
		sf::Vector2f l(490 + position * d.x, 650);
		health[id + 0].position = sf::Vector2f(l.x, l.y);
		health[id + 1].position = sf::Vector2f(l.x + d.x, l.y);
		health[id + 2].position = sf::Vector2f(l.x + d.x, l.y + d.y);
		health[id + 3].position = sf::Vector2f(l.x, l.y + d.y);

		sf::Vector2f p = texCoords;
		health[id + 0].texCoords = sf::Vector2f(p.x, p.y);
		health[id + 1].texCoords = sf::Vector2f(p.x + s.x, p.y);
		health[id + 2].texCoords = sf::Vector2f(p.x + s.x, p.y + s.y);
		health[id + 3].texCoords = sf::Vector2f(p.x, p.y + s.y);
	}

private:

	sf::Vector2f d;
	sf::Vector2f s;

	sf::Texture texture;
	std::vector<sf::Vertex> health;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.texture = &texture;
		target.draw(&health[0], 40, sf::Quads, states);
	}
};