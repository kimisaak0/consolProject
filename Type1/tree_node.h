#pragma once
#include "base_haeder.h"

template <typename T>
class ABT_array
{
public:
	int size;    //�迭�� �ִ� ũ��
	T* capacity; //�����͸� �����ϴ� �迭.
	int iLastIndex; //���� ���ִ� ������ Index.
	
	T tRet;      //����� �����͸� ��ȯ�ϱ� ���� ����.

	int OrderIndex; //ȣ��� �ε���

private:
	int   ParentIndex(int index); // ������ ����� �θ� ����� �ε����� ��ȯ
	int   LeftIndex(int index);   // ������ ����� ���� ����� �ε����� ��ȯ
	int   RightIndex(int index);  // ������ ����� ������ ����� �ε����� ��ȯ

	// �ε����� �޾� ���ȣ���� �ϸ� ��带 �����Ѵ�.
	bool     PreOrder(int index, T* tArray);
	bool     InOrder(int index, T* tArray);
	bool     PostOrder(int index, T* tArray);

public:
	bool AddNode(T data);
	bool DelNode();
	bool ChangeNode(int index, T data);

	T&   CheckNode(int index);

	int  getLastIndex();

	// Ʈ�� Ž�� �����
	//����� ���� �迭�� �μ��� �޴´�.
	void  LevelOrderTD(T* tArray);
	void  LevelOrderBU(T* tArray);
	void  PreInPost(T* tArray, orderSelect select); //select ���� ���� pre, in, post order�� �����Ѵ�.

public:
	ABT_array() {}
	ABT_array(int size);
};
