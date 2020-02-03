
#include<iostream>
#include<memory>
#include<vector>
#include<map>
using namespace std;
//auto_ptr
/*
���췽��
����     
operator=   ת�ƿ���Ȩ
get         ��ñ������ָ��
operator*  ���ʱ��������
operator-> ����
reset      ���ٶ���(�ƶ��¶�������֮ǰ��)
release    �ͷŶ���
*/
template<class T>
class LAuto_ptr{
	//�ڲ��洢ָ��ռ��һ����Ա����
	T* obj=nullptr;
public:
	LAuto_ptr(const LAuto_ptr&) = delete;
	LAuto_ptr() = default;
	LAuto_ptr(T* p){
		obj = p;
	}
	~LAuto_ptr(){
		delete obj;
	}
	void operator=(LAuto_ptr<T>& other){
		obj = other.obj;
		other.obj=nullptr;
	}
	T* get(){
		return obj;
	}
	T& operator*(){
		return *obj;
	}
	T& operator->(){
		return *obj;
	}
	void reset(T* ptr=nullptr){
		obj = ptr;
	}
	void release(){
		delete obj;
		obj = nullptr;
	}
};
class A{
public:
	int a;
	~A(){
		cout << "�����˶���" << endl;
	}
};
//0��������������͵Ĳ���
template<class T> 
void run(T g){
	cout << "������ģ��" << endl;
	cout << g << endl;
}
//sizeof...
template<class T,class... args> 
void run(T g, args... a){
	if (sizeof...(a) > 3){
		cout << "���������������Ҳ����ˣ�" << endl;
		return;
	}
	cout << "�����ģ��,��������" << sizeof... (a)<< endl;
	cout << g << endl;
	run(a...);
}
//void run(int g,int a1,int a2,const char* a3,const char* a4){
//	cout << g << endl;
//	run(a1,a2,a3,a4);
//}
//void run(int g, int a1, const char* a2, const char* a3){
//	cout << g << endl;
//	run(a1, a2, a3);
//}
//void run(int g,const char* a1, const char* a2){
//	cout << g << endl;
//	run(a1, a2);
//}
//void run(const char* g, const char* a1){
//	cout << g << endl;
//	run(a1);
//}

int main(){
	LAuto_ptr<A> ptr(new A);
	LAuto_ptr<A> ptr2;
	ptr2 = ptr;
	ptr.release();
	run(1,2,3,"255","12512");
}

//Ĭ�����ɵ��޲ι��죬���Զ����ó�Ա����� �޲ι���
//default  ��ʽ ָ������Ĭ�ϵĹ���

//��ֵ  �е�ַ�ı���
//��ֵ  �޷���õ�ַ��û����ȷ��ַ�ı���

//��ֵ���� &
//���ú�ָ�뱾����һ���£� ָ����Ҫָ��һ����ַ�����ñ��� Ҳ��Ҫָ��һ����ַ

//��ֵ���� &&
//ָ����ʱ���󣬳���