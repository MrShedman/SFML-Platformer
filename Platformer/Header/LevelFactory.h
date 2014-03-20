#pragma once

#include <SFML/System/NonCopyable.hpp>
#include <Level.h>
#include <ResourceIdentifiers.hpp>
#include <map>
#include <string>

class LevelFactory : private sf::NonCopyable
{
public:
	LevelFactory();

	void load(Levels::ID level);

	const std::vector<char>& getLevelData() const;

	unsigned int getWidth() const;

	unsigned int getHeight() const;

	std::string getFileName() const;

	Levels::ID getID() const;

private:

	Levels::ID							mCurrent;
	Level								mLevel;
	std::map<Levels::ID, std::string>	mFilenames;
};