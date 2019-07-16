#pragma once
#include "WorldMap.h"

const int maxX = 5;
const int maxY = 10;

int map_area::now_code = 0;
map_area** map_area::area_list = nullptr;

#pragma region ������ �Ҹ���

map_area::map_area()
{
	map_area::area_list = new map_area*;
	map_area::area_list[now_code] = this;

	area_name = "unsetted";
	
	ABT_array<room_data*> _root(100);
	tree_root = _root;

	vector2 _size(50, 50);
	map_size = _size;

	width = map_size.x;	//�� ����ũ��
	height = map_size.y; //�� ����ũ��

	total_cell_num = map_size.size(); //���� �� ����

	map_create(map_size);
	
	road_list = nullptr;
}

map_area::map_area(string _name, vector2 _mapSize)
{
	area_name = _name;


	ABT_array<room_data*> _root(100);
	tree_root = _root;

	map_size = _mapSize;

	width = map_size.x;	//�� ����ũ��
	height = map_size.y; //�� ����ũ��

	total_cell_num = map_size.size(); //���� �� ����

	map_create(map_size);
	
	road_list = nullptr;
}

map_area::~map_area()
{
	//�ϴ� ������ ���ִ� �� �Ű澲�� �ʴ� �ɷ� ��
}

#pragma endregion

void map_area::area_connect(int _code, int _distant)
{
	//area����ü�� ä��.
	area_link area;
	area.distance = _distant;
	area.dest = map_area::area_list[_code];
	area.next = nullptr;
	
	//������ �̾��� area��� �߰��ϴ� �ڵ�
	while (road_list->next != nullptr) {
		road_list = road_list->next;
	}

	road_list = &area;
}

void map_area::map_drawing()
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			switch (area_map[i][j]) {
				case area_state::empty: cout << "��"; break;
				case area_state::wall: cout << "��"; break;
			}
		}
		cout << endl;
	}
}

vector2 map_area::map_create(vector2 size)
{
	//���� �õ� �缳��
	srand((unsigned int)time(NULL));

	//���� ũ�� ����
	area_map = new area_state*[width];
	for (int i = 0; i < width; i++) {
		area_map[i] = new area_state[height];
	}

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			area_map[i][j] = area_state::empty;
		}
	}

	//�� ���� ���� ������
	room_data room(vector2(0, 0), vector2(width, height));
	tree_root.AddNode(&room);
	
	//����Լ��� ������ ������ �Լ�
	map_division(room);

	vector2 retVector;

	//���� ������ ��� ����
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			if (area_map[i][j] == area_state::empty) {
				retVector.x = i;
				retVector.y = j;
			}
		}
	}

	return retVector;
}

void map_area::map_division(room_data _node)
{
	//�μ��� ���� room_data�� ���̻� ���� �� ���� �����̸� return�Ѵ�.
	if (_node.complete == true) {
		return;
	}

	//������ �� �����͸� ������ ����
	room_data room1;
	room_data room2;

	if (rand() % 1 == 0) {
		int randValue = rand() % (_node.size.x / 4);
		randValue = (rand() % 2 == 0) ? randValue : randValue * -1;

		//���� ���� ��ǥ
		int division = _node.size.x / 2 + randValue;

		//���� �����.
		for (int i = _node.startPoint.y; i < _node.endPoint.y; i++) {
			if (i == _node.size.y / 2) {
				continue; // �߰��� ���� ������ �ʰ� ���д�.
			}
			area_map[division][i] = area_state::wall;
		}

		room1.size = vector2(division-1, _node.size.y);
		room1.startPoint = _node.startPoint;
		room1.endPoint = room1.startPoint + room1.size;
		
		if (room1.size.x <= maxX || room1.size.y <= maxY) {
			room1.complete = true;
		}

		room2.size = vector2(_node.size.x - division-1, _node.size.y);
		room2.startPoint = vector2(division + 1, _node.startPoint.y);
		room2.endPoint = room2.startPoint + room2.size;

		if (room2.size.x <= maxX || room2.size.y <= maxY) {
			room2.complete = true;
		}

		tree_root.AddNode(&room2);
	}
	else {
		//int randValue = rand() % (_node.size.y / 4);
		//randValue = (rand() % 2 == 0) ? randValue : randValue * -1;

		int division = _node.size.y / 2;// +randValue;

		for (int i = _node.startPoint.x; i < _node.endPoint.x; i++) {
			if (i == _node.size.x / 2) {
				continue;
			}
			area_map[i][division] = area_state::wall;
		}
		
		room1.size = vector2(_node.size.x, division - 1);
		room1.startPoint = _node.startPoint;
		room1.endPoint = room1.startPoint + room1.size;

		if (room1.size.x <= maxX || room1.size.y <= maxY) {
			room1.complete = true;
		}

		room2.size = vector2(_node.size.x, _node.size.y - division - 1);
		room2.startPoint = vector2(division + 1, _node.startPoint.y);
		room2.endPoint = room2.startPoint + room2.size;

		if (room2.size.x <= maxX || room2.size.y <= maxY) {
			room2.complete = true;
		}
	}

	//�ϼ��� �� �����͸� ��������Ʈ���� �ִ´�.
	tree_root.AddNode(&room1);
	tree_root.AddNode(&room2);

	//���ȣ��
	map_division(room1);
	map_division(room2);

	for (int i = 0; i < tree_root.getLastIndex(); i++) {
		cout << i << ": " << ((tree_root.capacity[i]->complete) ? "true" : "false") << endl ;
	}
}
