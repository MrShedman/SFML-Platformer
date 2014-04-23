#include <LevelFactory.h>

LevelFactory::LevelFactory()
{
	mCurrent = Levels::ID::Level001;

	mFilenames[Levels::ID::Level001] = "Levels/001.txt";
	mFilenames[Levels::ID::Level002] = "Levels/002.txt";
	mFilenames[Levels::ID::Level003] = "Levels/003.txt";
}

void LevelFactory::load(Levels::ID level)
{
	std::string filename = mFilenames[level];

	if (!mLevel.loadFromFile(filename))
		throw std::runtime_error("Level " + filename + " could not be loaded.");


	mCurrent = level;
}

const std::vector<char> &LevelFactory::getLevelData() const
{
	return mLevel.getLevelData();
}

unsigned int LevelFactory::getWidth() const
{
	return mLevel.getWidth();
}

unsigned int LevelFactory::getHeight() const
{
	return mLevel.getHeight();
}

std::string LevelFactory::getFileName() const
{
	return mFilenames.find(mCurrent)->second;
}

Levels::ID LevelFactory::getID() const
{
	return mCurrent;
}