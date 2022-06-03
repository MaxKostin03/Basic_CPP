
#include <iostream>
#include <fstream>
#include"myLib.h"
using namespace std;

#define Task2Verification(x, y) ((x >= 0, x < y) ? true : false)
#define Task3ArraySize 6
#define Task3SwapINT(a, b) (a = b)

#pragma pack(push, 1)
struct Task4Employee 
{
    int id; 
    unsigned short age; 
    double salary;
};
#pragma pack(pop)


int main()

//===============================Task5(1)=========================================
{
    const int Task1ArrSize = 15;
    float Task1Array[Task1ArrSize]{};
    float FirstNumber = -5.6f;
    MyLib::Task1InitArray(Task1Array, Task1ArrSize, FirstNumber);
    MyLib::Task1PrintArray(Task1Array, Task1ArrSize);
    MyLib::Task1NumberOfElements(Task1Array, Task1ArrSize);


//===============================Task2===========================================

    int x, y;
    cout << "Enter a number to check : ";
    cin >> x;
    cout << "Enter the number of the end of the range : ";
    cin >> y;
    if (Task2Verification(x, y) == 1)
    {
        cout << "True" << endl;
    }
    else cout << "False" << endl;

//===============================Task3============================================

    int i;
    int ARR[Task3ArraySize];
    cout << "Enter an array of integers" << endl;
    for (i = 0; i < Task3ArraySize; i++)
    {
        cout << "a[" << i << "] = ";
        cin >> ARR[i];
    }

    MyLib::Task3PrintArray(ARR, Task3ArraySize);

    for (int i = 1; i < Task3ArraySize; ++i)
    {
        for (int r = 0; r < Task3ArraySize - i; r++)
        {
            if (ARR[r] < ARR[r + 1])
            {
                int temp;
                Task3SwapINT(temp, ARR[r]);
                Task3SwapINT(ARR[r],ARR[r + 1]);
                Task3SwapINT(ARR[r + 1], temp);
            }
        }
    }

    MyLib::Task3PrintArray(ARR, Task3ArraySize);

//===============================Task4============================================

    Task4Employee* pTask4Employee = new Task4Employee;
    pTask4Employee->id = 440014477;
    pTask4Employee->age = 34;
    pTask4Employee->salary = 150000.0;
    
    cout << "ID = " << pTask4Employee->id << endl;
    cout << "AGE = " << pTask4Employee->age << endl;
    cout << "SALARY = " << pTask4Employee->salary << endl;
    cout << "SIZE = " << sizeof(Task4Employee) << endl;

    ofstream fout("struct.txt");
    fout << "ID = " << pTask4Employee->id << endl << "AGE = " << pTask4Employee->age << endl << "SALARY = " << pTask4Employee->salary <<endl;
    fout.close();
        
    delete pTask4Employee;
    return 0;
 }



   
    