#include "stdafx.h"
#include"数据结构\模板.h"
#include"数据结构\ptr.h"
#include<iostream>
#include<tuple>
#include<algorithm>

#include<iomanip>
#include<array>
#include<vector>

#include"stdafx.h"

using namespace std;
class A{
public:
	~A(){
		cout << "析构了" << endl;
	}
};
template<class T,class... args> 
void p(T a,args... A){
	cout << a << endl;
	p(A...);
}

template <typename T>
void debug(T argv)
{
	std::cout << argv << std::endl;
}
template <typename T1, typename... T2>
void debug(T1 argv1, T2... argvs)
{
	std::cout << sizeof...(T2) << argv1 << std::endl;
	debug(argvs...);
}
int main()
{
	debug(1,2,3,4,5);
	auto a = Lmake_shared<A>();
	{
		auto b = a;
		cout << a.use_count() << endl;
		auto c = a;
		cout << a.use_count() << endl;
	}
	
	
	cout << a.use_count() << endl;
}