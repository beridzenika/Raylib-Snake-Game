#pragma once
#include "Snake.h"
#include "Food.h"
#include "Menu.h"

class Game
{
public:
	Game(int cellSize, int cellCount);
	void Draw();
	void Update();
private:
	double lastUpdateTime, currentTime, triggerInterval;
	bool triggered, isPaused;
	bool EventTriggered(double interval);
	void CheckEating();
	void CheckBodyColision();
	void CheckBorderColision();
	void GameOver();
	void Paused();
	int cellSize, cellCount;
	int score, highScore;
	Snake snake;
	Food food;
	Menu menu;
};
