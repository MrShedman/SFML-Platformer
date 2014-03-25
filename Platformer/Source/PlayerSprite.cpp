#include "PlayerSprite.h"
#include "PlayerStanding.h"
#include <SoundPlayer.hpp>

PlayerSprite::PlayerSprite(State::Context context)
:
sounds(*context.sounds),
scoreboard(context)
{
	core.lastPlatformHeight = 900;
	core.health = 20;
	core.canClimb = false;

	core.x = 250;
	core.y = 900;
	core.vx = 0.f;
	core.vy = 0.f;
	core.seqs = new SpriteSequence*[6];
	
	core.seqs[0] = new SpriteSequence(context.textures->get(Textures::ID::PlayerStanding), 22, 5, 4, 7);
	core.seqs[1] = new SpriteSequence(context.textures->get(Textures::ID::PlayerRunning), 27, 2, 4, 7);
	core.seqs[2] = new SpriteSequence(context.textures->get(Textures::ID::PlayerJumping), 9, 3, 2, 5);
	core.seqs[3] = new SpriteSequence(context.textures->get(Textures::ID::PlayerFalling), 3, 7, 1, 3);
	core.seqs[4] = new SpriteSequence(context.textures->get(Textures::ID::PlayerClimbing), 8, 4, 2, 4);
	core.seqs[5] = new SpriteSequence(context.textures->get(Textures::ID::PlayerDying), 6, 3, 2, 3);

	core.state = new PlayerStanding( core );
	core.dir.SetRight();

	core.rect = RectF(-40, 48, -20, 20);

	float half = context.window->getSize().x / 2.f;
	scoreboard.setPosition(half, 40);
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

	core.state = new PlayerStanding(core);
	core.dir.SetRight();
}

void PlayerSprite::handleEvent(const sf::Event &event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Right:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlDirPress(BiDirection::MakeRight());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlDirRelease(BiDirection::MakeRight());
		}
		break;
	case sf::Keyboard::Left:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlDirPress(BiDirection::MakeLeft());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlDirRelease(BiDirection::MakeLeft());
		}
		break;
	case sf::Keyboard::D:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlDirPress(BiDirection::MakeRight());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlDirRelease(BiDirection::MakeRight());
		}
		break;
	case sf::Keyboard::A:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlDirPress(BiDirection::MakeLeft());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlDirRelease(BiDirection::MakeLeft());
		}
		break;
	case sf::Keyboard::Space:
		if (event.type == sf::Event::KeyPressed)
		{
			if (GetState().ID != 3)
			{
				sounds.play(SoundEffect::PlayerJump);
			}
			GetState().OnCtrlJumpPress();
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlJumpRelease();
		}
		break;
	case sf::Keyboard::Up:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlClimbPress(ClimbDirection::MakeUp());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlClimbRelease(ClimbDirection::MakeUp());
		}
		break;
	case sf::Keyboard::Down:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlClimbPress(ClimbDirection::MakeDown());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlClimbRelease(ClimbDirection::MakeDown());
		}
		break;
	case sf::Keyboard::W:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlClimbPress(ClimbDirection::MakeUp());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlClimbRelease(ClimbDirection::MakeUp());
		}
		break;
	case sf::Keyboard::S:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlClimbPress(ClimbDirection::MakeDown());
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlClimbRelease(ClimbDirection::MakeDown());
		}
		break;
	case sf::Keyboard::LShift:
		if (event.type == sf::Event::KeyPressed)
		{
			GetState().OnCtrlClimbFreezePress();
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			GetState().OnCtrlClimbFreezeRelease();
		}
		break;
	case sf::Keyboard::R:
		if (event.type == sf::Event::KeyPressed)
		{
			reset();
		}
		break;
	}
}
PlayerSprite::~PlayerSprite()
{
	delete core.seqs[0];
	delete core.seqs[1];
	delete core.seqs[2];
	delete core.seqs[3];
	delete core.seqs[4];
	delete core.seqs[5];
	delete [] core.seqs;
	delete core.state;
}