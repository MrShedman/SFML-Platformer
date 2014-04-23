#pragma once

#include <StateIdentifiers.hpp>
#include <ResourceIdentifiers.hpp>
#include <LevelFactory.h>
#include <Settings.h>
#include <EffectFactory.h>

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
	class RenderWindow;
}

class StateStack;
class MusicPlayer;
class SoundPlayer;

class State
{
	public:
		typedef std::unique_ptr<State> Ptr;

		struct Context
		{
			Context(sf::RenderWindow &window, TextureHolder &textures, ImageHolder &images, FontHolder &fonts, 
					LevelFactory &levels, MusicPlayer &music, SoundPlayer &sounds, 
					Settings &settings, EffectFactory &effects);

			sf::RenderWindow *window;
			TextureHolder *textures;
			ImageHolder *images;
			FontHolder *fonts;
			LevelFactory *levels;
			MusicPlayer *music;
			SoundPlayer *sounds;
			Settings *settings;
			EffectFactory *effects;
		};


	public:
		
		State(StateStack& stack, Context context);

		virtual ~State();

		virtual void draw() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(const sf::Event& event) = 0;


	protected:
		void requestStackPush(States::ID stateID);
		void requestStackPop();
		void requestStateClear();

		Context	getContext() const;

	private:
		StateStack* mStack;
		Context mContext;
};
