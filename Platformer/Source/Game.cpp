#include <Game.h>
#include <cmath>

Game::Game(unsigned int width, unsigned int height) 
	:
	view(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))),
	window(sf::VideoMode(width, height), "Platformer", sf::Style::Fullscreen, sf::ContextSettings(32, 24, 8, 4, 2))
{
	window.setView(view);
	//window.setFramerateLimit(120);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	map.load("Levels/level001.txt", sf::Vector2f(width, height));
	map.setWindow(window);

	texture.loadFromFile("Textures/background.png");
	background.setTexture(texture);
	background.setScale(1.5f, 1.5f);

	player.view.setCenter(sf::Vector2f(window.getSize().x / 2.f, map.getHeight() - window.getSize().y / 2.f));

	collision.setMap(map);
	collision.setPlayer(player);
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
			player.view.setCenter(sf::Vector2f(player.getX(), map.getHeight() - window.getSize().y / 2.f));
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
	
	if (player.getX() < map.getWidth() - window.getSize().x * 0.5f && player.getX() > window.getSize().x * 0.5f)
	{
		if (player.getY() < map.getHeight() - window.getSize().y * 0.5f && player.getY() > window.getSize().y * 0.5f)
		{
			player.view.setCenter(sf::Vector2f(player.getX(), player.getY()));
		}
		else
		{
			player.view.setCenter(sf::Vector2f(player.getX(), map.getHeight() - window.getSize().y / 2.f));
		}
	}
	else
	{
		if (player.getY() < map.getHeight() - window.getSize().y * 0.5f && player.getY() > window.getSize().y * 0.5f)
		{
			player.view.setCenter(sf::Vector2f(player.getX(), player.getY()));
		}
		else
		{
			player.view.setCenter(sf::Vector2f(window.getSize().x / 2.f, player.getY()));
		}
	}

	sf::Vector2f centre = player.view.getCenter();
	centre.x -= window.getSize().x / 2;
	centre.y -= window.getSize().y / 2;
	background.setPosition(centre);
}

void Game::render()
{
	window.clear(sf::Color(153, 217, 234));

	window.setView(player.view);

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