#include <MusicPlayer.hpp>
#include <Utility.h>

MusicPlayer::MusicPlayer()
: mMusic()
, mFilenames()
, mVolume(100.f)
{
	mCurrent = Music::ID::None;
	mFilenames[Music::MenuTheme] = "Sounds/Nostalgia.ogg";
	mFilenames[Music::GameTheme001] = "Sounds/Disc Riptide.ogg";
	mFilenames[Music::GameTheme002] = "Sounds/Cyberpunk Princess.ogg";
	mFilenames[Music::GameTheme003] = "Sounds/FAFS.ogg";
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

	clamp(mVolume, 0.f, 100.f);

	mMusic.setVolume(mVolume);
}

float MusicPlayer::getVolume() const
{
	return mVolume;
}

void MusicPlayer::setPaused(bool paused)
{
	if (paused)
		mMusic.pause();
	else
		mMusic.play();
}