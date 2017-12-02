#include <LightManager.h>
#include <ResourceHolder.hpp>
#include <iostream>

Light::Light(sf::Texture &texture, LightData &data)
:
data(data)
{
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setColor(data.color);
	
	float sx = static_cast<float>(texture.getSize().x);
	float sy = static_cast<float>(texture.getSize().y);
	setOrigin(sx / 2.f, sy / 2.f);

	float tx = data.radius * static_cast<float>(TileData::tileSize.x) * 2.f;
	float ty = data.radius * static_cast<float>(TileData::tileSize.y) * 2.f;

	scale = sf::Vector2f(tx / sx, ty / sy);
	setScale(scale);

	size = randomize(0.1f, 1.0f);
}

void Light::update()
{
	if (clock.getElapsedTime() > sf::seconds(1 / data.flickerFrequency))
	{
		float rand = randomize(0.f, data.flickerAmount);
		setScale(scale.x + rand, scale.y + rand);
		clock.restart();
	}
}

sf::Color Light::getColor()
{
	return data.color;
}

void Light::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.blendMode = sf::BlendAdd;
	target.draw(sprite, states);
}

TimeOfDay::TimeOfDay(sf::Image &palette, sf::Time dayNightCycle)
:
palette(palette),
dayNightCycle(dayNightCycle)
{}

void TimeOfDay::update(sf::Time dt)
{
	currentTime += dt;

	if (currentTime >= dayNightCycle)
	{
		currentTime = sf::Time::Zero;
	}
}

void TimeOfDay::forwardTime(sf::Time time)
{
	sf::Time t = (time / sf::seconds(2400)) * dayNightCycle;

	currentTime += t;
}

void TimeOfDay::backTime(sf::Time time)
{
	sf::Time t = (time / sf::seconds(2400)) * dayNightCycle;

	currentTime -= t;

	if (currentTime < sf::seconds(0.f))
	{
		currentTime += dayNightCycle;
	}
}

void TimeOfDay::setTimeOfDay(sf::Time time24hour)
{
	sf::Time irl = sf::seconds(2400);
	float ratio = (time24hour % irl) / irl;
	clamp(ratio, 0.f, 1.f);
	currentTime = ratio * dayNightCycle;
}

sf::Color TimeOfDay::getColorAtCurrentTime()
{
	float position = (currentTime / dayNightCycle) * static_cast<float>(palette.getSize().x);

	return palette.getPixel(static_cast<unsigned int>(position), 240u);
}

LightManager::LightManager(State::Context context)
	:
lightTexture(context.textures->get(Textures::Light)),
timeOfDay(context.images->get(Images::DayNightPalette), sf::seconds(300))
{
	rTexture.create(context.window->getSize().x, context.window->getSize().y);

	float wx = static_cast<float>(context.window->getSize().x);
	float wy = static_cast<float>(context.window->getSize().y);

	sprite.setTexture(rTexture.getTexture());
	sprite.setOrigin(std::floor(wx / 2.f), std::floor(wy / 2.f));
}

void LightManager::addLight(int ID, Tile &tile)
{
	if (lights.count(ID) < 1)
	{
		auto light = std::make_shared<Light>(lightTexture, tile.data->lightData);
		sf::Vector2f position = tile.rect.getCenter();
		light->setPosition(position);		

		lights.insert(std::make_pair(ID, std::move(light)));
	}
}

void LightManager::update(sf::Time dt)
{
	timeOfDay.update(dt);

	for (auto &l : lights)
	{
		l.second->update();
	}
}

void LightManager::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::PageUp)
		{
			timeOfDay.forwardTime(sf::seconds(100));
		}
		else if (event.key.code == sf::Keyboard::PageDown)
		{
			timeOfDay.backTime(sf::seconds(100));
		}
	}
}

void LightManager::removeLight(int ID)
{
	if (lights.count(ID) > 0)
	{
		lights.erase(lights.find(ID));
	}
}

void LightManager::draw(sf::RenderTarget& target)
{
	rTexture.setView(target.getView());

	rTexture.clear(timeOfDay.getColorAtCurrentTime());

	for (auto &l : lights)
	{
		rTexture.draw(*l.second.get());
	}

	rTexture.display();

	sprite.setPosition(target.getView().getCenter());

	target.draw(sprite, sf::BlendMultiply);
}

std::vector<Light*> LightManager::getLights() const
{
	std::vector<Light*> data;

	for (auto &l : lights)
	{
		data.push_back(l.second.get());
	}

	return data;
}