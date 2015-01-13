#pragma once

#include <State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SpriteState.h>
#include <PlayerSprite.h>
#include <EnemyFactory.h>
#include <EnemySprite.h>
#include <TileMap.h>
#include <TileEditor.h>
#include <CollisionSystem.h>
#include <TileMapRenderer.h>
#include <HealthBar.h>
#include <Camera.h>
#include <Scoreboard.h>

class GameState : public State
{
	public:
							GameState(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);

	private:

		sf::Clock clock;

		Camera camera;

		PlayerSprite player;
		EnemyFactory enemyFactory;

		SoftShadow shadow;
		sf::Texture &mTileset;

		TileMap map;
		TileMapRenderer mRender;
		TileEditor mapEditor;

		CollisionSystem collision;

		HealthBar health;	
};