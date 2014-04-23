#include <State.hpp>
#include <StateStack.hpp>


State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, ImageHolder &images, FontHolder& fonts, LevelFactory &levels, MusicPlayer& music, SoundPlayer& sounds, Settings &settings, EffectFactory &effects)
: window(&window)
, textures(&textures)
, images(&images)
, fonts(&fonts)
, levels(&levels)
, music(&music)
, sounds(&sounds)
, settings(&settings)
, effects(&effects)
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