#include "stdafx.h"
#include "递归.h"


递归::递归()
{
}


递归::~递归()
{
}
#include<iostream>
using namespace std;
//递归解法
int fun(int i){
	if (i == 1||i==2){
		return 1;
	}
	return fun(i - 1) + fun(i - 2);
}
//带备忘录的递归
int fun1(int level){
	static int *buff=0;
	bool flag = false;
	if (buff == 0){
		buff = new int[level];
		memset(buff,0,sizeof(int)*level);
		flag = true;
	}
	if (buff[level-1] != 0){
		return buff[level - 1];
	}
	if (level == 1 || level == 2){
		buff[level - 1] = 1;
		if (flag){
			delete buff;
			buff = 0;
		}
		return 1;
	}
	buff[level-1]=fun(level - 1) + fun(level - 2);
	int result=buff[level - 1];
	if (flag){
		delete buff;
		buff = 0;
	}
	return result;
}
//动态规划解法
int fun2(int level){
	int* buff = new int[level];
	buff[0] = 1;
	buff[1] = 1;
	for (int i = 2; i < level;i++){
		buff[i] = buff[i - 1] + buff[i - 2];
	}
	int result = buff[level - 1];
	delete buff;
	return result;
}
//递推解法
int fun3(int level){
	int one=1,after=1;
	for (int i = 2; i < level;i++){
		after = one + after;
		one = after - one;
	}
	return after;
}
