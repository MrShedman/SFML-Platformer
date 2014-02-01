#include "Sprite.h"

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*core.currentSeq, states);
}

SpriteState& Sprite::GetState()
{
	return *core.state;
}