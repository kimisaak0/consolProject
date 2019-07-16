#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>

using namespace std;

enum Behavior_state
{
	idle,
	search,
	trace,
	attack,
	hitted,
	Behavior_state_end,
};

struct vector2
{
	int x; int y;

	vector2()
	{
		x = 0;
		y = 0;
	}

	vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	int size()
	{
		return x * y;
	}

	vector2 operator+ (vector2 _data) {
		vector2 ret;
		ret.x = x + _data.x;
		ret.y = y + _data.y;

		return ret;
	}
};


#pragma region enum and struct
class map_area;

//맵 공간마다 갖고 있어야 하는 상태
enum area_state
{
	empty = 0,
	wall,
	door,

	area_state_end,
};

//현재 area node에서 이어질 수 있는 다른 area node들을 list로 갖는다.
struct area_link
{
	map_area* dest;
	int distance;
	area_link* next;

	area_link()
	{
		next = nullptr;
	}
};

//area 맵 생성을 위한 데이터
struct room_data
{
	vector2 startPoint;
	vector2 size;
	vector2 endPoint;

	bool complete;

	room_data(vector2 _point, vector2 _size)
	{
		startPoint = _point;
		size = _size;

		endPoint = startPoint + size;

		complete = false;
	}

	room_data()
	{
		startPoint = vector2(0, 0);
		size = vector2(0, 0);

		endPoint = startPoint + size;

		complete = false;
	}
};

#pragma endregion


enum orderSelect {
	pre,
	In,
	Post,
};