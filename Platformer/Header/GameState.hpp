#ifndef BOOK_GAMESTATE_HPP
#define BOOK_GAMESTATE_HPP

#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SpriteState.h>
#include <PlayerSprite.h>
#include <TileMap.h>
#include <ParticleSystem.h>
#include <CollisionSystem.h>

class GameState : public State
{
	public:
							GameState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update();
		virtual bool		handleEvent(const sf::Event& event);


	private:

		void updateView();

		PlayerSprite player;

		TileMap map;

		CollisionSystem collision;

		sf::Sprite background;
		
};

#endif // BOOK_GAMESTATE_HPP