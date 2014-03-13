#include <GameState.hpp>
#include <ResourceHolder.hpp>


GameState::GameState(StateStack& stack, Context context)
:
State(stack, context),
player(context),
map(context),
mapEditor(context, map),
mRender(context, map),
health(context)
{
	sf::Texture& texture = context.textures->get(Textures::GameBackground);
	background.setTexture(texture);

	map.load(context, Levels::Level001);

	collision.setMap(map);
	collision.setPlayer(player);
	player.viewBoundary = RectF(0.f, static_cast<float>(map.getHeight()), 0.f, static_cast<float>(map.getWidth()));
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.setView(window.getDefaultView());
	window.draw(background);
	
	window.setView(player.view);
	
	mRender.draw();
	window.draw(mapEditor);
	window.draw(player);
	window.draw(collision);
	window.setView(window.getDefaultView());
	window.draw(health);

	window.setView(player.view);
}

void GameState::updateView(sf::Time dt)
{
	sf::RenderWindow& window = *getContext().window;
	player.setViewPosition(dt);

	window.setView(player.view);
}

bool GameState::update(sf::Time dt)
{
	sf::RenderWindow& window = *getContext().window;

	player.GetState().OnUpdate(dt);

	if (clock.getElapsedTime() > sf::seconds(1) && player.isAlive())
	{
		player.core.health++;
		clamp(player.core.health, 0, 20);
		clock.restart();
	}

	collision.calculate();

	health.update(player.core.health);

	updateView(dt);
	
	map.update(player.getVX(), player.getVY());

	mapEditor.update();

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Resized)
	{
		sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(event.size.width, event.size.height));
		player.view.reset(visibleArea);
	}

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
		if (event.key.code == sf::Keyboard::Num3)
		{
			map.load(getContext(), Levels::Level003);
			player.viewBoundary = RectF(0.f, static_cast<float>(map.getHeight()), 0.f, static_cast<float>(map.getWidth()));
		}
	}

	player.handleEvent(event);

	collision.handleEvent(event);

	map.handleEvent(event);

	mapEditor.handleEvent(event);

	mRender.handleEvent(event);

	return true;
}