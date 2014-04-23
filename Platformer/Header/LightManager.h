#pragma once

#include <algorithm>
#include <Utility.h>
#include <Tile.h>
#include <map>
#include <ResourceIdentifiers.hpp>

class Light : public sf::Drawable, public sf::Transformable
{
public:

	Light(sf::Texture &texture, LightData &data);

	void update();

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Vector2f scale;

	sf::Clock clock;

	LightData &data;

	sf::Sprite sprite;
};

class TimeOfDay
{
public:

	TimeOfDay(sf::Image &palette, sf::Time dayNightCycle);

	void update(sf::Time dt);

	void setTimeOfDay(sf::Time time24hour);

	sf::Color getColorAtCurrentTime();

private:

	sf::Time currentTime;
	sf::Time dayNightCycle;
	sf::Image &palette;
};

class LightManager
{
public:

	LightManager(State::Context context);

	void addLight(int ID, Tile &tile);

	void removeLight(int ID);

	void update(sf::Time dt);

	void handleEvent(const sf::Event& event);

	void draw(sf::RenderTarget& target);

private:

	TimeOfDay timeOfDay;

	sf::Texture &lightTexture;
	sf::Sprite sprite;
	sf::RenderTexture rTexture;
	std::map<int, Light> lights;
};