#include <Game.h>
#include <cmath>

Game::Game(unsigned int width, unsigned int height) 
	:
	view(sf::FloatRect(0.f, 0.f, static_cast<float>(width), static_cast<float>(height))),
	window(sf::VideoMode(width, height), "Platformer", sf::Style::Default, sf::ContextSettings(32, 24, 8, 4, 2))
{
	window.setView(view);
	//window.setFramerateLimit(120);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	map.load("Levels/level001.txt", sf::Vector2f(width, height));
	map.setWindow(window);

	texture.loadFromFile("Textures/background.png");
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setScale(1.5f, 1.5f);

	player.view.setCenter(sf::Vector2f(window.getSize().x / 2.f, map.getHeight() - window.getSize().y / 2.f));
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
	}
}

void Game::collision()
{
	CollisionRectF rect;

	while (map.getCRectSingle(player.getCRect(), rect))
	{
		player.GetState().OnCollision(rect);
	}

	CollisionRectF cRect = player.getCRect();

	int iy = map.getIndexYBiasBottom(cRect.bottom);

	for (int ix = map.getIndexXBiasRight(cRect.left), ixEnd = map.getIndexXBiasLeft(cRect.right); ix <= ixEnd; ++ix)
	{
		if (!map.isPassable(ix, iy) && map.getCRect(ix, iy).top == cRect.bottom)
		{
			return;
		}
	}
	player.GetState().OnFreeFall();
}

void Game::update()
{
	collision();

	player.GetState().OnUpdate();
	
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