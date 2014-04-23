#pragma once

#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <State.hpp>
#include <TileMap.h>
#include <Utility.h>

class TileMapRenderer
{
public:

	TileMapRenderer(State::Context context, TileMap &map)
		:
	window(*context.window),
	map(map),
	effect(context.effects->getCurrentEffect())
	{
		float wx = static_cast<float>(context.window->getSize().x);
		float wy = static_cast<float>(context.window->getSize().y);

		effect.getShader().setParameter("InSize", sf::Vector2f(wx, wy));

		mTileset = context.textures->get(Textures::TileMap);

		rTexture.create(window.getSize().x, window.getSize().y);

		sprite.setTexture(rTexture.getTexture());
		sprite.setOrigin(std::floor(wx / 2.f), std::floor(wy / 2.f));

		if (map.getLevelID() == Levels::ID::Level003)
		{
			color = sf::Color(140, 0, 20);
		}
		else
		{
			color = sf::Color(120, 200, 255);
		}
	}

	void update(sf::Time dt)
	{
		effect.update();
	}

	void draw()
	{
		sf::View view = window.getView();
		float x = view.getCenter().x;
		float y = view.getCenter().y;

		//set sprite position before rounding
		sprite.setPosition(x, y);

		x = std::round(x);
		y = std::round(y);
		x += 0.375f;
		y += 0.375f;

		view.setCenter(x, y);
		rTexture.setView(view);

		rTexture.clear(color);
		rTexture.draw(map, &mTileset);
		rTexture.display();

		window.draw(sprite, &effect.getShader());
	}

	sf::Color color;
	sf::Sprite sprite;
	sf::Texture mTileset;

	Effect &effect;

	sf::RenderWindow &window;
	sf::RenderTexture rTexture;
	TileMap &map;
};