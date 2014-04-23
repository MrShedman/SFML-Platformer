#include <EnemyFalling.h>
#include <EnemyWalking.h>

#include <algorithm>

void EnemyFalling::OnUpdate(sf::Time dt)
{
	core.vx *= sdx;

	core.vy += ay;
	clamp(core.vy, -say, say);

	core.x += core.vx;
	core.y += core.vy;

	animation->setXDirection(core.xDirection);
	animation->update();
	animation->setPosition(core.x, core.y);

	if (core.health <= 0)
	{
		//transition(new PlayerDying(core));
	}
}


void EnemyFalling::OnCollision(const CollisionRectF &rect)
{
	CollisionRectF sRect = core.getCRect();

	if (core.vx > 0.f)
	{
		if (core.vy > 0.f)
		{
			float px = sRect.right - rect.left;
			float py = sRect.bottom - rect.top;

			if (core.vy * px > core.vx * py)
			{
				//top collision
				core.vy = 0.f;
				core.y -= py;

				transition(new EnemyWalking(core));				
			}
			else  //core.vy * px > core.vx * py
			{
				//side collision
				core.vx = 0.f;
				core.x -= px;
			}
		}
		else //core.vy > 0.f
		{
			float px = sRect.right - rect.left;
			float py = rect.bottom - sRect.top;

			if (-core.vy * px > core.vx * py)
			{
				//top collision
				core.vy = 0.f;
				core.y += py;
			}
			else  //core.vy * px > core.vx * py
			{
				//side collision
				core.vx = 0.f;
				core.x -= px;
			}
		}
	}
	else // core.vx > 0.f
	{
		if (core.vy > 0.f)
		{
			float px = rect.right - sRect.left;
			float py = sRect.bottom - rect.top;

			if (core.vy * px > -core.vx * py)
			{
				//top collision
				core.vy = 0.f;
				core.y -= py;

				transition(new EnemyWalking(core));
			}
			else  //core.vy * px > core.vx * py
			{
				//side collision
				core.vx = 0.f;
				core.x += px;
			}
		}
		else //core.vy > 0.f
		{
			float px = rect.right - sRect.left;
			float py = rect.bottom - sRect.top;

			if (-core.vy * px > -core.vx * py)
			{
				//top collision
				core.vy = 0.f;
				core.y += py;
			}
			else  //core.vy * px > core.vx * py
			{
				//side collision
				core.vx = 0.f;
				core.x += px;
			}
		}
	}
}