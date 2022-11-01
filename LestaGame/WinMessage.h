#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class WinMessage
{
private:
	Font font;
	Text win_message;
	uint32_t font_size = 52;

	Texture win_texture;
	Sprite win_sprite;

	Texture press_any_texture;
	Sprite press_any_sprite;

	Texture invitation_texture;
	Sprite invitation_sprite;

	Clock blink_clock;
	uint32_t blink = 255;
	const uint32_t BLINK_SPEED = 1;

	enum BlinkState
	{
		Falling,
		Growing
	} blink_state = BlinkState::Falling;

	void TextBlink();

public:
	WinMessage();
	void DrawMessage(RenderWindow&);
	void DrawInvitationMessage(RenderWindow&);
};
