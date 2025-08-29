#pragma once
#include "raylib.h"
#include <vector>
#include <string>
#include <filesystem>

class Menu
{
public:
	Menu();
	~Menu();
	void Draw();
	void Update();
	float GetSpeed();
	Texture2D& GetSelectedFoodTexture();
	Texture2D& GetSelectedSnakeTexture();
private:

	Color green, darkGreen;
	float marginX, marginY;
	int foodTextureI, snakeTextureI, speedI, selected, settingNum;

	std::vector<Texture2D> foodTextures;
	std::vector<Texture2D> snakeTextures;

	struct SpeedOption {
		std::string mode;
		float interval;
	};
	std::vector<SpeedOption> speedOptions;
	void FoodTextureLoader();
	void SnakeTextureLoader();

	struct selectedName {
		static constexpr int food = 0;
		static constexpr int snake = 1;
		static constexpr int speed = 2;
	};
};

