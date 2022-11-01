#include "Selector.h"

Selector::Selector() {
	texture.loadFromFile("./../LestaGame/images/new_tiles.png");
	sprite.setTexture(texture);
	chip_sprite.setTexture(texture);
	sprite.move(static_cast<float>(x), static_cast<float>(y));
	sprite.setTextureRect(IntRect(400, 0, TILE_SIZE, TILE_SIZE));
};

void Selector::SelectorBlink()
{
	float blink_time = blink_clock.getElapsedTime().asMilliseconds();
	if (blink_time > BLINK_SPEED)
	{
		blink_clock.restart();
		sprite.setColor(Color(255, 255, 255, blink));

		if (blink_state == BlinkState::Falling)
		{
			--blink;
			if (blink <= MIN_BLINK_THRESHOLD)
			{
				blink_state = BlinkState::Growing;
			}
		}
		if (blink_state == BlinkState::Growing)
		{
			++blink;
			if (blink >= MAX_BLINK_THRESHOLD)
			{
				blink_state = BlinkState::Falling;
			}
		}
	}
}

void Selector::DrawSelector(RenderWindow& window)
{
	sprite.setPosition(static_cast<float>(this->x), static_cast<float>(this->y));
	if (!is_selected)
	{
		SelectorBlink();
	}
	chip_sprite.setPosition(static_cast<float>(this->x), static_cast<float>(this->y));
	if ((chip_type == FieldElementType::BlueChip) || (chip_type == FieldElementType::YellowChip) || (chip_type == FieldElementType::GreenChip))
	{
		sprite.setColor(Color(255, 255, 255, 255));
		switch (chip_type)
		{
		case BlueChip:
			chip_sprite.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));
			break;
		case GreenChip:
			chip_sprite.setTextureRect(IntRect(100, 0, TILE_SIZE, TILE_SIZE));
			break;
		case YellowChip:
			chip_sprite.setTextureRect(IntRect(200, 0, TILE_SIZE, TILE_SIZE));
			break;
		default:
			break;
		}
		window.draw(chip_sprite);
	}
	window.draw(sprite);
}

void Selector::MoveSelector(const int& dx = 0, const int& dy = 0)
{
	uint32_t tmp_x = this->x + TILE_SIZE * dx;
	uint32_t tmp_y = this->y + TILE_SIZE * dy;
	
	if ((tmp_x < WINDOW_SIZE) && (tmp_x >= 0) && (tmp_y < WINDOW_SIZE) && (tmp_y >= 0))
	{
		this->x += TILE_SIZE * dx;
		this->y += TILE_SIZE * dy;
	}
	
}