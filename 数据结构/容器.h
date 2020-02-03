#pragma once
class 容器
{
public:
	容器();
	~容器();
};

//这个链表可以通过指针来定位迭代器
template<class T> class Llist{
	//内部存储方式
	class node{
		T data;
		node* pre=nullptr;
		node* next = nullptr;

		node() = delete;
		node(const node&) = delete;
		node(const T& p){
			data = p;
		}
	};
	node* head = nullptr;
	node* tail = nullptr;
	void del_node(node* p){
		if (p == head){
			head = p->next;
		}
		if (p == tail){
			tail = p->pre;
		}
		if (p->pre){
			p->pre->next = p->next;
		}
		if (p->next){
			p->next->pre = p->pre;
		}
		delete p;
	}
	//默认插在某个节点之前，如果传入空指针，则会放到链表最后一个节点
	void insert_node(node* index,node* p){
		if (head == nullptr){
			head = p;
			tail = p;
		}
		else{
			p->next = index;
			p->pre = index ? index->pre:nullptr;
			if (index){
				index->pre = p;
			}
			if (index == head){
				head = p;
			}
			if (index == nullptr){
				tail = p;
			}
		}
	}
	class iterator{
		node* target=nullptr;
		T& operator*();
		iterator& operator++();
		iterator operator++(int);
	}
public:
	
};