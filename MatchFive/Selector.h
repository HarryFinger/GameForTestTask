#pragma once
#include <SFML/Graphics.hpp>
#include "FieldElementType.h"
#include "SoundManager.h"

extern const uint32_t WINDOW_SIZE;
extern const uint32_t TILE_SIZE;
extern const uint32_t GRID_NUMBER;
extern const uint32_t WALL_OFFSET;
extern const uint32_t BORDER_SIZE;

using namespace sf;

class Selector
{

public:
	FieldElementType chip_type = FieldElementType::Empty;
	bool is_selected = false;
	uint32_t x = 400; //current position x
	uint32_t y = 500; //current position y

private:
	Texture texture;
	Sprite sprite; //selector sprite
	Sprite chip_sprite; //chip sprite if picked

	const float MIN_BLINK_THRESHOLD = 30.f;
	const float MAX_BLINK_THRESHOLD = 250.f;
	Clock blink_clock;
	uint32_t blink = 255;
	const uint32_t BLINK_SPEED = 1;
	enum BlinkState
	{
		Falling,
		Growing
	} blink_state = BlinkState::Falling;

public:
	Selector();
	void DrawSelector(RenderWindow&);
	void MoveSelector(const int&, const int&);
	void StopBlink();
private:
	void SelectorBlink();
};