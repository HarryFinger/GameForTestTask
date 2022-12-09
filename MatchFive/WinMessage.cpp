#include "WinMessage.h"

WinMessage::WinMessage()
{
	win_texture.loadFromFile("./../MatchFive/images/you_win_message.png");
	win_sprite.setTexture(win_texture);
	win_sprite.setPosition(-20.f, -20.f);

	press_any_texture.loadFromFile("./../MatchFive/images/press_message.png");
	press_any_sprite.setTexture(press_any_texture);
	press_any_sprite.setPosition(195.f, 650.f);

	font.loadFromFile("./../MatchFive/font/calibri.ttf");
	info_message.setFont(font); // select the font
	info_message.setString("use \"left/right/up/down\" buttons to move selector");// set the string to display
	info_message.setCharacterSize(28); // in pixels
	info_message.setFillColor(Color(255, 255, 255)); // set the color
	info_message.setStyle(Text::Bold);// set the text style
	info_message.move(20, 12);

	info_message1 = info_message;
	info_message1.setString("use \"space\" button to interact");// set the string to display
	info_message1.setPosition(20, 42);

	rect.move(15, 15);
	rect.setFillColor(Color(160, 160, 160));
	rect.setOutlineThickness(5.0f);
	rect.setOutlineColor(Color(100, 100, 100));
	rect.setSize(Vector2f(640, 66));

}


void WinMessage::DrawMessage(RenderWindow& window)
{
	window.draw(press_any_sprite);
	window.draw(win_sprite);
}

void WinMessage::DrawInvitationMessage(RenderWindow& window)
{
	window.draw(rect);
	window.draw(info_message);
	window.draw(info_message1);
}