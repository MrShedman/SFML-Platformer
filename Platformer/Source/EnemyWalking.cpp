#include <EnemyWalking.h>
#include <EnemyFalling.h>

void EnemyWalking::OnUpdate(sf::Time dt)
{
	core.vx += core.xDirection.transform(sax);
	clamp(core.vx, -maxsx, maxsx);

	core.x += core.vx;

	animation->setXDirection(core.xDirection);
	animation->update();
	animation->setPosition(core.x, core.y);

	if (core.health <= 0)
	{
		//transition(new PlayerDying(core));
	}
}

void EnemyWalking::OnCollision(const CollisionRectF &rect)
{
	if (core.vx > 0.f)
	{
		core.x -= core.getCRect().right - rect.left;
		core.vx = 0.0f;
	}
	else
	{
		core.x += rect.right - core.getCRect().left;
		core.vx = 0.0f;
	}
	core.xDirection.Reverse();
}

void EnemyWalking::OnFreeFall()
{
	transition(new EnemyFalling(core));
}