#pragma once
#include "tree_node.h"
#include "tree_node.cpp"
//#include "base_haeder.h"


class map_area
{
public:
	static int now_code;

	//��� ���� �����ϰ� �ִ� �迭
	static map_area** area_list;

public:
	//area�� ���� ��ȣ
	const int area_num = now_code++;

	string area_name;

	//state�� 2���� �迭�� ���������� �Ѵ�.
	area_state** area_map;

	vector2 map_size; 
	int width;	//�� ����ũ��
	int height; //�� ����ũ��
	
	int total_cell_num; ////���� �� ����

private:
	//�� ���ҿ� Ʈ���� root
	ABT_array<room_data*> tree_root;

	//���� area�� ����� area���� ���
	area_link* road_list;

private:
	//�� ������ �����ϱ�
	vector2 map_create(vector2 _size);
	void map_division(room_data _node);

public:
	//area ���� �߰��ϱ�
	void area_connect(int _code, int _distant);

	//�� �׸���
	void map_drawing();

public:
	map_area();
	map_area(string _name, vector2 _mapSize);

	~map_area();
};

