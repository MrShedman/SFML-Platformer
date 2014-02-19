#include <Tile.h>

Tile::Tile()
{
	data = nullptr;
}

Tile::Tile(sf::Vector2f position, TileData &data)
:
rect(position.y * TileData::tileSize.y, (position.y + 1) * TileData::tileSize.y,
position.x * TileData::tileSize.x, (position.x + 1) * TileData::tileSize.x),
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
	rhs.quad = { sf::Vertex() };
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
	sf::Vector2f s = TileData::texSize;

	sf::Vector2f padding((t.x * 2 + 1) * 4, (t.y * 2 + 1) * 4);

	quad[0].texCoords = sf::Vector2f(t.x * s.x, t.y * s.y) + padding;
	quad[1].texCoords = sf::Vector2f((t.x + 1) * s.x, t.y * s.y) + padding;
	quad[2].texCoords = sf::Vector2f((t.x + 1) * s.x, (t.y + 1) * s.y) + padding;
	quad[3].texCoords = sf::Vector2f(t.x * s.x, (t.y + 1) * s.y) + padding;

	quad[0].color = data->color;
	quad[1].color = data->color;
	quad[2].color = data->color;
	quad[3].color = data->color;
}