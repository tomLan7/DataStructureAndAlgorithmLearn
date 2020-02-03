#pragma once
#include<vector>
#include<list>
class ģ��
{
public:
	ģ��();
	~ģ��();
};
#define CONTAINING_RECORD(address,type,field) \
((type*)((PCHAR)(address)-(ULONG_PTR)(&((type*)0)->field)))
//������
//�����Ӧģ�壬�ȿ��Թ������Ӧ��ĵ�������Ҳ��ģ�幹���������һ�ι���ʱ���á�һ���಻ͬ�Ĳ�������Ҳֻ���һ�λṹ��ɹ������������Ա�֤һ����ֻ����һ�Ρ�
template<class T> class Singleton{
public:
	static volatile T* obj;
	template <class ... Types> static volatile T* getInstance(Types ... args){
		if (obj == nullptr){
			obj = new T(args...);
		}
		return obj;
	}
	static void distory(){
		delete obj;
		obj = nullptr;
	}
};

template<class T> volatile T* Singleton<T>::obj(nullptr);

//slab�ڴ����
/*
	��ǰ���⣬���ʹ��c++ stl list�Ļ����������ŵĴ�slabָ������λ��slabs_fullһ��������е�λ�����ı�slab��ָ�롣
	��������������slab �ڴ�ؾͽ�����
*/
template<class T>
class cache{
	class slab{
		public:
			cache* father=nullptr;
		class node{
			//�Ƿ�ʹ�ã����ʹ�þ�Ϊtrue
		public:
			T data;
			slab* father;
		};
		//ÿ�δ�ͷȡ��������ͷŵģ����ڸ�����ͷ
		std::list<node*> freeList;

		//��һ��ʹ�õ�ʱ�򣬻��ȱ���һ���ڴ�أ���ʱһ����ûʹ�á�Ȼ���ͷŵ�ʱ��Ϳ��Ե�����ָ�������ճ��С�
		size_t firstIndex=0;
		//��¼���е�����
		size_t freeNumb;
		size_t maxSize;
		//ʹ��void*�洢�ڴ棬��ֹ����vector�зŶ��󲻿ɱ���Ҫ��������޲ι����������������û���޲ι��캯��Ҳ���ԣ�
		void* dataArray;
		//��ʼ��һ������
		slab(size_t size = 16) :
			freeNumb(size),
			maxSize(size),
			dataArray(malloc(size*sizeof(T))){
			
		}
		//���һ��,���ò��������빹�캯��
		template<class ...args> T* getRef(){
			--freeNumb;
			//û�нڵ�
			if (firstIndex<maxSize){
				return new (&static_cast<node*>(dataArray+sizeof(T)*firstIndex++)->data) T (args...);
			}//˵���Ѿ�������һȦ�ˣ���������϶��л�
			else{
				node* p = freeList.front();
				freeList.pop_front();
				return new (&(p.data)) T(args...);
			}
		}
		//�ͷ��ڴ�
		static void freeRef(T* target){
			++freeNumb;
			//�����n�ĵ�ַ
			auto n=CONTAINING_RECORD(target,node,data);
			n->father->freeList.push_front(n);
		}
	};
	//����һ���µĿյ�slab
	void createSlab(size_t size=16){
		slabs_empty.push_back(new slab);
	}
public:
	//��ȫ�����slab
	std::list<slab*> slabs_full;
	//���ַ����slab
	std::list<slab*> slabs_partial;
	//��slab
	std::list<slab*> slabs_empty;
	//���Ի��һ���ڴ���еĶ��󣬻��ȴӲ��ַ�����Ѱ�ң�û���ٴӿ���Ѱ��
	T* allocMem(){
		
	}
	//�Ż�һ���ڴ�
	void delMem(T* target){
		slab::freeRef(target);
	}
};