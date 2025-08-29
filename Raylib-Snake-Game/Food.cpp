#include "Food.h"

Food::Food(int cellSize, int cellCount, std::deque<Vector2> snakeBody)
{
	this->cellSize = cellSize;
	this->cellCount = cellCount;
	this->snakeBody = snakeBody;
    //generating coordinates of apple
	position = GenerateRandomPos(snakeBody);

	foodTexture = nullptr;
}

void Food::Draw()
{
	DrawTextureEx(
		*foodTexture,
		{ position.x * cellSize, position.y * cellSize }, 
		0.0f, 
		float(cellSize/ foodTexture->width),
		WHITE);

}


bool Food::ElementInDeque(Vector2 e, std::deque<Vector2> deque)
{
	for (int i = 0; i < deque.size(); i++) {
		if (Vector2Equals(deque[i], e)) {
			return true;
		}
	}return false;
}
Vector2 Food::GenerateRandomPos(std::deque<Vector2> snakeBody)
{
	Vector2 position;
	do
	{
		float x = GetRandomValue(0, cellCount - 1);
		float y = GetRandomValue(0, cellCount - 1);
		position = { x,y };
	} while (ElementInDeque(position, snakeBody));

	return position;
}

