

#include <iostream>

using namespace std;




    void Task1PrintArray(double arr[], int size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << "  ";
    }
    cout << endl;
}

    void Task2ReplacementArray(int arr[], int size)
    {
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] == 0)
            {
                arr[i] = 1;
            }
            else arr[i] = 0;

        }
    }

    void Task3FillArray(int arr[], int size)
    {
        for (size_t i = 1; i < size; i++)
        {
            arr[0] = 1;
            arr[i] = arr[i-1] + 3;

        }
    }   

    void PrintArray(const int arr[], int size)
    {
        for (size_t i = 0; i < size; i++)
        {
            cout << arr[i] << "  ";
        }
        cout << endl;
    }
    

    void Task4ShiftLeft(int arr[], int size) //сдвиг влево на 1
    {
          
      int first = arr[0];
        
                        
      for (size_t i = 1; i < size; i++)
      {
         arr[i - 1] = arr[i];
      }
        arr[size - 1] = first;
                               
                   
    }

    bool Task5CheckBalance(int arr[], int size)
    {
      
        int AllSumm = 0;

        for (size_t i = 0; i < size; i++)
        {
          AllSumm = AllSumm + arr[i];
        }
        
        for (size_t i = 0; i < size; i++)
        {   
                      
            int RightSumm = 0;
            RightSumm = RightSumm + arr[i];
            if (RightSumm == AllSumm - RightSumm)
            {
                return true;
            }
            
            else return false;
            
        }
       
    }

int main()

{ 
   
    ////////////////////////Task 1//////////////////////////////////////

    const size_t mysize1 = 10;
    double myarr1[] = { 1.9, 2.1, 2.3, 2.5, 2.7, 2.9, 3.1, 3.3, 3.5, 3.7 };
    Task1PrintArray(myarr1, mysize1);
   
    ////////////////////////Task 2//////////////////////////////////////
   
    const size_t mysize2 = 12;
    int myarr2[] = { 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 };
    PrintArray(myarr2, mysize2);
    Task2ReplacementArray(myarr2, mysize2);
    PrintArray(myarr2, mysize2);

    ////////////////////////Task 3//////////////////////////////////////

    const size_t mysize3 = 8;
    int myarr3[mysize3];
    Task3FillArray(myarr3, mysize3);
    PrintArray(myarr3, mysize3);

    ////////////////////////Task 4//////////////////////////////////////

    
    signed int n;
    cout << "Set shift number" << endl;
    cin >> n;
    const size_t mysize4 = 9;
    int myarr4[] = { 11, 22, 33, 44, 55, 66, 77, 88, 99 };
    PrintArray(myarr4, mysize4);
    if (n<0)
    {
        for (size_t i = 0; i < abs(n); i++)// сдвиг влево на n
        {
            Task4ShiftLeft(myarr4, mysize4);
        }
       
    }  else  
    
       for (size_t i = 0; i < mysize4 - abs(n); i++)// сдвиг вправо = сдвигу влево на (mysize4 - n)  
       {
           Task4ShiftLeft(myarr4, mysize4);
       }
            
    PrintArray(myarr4, mysize4);
       
    ////////////////////////Task 5//////////////////////////////////////

    int myarr5[] = { 1, 1, 1, 2, 1};
    const size_t mysize5 = 5;
    PrintArray(myarr5, mysize5);
        
    if (Task5CheckBalance(myarr5, mysize5))
    {
        cout << "True" << endl;
    }else 
        cerr << "False" << endl;
    
    return 0;
    
}


