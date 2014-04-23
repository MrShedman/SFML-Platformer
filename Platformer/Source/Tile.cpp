#include <Tile.h>
#include <EnemyFactory.h>

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(&quad[0], 4, sf::Quads, states);
}

Tile::Tile()
:
data(nullptr),
rect()
{}

Tile::Tile(float x, float y, TileData &data)
{
	this->data = &data;

	rect = RectF(y * TileData::tileSize.y, (y + 1) * TileData::tileSize.y,
		x * TileData::tileSize.x, (x + 1) * TileData::tileSize.x);

	quad.resize(4);
}

Tile::~Tile()
{}

void Tile::updatePosition()
{
	quad[0].position = sf::Vector2f(rect.left, rect.top);
	quad[1].position = sf::Vector2f(rect.right, rect.top);
	quad[2].position = sf::Vector2f(rect.right, rect.bottom);
	quad[3].position = sf::Vector2f(rect.left, rect.bottom);
}

void Tile::updateTexCoords()
{
	sf::Vector2f t = data->texCoords;
	sf::Vector2i s = TileData::texSize;

	quad[0].texCoords = sf::Vector2f(t.x * s.x, t.y * s.y);
	quad[1].texCoords = sf::Vector2f((t.x + 1) * s.x, t.y * s.y);
	quad[2].texCoords = sf::Vector2f((t.x + 1) * s.x, (t.y + 1) * s.y);
	quad[3].texCoords = sf::Vector2f(t.x * s.x, (t.y + 1) * s.y);
}

void Tile::updateColor()
{
	quad[0].color = data->color;
	quad[1].color = data->color;
	quad[2].color = data->color;
	quad[3].color = data->color;
}

StaticTile::StaticTile() 
: 
Tile()
{}

StaticTile::StaticTile(float x, float y, TileData &data)
:
Tile(x, y, data)
{
	updatePosition();
	updateTexCoords();
	updateColor();
}

StaticTile& StaticTile::operator = (StaticTile&& rhs)
{
	rect = rhs.rect;
	quad = rhs.quad;
	data = rhs.data;

	updatePosition();
	updateTexCoords();
	updateColor();

	rhs.rect = RectF();
	rhs.quad.clear();
	rhs.data = nullptr;

	return *this;
}

AnimatedTile::AnimatedTile()
:
Tile(),
animation(nullptr)
{}

AnimatedTile::AnimatedTile(float x, float y, TileData &data, TileAnimation &animation)
:
Tile(x, y, data),
animation(&animation)
{
	updatePosition();
	updateTexCoords();
	updateColor();
}

AnimatedTile& AnimatedTile::operator = (AnimatedTile&& rhs)
{
	rect = rhs.rect;
	quad = rhs.quad;
	data = rhs.data;
	animation = rhs.animation;

	updatePosition();
	updateTexCoords();
	updateColor();

	rhs.rect = RectF();
	rhs.quad.clear();
	rhs.data = nullptr;
	rhs.animation = nullptr;

	return *this;
}

void AnimatedTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &animation->getTexture();
	target.draw(&quad[0], 4, sf::Quads, states);
}

void AnimatedTile::updateTexCoords()
{
	RectF tRect = animation->getTextureRect();

	quad[0].texCoords = sf::Vector2f(tRect.left, tRect.top);
	quad[1].texCoords = sf::Vector2f(tRect.right, tRect.top);
	quad[2].texCoords = sf::Vector2f(tRect.right, tRect.bottom);
	quad[3].texCoords = sf::Vector2f(tRect.left, tRect.bottom);
}

SpawnerTile::SpawnerTile()
:
Tile()
{}

SpawnerTile::SpawnerTile(float x, float y, TileData &data, EnemyFactory &factory)
:
Tile(x, y, data),
factory(&factory)
{
	updatePosition();
	updateTexCoords();
	updateColor();

	this->factory->addSpawnerTile(this);
}

SpawnerTile::~SpawnerTile()
{
	factory->removeSpawnerTile(this);
}

SpawnerTile& SpawnerTile::operator = (SpawnerTile&& rhs)
{
	rect = rhs.rect;
	quad = rhs.quad;
	data = rhs.data;
	factory = rhs.factory;

	updatePosition();
	updateTexCoords();
	updateColor();

	rhs.rect = RectF();
	rhs.quad.clear();
	rhs.data = nullptr;
	rhs.factory = nullptr;

	return *this;
}