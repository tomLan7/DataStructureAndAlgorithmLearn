
#include"stdafx.h"
template <typename T>
inline T const& max(T const & a, T const & b)
{
	std::cout << "all" << std::endl;
	return a < b ? b : a;
}

inline int const& max(int const & a, int const & b)
{
	std::cout << "int" << std::endl;
	return a < b ? b : a;
}

int main()
{
	int a = 7;
	int b = 42;
	int maxInt = ::max(a, b);
	std::cout << maxInt << std::endl; // ���÷�ģ��
	std::cout << max<>(a, b) << std::endl; // ����ģ��
	std::cout << max<int>(a, b) << std::endl; // ����ģ��
	std::cout << max(1.0, 2.0) << std::endl; // ���÷�ģ��
	std::cout << max("aaa", "bbb") << std::endl; // ����ģ��
	std::cout << max('42', 1) << std::endl; // ���÷�ģ��
}