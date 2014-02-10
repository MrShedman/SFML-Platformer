#include <Game.h>
#include <cmath>

Game::Game(unsigned int width, unsigned int height) 
	:
	view(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))),
	window(sf::VideoMode(width, height), "Platformer", sf::Style::Default, sf::ContextSettings(32, 24, 8, 4, 2))
{
	window.setView(view);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	map.load("Levels/level001.txt", sf::Vector2f(width, height));
	map.setWindow(window);

	texture.loadFromFile("Textures/background.png");
	background.setTexture(texture);
	background.setScale(1.5f, 1.5f);

	collision.setMap(map);
	collision.setPlayer(player);

	player.view = sf::View(sf::FloatRect(0, 0, width, height));
}

void Game::getInput()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			clean();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				clean();
			}
		}
		if (event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			player.view = sf::View(visibleArea);
			player.view.setCenter(sf::Vector2f(player.getX(), player.getY()));
		}
			
		player.pollEvent(event);

		map.pollEvent(event);

		collision.pollEvent(event);
	}
}

void Game::update()
{
	player.GetState().OnUpdate();

	collision.calculate();
	
	player.view.setCenter(sf::Vector2f(player.getX(), player.getY()));
	
	sf::Vector2f centre = player.view.getCenter();
	centre.x -= window.getSize().x / 2;
	centre.y -= window.getSize().y / 2;
	background.setPosition(centre);
	window.setView(player.view);

	map.update();
}

void Game::render()
{
	window.clear(sf::Color(153, 217, 234));

	window.draw(background);

	window.draw(map);

	window.draw(player);

	window.draw(collision);
	
	window.display();
}

void Game::clean()
{
	window.close();
}

void Game::run()
{
	while (window.isOpen())
	{
		getInput();
		update();
		render();		
	}

	clean();
}