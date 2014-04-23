#include <EnemySprite.h>
#include <EnemyWalking.h>
#include <SoundPlayer.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <utility>

EnemySprite::EnemySprite(State::Context context, sf::Vector2f position, int ID)
{
	this->ID = ID;

	core.setSoundPlayer(*context.sounds);

	core.mAnimationFactory.load(context.textures->get(Textures::EnemyWalking), Animations::EnemyWalking, 16, 5, 2, 8);

	core.rect = RectF(-40, 38, -35, 35);

	core.x = position.x;
	core.y = position.y;

	reset();
}

EnemySprite::~EnemySprite()
{}

void EnemySprite::reset()
{
	lifeTime = sf::seconds(randomize(10.f, 20.f));
	core.lastPlatformHeight = 900;
	core.health = 20;
	core.canClimb = false;

	core.vx = 0.f;
	core.vy = 0.f;
	core.state = std::make_unique<EnemyWalking>(core);
	core.xDirection.SetRight();
}

void EnemySprite::handleEvent(const sf::Event &event)
{}