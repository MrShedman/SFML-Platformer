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

	map.load(context, Levels::Level001);

	background.setOrigin(640, 360);

	collision.setMap(map);
	collision.setPlayer(player);

	player.view = sf::View(sf::Vector2f(0, 0), static_cast<sf::Vector2f>(context.window->getSize()));
	player.viewBoundary = RectF(0, map.getHeight(), 0, map.getWidth());
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	updateView();
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
	player.setViewPosition();

	float sx = window.getSize().x / 1280.f;
	float sy = window.getSize().y / 720.f;

	background.setScale(sx, sy);
	background.setPosition(player.view.getCenter());
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
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPush(States::Pause);
		}
		if (event.key.code == sf::Keyboard::Num1)
		{
			map.load(getContext(), Levels::Level001);
		}
		if (event.key.code == sf::Keyboard::Num2)
		{
			map.load(getContext(), Levels::Level002);
		}
	}

	player.pollEvent(event);

	collision.pollEvent(event);

	map.pollEvent(event);

	return true;
}