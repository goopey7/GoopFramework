//Copyright Sam Collier 2022

#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::addFrame(sf::IntRect frame)
{
	frames.push_back(frame);
}

size_t Animation::getNumFrames()
{
	return frames.size();
}

void Animation::animate(const float dt)
{
	if(bIsPlaying)
	{
		frameTimeElapsed += dt;
		if(frameTimeElapsed >= frameSpeed)
		{
			if(currentFrameIdx+1 >= frames.size())
			{
				if(bIsLooping)
					currentFrameIdx = 0;
				else
					bIsPlaying = false;
			}
			else currentFrameIdx++;
			frameTimeElapsed = 0;
		}
	}
}

sf::IntRect Animation::getCurrentFrame()
{
	return frames[currentFrameIdx];
}

void Animation::setFlipped(bool flip)
{
	bIsFlipped = flip;
}

void Animation::setFrameSpeed(float frameSpeed)
{
	this->frameSpeed = frameSpeed;
}

void Animation::pause()
{
	bIsPlaying = false;
}

void Animation::play()
{
	bIsPlaying = true;
}

void Animation::setIsLooping(bool loop)
{
	bIsLooping = loop;
}

