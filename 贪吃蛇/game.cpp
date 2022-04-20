/*
空白：0		蛇身：1		蛇头：2		果实：3		墙壁：4
*/
#include<iostream>
#include<iomanip>
#include<graphics.h>
#include"Snake.h"

#define num 30
#define TIME 128

using namespace std;

#pragma region Define

int space = (num - 3) * (num - 3);
int** board = nullptr;
bool EndGame = false;
bool creatfood = true;

IMAGE item(100, 20);							//画板
IMAGE screen(600, 600);							//显示屏

void Init();
int Check(Snake<int>);
int GetCmd();
void DoCmd(int, Snake<int>&);
void Print(Snake<int>);
void CreatFood();

#pragma endregion

int main()
{
	Init();
	Point<int> p1(1, 1);
	Point<int> p2(1, 2);
	Point<int> p3(1, 3);
	Snake<int> snake;
	snake.Add(p1);
	snake.Add(p2);
	snake.Add(p3);
	snake.SetDir(Right);
	int c = -1;
	while (c = GetCmd())
	{
		if (creatfood)
			CreatFood();
		Print(snake);
		DoCmd(c, snake);
		if (Check(snake) == 1 || Check(snake) == 4)
			break;
		else if (Check(snake) == 3)
		{
			snake.Eat();
			creatfood = true;
		}
		else
			snake.Move();
		Sleep(TIME);
	}

	//释放数组
	for (int i = 0; i < num; ++i)
		delete[] board[i];
	delete board;
	board = nullptr;
	cout << "游戏分数为：" << snake.GetLen() << endl;
	return 0;
}

#pragma region Functions

int Check(Snake<int> s)
{
	switch (s.GetDir())
	{
	case Up:
		if (board[s.GetBody()[0].GetX()][s.GetBody()[0].GetY() - 1] == 1)
			return 1;
		if (board[s.GetBody()[0].GetX()][s.GetBody()[0].GetY() - 1] == 3)
			return 3;
		if (board[s.GetBody()[0].GetX()][s.GetBody()[0].GetY() - 1] == 4)
			return 4;
		return 0;
	case Down:
		if (board[s.GetBody()[0].GetX()][s.GetBody()[0].GetY() + 1] == 1)
			return 1;
		if (board[s.GetBody()[0].GetX()][s.GetBody()[0].GetY() + 1] == 3)
			return 3;
		if (board[s.GetBody()[0].GetX()][s.GetBody()[0].GetY() + 1] == 4)
			return 4;
		return 0;
	case Left:
		if (board[s.GetBody()[0].GetX() - 1][s.GetBody()[0].GetY()] == 1)
			return 1;
		if (board[s.GetBody()[0].GetX() - 1][s.GetBody()[0].GetY()] == 3)
			return 3;
		if (board[s.GetBody()[0].GetX() - 1][s.GetBody()[0].GetY()] == 4)
			return 4;
		return 0;
	case Right:
		if (board[s.GetBody()[0].GetX() + 1][s.GetBody()[0].GetY()] == 1)
			return 1;
		if (board[s.GetBody()[0].GetX() + 1][s.GetBody()[0].GetY()] == 3)
			return 3;
		if (board[s.GetBody()[0].GetX() + 1][s.GetBody()[0].GetY()] == 4)
			return 4;
		return 0;
	}
	return 0;
}

int GetCmd()
{
	int c = -1;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)				//esc键
		c = 0;
	if (GetAsyncKeyState(VK_UP) & 0x8000)					//上方向键
		c = Up;
	if (GetAsyncKeyState('W') & 0x8000)						//W键
		c = Up;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)					//下方向键
		c = Down;
	if (GetAsyncKeyState('S') & 0x8000)						//S键
		c = Down;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)					//左方向键
		c = Left;
	if (GetAsyncKeyState('A') & 0x8000)						//A键
		c = Left;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)				//右方向键
		c = Right;
	if (GetAsyncKeyState('D') & 0x8000)						//D键
		c = Right;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)						//D键
		c = 5;
	return c;
}

