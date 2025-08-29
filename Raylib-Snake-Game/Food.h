#pragma once
#include "raylib.h"
#include "raymath.h"
#include <deque>

class Food
{
public:
	Food(int cellSize, int cellCount, std::deque<Vector2> snakeBody);
	void Draw();

	Texture2D* foodTexture;
	Vector2 position;
	Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody);
private:
	bool ElementInDeque(Vector2 e, std::deque<Vector2> deque);
	int cellSize;
	int cellCount;
	std::deque<Vector2> snakeBody;
};

