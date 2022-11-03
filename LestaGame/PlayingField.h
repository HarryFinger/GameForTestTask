#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "FieldElementType.h"

//#define DEBUG

using namespace sf;

class Selector; //forward declaration

extern const uint32_t WINDOW_SIZE;
extern const uint32_t TILE_SIZE;
extern const uint32_t GRID_NUMBER;
extern const uint32_t WALL_OFFSET;
extern const uint32_t BORDER_SIZE;

class PlayingField
{
private:
	Texture lives_texture;
	Sprite lives_sprite;

	Texture back_texture;
	Sprite back_sprite;

	Texture main_texture;
	Sprite blue_chip_sprite;
	Sprite green_chip_sprite;
	Sprite yellow_chip_sprite;
	Sprite blue_arrow_sprite;
	Sprite green_arrow_sprite;
	Sprite yellow_arrow_sprite;
	Sprite rock_sprite1;
	Sprite rock_sprite2;
	
	std::vector<FieldElementType> chip_array;
	const uint32_t BLUE_MAX_COUNT = 5;
	const uint32_t GREEN_MAX_COUNT = 5;
	const uint32_t YELLOW_MAX_COUNT = 5;
	bool game_over = false;

public:
	PlayingField(const uint32_t N, const uint32_t M);
	~PlayingField();

	const bool& getGameOverStatus() const
	{
		return game_over;
	}

	const std::vector<std::vector<FieldElementType>>& getFieldArray() const
	{
		return field_array;
	}

	void DrawField(RenderWindow&);
	bool CanPicked(const Selector&);
	bool CanPlaced(const Selector&);
	bool CheckIsEmpty(const uint32_t&, const uint32_t&);

	void ValidateWinStatus();

	std::vector<std::vector<FieldElementType>> field_array;
private:
	void RandomChipGenerator();
	bool ColumnCheck(const size_t, FieldElementType);
};