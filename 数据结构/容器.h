#pragma once
class ����
{
public:
	����();
	~����();
};

//����������ͨ��ָ������λ������
template<class T> class Llist{
	//�ڲ��洢��ʽ
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
	//Ĭ�ϲ���ĳ���ڵ�֮ǰ����������ָ�룬���ŵ��������һ���ڵ�
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