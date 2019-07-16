#pragma once
#include "tree_node.h"
#include "tree_node.cpp"
//#include "base_haeder.h"


class map_area
{
public:
	static int now_code;

	//모든 맵을 저장하고 있는 배열
	static map_area** area_list;

public:
	//area의 고유 번호
	const int area_num = now_code++;

	string area_name;

	//state의 2차원 배열을 지역맵으로 한다.
	area_state** area_map;

	vector2 map_size; 
	int width;	//맵 가로크기
	int height; //맵 세로크기
	
	int total_cell_num; ////맵의 총 셀수

private:
	//맵 분할용 트리의 root
	ABT_array<room_data*> tree_root;

	//현재 area와 연결된 area들의 목록
	area_link* road_list;

private:
	//맵 데이터 생성하기
	vector2 map_create(vector2 _size);
	void map_division(room_data _node);

public:
	//area 연결 추가하기
	void area_connect(int _code, int _distant);

	//맵 그리기
	void map_drawing();

public:
	map_area();
	map_area(string _name, vector2 _mapSize);

	~map_area();
};

