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
		m_tileset = context.textures->get(Textures::ID::TileMap);
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
		float x = view.getCenter().x;
		float y = view.getCenter().y;
		float cx = x - window->getSize().x / 2;
		float cy = y - window->getSize().y / 2;

		x = std::floor(x);
		y = std::floor(y);
		x += 0.375f;
		y += 0.375f;

		view.setCenter(x, y);
		rTexture.setView(view);

		sf::RenderStates states;
		states.texture = &m_tileset;

		rTexture.clear(sf::Color::Transparent);
		rTexture.draw(*map, states);
		rTexture.display();

		// draw it to the window
		sf::Sprite sprite(rTexture.getTexture());
		sprite.setPosition(cx ,cy);

		window->draw(sprite);
	}

	sf::Texture m_tileset;
	sf::RenderWindow *window;
	sf::RenderTexture rTexture;
	TileMap *map;
};