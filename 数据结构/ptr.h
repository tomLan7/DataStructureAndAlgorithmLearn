#pragma once
class ptr
{
public:
	ptr();
	~ptr();
};
//ģ��ģ������ָ��
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

//ģ�¹���shareָ�� ���ü�����ָ��
template<class T>
class LSharePtr{
	//��Դ������
	template<class T> class ref{
	public:
		//����
		size_t timer = 0;
		//��Դָ��
		T* data=nullptr;
		//������1
		void timerAdd(){
			timer++;
		}
		//�ͷ�һ��,�������ͷ��˶�Ӧ���ڴ�(���һ������)������true�����򷵻�false
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
	//������ü�����С
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
	//��������
	LSharePtr(const LSharePtr<T>& lsp){
		operator=(lsp);
	}
	LSharePtr(LSharePtr<T>&& lsp){
		data=lsp->data;
		lsp->data = nullptr;
	}
	//��ֵ����
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

//ģ��weakָ�룬