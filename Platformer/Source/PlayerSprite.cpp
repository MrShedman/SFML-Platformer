#include "PlayerSprite.h"
#include "PlayerStanding.h"

PlayerSprite::PlayerSprite(State::Context context)
{
	core.lastPlatformHeight = 0;
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

	sf::FloatRect visibleArea(sf::Vector2f(0.f, 0.f), sf::Vector2f(1280, 720));
	view.reset(visibleArea);

	core.rect = RectF(-40, 48, -20, 20);

	buffer.loadFromFile("Sounds/jump.wav");
	jump.setBuffer(buffer);
}

void PlayerSprite::reset()
{
	core.lastPlatformHeight = 0;
	core.health = 20;
	core.canClimb = false;

	core.x = 250;
	core.y = 900;
	core.vx = 0.f;
	core.vy = 0.f;

	core.state = new PlayerStanding(core);
	core.dir.SetRight();
}

void PlayerSprite::setViewPosition(sf::Time dt)
{
	float x = core.x - view.getCenter().x;
	float y = core.lastPlatformHeight - view.getCenter().y;
	
	if (std::abs(core.lastPlatformHeight - core.y - 6 * 48) > view.getSize().y / 2.f)
	{
		y = core.y - view.getCenter().y + 5 * 48;
	}

	if (core.canClimb)
	{
		y = core.y - view.getCenter().y;
	}

	if (!isAlive())
	{
		y = 0.f;
	}

	float dx = dt.asSeconds() * 2.f + (std::abs(core.vx) * 0.005f);
	float dy = dt.asSeconds() * 3.f;

	x *= dx;
	y *= dy;

	x = floorf(x * 10.f + 0.5f) / 10.f;
	y = floorf(y * 10.f + 0.5f) / 10.f;
	
	float nx = view.getCenter().x + x;
	float ny = view.getCenter().y + y;

	clamp(nx, viewBoundary.left + view.getSize().x / 2.f, viewBoundary.right - view.getSize().x / 2.f);
	clamp(ny, viewBoundary.top + view.getSize().y / 2.f, viewBoundary.bottom - view.getSize().y / 2.f);

	view.setCenter(nx, ny);
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
				jump.play();
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