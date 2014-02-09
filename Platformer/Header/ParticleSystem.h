#pragma once

#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable
{
public:

	void update(RectF position)
	{
		m_particles.push_back(sf::milliseconds(3000));

		tl.push_back(sf::Vertex(sf::Vector2f(position.left, position.top), sf::Color::Red));
		tr.push_back(sf::Vertex(sf::Vector2f(position.right, position.top), sf::Color::Green));
		br.push_back(sf::Vertex(sf::Vector2f(position.right, position.bottom), sf::Color::Yellow));
		bl.push_back(sf::Vertex(sf::Vector2f(position.left, position.bottom), sf::Color::Blue));
		

		for (std::size_t i = 0; i < m_particles.size(); ++i)
		{
			m_particles[i] -= clock.getElapsedTime();

			if (m_particles[i] <= sf::Time::Zero)
			{
				tl.erase(tl.begin());
				tr.erase(tr.begin());
				br.erase(br.begin());
				bl.erase(bl.begin());

				m_particles.erase(m_particles.begin());
			}
		}
		clock.restart();
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(&tl[0], tl.size(), sf::LinesStrip, states);
		target.draw(&tr[0], tr.size(), sf::LinesStrip, states);
		target.draw(&br[0], br.size(), sf::LinesStrip, states);
		target.draw(&bl[0], bl.size(), sf::LinesStrip, states);
	}
	
	std::vector<sf::Vertex> tl;
	std::vector<sf::Vertex> tr;
	std::vector<sf::Vertex> br;
	std::vector<sf::Vertex> bl;

	std::vector<sf::Time> m_particles;

	sf::Clock clock;
};