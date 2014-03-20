#pragma once

#include <SFML/Graphics.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <Utility.h>

class Scoreboard : public sf::Drawable, public sf::Transformable
{
public:
	Scoreboard(State::Context context)
		:
	mText("", context.fonts->get(Fonts::Main), 25),
	score(0)
	{
		base = "Score: ";
		updateText();
	}

	void increment()
	{
		score += 10;
		updateText();
	}

	void decrement()
	{
		score -= 10;
		updateText();
	}

private:

	void updateText()
	{
		mText.setString(base + toString(score));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mText, states);
	}
	
	int score;
	sf::Text mText;
	std::string base;
};