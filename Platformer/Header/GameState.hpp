#pragma once

#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SpriteState.h>
#include <PlayerSprite.h>
#include <TileMap.h>
#include <TileEditor.h>
#include <ParticleSystem.h>
#include <CollisionSystem.h>

class GameState : public State
{
	public:
							GameState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:

		void updateView();

		PlayerSprite player;

		TileMap map;

		TileEditor mapEditor;

		CollisionSystem collision;

		sf::Sprite background;		
};