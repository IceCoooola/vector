#include"vector.h"

int main()
{
	int arr[4] = { 1,2,3,4 };
	IceCola::vector<int> v1;
	IceCola::vector<int> v2(arr,arr + 4);
	v2.resize(10, 2);
	IceCola::vector<int> v3 = v2;
	for (auto e : v2)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	for (auto e : v3)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	v1.reserve(15);
	std::cout << v1.capacity() << std::endl;
	v1.insert(v1.begin(), 6);
	v1.insert(v1.begin(), 5);
	v1.insert(v1.begin() + 1, 4);
	v1.insert(v1.begin(), 3);
	for (auto e : v1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	v1.erase(v1.begin() + 3);
	for (auto e : v1)
	{
		std::cout << e << " ";
	}
	std::cout << std::endl;
	return 0;
}
