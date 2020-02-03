#pragma once
#include<thread>
#include<list>
#include <atomic>    
class thread
{
public:
	thread();
	~thread();
};
class LLock_base{
public:
	virtual void lock()=0;
	virtual void unlock() = 0;
	virtual bool try_lock() = 0;
};
//���㻥���ǰ�������������޵ȴ�
class SpinLock:public LLock_base{
protected:
	//������,����Ϊtrue��ռ��Ϊfalse
	std::atomic_flag isFree;
public:
	virtual void lock();
	virtual void unlock();
	virtual bool try_lock();
};
//���㻥��ǰ�����޵ȴ�
class SpinLock2 :public SpinLock{
	std::list<size_t> allTid;
	SpinLock tidLock;
	//��ǰ��
	size_t current=0;
public:
	virtual void lock();
	virtual void unlock();
	virtual bool try_lock();
};