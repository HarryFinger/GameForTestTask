#include "PlayingField.h"
#include "Selector.h"


PlayingField::PlayingField(const uint32_t N, const uint32_t M)
{
	back_texture.loadFromFile("./../LestaGame/images/ground_1.png");
	back_sprite.setTexture(back_texture);
	main_texture.loadFromFile("./../LestaGame/images/new_tiles.png");
	blue_chip_sprite.setTexture(main_texture);
	blue_chip_sprite.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	green_chip_sprite.setTexture(main_texture);
	green_chip_sprite.setTextureRect(IntRect(100, 0, TILE_SIZE, TILE_SIZE));
	yellow_chip_sprite.setTexture(main_texture);
	yellow_chip_sprite.setTextureRect(IntRect(200, 0, TILE_SIZE, TILE_SIZE));
	rock_sprite1.setTexture(main_texture);
	rock_sprite1.setTextureRect(IntRect(300, 0, TILE_SIZE, TILE_SIZE));
	rock_sprite2.setTexture(main_texture);
	rock_sprite2.setTextureRect(IntRect(800, 0, TILE_SIZE, TILE_SIZE));
	blue_arrow_sprite.setTexture(main_texture);
	blue_arrow_sprite.setTextureRect(IntRect(500, 0, TILE_SIZE, TILE_SIZE));
	green_arrow_sprite.setTexture(main_texture);
	green_arrow_sprite.setTextureRect(IntRect(600, 0, TILE_SIZE, TILE_SIZE));
	yellow_arrow_sprite.setTexture(main_texture);
	yellow_arrow_sprite.setTextureRect(IntRect(700, 0, TILE_SIZE, TILE_SIZE));
	
	//basic field(blocks)
	for (size_t i = 0; i < N; i++)
	{
		std::vector<FieldElementType> vec;
		for (size_t j = 0; j < M; j++)
		{
			if ((j < WALL_OFFSET || j >= GRID_NUMBER - WALL_OFFSET) || (i < WALL_OFFSET || i >= GRID_NUMBER - WALL_OFFSET)) 
			{
				if (rand() % 2 == 1)
					vec.push_back(FieldElementType::Rock1);
				else
					vec.push_back(FieldElementType::Rock2);
			}
			else 
				vec.push_back(FieldElementType::Empty);
		}
		field_array.push_back(vec);
	}

#ifdef DEBUG
	field_array[2][2] = FieldElementType::BlueChip;
	field_array[2][3] = FieldElementType::BlueChip;
	field_array[2][4] = FieldElementType::BlueChip;
	field_array[2][5] = FieldElementType::BlueChip;
	field_array[2][6] = FieldElementType::BlueChip;

	field_array[4][2] = FieldElementType::YellowChip;
	field_array[4][3] = FieldElementType::GreenChip;
	field_array[4][4] = FieldElementType::GreenChip;
	field_array[4][5] = FieldElementType::GreenChip;
	field_array[4][6] = FieldElementType::GreenChip;

	field_array[6][2] = FieldElementType::GreenChip;
	field_array[6][3] = FieldElementType::YellowChip;
	field_array[6][4] = FieldElementType::YellowChip;
	field_array[6][5] = FieldElementType::YellowChip;
	field_array[6][6] = FieldElementType::YellowChip;
#endif // DEBUG


#ifndef DEBUG
	//option field(blocks)
	field_array[3][2] = FieldElementType::Rock1;
	field_array[5][2] = FieldElementType::Rock1;
	field_array[3][4] = FieldElementType::Rock2;
	field_array[5][4] = FieldElementType::Rock1;
	field_array[3][6] = FieldElementType::Rock2;
	field_array[5][6] = FieldElementType::Rock1;

	RandomChipGenerator(); //generate chips 
#endif // not DEBUG


	//to do randomizer
	for (size_t i = 2; i <= 6; i += 2)
	{
		for (size_t j = 2; j < 7; j++)
		{
			if(!chip_array.empty())
			{
				field_array[i][j] = chip_array.back();
				chip_array.pop_back();
			}
		}
	}

	field_array[2][8] = FieldElementType::BlueChipArrow;
	field_array[4][8] = FieldElementType::GreenChipArrow;
	field_array[6][8] = FieldElementType::YellowChipArrow;
}

