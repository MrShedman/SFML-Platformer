#include "PlayerSprite.h"
#include "PlayerStanding.h"

PlayerSprite::PlayerSprite()
{
	core.x = 900;
	core.y = 900;
	core.vx = 0.f;
	core.vy = 0.f;
	core.seqs = new SpriteSequence*[4];
	core.seqs[0] = new SpriteSequence("Textures/standing.png", 22, 5, 4, 7);
	core.seqs[1] = new SpriteSequence("Textures/running.png", 27, 2, 4, 7);
	core.seqs[2] = new SpriteSequence("Textures/jumping.png", 9, 3, 2, 5);
	core.seqs[3] = new SpriteSequence("Textures/falling.png", 3, 7, 1, 3);
	core.state = new PlayerStanding( core );
	core.dir.SetRight();

	core.rect = RectF(-40, 48, -20, 20);

	buffer.loadFromFile("Sounds/jump.wav");
	jump.setBuffer(buffer);
}

void PlayerSprite::pollEvent(sf::Event &event)
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
	}
}
PlayerSprite::~PlayerSprite()
{
	delete core.seqs[0];
	delete core.seqs[1];
	delete core.seqs[2];
	delete core.seqs[3];
	delete [] core.seqs;
	delete core.state;
}