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
		m_shader.setParameter("Frequency", sf::Vector2f(128.0, 128.0)); //sf::Vector2f(512.0, 288.0));
		m_shader.setParameter("WobbleAmount", sf::Vector2f(0.003, 0.003));
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
		std::unique_ptr<Effect> default(new Default());
		default->load();
		mResourceMap.insert(std::make_pair(Effects::Default, std::move(default)));

		std::unique_ptr<Effect> acid(new Acid());
		acid->load();
		mResourceMap.insert(std::make_pair(Effects::Acid, std::move(acid)));

		std::unique_ptr<Effect> invert(new Invert());
		invert->load();
		mResourceMap.insert(std::make_pair(Effects::Invert, std::move(invert)));

		std::unique_ptr<Effect> outline(new Outline());
		outline->load();
		mResourceMap.insert(std::make_pair(Effects::Outline, std::move(outline)));

		std::unique_ptr<Effect> pinCushion(new PinCushion());
		pinCushion->load();
		mResourceMap.insert(std::make_pair(Effects::PinCushion, std::move(pinCushion)));
	}

	Effect& getEffect(Effects::ID id)
	{
		return *mResourceMap.find(id)->second;
	}


	Effect& getCurrentEffect()
	{
		return getEffect(mCurrentEffect);
	}

	std::vector<Effect*> getAllEffects()
	{
		std::vector<Effect*> vec;

		vec.push_back(&getEffect(Effects::Default));
		vec.push_back(&getEffect(Effects::Acid));
		vec.push_back(&getEffect(Effects::Invert));
		vec.push_back(&getEffect(Effects::Outline));
		vec.push_back(&getEffect(Effects::PinCushion));

		return vec;
	}

	void setCurrentEffect(Effects::ID id)
	{
		mCurrentEffect = id;
	}

private:

	Effects::ID mCurrentEffect;

	std::map<Effects::ID, std::unique_ptr<Effect>> mResourceMap;
};