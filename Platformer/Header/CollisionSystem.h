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

	void setQuad(int index, RectF rect)
	{
		sf::Vertex* quad = &vertices[index * 5];

		quad[0].position = sf::Vector2f(rect.left, rect.top);
		quad[1].position = sf::Vector2f(rect.right, rect.top);
		quad[2].position = sf::Vector2f(rect.right, rect.bottom);
		quad[3].position = sf::Vector2f(rect.left, rect.bottom);
		quad[4].position = sf::Vector2f(rect.left, rect.top);

		quad[0].color = sf::Color::Red;
		quad[1].color = sf::Color::Red;
		quad[2].color = sf::Color::Red;
		quad[3].color = sf::Color::Red;
		quad[4].color = sf::Color::Red;
	}

	void getVisibleContacts()
	{
		vertices.clear();

		std::vector<RectF> list;

		map->getCRectList(player->getCRect(), list);

		vertices.resize((list.size() + 1) * 5);

		for (std::size_t i = 0; i < list.size(); ++i)
		{
			setQuad(i, list[i]);
		}

		setQuad(list.size(), player->getCRect());
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

	void pollEvent(sf::Event &event)
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