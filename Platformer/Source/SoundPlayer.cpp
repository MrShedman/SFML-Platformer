#include <SoundPlayer.hpp>

#include <SFML/Audio/Listener.hpp>

#include <cmath>
#include <Utility.h>

SoundPlayer::SoundPlayer()
: mSoundBuffers()
, mSounds()
, mVolume(100)
{
	mSoundBuffers.load(SoundEffect::PlayerJump,		"Sounds/jump.wav");
	mSoundBuffers.load(SoundEffect::PlayerPickup,	"Sounds/pickup.wav");
	mSoundBuffers.load(SoundEffect::Button,			"Sounds/click.wav");
}

void SoundPlayer::play(SoundEffect::ID effect)
{
	mSounds.push_back(sf::Sound());
	sf::Sound& sound = mSounds.back();

	sound.setVolume(mVolume);
	sound.setBuffer(mSoundBuffers.get(effect));

	sound.play();

	if (mSounds.size() > 50)
	{
		removeStoppedSounds();
	}
}

void SoundPlayer::setVolume(float volume)
{
	mVolume = volume;

	clamp(mVolume, 0.f, 100.f);
}

float SoundPlayer::getVolume() const
{
	return mVolume;
}

void SoundPlayer::removeStoppedSounds()
{
	mSounds.remove_if([] (const sf::Sound& s)
	{
		return s.getStatus() == sf::Sound::Stopped;
	});
}