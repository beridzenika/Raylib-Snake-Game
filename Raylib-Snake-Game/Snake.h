#pragma once
#include "raylib.h"
#include "raymath.h"
#include <deque>


class Snake
{
public:
	Snake(int cellSize);
	void Draw();
	void Update(bool triggered);
	void Reset();
	std::deque <Vector2> body;
	Texture2D* snakeTexture;
private:
	int cellSize;
	Color darkGreen;
	Vector2 direction, chaceDiraction;
	int speed, x, y;
	float degree, width, height, texturePos;
	struct SnakePos {
		static constexpr int tail = 0;
		static constexpr int body = 1;
		static constexpr int head = 2;
		static constexpr int cornerL = 3;
		static constexpr int cornerR = 4;
	};
};