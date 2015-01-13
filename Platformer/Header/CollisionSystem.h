#pragma once

#include <SFML\Graphics.hpp>

#include <vector>

#include <TileMap.h>
#include <Sprite.h>
#include <PlayerSprite.h>
#include <SoundPlayer.hpp>

class CollisionSystem : public sf::Drawable
{
public:
	CollisionSystem()
	{
		showCollision = false;
	}

	void setMap(TileMap &map)
	{
		this->map = &map;
	}

	void addPlayer(PlayerSprite &player)
	{
		this->player = &player;
	}

	void addSprite(Sprite &sprite)
	{
		sprites.insert(std::make_pair(sprite.ID, &sprite));
	}

	void removeSprite(int ID)
	{
		sprites.erase(ID);
	}

	void playerChecks(PlayerSprite *player)
	{
		CollisionRectF cRect = player->getCRect();

		//get the tile the bottom centre of the player is over
		float cx = cRect.left + (cRect.right - cRect.left) / 2.f;
		float cy = cRect.bottom;

		int ix = map->getIndexXBiasLeft(cx);
		int iy = map->getIndexYBiasTop(cy);

		if (map->isPickup(ix, iy))	// find tiles that are pickups (collectibles) ie yellowflower etc..
		{
			map->modifyTile(ix, iy, Block::Air);
			player->sounds.play(SoundEffect::PlayerPickup);
			player->scoreboard.increment();
		}
		else if (map->isCheckPoint(ix, iy) || map->isCheckPoint(ix, iy + 1) || map->isCheckPoint(ix, iy + 2)) // find checkpoint tiles
		{
			player->sounds.play(SoundEffect::ID::Checkpoint);
		}
		else //find if player is standing on tile that is climable ie ladders etc.. 
		{
			player->core.canClimb = map->isClimable(ix, iy);
		}
	}

	void perSprite(Sprite *sprite)
	{
		//save sprite velocity to check if damage should be given by fall etc..
		float vx = sprite->core.vx;
		float vy = sprite->core.vy;

		CollisionRectF rect;

		//find and correct collisions with tiles
		while (map->getCRectSingle(sprite->getCRect(), rect) && sprite->isAlive())
		{
			sprite->GetState().OnCollision(rect);
		}

		CollisionRectF rect1;

		for (auto i = sprites.begin(); i != sprites.end(); ++i)
		{
			if (sprite == i->second)
			{
				continue;
			}

			sf::FloatRect r = i->second->getCRect().toSFML();

			if (sprite->getCRect().toSFML().intersects(r))
			{
				sprite->GetState().OnCollision(i->second->getCRect());
			}
		}

		CollisionRectF cRect = sprite->getCRect();

		float cx = cRect.left + (cRect.right - cRect.left) / 2.f;
		float cy = cRect.bottom;

		int ix = map->getIndexXBiasLeft(cx);
		int iy = map->getIndexYBiasTop(cy);

		if (map->isHarmful(ix, iy))	// find tiles that do damage ie lava etc..
		{
			sprite->GetState().applyDamage(1);
		}

		iy = map->getIndexYBiasBottom(cRect.bottom);

		//find if sprite is standing on tile
		for (int ix = map->getIndexXBiasRight(cRect.left), ixEnd = map->getIndexXBiasLeft(cRect.right); ix <= ixEnd; ++ix)
		{
			if (!map->isPassable(ix, iy) && map->getCRect(ix, iy).top == cRect.bottom)
			{
				//if sprite has fallen more than 10 blocks apply fall damage
				int dHeight = iy - sprite->core.lastPlatformHeight / TileData::tileSize.y;

				if (dHeight > 10)
				{
					sprite->GetState().applyDamage(dHeight - 10);
				}

				sprite->core.lastPlatformHeight = iy * TileData::tileSize.y;

				return;
			}
		}
		sprite->GetState().OnFreeFall();
	}

	void calculate()
	{
		for (auto &sprite : sprites)
		{
			perSprite(sprite.second);
		}

		perSprite(player);
		playerChecks(player);
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

	void drawBoundingRect(RectF rect, sf::RenderTarget &target, sf::Color color = sf::Color::White) const
	{
		sf::VertexArray vertices(sf::LinesStrip, 5u);

		vertices[0].position = sf::Vector2f(rect.left, rect.top);
		vertices[1].position = sf::Vector2f(rect.right, rect.top);
		vertices[2].position = sf::Vector2f(rect.right, rect.bottom);
		vertices[3].position = sf::Vector2f(rect.left, rect.bottom);
		vertices[4].position = sf::Vector2f(rect.left, rect.top);

		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;
		vertices[4].color = color;

		target.draw(vertices);
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (showCollision)
		{
			drawBoundingRect(player->getCRect(), target);

			for (auto &s : sprites)
			{
				drawBoundingRect(s.second->getCRect(), target, sf::Color::Red);
			}
		}
	}

	bool showCollision;

	TileMap *map;
	PlayerSprite *player;
	std::map<int, Sprite*> sprites;
};