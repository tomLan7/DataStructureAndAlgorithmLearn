#pragma once
#include<vector>
#include<list>
class 模板
{
public:
	模板();
	~模板();
};
#define CONTAINING_RECORD(address,type,field) \
((type*)((PCHAR)(address)-(ULONG_PTR)(&((type*)0)->field)))
//单例器
//传入对应模板，既可以构造出对应类的单例对象。也有模板构造参数，第一次构造时有用。一个类不同的参数构造也只会第一次会构造成功。单例器可以保证一个类只构造一次。
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

//slab内存分配
/*
	当前问题，如果使用c++ stl list的话，不能优雅的从slab指针来定位到slabs_full一类的数组中的位置来改变slab的指针。
	解决这个问题整个slab 内存池就结束了
*/
template<class T>
class cache{
	class slab{
		public:
			cache* father=nullptr;
		class node{
			//是否使用，如果使用就为true
		public:
			T data;
			slab* father;
		};
		//每次从头取，如果有释放的，放在该链表头
		std::list<node*> freeList;

		//第一次使用的时候，会先遍历一遍内存池，此时一定都没使用。然后释放的时候就可以单纯将指针放入回收池中。
		size_t firstIndex=0;
		//记录空闲的数量
		size_t freeNumb;
		size_t maxSize;
		//使用void*存储内存，防止出现vector中放对象不可避免要求对象有无参构造的需求。这样对象没有无参构造函数也可以！
		void* dataArray;
		//初始化一定数量
		slab(size_t size = 16) :
			freeNumb(size),
			maxSize(size),
			dataArray(malloc(size*sizeof(T))){
			
		}
		//获得一个,并用参数包传入构造函数
		template<class ...args> T* getRef(){
			--freeNumb;
			//没有节点
			if (firstIndex<maxSize){
				return new (&static_cast<node*>(dataArray+sizeof(T)*firstIndex++)->data) T (args...);
			}//说明已经遍历完一圈了，空闲链表肯定有货
			else{
				node* p = freeList.front();
				freeList.pop_front();
				return new (&(p.data)) T(args...);
			}
		}
		//释放内存
		static void freeRef(T* target){
			++freeNumb;
			//获得了n的地址
			auto n=CONTAINING_RECORD(target,node,data);
			n->father->freeList.push_front(n);
		}
	};
	//创建一个新的空的slab
	void createSlab(size_t size=16){
		slabs_empty.push_back(new slab);
	}
public:
	//完全分配的slab
	std::list<slab*> slabs_full;
	//部分分配的slab
	std::list<slab*> slabs_partial;
	//空slab
	std::list<slab*> slabs_empty;
	//尝试获得一个内存池中的对象，会先从部分分配中寻找，没有再从空中寻找
	T* allocMem(){
		
	}
	//放回一个内存
	void delMem(T* target){
		slab::freeRef(target);
	}
};