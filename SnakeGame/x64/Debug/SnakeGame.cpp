#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>

class SnakeGame
{
    struct Apple {
        int x;
        int y;
    };

    struct Node {
        int x;
        int y;
        Node* next;
    };
private:
    Node* snake = nullptr;
    Node* head = nullptr;
    Node* tail = nullptr;
    Apple apple;
    int score = 1;

public:
    void Tail()
    {
        Node* current = snake;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        tail = current;
    }

    void SnakeAdd(int x, int y) // добавление части змейки
    {
        if (snake == nullptr)
        {
            snake = new Node{ x, y, nullptr };
            return;
        }
        Tail();
        Node* current = tail;
        current->next = new Node{ x, y, nullptr };
        score += 1;
    }

    void GenerateApple() // генерация яблока на свободной ячейке
    {
        bool successfulX = false;
        bool successfulY = false;
        int finalX = 99;
        int finalY = 99;

        while (!successfulX) {
            bool completed = true;
            finalX = rand() % 10;
            Node* current = snake;
            if (current != nullptr)
            {
                if (current->x == finalX)
                {
                    completed = false;
                }
                while (current->next != nullptr && completed)
                {
                    if (current->next->x == finalX)
                    {
                        completed = false;
                        break;
                    }
                    current = current->next;
                }
            }
            if (completed)
                successfulX = true;
        }

        while (!successfulY) {
            bool completed = true;
            finalY = rand() % 10;
            Node* current = snake;
            if (current != nullptr)
            {
                if (current->y == finalY)
                {
                    completed = false;
                }
                while (current->next != nullptr && completed)
                {
                    if (current->next->y == finalY)
                    {
                        completed = false;
                        break;
                    }
                    current = current->next;
                }
            }
            if (completed)
                successfulY = true;
        }

        apple.x = finalX;
        apple.y = finalY;
    }

    bool RefreshField(char field[10][10], int align) // функция для отрисовки игры
    {
        system("cls");

        Node* nextPos = snake;
        int previousPosX = 0;
        int previousPosY = 0;
        bool active = true;

        if (nextPos != nullptr)
        {
            previousPosX = nextPos->x;
            previousPosY = nextPos->y;

            if (align == 0) // вверх
            {
                nextPos->x = (nextPos->x <= 0) ? 9 : nextPos->x - 1;
            }
            else if (align == 1) // вниз
            {
                nextPos->x = (nextPos->x >= 9) ? 0 : nextPos->x + 1;
            }
            else if (align == 2) // влево
            {
                nextPos->y = (nextPos->y <= 0) ? 9 : nextPos->y - 1;
            }
            else if (align == 3) // вправо
            {
                nextPos->y = (nextPos->y >= 9) ? 0 : nextPos->y + 1;
            }
        }

        for (int i = 0; i < 10; i++) // заполняем поле символами по умолчанию
        {
            for (int j = 0; j < 10; j++)
            {
                field[i][j] = '.';
            }
        }

        field[apple.x][apple.y] = '*';

        Node* current = snake;
        if (current != nullptr) // перемещение змейки и заполенение поля ее символами
        {
            int x = current->x;
            int y = current->y;

            Node* checkSnake = snake;

            while (checkSnake->next != nullptr) // проверка на то что врезалась ли змейка в саму себя
            {
                if (checkSnake->next->x == x && checkSnake->next->y == y)
                {
                    active = false;
                }
                checkSnake = checkSnake->next;
            }

            if (x == apple.x && y == apple.y) // проверка на то съела ли змейка яблоко
            {
                SnakeAdd(previousPosX, previousPosY);
                GenerateApple();
            }

            field[x][y] = 'O'; // голова змейки

            while (current->next != nullptr) // перемещение каждой части змейки на следующую ячейку
            {
                x = current->next->x;
                y = current->next->y;
                current->next->x = previousPosX;
                current->next->y = previousPosY;
                previousPosX = x;
                previousPosY = y;

                field[current->next->x][current->next->y] = 'o'; // ее части тела
                current = current->next;
            }
        }

        for (int i = 0; i < 10; i++) // выводим игру
        {
            for (int j = 0; j < 10; j++)
            {
                std::cout << field[i][j] << " ";
            }
            std::cout << "\n";
        }

        std::cout << "score : " << score;
        return active;
    }
};

int main()
{
    int d = 0;
    SnakeGame game;
    srand(time(NULL));
    char field[10][10]; // создаем поле
    game.SnakeAdd(5, 5); // добавляем начальную змейку
    game.GenerateApple(); // генерируем начальное яблоко
    bool active = true; // переменная для проверки на проигрышь
    int align = 0;

    while (active)
    {
        active = game.RefreshField(field, align);
        Sleep(150);

        if (_kbhit()) // когда нажата клавиша выполняется условие
        {
            switch (_getch())
            {
            case 'w':
                align = 0;
                break;
            case 's':
                align = 1;
                break;
            case 'a':
                align = 2;
                break;
            case 'd':
                align = 3;
                break;
            }
        }
    }

    std::cout << "\nИгра окончена! Нажмите любую клавишу для выхода...\n";
    _getch(); // Ожидание нажатия клавиши перед закрытием
    return 0;
}