#include <PauseState.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mPausedText()
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");	
	mPausedText.setCharacterSize(70);
	sf::FloatRect bounds = mPausedText.getLocalBounds();
	mPausedText.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
	mPausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
}

bool PauseState::update()
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStateClear();
			requestStackPush(States::Menu);
		}
		if (event.key.code == sf::Keyboard::Return)
		{
			requestStackPop();
		}
	}
	return false;
}