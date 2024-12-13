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
	Node* tail = nullptr;
	Apple apple;
	char field[10][10];
	int score = 95;

public:
	void Tail() // определяем хвост, последняя часть в змейке
	{
		Node* current = snake;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		tail = current;
	}

	void SnakeAdd(int x, int y) // добавление части змейки в конец
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
		while (true) {
			int x = rand() % 10;
			int y = rand() % 10;
			if (field[x][y] == '.' || field[x][y] == NULL) {
				apple.x = x;
				apple.y = y;
				break;
			}
		}
	}

	bool RefreshField(int align) // функция для отрисовки игры
	{
		system("cls"); // очищаем консоль
		Node* nextPos = snake;
		int previousPosX = 0;
		int previousPosY = 0;
		bool active = true;

		if (score >= 98) // проверка на победу
		{
			active = false;
		}

		if (nextPos != nullptr)
		{
			switch (align) // определяем в каком направлении двигается змейка
			{
			case 0: // вперед
				previousPosX = nextPos->x;
				previousPosY = nextPos->y;

				if (nextPos->x <= 0)
				{
					nextPos->x = 9;
				}
				else
				{
					nextPos->x -= 1;
				}
				break;
			case 1: // назад
				previousPosX = nextPos->x;
				previousPosY = nextPos->y;

				if (nextPos->x >= 9)
				{
					nextPos->x = 0;
				}
				else
				{
					nextPos->x += 1;
				}
				break;
			case 2: // влево
				
				previousPosX = nextPos->x;
				previousPosY = nextPos->y;

				if (nextPos->y <= 0)
				{
					nextPos->y = 9;
				}
				else
				{
					nextPos->y -= 1;
				}
				break;
			case 3: // вправо
				previousPosX = nextPos->x;
				previousPosY = nextPos->y;

				if (nextPos->y >= 9)
				{
					nextPos->y = 0;
				}
				else
				{
					nextPos->y += 1;
				}
				break;

			}

		}

		for (int i = 0; i < 10; i++) // заполняем поле символами по умолчанию
		{
			for (int j = 0; j < 10; j++)
			{
				field[i][j] = '.';
			}
		}

		field[apple.x][apple.y] = 'X'; // заносим в массив field яблоко

		Node* current = snake;
		if (current != nullptr) // перемещение змейки и заполенение массива field символами змейки
		{
			int x = current->x;
			int y = current->y;

			Node* checkSnake = snake;

			while (checkSnake->next != nullptr) // проходим по каждой части змейки
			{
				if (checkSnake->next->x == x && checkSnake->next->y == y) // проверка на то врезалась ли голова змейки в тело
				{
					active = false;
				}
				checkSnake = checkSnake->next;
			}

			field[x][y] = 'O'; // заносим в массив field голову змейки

			while (current->next != nullptr) // перемещение каждой части змейки на предыдущую позицию
			{
				x = current->next->x;
				y = current->next->y;
				current->next->x = previousPosX;
				current->next->y = previousPosY;
				previousPosX = x;
				previousPosY = y;

				field[current->next->x][current->next->y] = 'o'; // занесение в массив field ее части тела
				current = current->next;
			}

			Node* checkApple = snake;

			if (checkApple->x == apple.x && checkApple->y == apple.y) // проверка на то съела ли голова змейки яблоко
			{
				SnakeAdd(previousPosX, previousPosY); // добавляем часть змейки на последнюю позицию
				GenerateApple(); // генерируем новое яблоко
			}
			
		}

		for (int i = 0; i < 10; i++) // выводим массив field
		{
			for (int j = 0; j < 10; j++)
			{
				std::cout << field[i][j] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "score : " << score << "\n";
		return active;
	}
};



int main()
{
	int t = 0;
	SnakeGame game;
	srand(time(NULL));
	game.SnakeAdd(5, 5); // начальная змейка
	game.GenerateApple(); // начальное яблоко
	bool active = true;
	int align = 0;

	while (active)
	{
		active = game.RefreshField(align); // обновление поля игры
		Sleep(150);

		if (_kbhit()) // когда нажимается клавиша выполняется условие
		{
			switch (_getch()) // определяем какую клавишу нажали
			{
			case'w':
				if (align != 0 && align != 1)
				{
					align = 0;
				}
				break;
			case's':
				if (align != 0 && align != 1)
				{
					align = 1;
				}
				break;
			case'a':
				if (align != 2 && align != 3)
				{
					align = 2;
				}
				break;
			case'd':
				if (align != 2 && align != 3)
				{
					align = 3;
				}
				break;
			}

		}

	}

	std::cout << "GAME OVER";
}