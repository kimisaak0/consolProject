#pragma once
#include "base_haeder.h"


class Character
{
protected:
	int HP;
	int MP;
	
	int Health;
	int Magic;
	int Attack;
	int Defence;
	int Speed;

	Behavior_state state;



public:



#pragma region ����/�Ҹ���
public:
	Character();
	virtual ~Character();
#pragma endregion
};

