#pragma once

#include <State.hpp>
#include <Container.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class LevelSelectionState : public State
{
public:
	LevelSelectionState(StateStack& stack, Context context);

	virtual void			draw();
	virtual bool			update(sf::Time dt);
	virtual bool			handleEvent(const sf::Event& event);

private:

	void selectLevel(Levels::ID level);
	void initializeButtons();

	sf::Sprite				mBackgroundSprite;
	GUI::Container			mGUIContainer;
};