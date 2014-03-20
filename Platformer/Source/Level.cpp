#include <Level.h>
#include <sstream>
#include <fstream>
#include <iostream>

bool Level::loadFromFile(const std::string& filename)
{
	this->filename = filename;
	std::ifstream infile;

	infile.open(filename, std::ifstream::in);

	if (!infile.is_open())
	{
		std::cout << filename << " not open" << std::endl;
		return false;
	}

	std::string line;

	unsigned int nRows = 0;
	unsigned int nColumns = 0;

	cTiles.clear();

	while (std::getline(infile, line))
	{
		nColumns = line.length();
		std::istringstream iss(line);

		char t;

		while (iss >> std::noskipws >> t)
		{
			cTiles.push_back(t);
		}
		nRows++;
	}

	infile.close();

	width = nColumns;
	height = nRows;

	return true;
}

Level& Level::operator = (Level &rhs)
{
	cTiles = rhs.cTiles;
	width = rhs.width;
	height = rhs.height;

	return *this;
}

const std::vector<char>& Level::getLevelData() const
{
	return cTiles;
}

unsigned int Level::getWidth() const
{
	return width;
}

unsigned int Level::getHeight() const
{
	return height;
}