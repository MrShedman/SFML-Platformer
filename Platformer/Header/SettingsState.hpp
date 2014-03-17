#pragma once

#include <State.hpp>
#include <Container.hpp>
#include <Button.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class SettingsState : public State
{
	public:
										SettingsState(StateStack& stack, Context context);

		virtual void					draw();
		virtual bool					update(sf::Time dt);
		virtual bool					handleEvent(const sf::Event& event);

	private:

		void initializeButtons();
		void toggleFullscreen();

		sf::Sprite											mBackgroundSprite;
		GUI::Container										mGUIContainer;
};