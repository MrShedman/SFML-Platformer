#include <MusicPlayer.hpp>

MusicPlayer::MusicPlayer()
: mMusic()
, mFilenames()
, mVolume(100.f)
{
	mCurrent = Music::ID::None;
	mFilenames[Music::MenuTheme] = "Sounds/Menu Theme.ogg";
	mFilenames[Music::GameTheme] = "Sounds/Game Theme.ogg";
}

void MusicPlayer::play(Music::ID theme)
{
	if (mCurrent == theme)
	{
		return;
	}

	std::string filename = mFilenames[theme];

	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
	mCurrent = theme;
}

void MusicPlayer::stop()
{
	mMusic.stop();
}

void MusicPlayer::setVolume(float volume)
{
	mVolume = volume;
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
		mMusic.pause();
	else
		mMusic.play();
}