#pragma once

#include <SFML\Graphics.hpp>

#include <TileMap.h>
#include <PlayerSprite.h>

class CollisionSystem : public sf::Drawable
{
public:
	CollisionSystem()
	{
		vertices.setPrimitiveType(sf::LinesStrip);
		showCollision = false;
	}

	void setMap(TileMap &map)
	{
		this->map = &map;
	}

	void setPlayer(PlayerSprite &player)
	{
		this->player = &player;
	}

	void getVisibleContacts()
	{
		vertices.clear();

		RectF rect = player->getCRect();

		vertices.append(sf::Vertex(sf::Vector2f(rect.left, rect.top), sf::Color::Magenta));
		vertices.append(sf::Vertex(sf::Vector2f(rect.right, rect.top), sf::Color::Magenta));
		vertices.append(sf::Vertex(sf::Vector2f(rect.right, rect.bottom), sf::Color::Magenta));
		vertices.append(sf::Vertex(sf::Vector2f(rect.left, rect.bottom), sf::Color::Magenta));
		vertices.append(sf::Vertex(sf::Vector2f(rect.left, rect.top), sf::Color::Magenta));
	}

	void calculate()
	{
		//update vertex array with tiles in contact
		getVisibleContacts();

		CollisionRectF rect;

		//find and correct collisions with tiles
		while (map->getCRectSingle(player->getCRect(), rect))
		{
			player->GetState().OnCollision(rect);
		}

		//update line trails
		particles.update(player->getCRect());

		CollisionRectF cRect = player->getCRect();

		int iy = map->getIndexYBiasBottom(cRect.bottom);

		//find if player is standing on tile
		for (int ix = map->getIndexXBiasRight(cRect.left), ixEnd = map->getIndexXBiasLeft(cRect.right); ix <= ixEnd; ++ix)
		{
			if (!map->isPassable(ix, iy) && map->getCRect(ix, iy).top == cRect.bottom)
			{
				return;
			}
		}
		player->GetState().OnFreeFall();
	}

	void pollEvent(const sf::Event &event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::C)
			{
				showCollision = !showCollision;
			}
		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (showCollision)
		{
			target.draw(vertices, states);
			target.draw(particles, states);
		}
	}

	bool showCollision;

	sf::VertexArray vertices;

	TileMap *map;
	PlayerSprite *player;

	ParticleSystem particles;
};