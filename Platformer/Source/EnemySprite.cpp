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

	sf::Vector2f centre = core.state->getAnimation().getOrigin();

	auto pos = core.state->getAnimation().getPosition();

	const float border = 2.f;
	const float width = 70.f;
	const float height = 14.f;

	outline.setSize(sf::Vector2f(width, height));
	health.setSize(sf::Vector2f(width - 2 * border, height - 2 * border));

	const float offset = 16.f;

	outline.setPosition(sf::Vector2f(centre.x - 0.5f * width, offset));
	health.setPosition(sf::Vector2f(centre.x + border - 0.5f * width, offset + border));

	outline.setOutlineThickness(-border);
	outline.setOutlineColor(sf::Color::Black);

	outline.setFillColor(sf::Color::Transparent);
	health.setFillColor(sf::Color::Red);
}

EnemySprite::~EnemySprite()
{}

void EnemySprite::reset()
{
	lifeTime = sf::seconds(randomize(10.f, 20.f));
	life = lifeTime;
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

void EnemySprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Animation animation = core.state->getAnimation();

	target.draw(animation, states);

	float direction = std::copysign(1.0f, animation.getScale().x);
	sf::Vector2f origin = animation.getOrigin();

	sf::Transform transorm = animation.getTransform();
	transorm.scale(direction, 1.0f, origin.x, origin.y);

	states.transform *= transorm;

	target.draw(outline, states);
	target.draw(health, states);
}