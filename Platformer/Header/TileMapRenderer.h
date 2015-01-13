#pragma once

#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Sprite.hpp>

#include <State.hpp>
#include <TileMap.h>
#include <Utility.h>

class TileMapRenderer
{
public:

	enum Mode
	{
		Tiles,
		Lights,
	};

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

	void draw(Mode mode)
	{
		if (mode == Mode::Tiles)
		{
			sf::View view = window.getView();
	
			sprite.setPosition(view.getCenter());

			rTexture.setView(getAlignedView(view));

			sf::RenderStates states;
			states.texture = &mTileset;

			//rTexture.clear(color);
		////	map.drawShadows(window, states);
		//	rTexture.display();

			rTexture.clear(color);
			rTexture.draw(map, states);
			rTexture.display();

			window.draw(sprite, &effect.getShader());
		}
		else if (mode == Mode::Lights)
		{
			map.drawLights(window);
		}
	}

	sf::Color color;
	sf::Sprite sprite;
	sf::Texture mTileset;

	Effect &effect;

	sf::RenderWindow &window;
	sf::RenderTexture rTexture;
	TileMap &map;
};