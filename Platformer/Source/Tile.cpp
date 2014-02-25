#include <Tile.h>

Tile::Tile()
{
	data = nullptr;
}

Tile::Tile(float x, float y, TileData &data)
:
rect(y * TileData::tileSize.y, (y + 1) * TileData::tileSize.y,
	 x * TileData::tileSize.x, (x + 1) * TileData::tileSize.x),
data(&data)
{
	update();
}

Tile& Tile::operator = (Tile&& rhs)
{
	rect = rhs.rect;
	quad = rhs.quad;
	data = rhs.data;

	update();

	rhs.rect = RectF();
	rhs.quad.clear();
	rhs.data = nullptr;

	return *this;
}
void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(&quad[0], 4, sf::Quads, states);
}

void Tile::update()
{
	quad.resize(4);

	quad[0].position = sf::Vector2f(rect.left, rect.top);
	quad[1].position = sf::Vector2f(rect.right, rect.top);
	quad[2].position = sf::Vector2f(rect.right, rect.bottom);
	quad[3].position = sf::Vector2f(rect.left, rect.bottom);

	sf::Vector2f t = data->texCoords;
	sf::Vector2i s = TileData::texSize;

	quad[0].texCoords = sf::Vector2f(t.x * s.x, t.y * s.y);
	quad[1].texCoords = sf::Vector2f((t.x + 1) * s.x, t.y * s.y);
	quad[2].texCoords = sf::Vector2f((t.x + 1) * s.x, (t.y + 1) * s.y);
	quad[3].texCoords = sf::Vector2f(t.x * s.x, (t.y + 1) * s.y);

	quad[0].color = data->color;
	quad[1].color = data->color;
	quad[2].color = data->color;
	quad[3].color = data->color;
}