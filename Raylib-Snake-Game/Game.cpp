#include "Game.h"

Game::Game(int cellSize, int cellCount)
    : cellSize(cellSize),
    cellCount(cellCount),
    snake(cellSize),
    food(cellSize, cellCount, snake.body)
{
    currentTime = 0;
    triggered = false;
    lastUpdateTime = 0;
    triggerInterval = 0.2;
    isPaused = false;
}

Game::~Game()
{
}
void Game::Draw() 
{
    snake.Draw();
    food.Draw();
    // pausing
    if (isPaused) {
        DrawText("Click SPACE to continue", GetScreenWidth() / 6, GetScreenHeight() / 2 - 10, 20, WHITE);
    }
    // draw scores
    DrawText(TextFormat("score %03i", score), 5, 5, 20, WHITE);
    DrawText(TextFormat("high score %03i", highScore), 5, 30, 10, WHITE);
}
void Game::Update() 
{
    // update scores
    score = snake.body.size();
    if (score > highScore) highScore = score;
    //changing pause mode
    if (paused())isPaused = !isPaused;
    
    if (!isPaused) {
        //updating between intervals    
        triggered = eventTriggered(triggerInterval);
        snake.Update(triggered);
        if (triggered) {
            CheckEating();
            CheckBodyColision();
            CheckBorderColision();
        }
    }

}

bool Game::paused()
{
    if (IsKeyPressed(KEY_SPACE)) return true;
    return false;
}

bool Game::eventTriggered(double interval)
{
    currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void Game::CheckEating()
{
    if (Vector2Equals(snake.body[0], food.position)) {
        food.position = food.GenerateRandomPos(snake.body);
    }
    else {
        snake.body.pop_back();
    }
}

void Game::CheckBodyColision()
{
    for (int i = 1; i < snake.body.size(); i++) {
        if (Vector2Equals(snake.body[0], snake.body[i])) {
            GameOver();
            return;
        }
    }
}


void Game::CheckBorderColision()
{
    if (snake.body[0].x == cellCount || snake.body[0].x == -1
     || snake.body[0].y == cellCount || snake.body[0].y == -1)
    {
        GameOver();
    }
}

void Game::GameOver()
{
    snake.Reset();
    food.GenerateRandomPos(snake.body);
}
