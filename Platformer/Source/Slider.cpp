#include <Slider.h>

#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{

Slider::Slider(State::Context context)
	: mCallback()
	, mShape(sf::Vector2f(240, 70))
	, mText("", context.fonts->get(Fonts::Main), 35)
	, window(*context.window)
	, isPressed(false)
{
	changeState(Normal);

	mOutline.setFillColor(sf::Color(150, 150, 150));
	mOutline.setOutlineThickness(-5.f);
	mOutline.setOutlineColor(sf::Color::Black);

	mShape.setOutlineThickness(-5.f);
	mShape.setOutlineColor(sf::Color::Black);

	sf::FloatRect bounds = mShape.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f - 5);
	mText.setColor(sf::Color::White);
}

void Slider::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Slider::setPossibleValues(std::vector<std::string> values)
{
	possibleValues = values;

	setText(getDisplayString());
}


void Slider::setCurrentValue(std::string value)
{
	int size = static_cast<float>(possibleValues.size());

	for (int i = 0; i < size; ++i)
	{
		if (value == possibleValues[i])
		{
			float percent = static_cast<float>(i) / static_cast<float>((size - 1));

			float position = (maxRange - minRange) * percent + minRange;
			position = std::ceil(position);
			mShape.setPosition(position, mShape.getPosition().y);
		}
	}

	setText(getDisplayString());
}

void Slider::setText(const std::string& text)
{
	mText.setString(text);
	sf::FloatRect bounds = mText.getLocalBounds();
	mText.setOrigin(std::floor((bounds.left + bounds.width) / 2.f), std::floor((bounds.top + bounds.height) / 2.f));
	bounds = mOutline.getGlobalBounds();
	mText.setPosition(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f - 5);	
}

void Slider::setRange(float min, float max)
{
	minRange = min;
	maxRange = max - mShape.getSize().x;
}

void Slider::setSize(sf::Vector2f size)
{
	mShape.setSize(sf::Vector2f(30, size.y));
	mOutline.setSize(size);

	float max = mOutline.getLocalBounds().left + mOutline.getLocalBounds().width;

	setRange(0.f, max);
}

void Slider::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseMoved)
	{
		mouseMoved();
	}
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		mousePressed();
	}
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		mouseReleased();
	}
}

void Slider::update()
{

}

int	Slider::getIndex()
{
	float percent = (mShape.getPosition().x - minRange) / (maxRange - minRange);
	float size = possibleValues.size() - 1;

	int index =  std::ceil(percent * size);

	clamp(index, 0, static_cast<int>(possibleValues.size() - 1));

	return index;
}

std::string Slider::getDisplayString()
{
	return possibleValues[getIndex()];
}

bool Slider::mouseOver()
{
	return getTransform().transformRect(mShape.getGlobalBounds()).contains(getMousePosition(window));
}

void Slider::mouseMoved()
{
	if (isPressed)
	{
		float newPos = getMousePosition(window).x - offset;
		float oldPos = newPos;

		clamp(newPos, minRange, maxRange);

		// if we are at edge calculate new offset
		if (oldPos != newPos)
		{
			offset = getMousePosition(window).x - mShape.getPosition().x;
		}

		mShape.setPosition(newPos, mShape.getPosition().y);

		setText(getDisplayString());

		mCallback(getIndex());
	}

	if (mouseOver())
	{
		isPressed ? changeState(Pressed) : changeState(Hover);
	}
	else
	{
		changeState(Normal);
		isPressed = false;
	}
}

void Slider::mousePressed()
{
	if (mouseOver())
	{
		//find offset between first click and sliders top left corner
		offset = getMousePosition(window).x - mShape.getPosition().x;

		changeState(Pressed);
		isPressed = true;
	}
	else if (getTransform().transformRect(mOutline.getGlobalBounds()).contains(getMousePosition(window)))
	{
		float newPos = getMousePosition(window).x - getPosition().x - mShape.getSize().x / 2.f;

		clamp(newPos, minRange, maxRange);
		
		mShape.setPosition(newPos, mShape.getPosition().y);
		
		setText(getDisplayString());

		mCallback(getIndex());

		offset = getMousePosition(window).x - mShape.getPosition().x;

		changeState(Pressed);
		isPressed = true;
	}
}

void Slider::mouseReleased()
{
	if (mouseOver() && isPressed)
	{
		changeState(Hover);
		isPressed = false;
	}
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mOutline, states);
	target.draw(mShape, states);
	target.draw(mText, states);
}

void Slider::changeState(Type buttonType)
{
	sf::Color color;

	switch (buttonType)
	{

	case Pressed: color = sf::Color(255, 177, 0);  break;

	case Hover: color = sf::Color(181, 230, 29); break;

	case Normal: color = sf::Color(31, 177, 76);  break;

	}

	mShape.setFillColor(color);
}

}