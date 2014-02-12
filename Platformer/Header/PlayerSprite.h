#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Sprite.h>
#include <State.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>

class PlayerSprite : public Sprite
{
public:
	PlayerSprite(State::Context context);
	virtual ~PlayerSprite();
	void pollEvent(const sf::Event &event);
	sf::View view;
	sf::SoundBuffer buffer;
	sf::Sound jump;
};