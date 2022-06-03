

#include <iostream>
#include <clocale>
using namespace std;

int main()
{

    setlocale(LC_ALL, "Russian");


     //Task 1

    int a;
    int b;
    cout << "Введите первое число" << endl;
    cin >> a;
    cout << "Введите второе число" << endl;
    cin >> b;
        if (a+b >= 10 && a+b <= 20)
        {
         cout << "true" << endl;
        }
        else cout << "false" << endl;

     //Task 2

    int f = 5;
    int e = 5;
        if ((f >= 10 && e >= 10) || f + e == 10)
        {
        cout << "true" << endl;
        }
        else cout << "false" << endl;

     //Task 3

    int h = 0;
    int o = 50;
    cout << "Нечетные числа:";
        while (h++ < o)
        {
            if (h % 2 != 0)
            {
            cout << " " << h;
            //h++;
            }
            }
            cout << endl;

        //Task 4

     int c;
     cout << "Введите число: ";
     cin >> c;
     int i = 1;
     int k = 0;
     while (i <= c)
        {
        if (c % i++ == 0)
        {
            k++;
        }
        else
            {
                continue;
            }
              if (k==3)
              {
                break;
              }
        }
                if (k == 2)
                {
                cout << "Введенное число " << c << " является простым" << endl;
                }
                else 
                cout << "Введенное число " << c << " не является простым" << endl;
                
           
           //Task 5

        int g;
        cout << "Введите год (от 1 до 3000): ";
        cin >> g;
            if ((g < 1) || (g > 3000))
            {
                cout << "Недопустимый ввод";
            }
            else  if ((g % 4 == 0) && (g % 100 != 0) || g % 400 == 0)
            {
                 cout << g << " - високосный год";
            } 
             else  cout << g << " - невисокосный год";

      
            return 0;
    
}



