#include <iostream>
#include "raylib.h"
#include "Game.h"


int main() {
	Color green = { 173,204,96,255 };
	Color darkGreen = { 43,51,24,255 };

	int cellSize = 32, cellCount = 15;

	InitWindow(cellCount*cellSize, cellCount * cellSize, "Hungry Snake Game");
	SetTargetFPS(60);
	
	Game game(cellSize, cellCount);

	while (!WindowShouldClose()) 
	{
		//update
		game.Update();
		
		BeginDrawing();
		//draw
		ClearBackground(green);
		game.Draw();
		
		EndDrawing();
	}
	CloseWindow();
	return 0;
}