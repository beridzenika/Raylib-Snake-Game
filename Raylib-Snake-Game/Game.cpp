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

    highScore = 0;
    score = 0;

    food.foodTexture = &menu.GetSelectedFoodTexture();
    snake.snakeTexture = &menu.GetSelectedSnakeTexture();
}


void Game::Draw() 
{
    snake.Draw();
    food.Draw();
    // draw scores
    DrawText(TextFormat("score %03i", score), 5, 5, 20, WHITE);
    DrawText(TextFormat("high score %03i", highScore), 5, 30, 10, WHITE);

    // pausing
    if (isPaused) {
        menu.Draw();
    }
}
void Game::Update() 
{
    // update scores
    score = snake.body.size();
    if (score > highScore) highScore = score;
    //changing pause mode
    Paused();

    
    if (!isPaused) {
        //updating between intervals    
        triggered = EventTriggered(triggerInterval);
        snake.Update(triggered);
        if (triggered) {
            CheckEating();
            CheckBodyColision();
            CheckBorderColision();
        }
    }
    else {
        menu.Update();
        triggerInterval = menu.GetSpeed();
        food.foodTexture = &menu.GetSelectedFoodTexture();
        snake.snakeTexture = &menu.GetSelectedSnakeTexture();
    }

}

void Game::Paused()
{
    if (IsKeyPressed(KEY_SPACE)) isPaused = !isPaused;
}

bool Game::EventTriggered(double interval)
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
