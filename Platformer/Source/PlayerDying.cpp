#include <PlayerDying.h>

void PlayerDying::OnUpdate(sf::Time dt)
{
	core.vy += say;

	clamp(core.vy, -maxsy, maxsy);
	clamp(core.vx, -maxsx, maxsx);

	core.vx *= sdx;

	core.x += core.vx;
	core.y += core.vy;
	
	if (frameLimit < 16)
	{
		animation->setXDirection(core.xDirection);
		animation->update();
		animation->setRotation(frameLimit * core.xDirection.transform(-4));
	}
	
	animation->setPosition(core.x, core.y);
	frameLimit++;
}