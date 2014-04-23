#include <GameState.hpp>
#include <ResourceHolder.hpp>
#include <MusicPlayer.hpp>
#include <SoundPlayer.hpp>


GameState::GameState(StateStack& stack, Context context)
:
State(stack, context),
player(context),
enemyFactory(context, collision, 100),
map(context, enemyFactory),
mapEditor(context, map),
mRender(context, map),
health(context)
{
	collision.setMap(map);

	collision.addPlayer(player);

	camera.setSpriteToFollow(player);
	camera.setViewBoundary(map.getBoundary());
	camera.setViewSize(static_cast<sf::Vector2f>(context.window->getSize()));

	context.music->play(static_cast<Music::ID>(randomize(Music::GameTheme001, Music::GameTheme003)));
}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	
	window.setView(camera.getView());
	
	mRender.draw();
	enemyFactory.draw(window);
	window.draw(mapEditor);
	window.draw(player);
	
	map.drawLights(window);

	window.draw(collision);

	window.setView(window.getDefaultView());
	window.draw(health);
	window.draw(player.scoreboard);

	window.setView(camera.getView());
}

bool GameState::update(sf::Time dt)
{
	sf::RenderWindow& window = *getContext().window;

	player.GetState().OnUpdate(dt);
	enemyFactory.update(dt);

	if (clock.getElapsedTime() > sf::seconds(1) && player.isAlive())
	{
		player.core.health++;
		clamp(player.core.health, 0, 20);
		clock.restart();
	}
	
	collision.calculate();

	health.update(player.core.health);

	camera.updatePosition(dt);
	window.setView(camera.getView());
	
	map.update(dt);

	mapEditor.update();

	mRender.update(dt);

	return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::Resized)
	{
		camera.setViewSize(static_cast<sf::Vector2f>(getContext().window->getSize()));
	}
	if (event.type == sf::Event::KeyPressed)
	{
		// Escape pressed, trigger the pause screen
		if (event.key.code == sf::Keyboard::Escape)
		{
			requestStackPush(States::Pause);
		}
	}

	player.handleEvent(event);

	collision.handleEvent(event);

	map.handleEvent(event);

	getContext().window->setView(camera.getView());
	mapEditor.handleEvent(event);

	return true;
}