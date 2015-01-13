#pragma once

#include <SFML/Graphics.hpp>
#include <EnemySprite.h>
#include <algorithm>
#include <Utility.h>
#include <Tile.h>
#include <CollisionSystem.h>
#include <map>

class EnemyFactory : public sf::Drawable
{
public:

	EnemyFactory(State::Context context, CollisionSystem &cSystem, int maxSize)
		:
	context(context),
	cSystem(cSystem),
	maxSize(maxSize),
	count(0)
	{}

	void addEnemy(sf::Vector2f position)
	{
		++count;
		enemies.insert(std::make_pair(count, std::make_unique<EnemySprite>(context, position, count)));
		
		auto found = enemies.find(count);

		cSystem.addSprite(*found->second.get());
	}

	void removeEnemy(int ID)
	{
		enemies.erase(ID);
		cSystem.removeSprite(ID);

		std::cout << "Enemy Removed: " << ID << std::endl;
	}

	void update(sf::Time dt)
	{
		for (auto &s : spawnerLocations)
		{
			int rand = randomize(0, 100);

			if (rand == 42 && enemies.size() < maxSize)
			{
				float x = s->rect.left - 96.f + randomize(0.f, 240.f);
				float y = s->rect.top;
				
				addEnemy(sf::Vector2f(x, y));
			}
		}
	
		std::vector<int> removal;

		for (auto &e : enemies)
		{
			e.second->GetState().OnUpdate(dt);
			e.second->updateLife(dt);

			if (e.second->lifeTime < sf::Time::Zero)
			{
				removal.push_back(e.first);
			}
		}

		for (auto &i : removal)
		{
			removeEnemy(i);
		}
	}	

	void addSpawnerTile(SpawnerTile *tile)
	{
		spawnerLocations.push_back(tile);
		std::cout << "Add x: " << tile->rect.left << "y: " << tile->rect.top << " Size: " << spawnerLocations.size() << std::endl;
	}

	void removeSpawnerTile(SpawnerTile *tile)
	{
		auto end = std::remove_if(spawnerLocations.begin(), spawnerLocations.end(), [&](SpawnerTile *t){return t == tile; });

		auto size = end - spawnerLocations.begin();

		spawnerLocations.resize(size);

		std::cout << "Remove x: " << tile->rect.left << "y: " << tile->rect.top << " Size: " << spawnerLocations.size() << std::endl;
	}

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto &e : enemies)
		{
			target.draw(*e.second.get());
		}
	}

	State::Context context;

	int maxSize;
	int count;

	CollisionSystem &cSystem;

	std::vector<SpawnerTile*> spawnerLocations;
	
	std::map<int, std::unique_ptr<EnemySprite>> enemies;
};