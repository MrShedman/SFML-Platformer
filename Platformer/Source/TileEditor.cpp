#include <TileEditor.h>
#include <TileMap.h>
#include <Utility.h>
#include <iostream>

TileEditor::TileEditor(State::Context context, TileMap &map)
	:
	map(map),
	window(*context.window),
	m_tileset(context.textures->get(Textures::TileMap))
{
	editingMode = false;

	tileID = static_cast<int>(Block::Stone);

	block.resize(4);
}

void TileEditor::update()
{
	if (editingMode)
	{
		sf::Vector2f mPos = getMousePosition(window);

		float x = static_cast<float>(map.getIndexXBiasLeft(mPos.x) * TileData::tileSize.x);
		float y = static_cast<float>(map.getIndexYBiasTop(mPos.y) * TileData::tileSize.y);

		Block::ID type = static_cast<Block::ID>(tileID);

		createBlock(sf::Vector2f(x, y), map.getTileData([&](TileData data) { return data.type == type; }));
	
		createGrid();
	}
}

void TileEditor::createBlock(sf::Vector2f position, TileData &data)
{
	sf::Vector2f d;
	d.x = static_cast<float>(data.tileSize.x);
	d.y = static_cast<float>(data.tileSize.y);
	sf::Vector2f l(position);

	block[0].position = sf::Vector2f(l.x, l.y);
	block[1].position = sf::Vector2f(l.x + d.x, l.y);
	block[2].position = sf::Vector2f(l.x + d.x, l.y + d.y);
	block[3].position = sf::Vector2f(l.x, l.y + d.y);
	
	sf::Vector2f s(data.texSize);
	sf::Vector2f p;
	p.x = data.texCoords.x * s.x;
	p.y = data.texCoords.y * s.y;

	block[0].texCoords = sf::Vector2f(p.x, p.y);
	block[1].texCoords = sf::Vector2f(p.x + s.x, p.y);
	block[2].texCoords = sf::Vector2f(p.x + s.x, p.y + s.y);
	block[3].texCoords = sf::Vector2f(p.x, p.y + s.y);

	block[0].color = data.color - sf::Color(50, 50, 0, 30);
	block[1].color = data.color - sf::Color(50, 50, 0, 30);
	block[2].color = data.color - sf::Color(50, 50, 0, 30);
	block[3].color = data.color - sf::Color(50, 50, 0, 30);
}

void TileEditor::createGrid()
{
	RectI rect = map.getDrawingRect(window);

	int vertexCount = (rect.right - rect.left + rect.bottom - rect.top) * 2;

	grid.clear();
	grid.resize(vertexCount);

	int count = 0;

	for (int ix = rect.left; ix < rect.right; ++ix)
	{
		float x = static_cast<float>(ix * TileData::tileSize.x);
		float top = static_cast<float>(rect.top  * TileData::tileSize.y);
		float bottom = static_cast<float>(rect.bottom  * TileData::tileSize.y);

		grid[count++].position = sf::Vector2f(x, top);
		grid[count++].position = sf::Vector2f(x, bottom);
	}

	for (int iy = rect.top; iy < rect.bottom; ++iy)
	{
		float y = static_cast<float>(iy * TileData::tileSize.y);
		float left = static_cast<float>(rect.left * TileData::tileSize.x);
		float right = static_cast<float>(rect.right * TileData::tileSize.x);

		grid[count++].position = sf::Vector2f(left, y);
		grid[count++].position = sf::Vector2f(right, y);
	}

	for (int i = 0; i < vertexCount; ++i)
	{
		grid[i].color = sf::Color::White;
	}
}


void TileEditor::handleEvent(const sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::E)
		{
			editingMode = !editingMode;
		}
	}

	if (!editingMode)
	{
		return;
	}

	sf::Vector2f mPos = getMousePosition(window);

	if (event.type == sf::Event::MouseMoved)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			map.modifyTile(mPos.x, mPos.y, static_cast<Block::ID>(tileID));
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			map.modifyTile(mPos.x, mPos.y, Block::ID::Air);
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			map.modifyTile(mPos.x, mPos.y, static_cast<Block::ID>(tileID));
		}
		if (event.mouseButton.button == sf::Mouse::Middle)
		{
			map.modifyTile(mPos.x, mPos.y, Block::ID::Air);
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			tileID = map.getTileID(mPos.x, mPos.y);
		}
	}
	else if (event.type == sf::Event::MouseWheelMoved)
	{
		int size = Block::ID::TypeCount;

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
	if (editingMode)
	{
		target.setView(getAlignedView(target.getView()));

		target.draw(&grid[0], grid.size(), sf::Lines, states);

		states.texture = &m_tileset;

		target.draw(&block[0], 4, sf::Quads, states);
	}
}