#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <vector>

class Level
{
public:

	bool loadFromFile(const std::string& filename)
	{
		this->filename = filename;
		std::ifstream infile(filename);

		if (!infile.is_open())
		{
			return false;
		}		

		std::string line;

		unsigned int nTiles = 0;
		unsigned int nRows = 0;
		unsigned int nColumns = 0;

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

		nTiles = cTiles.size();

		width = nColumns;
		height = nRows;

		return true;
	}

	Level& operator = (Level &rhs)
	{
		cTiles = rhs.cTiles;
		width = rhs.width;
		height = rhs.height;

		return *this;
	}

	std::string filename;
	std::vector<char> cTiles;
	unsigned int width;
	unsigned int height;
};