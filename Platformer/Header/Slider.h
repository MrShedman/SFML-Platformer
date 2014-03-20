#pragma once

#include <Component.hpp>
#include <ResourceIdentifiers.hpp>
#include <State.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <Utility.h>

#include <vector>
#include <string>
#include <memory>
#include <functional>

namespace GUI
{

class Slider : public Component
{
public:
	typedef std::shared_ptr<Slider>			Ptr;
	typedef std::function<void(int)>		Callback;

	enum Type
	{
		Normal,
		Hover,
		Pressed,
		ButtonCount
	};

public:
	Slider(State::Context context);

	void					setCallback(Callback callback);
	void					setText(const std::string& text);
	void					setSize(sf::Vector2f size);

	void					setCurrentValue(std::string value);
	void					setPossibleValues(std::vector<std::string> values);
	std::string				getDisplayString();

	virtual void			handleEvent(const sf::Event& event);
	virtual void			update();

private:

	bool					mouseOver();
	void					mouseMoved();
	void					mousePressed();
	void					mouseReleased();
	void					changeState(Type buttonType);
	void					setRange(float min, float max);
	int						getIndex();

	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:

	bool						isPressed;
	float						minRange;
	float						maxRange;
	float						offset;

	std::vector<std::string>	possibleValues;
	Callback					mCallback;
	sf::RectangleShape			mOutline;
	sf::RectangleShape			mShape;
	sf::Text					mText;
	sf::RenderWindow			&window;
};

}