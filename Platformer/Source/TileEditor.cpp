#include <TileEditor.h>
#include <TileMap.h>

TileEditor::TileEditor(State::Context context, TileMap &map)
	:
	map(map)
{
	isOn = false;

	window = context.window;
	m_tileset = context.textures->get(Textures::TileMap);
	block.setTexture(m_tileset);

	tileID = 1;

	sf::Vector2f size = TileData::texSize;

	border.setSize(size);
	border.setOutlineThickness(5.f);
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Black);
	border.setScale(0.6f, 0.6f);
	block.setScale(0.6f, 0.6f);
}

void TileEditor::update()
{
	if (isOn)
	{
		sf::Vector2f mPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		block.setPosition(mPos + sf::Vector2f(20, 20));
		border.setPosition(block.getPosition());

		sf::Vector2f t = map.Table[tileID].texCoords;
		sf::Vector2f size = TileData::texSize;
		sf::Vector2f padding((t.x * 2 + 1) * 4, (t.y * 2 + 1) * 4);
		sf::Vector2f position = sf::Vector2f(t.x * size.x, t.y * size.y) + padding;

		border.setSize(size);
		block.setTextureRect(sf::IntRect(static_cast<sf::Vector2i>(position), static_cast<sf::Vector2i>(size)));
	}
}

void TileEditor::pollEvent(const sf::Event &event)
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

	sf::Vector2f mPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

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
			int id = map.getIndexXBiasRight(mPos.x) + map.getIndexYBiasBottom(mPos.y) * map.width;
			tileID = map.vTiles[id]->data->ID;
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
		target.draw(block);
		target.draw(border);
	}
}