void DoCmd(int cmd, Snake<int>& s)
{
	if (cmd == 0)
	{
		EndGame = true;
		return;
	}
	if (cmd == Up)
	{
		if (s.GetDir() == Left || s.GetDir() == Right)
		{
			s.SetDir(Up);
		}
	}
	if (cmd == Down)
	{
		if (s.GetDir() == Left || s.GetDir() == Right)
		{
			s.SetDir(Down);
		}
	}
	if (cmd == Left)
	{
		if (s.GetDir() == Up || s.GetDir() == Down)
		{
			s.SetDir(Left);
		}
	}
	if (cmd == Right)
	{
		if (s.GetDir() == Up || s.GetDir() == Down)
		{
			s.SetDir(Right);
		}
	}
	if (cmd == 5)
	{
		system("pause");
	}
}

void Print(Snake<int> s)
{
	//清空画板
	for (int i = 1; i < num - 1; ++i)
	{
		for (int j = 1; j < num - 1; ++j)
		{
			if (board[i][j] != 3)
				board[i][j] = 0;
		}
	}
	//绘制蛇身
	for (int i = 0; i < s.GetLen(); ++i)
	{
		board[s.GetBody()[i].GetX()][s.GetBody()[i].GetY()] = 1;
	}
	//绘制蛇头
	board[s.GetBody()[0].GetX()][s.GetBody()[0].GetY()] = 2;
	//同步到画板
	SetWorkingImage(&screen);
	int x = 0, y = 0;
	for (int j = 0; j < num; ++j)
	{
		for (int i = 0; i < num; ++i)
		{
			x = i * 20;
			y = j * 20;
			switch (board[i][j])
			{
			case 0:
				putimage(x, y, 20, 20, &item, 0, 0);
				break;
			case 1:
				putimage(x, y, 20, 20, &item, 20, 0);
				break;
			case 2:
				putimage(x, y, 20, 20, &item, 40, 0);
				break;
			case 3:
				putimage(x, y, 20, 20, &item, 60, 0);
				break;
			case 4:
				putimage(x, y, 20, 20, &item, 80, 0);
			}
		}
	}
	SetWorkingImage();
	putimage(0, 0, 600, 600, &screen, 0, 0);
}

void Init()
{
	srand(unsigned(time(NULL)));
	//画板初始化
	board = new int* [num];
	for (int i = 0; i < num; ++i)
	{
		board[i] = new int[num];
	}
	for (int i = 0; i < num; ++i)
	{
		for (int j = 0; j < num; ++j)
		{
			board[i][j] = 0;
		}
	}
	//绘制边界
	for (int i = 0; i < num; ++i)
	{
		board[0][i] = 4;
		board[num - 1][i] = 4;
		board[i][0] = 4;
		board[i][num - 1] = 4;
	}
	//图像初始化
	SetWorkingImage(&item);
	cleardevice();
	//空白
	setorigin(0, 0);
	setfillcolor(BLACK);
	setlinecolor(BLACK);
	solidrectangle(0, 0, 20, 20);
	//蛇身
	setorigin(20, 0);
	setfillcolor(GREEN);
	solidcircle(10, 10, 10);
	//蛇头
	setorigin(40, 0);
	setfillcolor(RED);
	solidcircle(10, 10, 10);
	//果实
	setorigin(60, 0);
	setfillcolor(YELLOW);
	solidcircle(10, 10, 8);
	//墙壁
	setorigin(80, 0);
	setfillcolor(BROWN);
	solidrectangle(1, 1, 19, 19);
	line(1, 5, 19, 5);
	line(1, 10, 19, 10);
	line(1, 15, 19, 15);
	line(10, 1, 10, 5);
	line(10, 10, 10, 15);
	line(5, 5, 5, 10);
	line(5, 15, 5, 20);
	line(15, 5, 15, 10);
	line(15, 15, 15, 20);
	rectangle(0, 0, 20, 20);

	setorigin(0, 0);
	initgraph(600, 600);
}

void CreatFood()
{
	int n = rand() % space;
	int count = 0;
	for (int j = 2; j < num - 2; ++j)
	{
		for (int i = 2; i < num - 2; ++i)
		{
			++count;
			if (count >= n && !board[i][j])
			{
				board[i][j] = 3;
				--space;
				creatfood = false;
				return;
			}
		}
	}
}
#pragma endregion
