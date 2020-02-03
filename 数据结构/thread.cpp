#include "stdafx.h"
#include "thread.h"
#include<thread>
#include<mutex>

thread::thread()
{
}


thread::~thread()
{
}
void SpinLock::lock(){
	while (!isFree.test_and_set()){
		std::this_thread::yield();
	}
}
void SpinLock::unlock(){
	isFree.clear();
}
bool SpinLock::try_lock(){
	return isFree.test_and_set();
}
void SpinLock2::lock(){
	auto tid=std::this_thread::get_id().hash();
	tidLock.lock();
	allTid.push_back(tid);
	tidLock.unlock();
	while (!((current==0||current==tid)&&isFree.test_and_set())){
		std::this_thread::yield();
	}
}
void SpinLock2::unlock(){
	std::lock_guard<SpinLock> lg(tidLock);
	isFree.clear();
	if (allTid.size()>0){
		current = allTid.front();
		allTid.pop_front();
	}
	else{
		current = 0;
	}
}
bool SpinLock2::try_lock(){
	if (current == 0 && isFree.test_and_set()){//获得锁成功
		return true;
	}
	else{//获得锁失败
		return false;
	}
}

