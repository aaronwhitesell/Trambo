#ifndef TRAMBO_MUSIC_PLAYER_H
#define TRAMBO_MUSIC_PLAYER_H

#include <SFML/Audio/Music.hpp>
#include <SFML/System/NonCopyable.hpp>

#include <map>
#include <string>

namespace Music
{
	enum class ID;
}

namespace trmb
{

class MusicPlayer : private sf::NonCopyable
{
public:
								MusicPlayer();

	void 						load(Music::ID theme, const std::string& filename);

	void						play(Music::ID theme);
	void						stop();

	void						setPaused(bool paused);
	void						setVolume(float volume);


private:
	sf::Music							mMusic;
	std::map<Music::ID, std::string>	mFilenames;
	float								mVolume;
};

} // trmb namespace

#endif

