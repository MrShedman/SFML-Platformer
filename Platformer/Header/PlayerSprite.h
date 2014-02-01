#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Sprite.h"

class PlayerSprite : public Sprite
{
public:
	PlayerSprite();
	virtual ~PlayerSprite();
	void pollEvent(sf::Event &event);
	sf::View view;
	sf::SoundBuffer buffer;
	sf::Sound jump;
};