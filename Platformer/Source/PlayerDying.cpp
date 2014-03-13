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
		core.currentSeq->advanceFrame(core.dir);
		core.currentSeq->setRotation(frameLimit * core.dir.transform(-4));
	}
	core.currentSeq->setPosition(core.x, core.y);
	frameLimit++;
}