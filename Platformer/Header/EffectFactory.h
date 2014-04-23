#pragma once

#include <Effect.h>
#include <SFML/System/Clock.hpp>

#include <memory>
#include <map>

class Default : public Effect
{
public:

	Default() :
		Effect("Default")
	{}

	bool onLoad()
	{
		return true;
	}

	void onUpdate()
	{}
};

class Acid : public Effect
{
public:

	Acid() :
		Effect("Acid")
	{}

	bool onLoad()
	{
		// Load the shader
		if (!m_shader.loadFromFile("Shaders/acid.fsh", sf::Shader::Fragment))
		{
			return false;
		}

		m_shader.setParameter("DiffuseSampler", sf::Shader::CurrentTexture);

		clock.restart();
		return true;
	}

	void onUpdate()
	{
		m_shader.setParameter("Time", clock.getElapsedTime().asSeconds());
		m_shader.setParameter("Frequency", sf::Vector2f(64.f, 64.f));
		m_shader.setParameter("WobbleAmount", sf::Vector2f(0.003f, 0.003f));
	}

private:

	sf::Clock clock;
};

class Invert : public Effect
{
public:

	Invert() :
		Effect("Invert")
	{}

	bool onLoad()
	{
		// Load the shader
		if (!m_shader.loadFromFile("Shaders/invert.fsh", sf::Shader::Fragment))
		{
			return false;
		}

		m_shader.setParameter("DiffuseSampler", sf::Shader::CurrentTexture);

		m_shader.setParameter("InverseAmount", 1.f);

		return true;
	}

	void onUpdate()
	{}
};

class Outline : public Effect
{
public:

	Outline() :
		Effect("Outline")
	{}

	bool onLoad()
	{
		// Load the shader
		if (!m_shader.loadFromFile("Shaders/outline.fsh", sf::Shader::Fragment))
		{
			return false;
		}

		m_shader.setParameter("DiffuseSampler", sf::Shader::CurrentTexture);

		return true;
	}

	void onUpdate()
	{}
};

class PinCushion : public Effect
{
public:

	PinCushion() :
		Effect("PinCushion")
	{}

	bool onLoad()
	{
		// Load the shader
		if (!m_shader.loadFromFile("Shaders/pincushion.fsh", sf::Shader::Fragment))
		{
			return false;
		}

		m_shader.setParameter("DiffuseSampler", sf::Shader::CurrentTexture);

		return true;
	}

	void onUpdate()
	{}
};

class EffectFactory
{
public:
	EffectFactory()
	{
		mCurrentEffect = Effects::Default;
		load();
	}

	void load()
	{
		insert(Effects::Default, std::make_unique<Default>());
		insert(Effects::Acid, std::make_unique<Acid>());
		insert(Effects::Invert, std::make_unique<Invert>());
		insert(Effects::Outline, std::make_unique<Outline>());
		insert(Effects::PinCushion, std::make_unique<PinCushion>());

		for (auto &e : mResourceMap)
		{
			e.second->load();
		}
	}

	Effect& getEffect(Effects::ID id)
	{
		return *mResourceMap.find(id)->second.get();
	}


	Effect& getCurrentEffect()
	{
		return getEffect(mCurrentEffect);
	}

	std::vector<Effect*> getAllEffects()
	{
		std::vector<Effect*> vec;

		for (auto &e : mResourceMap)
		{
			vec.push_back(e.second.get());
		}

		return vec;
	}

	void setCurrentEffect(Effects::ID id)
	{
		mCurrentEffect = id;
	}

private:

	void insert(Effects::ID id, std::unique_ptr<Effect> resource)
	{
		mResourceMap.insert(std::make_pair(id, std::move(resource)));
	}

	Effects::ID mCurrentEffect;

	std::map<Effects::ID, std::unique_ptr<Effect>> mResourceMap;
};