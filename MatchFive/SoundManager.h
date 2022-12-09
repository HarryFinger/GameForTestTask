#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;

class SoundManager
{
public:
	Music main_music; //main theme
	Music achieve_music; //play's when chip picked or droped
	Music win_music; //win state music

	SoundManager()
	{

		main_music.openFromFile("./../MatchFive/music/crew_1.wav");
		achieve_music.openFromFile("./../MatchFive/music/stone.wav");
		win_music.openFromFile("./../MatchFive/music/mixkit_win_music.wav");

		main_music.setLoop(1);
		main_music.setVolume(0.f);
		main_music.play();

		win_music.setVolume(30.f);
	}

	void RiseMainSound(const Clock& clock)
	{
		if (main_music.getVolume() < 30)
		{
			float blink_time = 0.f;
			blink_time = clock.getElapsedTime().asSeconds() * MAIN_SOUND_RISHING_SPEED;
			main_music.setVolume(0.0f + blink_time);
		}
	}
private:
	const float MAIN_SOUND_RISHING_SPEED = 8.f;
};
