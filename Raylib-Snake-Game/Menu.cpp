#include "Menu.h"


Menu::Menu()
{
	marginX = 20;
	marginY = 20;
	green = { 173,204,96,255 };
	darkGreen = { 43,51,24,255 };
	
	foodTextureI = 0;
	snakeTextureI = 0;
	speedI = 1;
	selected = 0;
	settingNum = 3;

	speedOptions = {
		{ "Low", 0.3 },
		{ "Medium", 0.2 },
		{ "Fast", 0.1 }
	};

	FoodTextureLoader();
	SnakeTextureLoader();
}

Menu::~Menu()
{
	for (Texture2D& food : foodTextures) {
		UnloadTexture(food);
	}
	for (Texture2D& snake : snakeTextures) {
		UnloadTexture(snake);
	}
}



void Menu::Draw() {
	DrawRectangleRounded(Rectangle{ marginX,marginY, GetScreenWidth() - marginX*2, GetScreenHeight() - marginY*2}, 0.1, 0, green);
	DrawRectangleRoundedLines (Rectangle{ marginX,marginY, GetScreenWidth() - marginX * 2, GetScreenHeight() - marginY * 2 }, 0.1, 6, darkGreen);
	DrawText("Move with arrows to chose, enter to change, space to continue", 
		      40, 40, 12, darkGreen);

	
	DrawTextureEx(
		foodTextures[foodTextureI],
		{ 60, 80 },
		0.0f,
		3,
		selected == selectedName::food? WHITE : GRAY);
	DrawTexturePro(
		snakeTextures[snakeTextureI],
		{ 0, 0, 16, 16*3 },
		{ 220, 80, 16*3, 16*9 },
		{3,3},
		0.0f,
		selected == selectedName::snake ? WHITE : GRAY
	);
	DrawText(speedOptions[speedI].mode.c_str(), 350, 90, 24, selected == selectedName::speed ? WHITE : GRAY);
}
void Menu::Update() {
	
	if (IsKeyPressed(KEY_RIGHT)) {
		selected++;
		selected = selected % settingNum;
	}
	if (IsKeyPressed(KEY_LEFT)) {
		selected += settingNum - 1;
		selected = selected % settingNum;
	}

	if (IsKeyPressed(KEY_ENTER) && selected == selectedName::food) {
		foodTextureI++;
		foodTextureI = foodTextureI % foodTextures.size();
	}
	if (IsKeyPressed(KEY_ENTER) && selected == selectedName::snake) {
		snakeTextureI++;
		snakeTextureI = snakeTextureI % snakeTextures.size();
	}
	if (IsKeyPressed(KEY_ENTER) && selected == selectedName::speed) {
		speedI++;
		speedI = speedI % speedOptions.size();
	}
}

float Menu::GetSpeed()
{
	return speedOptions[speedI].interval;
}

Texture2D& Menu::GetSelectedFoodTexture()
{
	return foodTextures[foodTextureI];
}

Texture2D& Menu::GetSelectedSnakeTexture()
{
	return snakeTextures[snakeTextureI];
}

void Menu::FoodTextureLoader()
{
	for (const auto& entry :
		std::filesystem::directory_iterator("Textures/food")) {
		foodTextures.push_back(LoadTexture(entry.path().string().c_str()));
	}
}

void Menu::SnakeTextureLoader()
{
	for (const auto& entry :
		std::filesystem::directory_iterator("Textures/snakes")) {
		snakeTextures.push_back(LoadTexture(entry.path().string().c_str()));
	}
}
