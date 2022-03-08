//Copyright Sam Collier 2022
//Credits: Paul Robertson
//(inspired by the implementation in the cmp105 framework)
#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
	public:
		Animation();
		~Animation();
		void addFrame(sf::IntRect frame);
		size_t getNumFrames();
		void animate(const float dt);
		sf::IntRect getCurrentFrame();
		void setFlipped(bool flip);
		void setFrameSpeed(float frameSpeed);
		void pause();
		void play();
		void setIsLooping(bool loop);
		void setToInitialFrame();

	private:
		std::vector<sf::IntRect> frames;
		bool bIsFlipped = false;
		bool bIsPlaying = true;
		bool bIsLooping = true;
		float frameSpeed = 1.f;
		int currentFrameIdx = 0;

		float frameTimeElapsed = 0.f;
};

