



#include <iostream>
using namespace std;
extern int a, b, c, d;
int main()
{

    //Task 4

    
    float m = a * (b + (float(c) / d));
    cout << m << endl;


   
    // Task 2

    int e = 18, n;
    n = (e <= 21) ? 21 - e : (e - 21) * 2;
    cout << n << endl;


    // Task 3 
   
    int Array[3][3][3]{ { {4, 12, 3}, {7, 89, 3}, {9, 66, 92} },
                        { {3, 67, 3}, {8, 777, 3}, {10, 60, 91} },
                        { {2, 34, 3}, {9, 42, 3}, {11, 56, 90} } };  
    int * pArr = nullptr;
    pArr = &Array[0][0][0];
    int y;
    y = *(pArr+13);
    cout << "y = " << y << endl;


    return 0;
}

