#pragma once
#include "base_haeder.h"

template <typename T>
class ABT_array
{
public:
	int size;    //배열의 최대 크기
	T* capacity; //데이터를 저장하는 배열.
	int iLastIndex; //값이 들어가있는 마지막 Index.
	
	T tRet;      //저장된 데이터를 반환하기 위한 변수.

	int OrderIndex; //호출용 인덱스

private:
	int   ParentIndex(int index); // 지정한 노드의 부모 노드의 인덱스를 반환
	int   LeftIndex(int index);   // 지정한 노드의 왼쪽 노드의 인덱스를 반환
	int   RightIndex(int index);  // 지정한 노드의 오른쪽 노드의 인덱스를 반환

	// 인덱스를 받아 재귀호출을 하며 노드를 저장한다.
	bool     PreOrder(int index, T* tArray);
	bool     InOrder(int index, T* tArray);
	bool     PostOrder(int index, T* tArray);

public:
	bool AddNode(T data);
	bool DelNode();
	bool ChangeNode(int index, T data);

	T&   CheckNode(int index);

	int  getLastIndex();

	// 트리 탐색 방법들
	//결과를 담을 배열을 인수로 받는다.
	void  LevelOrderTD(T* tArray);
	void  LevelOrderBU(T* tArray);
	void  PreInPost(T* tArray, orderSelect select); //select 값에 따라 pre, in, post order를 수행한다.

public:
	ABT_array() {}
	ABT_array(int size);
};
