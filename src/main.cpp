#include "Function.h"

#include <deque>
#include <iostream>
#include <raylib.h>
#include <cstdlib>
#include <ctime>
#include <raymath.h>

using namespace std;

//The game variable and sizes
int cellSize = 30;
int cellCount = 32;

float offset = 90;

int screenWidth = cellSize *cellCount; 
int screenHeight = cellSize *cellCount; 

//Game colors
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};
Color snakeRed = {187, 101, 68 , 255};

//Player's data
int score = 100;
int numberFoodEaten = 0;

double lastUpdateTime = 0;

bool eventTriggered(double interval){
    double currentTime = GetTime();

    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }

    return false;
}

class Snake{
    public:
        //where the coordinates of the body will be stored.
        deque<Vector2>body = {};
        //default movement
        Vector2 direction = {1,0};
        bool addTail = false;

        Snake(){
            //pushTail
            body.push_back(randomPosition());
        }

        void draw(){
            drawSnakeBody(cellSize, body, snakeRed);
        }

        //the way it works is like poptail then pushhead where head coordinates is changing every frame
        void update(){
            body.push_front(Vector2Add(body[0], direction));
            if(addTail){
                addTail = false;
            }else{
                body.pop_back();
            }

        }

        //when game end, restart, poptail until gone then generate new random position
        void resetSnake(){
            while(!body.empty()){
            body.pop_back();
            }
            body.push_back(randomPosition());
        }

        Vector2 randomPosition(){
            float x = (rand() % 23)+4;
            float y = (rand() % 23)+4;
            return Vector2{x, y};
        }
};

class Food {
    public:
        Vector2 foodPosition;
    
        Food(std::deque<Vector2> snakeBody){
            foodPosition = randomPosition(snakeBody);
        }

        void draw(){
            // DrawText(TextFormat("%f %f", foodPosition.x, foodPosition.y), 1*cellSize, 20*cellSize, 26, DARKGRAY);
            // DrawRectangle(foodPosition.x*cellSize, foodPosition.y*cellSize, cellSize, cellSize, darkGreen);
            drawCircleBlinking(cellSize, foodPosition.x, foodPosition.y, cellSize/2, darkGreen);
        }

        Vector2 randomPositionCell(){
            float x = (rand() % 23)+4;
            float y = (rand() % 23)+4;
            return Vector2{x, y};
        }

        Vector2 randomPosition(std::deque<Vector2> snakeBody){
            Vector2 tempPos = randomPositionCell();

            while(coordinatesOfSnakeBody(tempPos, snakeBody)){
                tempPos = randomPositionCell();
            }

            return tempPos;
        }
};

class Game{
    public:
        Snake snake;
        Food food = Food(snake.body);

        void draw(){
            food.draw();
            snake.draw();
        }

        void update(){
            snake.update();
            foodEaten();
            gameOverValidation();
            // DrawText(TextFormat("%lf, %lf, %lf, %lf", food.foodPosition.x, food.foodPosition.y, snake.body[0].x, snake.body[0].y), 1*cellSize, 25*cellSize, 26, DARKGRAY);
        }

        void foodEaten(){
         if(myOwn_Vector2Equals(snake.body[0], food.foodPosition)){
            score+=100;
            numberFoodEaten++;
            food.foodPosition = food.randomPosition(snake.body); 
            snake.addTail = true;
         }   
        }

        //by checking hit edges or not
        void gameOverValidation(){
            if(snake.body[0].x == (cellCount-4) || snake.body[0].x == 2 || (collidesWithSnakeBody(snake.body[0], snake.body))){
                // gameOverScreen();
                snake.resetSnake();
                DrawText("annyeong", 1*cellSize, 25*cellSize, 30, VIOLET);
            }

            if(snake.body[0].y == (cellCount-3) || snake.body[0].y == 2 || (collidesWithSnakeBody(snake.body[0], snake.body))){
                // gameOverScreen();
                snake.resetSnake();
                DrawText("annyeong", 1*cellSize, 25*cellSize, 30, VIOLET);
            }
        }
};

int main()
{
    srand(time(NULL));

    InitWindow(cellSize*(cellCount-1),cellSize*cellCount, "Snake Game");
    
    SetTargetFPS(60);
    
    Game game;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if(eventTriggered(0.2)){
            game.update();
        }
        
       if(((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && game.snake.direction.y != 1)){
            game.snake.direction = {0,-1};
       }

       if(((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && game.snake.direction.x != 1)){
            game.snake.direction = {-1,0};
       }

       if(((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && game.snake.direction.y != -1)){
            game.snake.direction = {0,1};
       }  

       if((((IsKeyPressed(KEY_D)) || (IsKeyPressed(KEY_RIGHT))) && game.snake.direction.x != -1)){
          game.snake.direction = {1,0};
      }

        // score+=100;
        DrawText(TextFormat("Your Score is: %d", score), 1*cellSize, 30*cellSize, 26, DARKGRAY);

        //Drawing to Window
        game.draw();
        ClearBackground(green);
        DrawRectangleLinesEx(Rectangle{static_cast<float>(offset), static_cast<float>(offset), static_cast<float>(cellSize*cellCount - 210), static_cast<float>(cellSize*cellCount - 210)}, 10, darkGreen);
        DrawText(TextFormat("%lf %lf %d", cellCount-2-offset, offset, cellSize*cellCount - 210), 4*cellSize, 25*cellSize, 26, DARKGRAY);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
