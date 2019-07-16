#include "tree_node.h"

#pragma region //생성,소멸자

template <typename T>
ABT_array<T>::ABT_array(int _size)
{
	size = _size;
	capacity = new T[size];
	iLastIndex = 0;
	OrderIndex = 0;
}

#pragma endregion

#pragma region //private Function
// 지정한 노드의 부모 노드의 인덱스를 반환, -1은 없음을 의미.
template <typename T>
int   ABT_array<T>::ParentIndex(int index)
{
	if (index == 0) {
		return -1;
	}

	return (index - 1) / 2;
}

// 지정한 노드의 왼쪽 노드의 인덱스를 반환, -1은 없음을 의미.
template <typename T>
int   ABT_array<T>::LeftIndex(int index)
{
	int iRet = index * 2 + 1;

	if (iRet >= iLastIndex) {
		return -1;
	}

	return iRet;
}

// 지정한 노드의 오른쪽 노드의 인덱스를 반환, -1은 없음을 의미.
template <typename T>
int   ABT_array<T>::RightIndex(int index)
{
	int iRet = index * 2 + 2;

	if (iRet >= iLastIndex) {
		return -1;
	}

	return iRet;
}

// 인덱스를 받아 재귀호출을 하며 노드를 저장한다.
template <typename T>
bool ABT_array<T>::PreOrder(int index, T* tArray)
{
	if (index != -1) {
		tArray[OrderIndex++] = capacity[index];
		PreOrder(LeftIndex(index), tArray);
		PreOrder(RightIndex(index), tArray);
		return true;
	}

	return false;
}

template <typename T>
bool ABT_array<T>::InOrder(int index, T* tArray)
{
	if (index != -1) {
		InOrder(LeftIndex(index), tArray);
		tArray[OrderIndex++] = capacity[index];
		InOrder(RightIndex(index), tArray);
	}

	return false;
}

template <typename T>
bool ABT_array<T>::PostOrder(int index, T* tArray)
{
	if (index != -1) {
		PostOrder(LeftIndex(index), tArray);
		PostOrder(RightIndex(index), tArray);
		tArray[OrderIndex++] = capacity[index];
	}

	return false;
}

#pragma endregion


#pragma region //Public Function

template <typename T>
bool ABT_array<T>::AddNode(T data)
{
	if (iLastIndex == size) {
		return false;
	}

	capacity[iLastIndex++] = data;

	return true;
}

template <typename T>
bool ABT_array<T>::DelNode()
{
	if (iLastIndex == 0) {
		return false;
	}

	iLastIndex--;

	return true;
}

template <typename T>
bool ABT_array<T>::ChangeNode(int index, T data)
{
	if (index < 0 && index >= iLastIndex) {
		return false;
	}

	capacity[index] = data;

	return true;
}



template <typename T>
T& ABT_array<T>::CheckNode(int index)
{
	if (index >= 0 && index < iLastIndex) {
		tRet = capacity[index];
		return tRet;
	}
	else {
		return nullptr;
	}
}

template <typename T>
int  ABT_array<T>::getLastIndex()
{
	return iLastIndex;
}



// 결과를 담을 배열을 인수로 받는다.
template <typename T>
void ABT_array<T>::LevelOrderTD(T* tArray)
{
	for (int i = 0; i < iLastIndex; i++) {
		tArray[i] = capacity[i];
	}
}

template <typename T>
void ABT_array<T>::LevelOrderBU(T* tArray)
{
	int depth = 0;
	int depthCheck = 0;

	while (iLastIndex - 1 > depthCheck) {
		depth++;
		depthCheck += pow(2, depth);
	}

	int tIndex = 0;
	for (int i = depth; i >= 0; i--) {
		depthCheck -= pow(2, i);
		for (int k = 1; k <= pow(2, i); k++) {
			tArray[tIndex] = capacity[depthCheck + k];
			tIndex++;
		}
	}

}

//select 값에 따라 pre, in, post order를 수행한다.
template <typename T>
void  ABT_array<T>::PreInPost(T* tArray, orderSelect select)
{
	OrderIndex = 0;
	switch (select) {
		case (orderSelect::pre) : { PreOrder(0, tArray); } break;

		case (orderSelect::in): { InOrder(0, tArray); } break;

		case (orderSelect::post): { PostOrder(0, tArray); } break;
	}
}

#pragma endregion
