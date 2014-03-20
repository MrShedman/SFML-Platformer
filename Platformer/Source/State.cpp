#include <State.hpp>
#include <StateStack.hpp>


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, LevelFactory &levels, MusicPlayer& music, SoundPlayer& sounds, Settings &settings)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, levels(&levels)
, music(&music)
, sounds(&sounds)
, settings(&settings)
{
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}