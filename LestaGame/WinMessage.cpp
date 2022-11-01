#include "WinMessage.h"

WinMessage::WinMessage()
{
	win_texture.loadFromFile("./../LestaGame/images/you_win_message.png");
	win_sprite.setTexture(win_texture);
	win_sprite.setPosition(-20.f, -20.f);

	press_any_texture.loadFromFile("./../LestaGame/images/press_message.png");
	press_any_sprite.setTexture(press_any_texture);
	press_any_sprite.setPosition(195.f, 650.f);

	invitation_texture.loadFromFile("./../LestaGame/images/invitation_message.png");
	invitation_sprite.setTexture(invitation_texture);
	invitation_sprite.setPosition(155.f, -5.f);

	font.loadFromFile("./../LestaGame/font/calibri.ttf");
	win_message.setFont(font); // select the font
	win_message.setString("Press any key to exit...");// set the string to display
	win_message.setCharacterSize(font_size); // in pixels
	win_message.setFillColor(Color::Red); // set the color
	win_message.setStyle(Text::Bold);// set the text style
	win_message.move(220, 710);
}

void WinMessage::TextBlink()
{
	float blink_time = blink_clock.getElapsedTime().asMilliseconds();
	if (blink_time > BLINK_SPEED)
	{
		blink_clock.restart();
		press_any_sprite.setColor(Color(255, 255, 255, blink));

		if (blink_state == BlinkState::Falling)
		{
			--blink;
			if (blink <= 50)
			{
				blink_state = BlinkState::Growing;
			}
		}
		if (blink_state == BlinkState::Growing)
		{
			++blink;
			if (blink >= 250)
			{
				blink_state = BlinkState::Falling;
			}
		}
	}
}

void WinMessage::DrawMessage(RenderWindow& window)
{
	TextBlink();
	window.draw(press_any_sprite);
	window.draw(win_sprite);
}

void WinMessage::DrawInvitationMessage(RenderWindow& window)
{
	if (true)
	{
		window.draw(invitation_sprite);
	}
}