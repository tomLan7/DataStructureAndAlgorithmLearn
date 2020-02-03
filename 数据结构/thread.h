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
//满足互斥和前进，不满足有限等待
class SpinLock:public LLock_base{
protected:
	//自旋锁,空闲为true，占有为false
	std::atomic_flag isFree;
public:
	virtual void lock();
	virtual void unlock();
	virtual bool try_lock();
};
//满足互斥前进有限等待
class SpinLock2 :public SpinLock{
	std::list<size_t> allTid;
	SpinLock tidLock;
	//当前的
	size_t current=0;
public:
	virtual void lock();
	virtual void unlock();
	virtual bool try_lock();
};