PlayingField::~PlayingField() 
{

}

void PlayingField::DrawField(RenderWindow& window)
{
	window.draw(back_sprite);

	for (size_t i = 0; i < GRID_NUMBER; i++)
	{
		for (size_t j = 0; j < GRID_NUMBER; j++)
		{
			
			switch (field_array[i][j])
			{
			case BlueChip:
				blue_chip_sprite.setPosition(static_cast<float>(TILE_SIZE * i), static_cast<float>(TILE_SIZE * j));
				window.draw(blue_chip_sprite);
				break;
			case GreenChip:
				green_chip_sprite.setPosition(static_cast<float>(TILE_SIZE * i), static_cast<float>(TILE_SIZE * j));
				window.draw(green_chip_sprite);
				break;
			case YellowChip:
				yellow_chip_sprite.setPosition(static_cast<float>(TILE_SIZE * i), static_cast<float>(TILE_SIZE * j));
				window.draw(yellow_chip_sprite);
				break;
			case Rock1:
				rock_sprite1.setPosition(static_cast<float>(TILE_SIZE * i), static_cast<float>(TILE_SIZE * j));
				window.draw(rock_sprite1);
				break;
			case Rock2:
				rock_sprite2.setPosition(static_cast<float>(TILE_SIZE * i), static_cast<float>(TILE_SIZE * j));
				window.draw(rock_sprite2);
				break;
			case Empty:
				continue;
			case BlueChipArrow:
				blue_arrow_sprite.setPosition(static_cast<float>(TILE_SIZE * i), static_cast<float>(TILE_SIZE * j));
				window.draw(blue_arrow_sprite);
				break;
			case GreenChipArrow:
				green_arrow_sprite.setPosition(static_cast<float>(TILE_SIZE * i), static_cast<float>(TILE_SIZE * j));
				window.draw(green_arrow_sprite);
				break; 
			case YellowChipArrow:
				yellow_arrow_sprite.setPosition(static_cast<float>(TILE_SIZE * i), static_cast<float>(TILE_SIZE * j));
				window.draw(yellow_arrow_sprite);
				break;

			default:
				break;
			}
		}
	}
}

bool PlayingField::CanPicked(const Selector& selector)
{
	uint32_t i = selector.x / TILE_SIZE;
	uint32_t j = selector.y / TILE_SIZE;
	if ((field_array[i][j] == FieldElementType::BlueChip) || (field_array[i][j] == FieldElementType::GreenChip) || (field_array[i][j] == FieldElementType::YellowChip))
	{
		return true;
	}
	else return false;
}

bool PlayingField::CanPlaced(const Selector& selector)
{
	uint32_t i = selector.x / TILE_SIZE;
	uint32_t j = selector.y / TILE_SIZE;
	if (field_array[i][j] == FieldElementType::Empty)
	{
		return true;
	}
	else return false;
}

bool PlayingField::CheckIsEmpty(const uint32_t& x, const uint32_t& y)
{
	uint32_t i = x / TILE_SIZE;
	uint32_t j = y / TILE_SIZE;
	if (field_array[i][j] == FieldElementType::Empty)
		return true;
	else
		return false;
}

void PlayingField::ValidateWinStatus()
{
	game_over = (ColumnCheck(2, FieldElementType::BlueChip) && ColumnCheck(4, FieldElementType::GreenChip) && ColumnCheck(6, FieldElementType::YellowChip));
}

void PlayingField::RandomChipGenerator()
{
	for (size_t i = 0; i < BLUE_MAX_COUNT; i++)
	{
		this->chip_array.push_back(FieldElementType::BlueChip);
		this->chip_array.push_back(FieldElementType::GreenChip);
		this->chip_array.push_back(FieldElementType::YellowChip);
	}
	std::random_device r;
	std::default_random_engine rng(r());
	std::shuffle(chip_array.begin(), chip_array.end(), rng);

}

bool PlayingField::ColumnCheck(const size_t index, FieldElementType type)
{
	if (field_array[index][2] != type)
		return false;

	return
		(field_array[index][2] == field_array[index][3]) &&
		(field_array[index][2] == field_array[index][4]) &&
		(field_array[index][2] == field_array[index][5]) &&
		(field_array[index][2] == field_array[index][6]);
}