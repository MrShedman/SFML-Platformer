#pragma once

#include <SFML\Graphics\Shader.hpp>
#include <string>

class Effect : private sf::NonCopyable
{
public:

	virtual ~Effect()
	{}

	const std::string& getName() const
	{
		return m_name;
	}

	void load()
	{
		m_isLoaded = sf::Shader::isAvailable() && onLoad();
	}

	void update()
	{
		if (m_isLoaded)
		{
			onUpdate();
		}
	}

	sf::Shader& getShader()
	{
		return m_shader;
	}

protected:

	Effect(const std::string& name) : m_name(name), m_isLoaded(false)
	{}

	sf::Shader m_shader;

private:

	// Virtual functions to be implemented in derived effects
	virtual bool onLoad() = 0;
	virtual void onUpdate() = 0;

private:

	std::string m_name;
	bool m_isLoaded;
};