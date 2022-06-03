
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//=====================================Task1========================================

void __fastcall Task1PrintArray(int* arr, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;
}

bool Task1FillArray(int* arr, int size) 
{
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = pow(2, i);
	}
	return true;
}

void inline Task1()
{
	int* ptrArray;
	int Task1ArrSize;
	cout << "Enter size of your array: ";
	cin >> Task1ArrSize;

	if (Task1ArrSize > 0)
	{
		ptrArray = new (nothrow) int[Task1ArrSize];
		if (ptrArray != nullptr)
		{
			Task1FillArray(ptrArray, Task1ArrSize);
			Task1PrintArray(ptrArray, Task1ArrSize);

			delete[] ptrArray;
			ptrArray = nullptr;
		}
		else
		{
			cout << "Error! Can not allocate memory!";
		}
	}
	cin.clear();
	cin.ignore(32767, '\n');
}

//=====================================Task2========================================

void __fastcall Task2AllocateMemory(int** arr, int size)
{
	for (size_t i = 0; i < size; i++) 
	{
		arr[i] = new int[size];
	}
}

bool Task2InitRandArray(int** arr, int size)
{
	for (size_t i = 0; i < size; i++)
		for (size_t j = 0; j < size; j++)
		{
			arr[i][j] = rand() % 100 - 50;
		}
		return true;
}

void __fastcall Task2PrintArray(int** arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << "   " << arr[i][j] << "   ";
		}
		cout << endl;
	}
}

void __fastcall Task2FreeingMemory(int** arr, int size)
{
	for (size_t i = 0; i < size; i++) 
	{
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

void inline Task2()
{
	int** ptrArray2;
	const size_t Task2ArrSize = 4;
	ptrArray2 = new int* [Task2ArrSize];
	Task2AllocateMemory(ptrArray2, Task2ArrSize);
	Task2InitRandArray(ptrArray2, Task2ArrSize);
	Task2PrintArray(ptrArray2, Task2ArrSize);
	Task2FreeingMemory(ptrArray2, Task2ArrSize);
}

//=====================================Task3========================================

void inline Task3()
{
	cout << "Enter the name of the first file: ";
	string Name1;
	getline(cin, Name1);
	cout << "Enter the name of the second file: ";
	string Name2;
	getline(cin, Name2);

	const string Text1 = "All C++ programs must have a main function. If you try to compile a C++ program without a main function, the compiler raises an error.";
	const string Text2 = "The main function is where your source code begins execution, but before a program enters the main function, all static class members without explicit initializers are set to zero.";

	ofstream fout1, fout2;

	fout1.open(Name1);
	fout2.open(Name2);

	if (fout1.is_open())
	{
		if (fout2.is_open())
		{
			fout1 << Text1 << endl;
			fout2 << Text2 << endl;
		}
	}
	fout1.close();
	fout2.close();
}

//=====================================Task4========================================

void Task4FileMerged(string Name1, string Name2, string Unite)
{
	string buf;
	ofstream fout; 
	fout.open(Unite);
	ifstream fin1(Name1), fin2(Name2); 
	if (fin1.is_open())// 
	{
		if (fin2.is_open())
		{
			if (fout.is_open())
			{
				while (!fin1.eof())
				{
					getline(fin1, buf);
					fout << buf;
				}
				while (!fin2.eof())
				{
					getline(fin2, buf);
					fout << " " << buf;
					
				}
			}
		}
	}
		fin1.close();
		fin2.close();
		fout.close();
}

void inline Task4()
{
	cout << "Enter the name of the first file to merge: ";
	string NameForMerge1;
	getline(cin, NameForMerge1);

	cout << "Enter the name of the second file to merge: ";
	string NameForMerge2;
	getline(cin, NameForMerge2);

	cout << "Enter the name of the merged file: ";
	string MergeFile;
	getline(cin, MergeFile);

	Task4FileMerged(NameForMerge1, NameForMerge2, MergeFile);
}

//=====================================Task5========================================

void inline Task5()
{
	cout << "Enter the name of the file: ";
	string FileForSearch;
	getline(cin, FileForSearch);

	cout << "Enter a search word: ";
	string Word;
	getline(cin, Word);

	int k = 0;
	string buf;
	ifstream finTask5(FileForSearch);
	if (finTask5.is_open())
	{
		while (!finTask5.eof())
		{
			getline(finTask5, buf);
			if (buf.find(Word) != string::npos)
			{
				k++;
				if (k == 1)
				{
					break;
				}
			}

		}
		if (k == 1)
		{
			cout << "Word found! :)";
		}
		else
		{
			cout << "Word not found :(";
		}
	}
	finTask5.close();
}

int main()
{
	Task1();
	Task2();
	Task3();
	Task4();
	Task5();
	return 0;
}

