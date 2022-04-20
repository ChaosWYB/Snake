#pragma once
#include<iostream>

using namespace std;

enum Direction { Up = 1, Down = 2, Left = 3, Right = 4 };

template<typename T>
class Point
{
	T m_x;
	T m_y;
public:
	Point();
	Point(T, T);
	void SetX(T);
	void SetY(T);
	T GetX()const;
	T GetY()const;
	Point<T>& operator=(const Point<T>&);
};

template<typename T>
class Snake
{
	Point<T>* body;
	int length;
	int direction;
public:
	Snake();
	Snake(int);
	Snake(int, int);
	~Snake();
	void SetLen(int&);
	void SetDir(const int&);
	int GetLen() const;
	int GetDir() const;
	Point<T>* GetBody() const;
	void Add(Point<T>);
	void Move();
	void Eat();
};

#pragma region Struct

template<typename T>
Point<T>::Point()
{
	m_x = 0;
	m_y = 0;
}

template<typename T>
Point<T>::Point(T x, T y)
{
	m_x = x;
	m_y = y;
}

template<typename T>
Snake<T>::Snake()
{
	body = new Point<T>[100];
	length = 0;
	direction = 0;
}

template<typename T>
Snake<T>::Snake(int len)
{
	body = new Point<T>[100];
	length = len;
	direction = 0;
}

template<typename T>
Snake<T>::Snake(int len, int dir)
{
	body = new Point<T>[100];
	length = len;
	direction = dir;
}

template<typename T>
Snake<T>::~Snake()
{
	if (!body)
		delete[] body;
}

#pragma endregion

#pragma region Function

template<typename T>
void Point<T>::SetX(T x)
{
	m_x = x;
}

template<typename T>
void Point<T>::SetY(T y)
{
	m_y = y;
}

template<typename T>
T Point<T>::GetX() const
{
	return m_x;
}

template<typename T>
T Point<T>::GetY() const
{
	return m_y;
}

template<typename T>
void Snake<T>::SetLen(int& len)
{
	length = len;
}

template<typename T>
void Snake<T>::SetDir(const int& dir)
{
	direction = dir;
}

template<typename T>
int Snake<T>::GetLen() const
{
	return length;
}

template<typename T>
int Snake<T>::GetDir() const
{
	return direction;
}

template<typename T>
Point<T>* Snake<T>::GetBody() const
{
	return body;
}

template<typename T>
void Snake<T>::Add(Point<T> p)
{
	body[length] = p;
	++length;
}

template<typename T>
void Snake<T>::Move()									//ÉßµÄÒÆ¶¯
{
	for (int i = length - 1; i > 0; --i)
	{
		body[i] = body[i - 1];
	}
	switch (direction)
	{
	case Up:
		body->SetY(body->GetY() - 1);
		break;
	case Down:
		body->SetY(body->GetY() + 1);
		break;
	case Left:
		body->SetX(body->GetX() - 1);
		break;
	case Right:
		body->SetX(body->GetX() + 1);
	}
}

template<typename T>
void Snake<T>::Eat()
{
	Add(body[length - 1]);
	for (int i = length - 2; i > 0; --i)
	{
		body[i] = body[i - 1];
	}
	switch (direction)
	{
	case Up:
		body->SetY(body->GetY() - 1);
		break;
	case Down:
		body->SetY(body->GetY() + 1);
		break;
	case Left:
		body->SetX(body->GetX() - 1);
		break;
	case Right:
		body->SetX(body->GetX() + 1);
	}
}

#pragma endregion

#pragma region Operator

template<typename T>
Point<T>& Point<T>::operator=(const Point<T>& p)
{
	m_x = p.GetX();
	m_y = p.GetY();
	return *this;
}

#pragma endregion