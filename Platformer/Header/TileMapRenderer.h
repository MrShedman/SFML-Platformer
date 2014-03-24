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
	window(context.window),
	map(&map)
	{
		mTileset = context.textures->get(Textures::TileMap);

		rTexture.create(window->getSize().x, window->getSize().y);
		sprite.setTexture(rTexture.getTexture());
		sprite.setOrigin(window->getSize().x / 2, window->getSize().y / 2);

		if (map.getLevelID() == Levels::ID::Level003)
		{
			color = sf::Color(140, 0, 20);
		}
		else
		{
			color = sf::Color(120, 200, 255);
		}
	}

	void handleEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::Resized)
		{
			rTexture.create(event.size.width, event.size.height);
			sprite.setTexture(rTexture.getTexture(), true);
			sprite.setOrigin(window->getSize().x / 2, window->getSize().y / 2);
		}
	}

	void draw()
	{
		sf::View view = window->getView();
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

		sf::RenderStates states;
		states.texture = &mTileset;

		rTexture.clear(color);
		rTexture.draw(*map, states);
		rTexture.display();

		window->draw(sprite);
	}

	sf::Color color;
	sf::Sprite sprite;
	sf::Texture mTileset;

	sf::RenderWindow *window;
	sf::RenderTexture rTexture;
	TileMap *map;
};