#ifndef TRAMBO_SOUND_PLAYER_H
#define TRAMBO_SOUND_PLAYER_H

#include "../Resources/resourceHolder.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>

#include <list>
#include <string>


namespace SoundEffects
{
	enum class ID;
}

namespace trmb
{

class SoundPlayer : private sf::NonCopyable
{
public:
								SoundPlayer();

	void 						load(SoundEffects::ID effect, const std::string& filename);

	void						play(SoundEffects::ID effect);
	void						play(SoundEffects::ID effect, sf::Vector2f position);

	void						removeStoppedSounds();
	void						setListenerPosition(sf::Vector2f position);
	sf::Vector2f				getListenerPosition() const;

private:
	SoundBufferHolder			mSoundBuffers;
	std::list<sf::Sound>		mSounds;
};

} // trmb namespace

#endif
