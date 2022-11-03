#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <Windows.h>

#include "PlayingField.h"
#include "Selector.h"
#include "FieldElementType.h"
#include "WinMessage.h"
#include "SoundManager.h"

using namespace sf;

const uint32_t WINDOW_SIZE = 900;
const uint32_t TILE_SIZE = 100;
const uint32_t GRID_NUMBER = WINDOW_SIZE / TILE_SIZE;
const uint32_t WALL_OFFSET = 2;
const uint32_t BORDER_SIZE = TILE_SIZE * 2;

const uint32_t M = 9; //height of game field
const uint32_t N = 9; //width of game field



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	Clock main_clock;
	SoundManager sound_manager;
	PlayingField playing_field(N, M); //generate playing field
	Selector selector; //generate main selector
	WinMessage win_message; //generate win message statement

	int32_t dx = 0; //direction (right or left)
	int32_t dy = 0; //direction (up or down)
	bool space_pressed = false;

	RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "LestaGame!");

	Event event;

	//main loop
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if ((event.type == Event::Closed) || (playing_field.getGameOverStatus() && event.type == Event::KeyPressed))
			{
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Left) { dx = -1; }
				else if (event.key.code == Keyboard::Right) { dx = 1; }
				else if (event.key.code == Keyboard::Down) { dy = 1; }
				else if (event.key.code == Keyboard::Up) { dy = -1; }
				else if (event.key.code == Keyboard::Space) { space_pressed = true; }
			}
		}

		sound_manager.RiseMainSound(main_clock); //raising main sound effect

		if (!playing_field.getGameOverStatus()) //if game is not over
		{
			window.clear(Color::Black); //crear window

			//move state
			if (!selector.is_selected)
				selector.MoveSelector(dx, dy);
			else
			{
				if (playing_field.CheckIsEmpty((selector.x + TILE_SIZE * dx), (selector.y + TILE_SIZE * dy)))
				{
					selector.MoveSelector(dx, dy);
				}
			}

			//selection state
			if ((playing_field.CanPicked(selector)) && space_pressed && !selector.is_selected)
			{
				uint32_t i = selector.x / TILE_SIZE;
				uint32_t j = selector.y / TILE_SIZE;
				selector.chip_type = playing_field.field_array[i][j];
				selector.is_selected = true;
				playing_field.field_array[i][j] = FieldElementType::Empty;
				space_pressed = false;
				sound_manager.achieve_music.stop();
				sound_manager.achieve_music.play();
			}

			//placement state
			if ((playing_field.CanPlaced(selector)) && space_pressed && selector.is_selected)
			{
				uint32_t i = selector.x / TILE_SIZE;
				uint32_t j = selector.y / TILE_SIZE;
				playing_field.field_array[i][j] = selector.chip_type;
				selector.is_selected = false;
				selector.chip_type = FieldElementType::Empty;
				space_pressed = false;
				sound_manager.achieve_music.stop();
				sound_manager.achieve_music.play();
			}

			//is game is ended
			playing_field.ValidateWinStatus();

			//reset statement
			dx = 0;
			dy = 0;
			space_pressed = false;
		}


		//drawing playing_field
		playing_field.DrawField(window);

		//drawing selector
		if (!playing_field.getGameOverStatus())
		{
			selector.DrawSelector(window);
		}

		//win state
		static bool initialized = false;
		if (!initialized && playing_field.getGameOverStatus())
		{
			initialized = true;
			sound_manager.main_music.stop(); 
			sound_manager.win_music.play();
		}

		//invitation message
		if (main_clock.getElapsedTime().asSeconds() < 12)
		{
			win_message.DrawInvitationMessage(window);
		}
	
		if (playing_field.getGameOverStatus())
		{
			selector.StopBlink();
			win_message.DrawMessage(window);
		}
		
		window.display();
	}
	return 0;
}