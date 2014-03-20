#pragma once

#include <SFML\Graphics.hpp>

#include <TileMap.h>
#include <PlayerSprite.h>
#include <SoundPlayer.hpp>

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
		//save player velocity to check if damage should be given by fall etc..
		float vx = player->core.vx;
		float vy = player->core.vy;

		//update vertex array with tiles in contact
		getVisibleContacts();

		CollisionRectF rect;

		//find and correct collisions with tiles
		while (map->getCRectSingle(player->getCRect(), rect) && player->isAlive())
		{
			player->GetState().OnCollision(rect);
		}

		//update line trails
		particles.update(player->getCRect());

		CollisionRectF cRect = player->getCRect();

		//get the tile the bottom centre of the player is over
		float cx = cRect.left + (cRect.right - cRect.left) / 2.f;
		float cy = cRect.bottom;

		int ix = map->getIndexXBiasLeft(cx);
		int iy = map->getIndexYBiasTop(cy);

		// find tiles that do damage ie lava etc..
		if (map->isHarmful(ix, iy))
		{
			player->GetState().applyDamage(1);
		}

		// find tiles that are pickups (collectibles) ie yellowflower etc..
		if (map->isPickup(ix, iy))
		{
			map->modifyTile(ix, iy, Block::ID::Air);
			player->sounds.play(SoundEffect::ID::PlayerPickup);
			player->scoreboard.increment();
		}

		//find if player is standing on tile that is climable ie ladders etc..
		player->core.canClimb = map->isClimable(ix, iy);

		iy = map->getIndexYBiasBottom(cRect.bottom);

		//find if player is standing on tile
		for (int ix = map->getIndexXBiasRight(cRect.left), ixEnd = map->getIndexXBiasLeft(cRect.right); ix <= ixEnd; ++ix)
		{
			if (!map->isPassable(ix, iy) && map->getCRect(ix, iy).top == cRect.bottom)
			{
				//if player has fallen more than 10 blocks apply fall damage
				int dHeight = iy - player->core.lastPlatformHeight / TileData::tileSize.y;

				if (dHeight > 10)
				{
					player->GetState().applyDamage(dHeight - 10);
				}

				player->core.lastPlatformHeight = iy * TileData::tileSize.y;

				return;
			}
		}
		player->GetState().OnFreeFall();
	}

	void handleEvent(const sf::Event &event)
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