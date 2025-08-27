#pragma once
#include "Snake.h"
#include "Food.h"

class Game
{
public:
	Game(int cellSize, int cellCount);
	~Game();
	void Draw();
	void Update();
private:
	double lastUpdateTime, currentTime, triggerInterval;
	bool triggered, isPaused;
	bool paused();
	bool eventTriggered(double interval);
	void CheckEating();
	void CheckBodyColision();
	void CheckBorderColision();
	void GameOver();
	int cellSize, cellCount;
	int score, highScore;
	Snake snake;
	Food food;
};
