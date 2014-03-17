#include <Utility.h>
#include <random>

sf::Vector2f getMousePosition(sf::RenderWindow &window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

void scaleSpriteToFitWindow(sf::Sprite &sprite, sf::RenderWindow &window)
{
	sf::Vector2u tSize = sprite.getTexture()->getSize();
	sf::Vector2u wSize = window.getSize();

	float sx = static_cast<float>(wSize.x) / static_cast<float>(tSize.x);
	float sy = static_cast<float>(wSize.y) / static_cast<float>(tSize.y);

	sprite.setScale(sx, sy);
}

float randomize(float min, float max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(generator);
}

int randomize(int min, int max)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}