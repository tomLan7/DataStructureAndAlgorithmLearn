#pragma once
//�Զ����ݵ�
#include"stdafx.h"
template<class T>
class ����
{
	//����
	size_t length=0;
	size_t capacity=0;
	T* data=0;
public:
	size_t getLenth(){
		return length;
	}
	size_t getCapacity(){
		return capacity;
	}
	void push_back(T&& t){
		if (length == capacity){
			std::realloc(data,capacity*2+10);
		}
		data[length++]=t;
	}
	T& operator[](int index){
		return data[index];
	};
	����(){
	}
	~����(){
	}
};

