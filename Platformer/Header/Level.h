#pragma once

#include <string>
#include <vector>

class Level
{
public:

	bool loadFromFile(const std::string& filename);

	Level& operator = (Level &rhs);

	const std::vector<char>& getLevelData() const;

	unsigned int getWidth() const;

	unsigned int getHeight() const;

private:

	std::string filename;
	std::vector<char> cTiles;
	unsigned int width;
	unsigned int height;
};