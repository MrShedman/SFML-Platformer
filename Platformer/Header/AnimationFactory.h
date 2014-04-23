#pragma once

#include <Animation.h>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <memory>

#include <map>

class AnimationFactory
{
public:

	void load(sf::Texture &texture, Animations::ID id, int nFrames, int nHoldFrames, int nRow, int nColumn)
	{
		auto animation = std::make_unique<Animation>(texture, nFrames, nHoldFrames, nRow, nColumn);
	
		insert(id, std::move(animation));
	}

	Animation& get(Animations::ID id)
	{
		return *mAnimationFactory.find(id)->second.get();
	}
	
private:

	void insert(Animations::ID id, std::unique_ptr<Animation> animation)
	{
		mAnimationFactory.insert(std::make_pair(id, std::move(animation)));
	}

	std::map<Animations::ID, std::unique_ptr<Animation>> mAnimationFactory;
};