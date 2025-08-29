#include "Snake.h"

Snake::Snake(int cellSize)
{
	this->cellSize = cellSize;
	
	Reset();
	
	snakeTexture = nullptr;
}

void Snake::Draw()
{

	for (int i = 0; i < body.size(); i++)
	{
		degree = 0;
		//body directions
		if (i != 0) {
			if (body[i].x > body[i - 1].x) degree = 90;
			else if (body[i].y > body[i - 1].y) degree = 180;
			else if (body[i].x < body[i - 1].x) degree = 270;
			else degree = 0;
		}
		//head direction
		if(i == 0) {
			texturePos = SnakePos::head;
			if (direction.x == -1) degree = 90;
			else if (direction.y == -1) degree = 180;
			else if (direction.x == 1) degree = 270;
			else degree = 0;
		} 
		//tail direction
		else if (i == body.size()-1) {
			texturePos = SnakePos::tail;
		}
		//corner directions
		else {
			if (body[i - 1].x != body[i + 1].x && body[i - 1].y != body[i + 1].y) {
				texturePos = SnakePos::cornerL;
				int cross = (body[i - 1].x - body[i].x) * (body[i + 1].y - body[i].y)
						  - (body[i - 1].y - body[i].y) * (body[i + 1].x - body[i].x);
				//if turn right
				if (cross > 0) {
					degree += 90;
					texturePos = SnakePos::cornerR;
				}
			}
			else texturePos = SnakePos::body;
		}
		//texture drawings
		width = snakeTexture->width;
		DrawTexturePro(
			*snakeTexture,
			{ 0, texturePos* width, width, width },
			{ float(body[i].x + 0.5) * cellSize, float(body[i].y + 0.5) * cellSize, (float)cellSize, (float)cellSize },
			{ (float)cellSize / 2, (float)cellSize / 2 },
			degree,
			WHITE
		);
	}
}

void Snake::Update(bool triggered)
{
	//snake movements
	if (IsKeyDown(KEY_UP) && direction.y != 1) {
		chaceDiraction = { 0,-1 };
	}
	else if (IsKeyDown(KEY_DOWN) && direction.y != -1) {
		chaceDiraction = { 0,1 };
	}
	else if (IsKeyDown(KEY_LEFT) && direction.x != 1) {
		chaceDiraction = { -1,0 };
	}
	else if (IsKeyDown(KEY_RIGHT) && direction.x != -1) {
		chaceDiraction = { 1,0 };
	}
	//moving front
	if (triggered) {
		direction = chaceDiraction;
		body.push_front(Vector2Add(body[0], direction));
	}
}

void Snake::Reset()
{
	body = { Vector2{3, 1}, Vector2{2, 1}, Vector2{1, 1} };
	direction = { 1,0 };
	chaceDiraction = { 0,0 };
}
