#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

class Level
{
public:

	bool loadFromFile(const std::string& filename)
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

	Level& operator = (Level &rhs)
	{
		cTiles = rhs.cTiles;
		width = rhs.width;
		height = rhs.height;

		return *this;
	}

	std::string getFileName() const
	{
		return filename;
	}

	const std::vector<char>& getLevelData() const
	{
		return cTiles;
	}

	unsigned int getWidth() const
	{
		return width;
	}

	unsigned int getHeight() const
	{
		return height;
	}

private:

	std::string filename;
	std::vector<char> cTiles;
	unsigned int width;
	unsigned int height;
};