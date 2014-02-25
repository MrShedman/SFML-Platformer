#include <GameState.hpp>
#include <ResourceHolder.hpp>


GameState::GameState(StateStack& stack, Context context)
: 
State(stack, context),
player(context),
map(context),
mapEditor(context, map),
mRender(context, map)
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
	
	updateView();
	
	mRender.draw();
	window.draw(mapEditor);
	window.draw(player);
	window.draw(collision);
}

void GameState::updateView()
{
	sf::RenderWindow& window = *getContext().window;
	sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f), static_cast<sf::Vector2f>(window.getSize()));
	player.view = sf::View(visibleArea);
	player.setViewPosition();

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

	player.handleEvent(event);

	collision.handleEvent(event);

	map.handleEvent(event);

	mapEditor.handleEvent(event);

	mRender.handleEvent(event);

	return true;
}