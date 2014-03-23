#ifndef TRAMBO_STATE_H
#define TRAMBO_STATE_H

#include "../Resources/resourceHolder.h"

#include <memory>


namespace sf
{
	class Event;
	class RenderWindow;
	class Time;
}

class Player;

namespace States
{
	enum class ID;
}

namespace trmb
{

class MusicPlayer;
class SoundPlayer;
class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
								Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts,
									Player& player, MusicPlayer& music, SoundPlayer& sounds);

		sf::RenderWindow*		window;
		TextureHolder*			textures;
		FontHolder*				fonts;
		Player*					player;
		MusicPlayer*			music;
		SoundPlayer*			sounds;
	};


public:
						State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(sf::Time dt) = 0;
	virtual bool		handleEvent(const sf::Event& event) = 0;


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;


private:
	StateStack*			mStack;
	Context				mContext;
};

} // trmb namespace

#endif