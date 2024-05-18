#ifndef Function_h
#define Function_h
#include "raylib.h"
#include "deque"
extern float offset;
extern int screenWidth;
extern int screenWeight;
void drawCircleBlinking(int cellSize, int foodPositionX, int foodPositionY, int radious, Color circleColor);
void drawSnakeBody(int cellSize, std::deque<Vector2> body, Color snakeBodyColor);
bool myOwn_Vector2Equals(Vector2 a, Vector2 b);
bool coordinatesOfSnakeBody(Vector2 element, std::deque<Vector2> deque);
bool collidesWithSnakeBody(Vector2 element, std::deque<Vector2> deque);
#endif
