#include <Button.hpp>
#include <ResourceHolder.hpp>
#include <iostream>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace GUI
{

Button::Button(State::Context context)
: mCallback()
, mShape(sf::Vector2f(200, 50))
, mText("", context.fonts->get(Fonts::Main), 20)
, window(context.window)
{
	changeState(Normal);
	mShape.setOutlineThickness(-5.f);
	mShape.setOutlineColor(sf::Color::Black);

	sf::FloatRect bounds = mShape.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void Button::setCallback(Callback callback)
{
	mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
	mText.setString(text);
	sf::FloatRect bounds = mText.getLocalBounds();
	mText.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void Button::setToggle(bool flag)
{
	
}

void Button::handleEvent(const sf::Event& event)
{
	sf::Vector2i worldPos = static_cast<sf::Vector2i>(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

	if (event.type == sf::Event::MouseMoved)
	{
		mouseMoved(worldPos.x, worldPos.y);
	}
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		mousePressed(worldPos.x, worldPos.y);
	}
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
	{
		mouseReleased(worldPos.x, worldPos.y);
	}
}

bool Button::mouseOver(int x, int y)
{
	return getTransform().transformRect(mShape.getLocalBounds()).contains(static_cast<float>(x), static_cast<float>(y));
}

void Button::mouseMoved(int x, int y)
{
	if (mouseOver(x, y))
	{
		isPressed ? changeState(Pressed) : changeState(Hover);
	}
	else
	{
		changeState(Normal);
		isPressed = false;
	}
}

void Button::mousePressed(int x, int y)
{
	if (mouseOver(x, y))
	{
		changeState(Pressed);
		isPressed = true;
	}
}

void Button::mouseReleased(int x, int y)
{
	if (mouseOver(x, y) && isPressed)
	{
		changeState(Hover);
		isPressed = false;
		mCallback();
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mShape, states);
	target.draw(mText, states);
}

void Button::changeState(Type buttonType)
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