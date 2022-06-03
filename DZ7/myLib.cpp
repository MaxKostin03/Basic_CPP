
#include<iostream>
#include "myLib.h"
using namespace std;
namespace MyLib
{
	bool __fastcall Task1InitArray(float* arr, int size, float n)
	{
		for (size_t i = 0; i < size; i++)
		{
			arr[i] = n + i;
		}
		return true;
	}

	void __fastcall Task1PrintArray(float* arr, int size)
	{
		for (size_t i = 0; i < size; i++)
		{
			cout << arr[i] << "  ";
		}
		cout << endl;
	}
	void __fastcall Task1NumberOfElements(float* arr, int size)
	{
		int pos = 0, neg = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (arr[i] < 0)
			{
				neg++;
			}
			else pos++;
		}
		cout << "Positive: " << pos << endl;
		cout << "Negative: " << neg << endl;
	}
	void __fastcall Task3PrintArray(int* arr, int size)
	{
		for (size_t i = 0; i < size; i++)
		{
			cout << arr[i] << "  ";
		}
		cout << endl;
	}
}


