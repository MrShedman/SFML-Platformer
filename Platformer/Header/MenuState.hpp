#ifndef BOOK_MENUSTATE_HPP
#define BOOK_MENUSTATE_HPP

#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context);

		virtual void			draw();
		virtual bool			update();
		virtual bool			handleEvent(const sf::Event& event);


	private:
		sf::Sprite				mBackgroundSprite;
};

#endif // BOOK_MENUSTATE_HPP
