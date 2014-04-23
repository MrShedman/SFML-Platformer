#include <PlayerSprite.h>
#include <PlayerStanding.h>
#include <SoundPlayer.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <utility>

PlayerSprite::PlayerSprite(State::Context context)
:
sounds(*context.sounds),
scoreboard(context)
{
	core.setSoundPlayer(*context.sounds);
	
	core.mAnimationFactory.load(context.textures->get(Textures::PlayerStanding),	Animations::Standing, 22, 5, 4, 7);
	core.mAnimationFactory.load(context.textures->get(Textures::PlayerRunning),		Animations::Running,  27, 2, 4, 7);
	core.mAnimationFactory.load(context.textures->get(Textures::PlayerJumping),		Animations::Jumping,  9,  3, 2, 5);
	core.mAnimationFactory.load(context.textures->get(Textures::PlayerFalling),		Animations::Falling,  3,  7, 1, 3);
	core.mAnimationFactory.load(context.textures->get(Textures::PlayerClimbing),	Animations::Climbing, 8,  4, 2, 4);
	core.mAnimationFactory.load(context.textures->get(Textures::PlayerDying),		Animations::Dying,	  6,  3, 2, 3);

	core.rect = RectF(-40, 48, -20, 20);

	scoreboard.setPosition(context.window->getSize().x / 2.f, 40);

	reset();
}

PlayerSprite::~PlayerSprite()
{

}

void PlayerSprite::reset()
{
	core.lastPlatformHeight = 900;
	core.health = 20;
	core.canClimb = false;

	core.x = 250;
	core.y = 900;
	core.vx = 0.f;
	core.vy = 0.f;
	core.state = std::make_unique<PlayerStanding>(core);
	core.xDirection.SetRight();

	core.sounds->play(SoundEffect::PlayerSpawn);
}

void PlayerSprite::handleEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Right:	GetState().OnCtrlDirPress(BiDirectionX::MakeRight());	break;
		
		case sf::Keyboard::Left:	GetState().OnCtrlDirPress(BiDirectionX::MakeLeft());	break;

		case sf::Keyboard::D:		GetState().OnCtrlDirPress(BiDirectionX::MakeRight());	break;

		case sf::Keyboard::A:		GetState().OnCtrlDirPress(BiDirectionX::MakeLeft());	break;

		case sf::Keyboard::Space:	GetState().OnCtrlJumpPress();							break;

		case sf::Keyboard::Up:		GetState().OnCtrlClimbPress(BiDirectionY::MakeUp());	break;

		case sf::Keyboard::Down:	GetState().OnCtrlClimbPress(BiDirectionY::MakeDown());	break;

		case sf::Keyboard::W:		GetState().OnCtrlClimbPress(BiDirectionY::MakeUp());	break;

		case sf::Keyboard::S:		GetState().OnCtrlClimbPress(BiDirectionY::MakeDown());	break;

		case sf::Keyboard::R:		reset();												break;
		}
	}
	else if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Right:	GetState().OnCtrlDirRelease(BiDirectionX::MakeRight());		break;

		case sf::Keyboard::Left:	GetState().OnCtrlDirRelease(BiDirectionX::MakeLeft());		break;

		case sf::Keyboard::D:		GetState().OnCtrlDirRelease(BiDirectionX::MakeRight());		break;

		case sf::Keyboard::A:		GetState().OnCtrlDirRelease(BiDirectionX::MakeLeft());		break;

		case sf::Keyboard::Space:	GetState().OnCtrlJumpRelease();								break;

		case sf::Keyboard::Up:		GetState().OnCtrlClimbRelease(BiDirectionY::MakeUp());		break;

		case sf::Keyboard::Down:	GetState().OnCtrlClimbRelease(BiDirectionY::MakeDown());	break;

		case sf::Keyboard::W:		GetState().OnCtrlClimbRelease(BiDirectionY::MakeUp());		break;

		case sf::Keyboard::S:		GetState().OnCtrlClimbRelease(BiDirectionY::MakeDown());	break;
		}
	}
}