#include <MenuState.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
{
	sf::Texture& texture = context.textures->get(Textures::MenuBackground);
	mBackgroundSprite.setTexture(texture);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
}

bool MenuState::update()
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPop();
		}
		else
		{
			requestStackPop();
			requestStackPush(States::Game);
		}
	}

	return false;
}
