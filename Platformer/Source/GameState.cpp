#include <GameState.hpp>
#include <ResourceHolder.hpp>


GameState::GameState(StateStack& stack, Context context)
: 
State(stack, context),
player(context),
map(context),
mapEditor(context, map)
{
	sf::Texture& texture = context.textures->get(Textures::GameBackground);
	background.setTexture(texture);

	map.load(context, Levels::Level002);

	background.setOrigin(640.f, 360.f);

	collision.setMap(map);
	collision.setPlayer(player);

	player.view = sf::View(sf::Vector2f(0.f, 0.f), static_cast<sf::Vector2f>(context.window->getSize()));
	player.viewBoundary = RectF(0.f, static_cast<float>(map.getHeight()), 0.f, static_cast<float>(map.getWidth()));
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	updateView();

	window.draw(background);
	window.draw(map);	
	window.draw(mapEditor);
	window.draw(player);
	window.draw(collision);
}

void GameState::updateView()
{
	sf::RenderWindow& window = *getContext().window;
	sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

	player.view = sf::View(visibleArea);
	player.setViewPosition();

	float sx = window.getSize().x / 1280.f;
	float sy = window.getSize().y / 720.f;

	background.setScale(sx, sy);
	background.setPosition(player.view.getCenter());
	window.setView(player.view);
}

bool GameState::update(sf::Time dt)
{
	sf::RenderWindow& window = *getContext().window;

	player.GetState().OnUpdate(dt);

	collision.calculate();
	
	updateView();
	
	map.update(player.getVX(), player.getVY());

	mapEditor.update();

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
			player.viewBoundary = RectF(0.f, static_cast<float>(map.getHeight()), 0.f, static_cast<float>(map.getWidth()));
		}
		if (event.key.code == sf::Keyboard::Num2)
		{
			map.load(getContext(), Levels::Level002);
			player.viewBoundary = RectF(0.f, static_cast<float>(map.getHeight()), 0.f, static_cast<float>(map.getWidth()));
		}
	}

	player.pollEvent(event);

	collision.pollEvent(event);

	map.pollEvent(event);

	mapEditor.pollEvent(event);

	return true;
}