#pragma once

#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable
{
public:

	ParticleSystem()
	{
	}

	void update(RectF position)
	{
		m_particles.push_back(sf::milliseconds(3000));

		top.push_back(sf::Vertex(sf::Vector2f(position.left, position.top), sf::Color::Red));
		bottom.push_back(sf::Vertex(sf::Vector2f(position.right, position.top), sf::Color::Green));
		left.push_back(sf::Vertex(sf::Vector2f(position.right, position.bottom), sf::Color::Yellow));
		right.push_back(sf::Vertex(sf::Vector2f(position.left, position.bottom), sf::Color::Blue));
		

		for (std::size_t i = 0; i < m_particles.size(); ++i)
		{
			m_particles[i] -= clock.getElapsedTime();

			if (m_particles[i] <= sf::Time::Zero)
			{
				top.erase(top.begin());
				bottom.erase(bottom.begin());
				left.erase(left.begin());
				right.erase(right.begin());

				m_particles.erase(m_particles.begin());
			}
		}
		clock.restart();
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(&top[0], top.size(), sf::LinesStrip, states);
		target.draw(&bottom[0], bottom.size(), sf::LinesStrip, states);
		target.draw(&left[0], left.size(), sf::LinesStrip, states);
		target.draw(&right[0], right.size(), sf::LinesStrip, states);
	}
	
	std::vector<sf::Vertex> top;
	std::vector<sf::Vertex> bottom;
	std::vector<sf::Vertex> left;
	std::vector<sf::Vertex> right;

	std::vector<sf::Time> m_particles;

	sf::Clock clock;
};