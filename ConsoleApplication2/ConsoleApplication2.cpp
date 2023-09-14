#include <iostream>
#include <ctime> // time
#include <Windows.h> // окрашивание, работа с координатами
#include <conio.h> // configurate input output
using namespace std;

enum derections { LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };


int main()
{
	system("title Maze"); // смена текста в заголовке консольлного окна

	// дескриптор (идентификатор), уникальный номер окна консоли
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	// скрываем мигающий курсор в консоли
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100; // 1...100
	SetConsoleCursorInfo(h, &info);

	srand(time(0)); // запуск алгоритма генерации СЧ

	const int width = 60; // ширина лабиринта
	const int height = 15; // высота лабиринта
	int maze[height][width] = {}; // заготовка для лабиринта в виде двумерного массива, заполненного нулями
	int two=0;//создал переменную для посчета кол-ва монет 





	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			maze[y][x] = rand() % 5; // 0 1 2 3

			// установка стен по бокам (делаем рамки)
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
				maze[y][x] = 1; // стенка слева

			// определение точки входа и выхода из лабиринта
			if (x == 0 && y == 2 || x == 1 && y == 2 || x == 2 && y == 2 ||
				x == width - 1 && y == height - 3)
				maze[y][x] = 0;

			// если текущий элемент 2д-массива - это враг,
			// то ниже код, который уменьшает их количество
			// условно, произойдёт жеребьёвка (или же подбрасывание монетки)

			if (maze[y][x] == 3)
			{
				int r = rand() % 10; // 0...9
				// если выпадает 0 - враг остаётся (10% случаев)
				if (r != 0) // если выпадает не 0 (а число от 1 до 9) - врага убираем (вероятность 90%)
				{
					maze[y][x] = 0; // убираем врага
				}
			}
			if (maze[y][x] == 4)
			{
				int a = rand() % 10; // 0...9
				// если выпадает 0 - аптечка остаётся (10% случаев)
				if (a != 0) // если выпадает не 0 (а число от 1 до 9) - врага убираем (вероятность 90%)
				{
					maze[y][x] = 0; // убираем аптечку 
				}
				
			}
			if (maze[y][x] == 2)
			{
				two++;//считаем кол-во монет на карте
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////
			if (maze[y][x] == 0)
			{
				SetConsoleTextAttribute(h, 0); // чёрные 
				cout << " "; // коридор
			}
			else if (maze[y][x] == 1)
			{
				SetConsoleTextAttribute(h, 3); // бирюзовые 
				cout << (char)178; // стена
				// cout << "#";
			}
			else if (maze[y][x] == 2)
			{
				SetConsoleTextAttribute(h, 14); // ярко-жёлтый 
				cout << "."; // монетка
			}
			else if (maze[y][x] == 3)
			{
				// cout << "*"; // враг
				SetConsoleTextAttribute(h, 12); // ярко-красный 
				cout << (char)1;
			}
			else if (maze[y][x] == 4)
			{
				
				SetConsoleTextAttribute(h, 9); // ярко-красный 
				cout << "+";//аптечка
			}
			else
			{
				cout << maze[y][x];
			}

		}
		cout << "\n";
	}

	// пример установки курсора в любые координаты консоли
	COORD position; // координаты ГГ
	position.X = 0;
	position.Y = 2;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, 13);
	// cout << "O";
	int coins = 0;
	int health = 100;
	int health2 = 100;
	int money = two;

	cout << (char)1;

	
	// начинаем интерактив (польщователь управляет смайликом с помощью клавиатуры)
	while (true)
	{
		int code = _getch(); // get character - получение кода нажатой клавиши
		if (code == 224) // если была нажата какая-то стрелка
		{
			code = _getch();
		}

		// после того, как клавиша стрелки была нажата, программа уже знает, куда побежит смайлик
		// можно стереть смайлик в его текущей позиции
		SetConsoleCursorPosition(h, position);
		cout << " ";

		if (code == 77 and maze[position.Y][position.X + 1] != 1) // right
		{
			position.X++; // изменение позиции ГГ вправо на 1 по иксу
		}
		else if (code == 75 and maze[position.Y][position.X - 1] != 1)
		{
			position.X--;
		}
		else if (code == 72 and maze[position.Y - 1][position.X] != 1)
		{
			position.Y--;
		}
		else if (code == 80 and maze[position.Y + 1][position.X] != 1)
		{
			position.Y++;
		}

		// ПРАКТИКА1: сделать перемещение вниз и вверх!
		// скинуть в телеграм только длва элс-ифа на перемещение вверх-вниз

		// показываем смайлик в новых координатах
		SetConsoleCursorPosition(h, position); // установка курсора в новые координаты
		SetConsoleTextAttribute(h, 13);
		cout << (char)1;


		///////////////////////////////////////////////////////////////////
		//проверка на выход из лаберинта 

		//////////////////////////////////////////////////////////////////
		//выводжу кол-монет
		COORD money_info;
		money_info.X = width + 1;
		money_info.Y = 1;

		SetConsoleCursorPosition(h, money_info); // установка курсора в новые координаты
		SetConsoleTextAttribute(h, 10);
		cout << "The number of coins in the gaim : " << money;


		if (position.X == width - 1 and position.Y == height - 3)
		{
			MessageBoxA(0, "You found your way out of the maze!!!!", "You win!!!", MB_OK);
			break;
		}
		////////////////////////////////////////////////////////////////////
		//ПРОВЕРКА НА ПОДБОР МОНЕТКИ
		if (maze[position.Y][position.X] == 2)
		{
			coins++;
			maze[position.Y][position.X] = 0;
			COORD coins_info;
			coins_info.X = width + 1;
			coins_info.Y = 2;

			SetConsoleCursorPosition(h, coins_info); // установка курсора в новые координаты
			SetConsoleTextAttribute(h, 14);
			cout << "Number of coins picked up: " << coins;

		}
		if (coins == two)//если мы собрали все монеты,то игра заканчивается выигрышом

		{
			MessageBoxA(0, "You have collected all the coins!!! ", "You win!!!",MB_OK);
			break;
		}



		////////////////////////////////////////////////////////


	

		if (maze[position.Y][position.X] == 3)
		{
			health -= 20;
		
			maze[position.Y][position.X] = 0;
			COORD health_info;
			health_info.X = width + 1;
			health_info.Y = 3;

			SetConsoleCursorPosition(h, health_info); // установка курсора в новые координаты
			SetConsoleTextAttribute(h, 13);


			cout << "Hit points: " << health;


		}


		if (maze[position.Y][position.X] == 4 and health < 100)
		{

			health += 20;

			maze[position.Y][position.X] = 0;
			COORD health_info;
			health_info.X = width + 1;
			health_info.Y = 3;

			SetConsoleCursorPosition(h, health_info); // установка курсора в новые координаты
			SetConsoleTextAttribute(h, 13);


			cout << "Hit points: " << health;
		}




		/////////////////////////////////////////////////////////////////////////////////////////


		if (health == 0)
		{

			MessageBoxA(0, "You have run out of health!!!!", "You are dead!!!!", MB_OK);
			break; 
	    }



		
		////////////////////////////////////////////////////////////////////////


	}
	system("cls");//очистка экрана
	main();
	Sleep(INFINITE);
}
