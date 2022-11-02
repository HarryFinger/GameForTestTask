#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class WinMessage
{
private:
	Font font;
	Text info_message, info_message1;

	Texture win_texture;
	Sprite win_sprite;

	Texture press_any_texture;
	Sprite press_any_sprite;

	Texture invitation_texture;
	Sprite invitation_sprite;

	RectangleShape rect;

	uint32_t blink = 255;

	enum BlinkState
	{
		Falling,
		Growing
	} blink_state = BlinkState::Falling;

	void TextBlink(Sprite&, uint32_t);

public:
	WinMessage();
	void DrawMessage(RenderWindow&);
	void DrawInvitationMessage(RenderWindow&);
};
