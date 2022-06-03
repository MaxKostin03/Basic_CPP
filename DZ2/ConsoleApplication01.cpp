
#include <iostream>

int main()
{
	// Task 1

	{
		short int A = 32000;
		int B = 0b0000'1111'0000'1111;
		long long C = 9223372036854775800;
		float D = 3.14f;
		double E{ 2.71828182846 };
		bool Flag{ true };
		char g;
		g = 'M';
	}

	// Task 2

	enum class CrossZero
	{
		Cross,
		Zero,
		Empty
	};

	//  Task 3

	{
		int Array[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	}

	// Task 4

	struct FieldCrossZero

	{
		char PlayerName1[32]; //имя первого игрока
		char PlayerName2[32]; //имя второго игрока
		char Cell[9] = { 1,2,3,4,5,6,7,8,9 }; //номера ячеек поля
		int WinMove[8][3] = { {0,1,2}, {3,4,5}, {2,4,6}, {6,7,8}, {0,3,6}, {1,4,7},{2,5,8}, {0,4,8}, }; //выигрышные варианты
		int Move; //количество ходов

	};



	return 0;
}