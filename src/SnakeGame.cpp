// SnakeGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

#include <cmath>

struct Point {
    Point(int x, int y) {
        X = x;
        Y = y;
    }

    bool operator == (const Point& p) {
        return(X == p.X && Y == p.Y) ? true : false;
    }
    int X;
    int Y;
};

#define SCREEN_WIDTH 51
#define SCREEN_HEIGHT 21

#define SCREEN_BORDER 1

#define SCORE_PER_FOOD 10;

//#define KEY_UP 72
//#define KEY_DOWN 80
//#define KEY_LEFT 75
//#define KEY_RIGHT 77
// _getchar() can use to capture keyboard inputs. But it's give additional charcters for arrow presses. So implemented own method => GetChar()

#define KEY_UP 38
#define KEY_DOWN 40
#define KEY_LEFT 37
#define KEY_RIGHT 39
#define KEY_ESC 27

bool gameStarted = false;

enum Direction {
    Up = 0,
    Down,
    Left,
    Right
};

Direction snake_current_direction = Up;
bool game_over = false;
std::vector<Point> snake_body;
int snake_length = 2;
Point current_food_position = Point(0,0);
Point deafult_snake_position = Point(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
int score = 0;

void SETUP() {
    std::string setupMsg = "GAME LOADING";
    for (int i = 0; i < 10; i++) {
        system("cls");
        setupMsg += ".";
        std::cout << setupMsg << std::endl;
        Sleep(100);
    }
    snake_body.push_back(deafult_snake_position);
    for (int i = 1; i < snake_length; i++) {
        switch (snake_current_direction) {
        case Up:
            snake_body.push_back(Point(deafult_snake_position.X, deafult_snake_position.Y + i));
            break;
        case Down:
            snake_body.push_back(Point(deafult_snake_position.X, deafult_snake_position.Y - i));
            break;
        case Left:
            snake_body.push_back(Point(deafult_snake_position.X + i, deafult_snake_position.Y));
            break;
        case Right:
            snake_body.push_back(Point(deafult_snake_position.X - i, deafult_snake_position.Y));
            break;
        default:
            break;
        }
    }
    current_food_position = Point(1 + (rand() % SCREEN_WIDTH) , 1 + (rand() % SCREEN_HEIGHT));
    system("cls");
    setupMsg = "GAME START";
    std::cout << setupMsg << std::endl;
    Sleep(100);
}

WORD GetChar()
{
    DWORD NumEventsRead;
    INPUT_RECORD InputRecord;
    HANDLE StdIn = GetStdHandle(STD_INPUT_HANDLE);
    while (1)
    {
        if (!ReadConsoleInput(StdIn, &InputRecord, 1, &NumEventsRead))
            return 0;
        if (InputRecord.EventType & KEY_EVENT && InputRecord.Event.KeyEvent.bKeyDown)
        {
            if (InputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL &&
                InputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU &&
                InputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT)
            {
                return InputRecord.Event.KeyEvent.wVirtualKeyCode;
            }
        }
    }
}

void INPUTVALUE() {
    if (_kbhit()) { 
        int input_value = GetChar();
        switch (input_value) {
        case KEY_UP:
            if (snake_current_direction == Down) {
                break;
            }
            snake_current_direction = Up;
            break;
        case KEY_DOWN:
            if (snake_current_direction == Up) {
                break;
            }
            snake_current_direction = Down;
            break;
        case KEY_LEFT:
            if (snake_current_direction == Right) {
                break;
            }
            snake_current_direction = Left;
            break;
        case KEY_RIGHT:
            if (snake_current_direction == Left) {
                break;
            }
            snake_current_direction = Right;
            break;
        case KEY_ESC:
            snake_current_direction = Right;
            break;
        default:
            break;
        }
    }
}

void LOGIC() {
    Point prevPos = snake_body[0];
    for (int i = 1; i < snake_body.size(); i++) {
        Point prevPrevPos = snake_body[i];
        snake_body[i] = prevPos;
        prevPos = prevPrevPos;
    }

    switch (snake_current_direction) {
    case Up:
        snake_body[0].Y = snake_body[0].Y - 1;
        break;
    case Down:
        snake_body[0].Y = snake_body[0].Y + 1;
        break;
    case Left:
        snake_body[0].X = snake_body[0].X - 1;
        break;
    case Right:
        snake_body[0].X = snake_body[0].X + 1;
        break;
    default:
        break;
    }

    if (snake_body[0].X < 0 || snake_body[0].X > SCREEN_WIDTH 
        || snake_body[0].Y < 0 || snake_body[0].Y > SCREEN_HEIGHT ||
        std::find(snake_body.begin() + 1, snake_body.end(), snake_body[0]) != std::end(snake_body)) {
        game_over = true;
    }
    if (snake_body[0] == current_food_position) {
        score += SCORE_PER_FOOD;
        snake_body.push_back(snake_body[snake_body.size() - 1]);
        ++snake_length;
        current_food_position = Point(1 + (rand() % SCREEN_WIDTH), 1 + (rand() % SCREEN_HEIGHT));
    }
}

void RENDER() {
    system("cls");
    for (int i = 0; i < SCREEN_HEIGHT + (SCREEN_BORDER * 2); i++) {
        for (int j = 0; j < SCREEN_WIDTH + (SCREEN_BORDER * 2); j++) {
            if (i == 0 || i == SCREEN_HEIGHT + (SCREEN_BORDER * 2) - 1) {
                std::cout << "#";
            }
            else {
                if (j == 0 || j == SCREEN_WIDTH + (SCREEN_BORDER * 2) - 1) {
                    std::cout << "#";
                }
                else {
                    if (std::find(snake_body.begin(), snake_body.end(), Point(j,i)) != std::end(snake_body))
                    {
                        if (snake_body[0] == Point(j, i))
                        {
                            std::cout << "@";
                        }
                        else
                        {
                            std::cout << "o";
                        }
                    }
                    else {
                        if (current_food_position == Point(j, i))
                        {
                            std::cout << "*";
                        }
                        else
                        {
                            std::cout << " ";
                        }
                    }
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "Score: " << score << std::endl;
}

int main()
{
    SETUP();
    while (!game_over) {
        INPUTVALUE();
        LOGIC();
        RENDER();
        Sleep(10);
    }
    
    system("cls");
    std::cout << "-------------- Game Over! --------------" << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}
