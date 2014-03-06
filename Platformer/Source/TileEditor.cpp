#include <TileEditor.h>
#include <TileMap.h>

TileEditor::TileEditor(State::Context context, TileMap &map)
	:
	map(map)
{
	isOn = false;

	window = context.window;
	m_tileset = context.textures->get(Textures::TileMap);

	tileID = 1;

	block.resize(8);

	block[0].color = sf::Color::Black;
	block[1].color = sf::Color::Black;
	block[2].color = sf::Color::Black;
	block[3].color = sf::Color::Black;
}

void TileEditor::update()
{
	if (isOn)
	{
		sf::Vector2f mPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		mPos += sf::Vector2f(20, 20);

		createBlock(mPos, map.Table[tileID]);
	}
}

void TileEditor::createBlock(sf::Vector2f position, TileData data)
{
	sf::Vector2f d;
	d.x = data.tileSize.x;
	d.y = data.tileSize.y;
	sf::Vector2f l(position);
	sf::Vector2f o(4, 4);

	block[0].position = sf::Vector2f(l.x - o.x, l.y - o.y);
	block[1].position = sf::Vector2f(l.x + d.x + o.x, l.y - o.y);
	block[2].position = sf::Vector2f(l.x + d.x + o.x, l.y + d.y + o.y);
	block[3].position = sf::Vector2f(l.x - o.x, l.y + d.y + o.y);

	block[4].position = sf::Vector2f(l.x, l.y);
	block[5].position = sf::Vector2f(l.x + d.x, l.y);
	block[6].position = sf::Vector2f(l.x + d.x, l.y + d.y);
	block[7].position = sf::Vector2f(l.x, l.y + d.y);

	sf::Vector2f s(data.texSize);
	sf::Vector2f p;
	p.x = data.texCoords.x * s.x;
	p.y = data.texCoords.y * s.y;

	block[4].texCoords = sf::Vector2f(p.x, p.y);
	block[5].texCoords = sf::Vector2f(p.x + s.x, p.y);
	block[6].texCoords = sf::Vector2f(p.x + s.x, p.y + s.y);
	block[7].texCoords = sf::Vector2f(p.x, p.y + s.y);

	block[4].color = data.color;
	block[5].color = data.color;
	block[6].color = data.color;
	block[7].color = data.color;
}


void TileEditor::handleEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::E)
		{
			isOn = !isOn;
		}
	}

	if (!isOn)
	{
		return;
	}

	sf::Vector2i mPos = static_cast<sf::Vector2i>(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			map.modifyTile(mPos.x, mPos.y, map.Table[tileID]);
		}
		if (event.mouseButton.button == sf::Mouse::Middle)
		{
			map.modifyTile(mPos.x, mPos.y, map.Table[Block::Air]);
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			int id = map.getIndexXBiasRight(static_cast<float>(mPos.x)) + map.getIndexYBiasBottom(static_cast<float>(mPos.y)) * map.width;
			tileID = map.vTiles[id].data->ID;
		}
	}
	if (event.type == sf::Event::MouseWheelMoved)
	{
		int size = map.Table.size();

		tileID += event.mouseWheel.delta;

		if (tileID >= 0)
		{
			tileID %= size;
		}
		else
		{
			tileID = size - std::abs(tileID % size) % size;
		}
	}
}

void TileEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (isOn)
	{
		states.texture = &m_tileset;
		target.draw(&block[0], 8, sf::Quads, states);
	}
}