#pragma once
class ptr
{
public:
	ptr();
	~ptr();
};
//模仿模板智能指针
template<class T>
class LAutoPtr{
	T* obj=nullptr;
public:
	LAutoPtr(T* target):obj(target){
	}
	LAutoPtr(LAutoPtr & data){
		operator=(data);
		data.obj = nullptr;
	}
	~LAutoPtr(){
		reset(nullptr);
	}
	void reset(T* otherTarget = nullptr){
		delete obj;
		obj = otherTarget;
	}
	T release(){
		return obj;
	}
	LAutoPtr<T>& operator=(LAutoPtr<T>& p){
		reset();
		obj = p.obj;
		p.obj = nullptr;
		return *this;
	}
};

//模仿共享share指针 引用计数的指针
template<class T>
class LSharePtr{
	//资源计数，
	template<class T> class ref{
	public:
		//计数
		size_t timer = 0;
		//资源指针
		T* data=nullptr;
		//计数加1
		void timerAdd(){
			timer++;
		}
		//释放一个,如果真的释放了对应的内存(最后一个计数)，返回true，否则返回false
		bool timerDel(){
			if (--timer == 0){
				delete this;
				return true;
			}
			return false;
		}
		~ref(){
			delete data;
		}
		ref(T* target):data(target){
			timerAdd();
		}
	};
	ref<T>* data = nullptr;
public:
	//获得引用计数大小
	size_t use_count(){
		return data->timer;
	}
	void retain(){
		timer++;
	}
	LSharePtr(){
		
	}
	LSharePtr(T* obj){
		data = new ref<T>(obj);
	}
	//拷贝构造
	LSharePtr(const LSharePtr<T>& lsp){
		operator=(lsp);
	}
	LSharePtr(LSharePtr<T>&& lsp){
		data=lsp->data;
		lsp->data = nullptr;
	}
	//赋值构造
	LSharePtr<T>& operator=(const LSharePtr<T>& target){
		if (data&&data->timerDel()){
			data = 0;
		}
		data = target.data;
		data->timerAdd();
		return *this;
	}
	~LSharePtr(){
		data->timerDel();
	}
	T* get(){
		return data->data;
	}
};
template<class T,class ...args> LSharePtr<T> Lmake_shared(args... a){
	return LSharePtr<T>(new T(a...));
}

//模仿weak指针，