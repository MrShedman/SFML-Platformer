#pragma once

#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <State.hpp>
#include <TileMap.h>

class TileMapRenderer
{
public:

	TileMapRenderer(State::Context context, TileMap &map)
		:
	window(context.window),
	map(&map)
	{
		rTexture.create(window->getSize().x, window->getSize().y);
	}

	void handleEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::Resized)
		{
			rTexture.create(event.size.width, event.size.height);
		}
	}

	void draw()
	{
		sf::View view = window->getView();
		rTexture.setView(view);

		rTexture.clear(sf::Color::Transparent);
		rTexture.draw(*map);
		rTexture.display();

		const sf::Texture& texture = rTexture.getTexture();

		// draw it to the window
		sf::Sprite sprite(texture);
		float cx = view.getCenter().x - window->getSize().x / 2;
		float cy = view.getCenter().y - window->getSize().y / 2;
		sprite.setPosition(cx ,cy);

		window->draw(sprite);
	}

	sf::RenderWindow *window;
	sf::RenderTexture rTexture;
	TileMap *map;
};