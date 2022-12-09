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

	RectangleShape rect;

public:
	WinMessage();
	void DrawMessage(RenderWindow&);
	void DrawInvitationMessage(RenderWindow&);
};
