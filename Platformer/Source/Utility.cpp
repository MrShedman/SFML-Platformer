#include <Utility.h>
#include <random>

sf::Vector2f getMousePosition(const sf::RenderWindow &window)
{
	return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

std::vector<sf::VideoMode> getValidVideoModes()
{
	std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();

	// get the best bits per pixel supported
	unsigned int bpp = modes.front().bitsPerPixel;

	// remove all modes that have different bits per pixel
	auto end = std::remove_if(modes.begin(), modes.end(), [&](const sf::VideoMode &v)
	{
		return v.bitsPerPixel != bpp;
	});

	std::vector<sf::VideoMode> validModes;

	// populate new vector with found modes
	for (auto i = modes.begin(); i != end; ++i)
	{
		validModes.emplace_back(i->width, i->height, i->bitsPerPixel);
		//validModes.push_back(sf::VideoMode(i->width, i->height, bpp));
	}

	// reverse so worst is at front and best is at back
	std::reverse(validModes.begin(), validModes.end());

	return validModes;
}


void scaleSpriteToFitWindow(sf::Sprite &sprite, const sf::RenderWindow &window)
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