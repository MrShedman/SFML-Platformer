#include <GameState.hpp>
#include <ResourceHolder.hpp>


GameState::GameState(StateStack& stack, Context context)
: 
State(stack, context),
player(context),
map(context)
{
	sf::Texture& texture = context.textures->get(Textures::GameBackground);
	background.setTexture(texture);

	map.load("Levels/level001.txt");


	background.setOrigin(640, 360);

	collision.setMap(map);
	collision.setPlayer(player);

	player.view = sf::View(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(context.window->getSize()));
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(background);
	window.draw(map);
	window.draw(player);
	window.draw(collision);
}

void GameState::updateView()
{
	sf::RenderWindow& window = *getContext().window;
	sf::FloatRect visibleArea(0, 0, window.getSize().x, window.getSize().y);
	player.view = sf::View(visibleArea);
	sf::Vector2f centre = sf::Vector2f(player.getX(), player.getY());
	player.view.setCenter(centre);
	background.setPosition(centre);
	window.setView(player.view);
}

bool GameState::update()
{
	sf::RenderWindow& window = *getContext().window;

	player.GetState().OnUpdate();

	collision.calculate();
	
	updateView();
	
	map.update();

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	// Escape pressed, trigger the pause screen
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(States::Pause);
	}

	player.pollEvent(event);

	collision.pollEvent(event);

	map.pollEvent(event);

	return true;
}