#include <PauseState.hpp>
#include <ResourceHolder.hpp>
#include <Button.hpp>
#include <GameState.hpp>
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

	auto returnButton = std::make_shared<GUI::Button>(context);
	returnButton->setPosition(425, 400);
	returnButton->setText("Return");
	returnButton->setCallback([this]()
	{
		requestStackPop();
	});

	auto exitButton = std::make_shared<GUI::Button>(context);
	exitButton->setPosition(665, 400);
	exitButton->setText("Exit");
	exitButton->setCallback([this]()
	{
		requestStateClear();
		requestStackPush(States::Menu);
	});

	mGUIContainer.pack(returnButton);
	mGUIContainer.pack(exitButton);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());
	mPausedText.setPosition(0.5f * window.getView().getSize().x, 0.4f * window.getView().getSize().y);

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mGUIContainer);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);

	return false;
}