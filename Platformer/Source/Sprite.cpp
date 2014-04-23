#include "Sprite.h"

SpriteState& Sprite::GetState() const
{
	return *core.state.get();
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(core.state->getAnimation(), states);
}