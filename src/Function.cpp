#include<iostream>
#include<raylib.h>
#include<deque>
#include <raymath.h>
#include "Function.h"

float blinkingScale = 1.0f;
int blinkDirection = 0;

bool myOwn_Vector2Equals(Vector2 a, Vector2 b) {
    return a.x == b.x && a.y == b.y;
}

void drawCircleBlinking(int cellSize,int foodPositionX, int foodPositionY, int radious, Color circleColor){
    if (blinkDirection) {
        blinkingScale += 0.02f; 
        if (blinkingScale >= 1.5f) { 
            blinkDirection = 0;
        }
    } else {
        blinkingScale -= 0.02f; 
        if (blinkingScale <= 1.0f) { 
            blinkDirection = 1;
        }
    }

    DrawCircle(foodPositionX * cellSize, foodPositionY * cellSize, radious*blinkingScale, circleColor);
}

void drawSnakeBody(int cellSize, std::deque<Vector2> body, Color snakeBodyColor){
    for(unsigned int i = 0; i<body.size(); i++){
        float x = body[i].x; 
        float y = body[i].y;
        Rectangle segment = Rectangle{(x*cellSize), (y*cellSize), float(cellSize), float(cellSize)};
        if(i == 0){
            // DrawTriangle({x*cellSize, (y*cellSize)-cellSize}, {(x*cellSize)-cellSize, (y*cellSize) + cellSize}, {(x*cellSize)-cellSize, (y*cellSize) + cellSize}, snakeBodyColor);
            DrawRectangleRounded(segment, 1, 6, snakeBodyColor);
        }else{
            DrawRectangleRounded(segment, 0.5, 6, snakeBodyColor);
        // DrawRectangle(x*cellSize, y*cellSize, cellSize, cellSize, snakeBodyColor); 
        }
    }
}

bool coordinatesOfSnakeBody(Vector2 element, std::deque<Vector2> deque){
    for(unsigned i = 0; i<deque.size(); i++){
        if(myOwn_Vector2Equals(deque[i], element)){
            return true;
        }
    }
    return false;
}

bool collidesWithSnakeBody(Vector2 element, std::deque<Vector2> deque){
    for(unsigned i = 1; i<=deque.size(); i++){
        if(myOwn_Vector2Equals(deque[i], element)){
            return true;
        }
    }
    return false;
}

