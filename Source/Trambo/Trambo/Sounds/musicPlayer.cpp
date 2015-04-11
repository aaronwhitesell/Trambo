#include "../../../../Include/Trambo/Sounds/musicPlayer.h"

#include <stdexcept>


namespace trmb
{

MusicPlayer::MusicPlayer()
: mMusic()
, mFilenames()
, mVolume(100.f)
{
}

void MusicPlayer::load(Music::ID theme, const std::string& filename)
{
	mFilenames[theme] = filename;
}

void MusicPlayer::play(Music::ID theme)
{
	std::string filename = mFilenames[theme];

	if (!mMusic.openFromFile(filename))
		throw std::runtime_error("Music " + filename + " could not be loaded.");

	mMusic.setVolume(mVolume);
	mMusic.setLoop(true);
	mMusic.play();
}

void MusicPlayer::stop()
{
	mMusic.stop();
}

sf::SoundSource::Status MusicPlayer::getStatus()
{
	return mMusic.getStatus();
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

} // trmb namespace
