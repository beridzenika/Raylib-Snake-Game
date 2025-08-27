#pragma once
#include "raylib.h"
#include "raymath.h"
#include <deque>


class Snake
{
public:
	Snake(int cellSize);
	~Snake();
	void Draw();
	void Update(bool triggered);
	void Reset();
	std::deque <Vector2> body;
	Texture2D snakeHead, snakeTail, snakeBody, snakeCornerR, snakeCornerL;
private:
	int cellSize;
	Color darkGreen;
	Vector2 direction, chaceDiraction;
	int speed, x, y;
	float degree, width, height;
};