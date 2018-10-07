#include <stdio.h>
#include <windows.h>

#define BLACK 0
#define BLUE 11
#define RED 12
#define YELLOW 6
#define WHITE 14

#define NUMMAX 3

int Check_Input(int Input);
void Input_arr(int Input, int arr[NUMMAX]);
int Print_arr(int Color, int arr[NUMMAX], int Check[NUMMAX]);

void main()
{
	int player = 0;
	int i;
	int Num;
	int Start_Num[2][NUMMAX];
	for (i = 0; i < 2; i++)
	{
		printf("%dP의 시작 숫자를 입력해 주세요.\n", i + 1);
		do {
			scanf_s("%d", &Num);
		} while (Check_Input(Num));
		Input_arr(Num, Start_Num[i]);
		system("cls");
	}

	int P1[100][NUMMAX];
	int P2[100][NUMMAX];
	int Turn = 0;
	int C;
	do
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("1P가 공격하세요\n");
		do
		{
			scanf_s("%d", &Num);
		} while (Check_Input(Num));
		Input_arr(Num, P1[Turn]);
		system("cls");
		for (i = 0; i <= Turn; i++) {
			C = Print_arr(BLUE, P1[i], Start_Num[1]);
			if (i == Turn)
			{
				printf("\n");
				break;
			}
			printf("\t");
			Print_arr(RED, P2[i], Start_Num[0]);
			printf("\n");
		}
		if (C == 0) break;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
		printf("2P가 공격하세요\n");
		do
		{
			scanf_s("%d", &Num);
		} while (Check_Input(Num));
		Input_arr(Num, P2[Turn]);
		system("cls");
		for (i = 0; i <= Turn; i++) {
			Print_arr(BLUE, P1[i], Start_Num[1]);
			printf("\t");
			C = Print_arr(RED, P2[i], Start_Num[0]);
			printf("\n");
		}
		if (C == 0) continue;

		Turn++;
	} while (C != 0);
}

int Check_Input(int Input)
{
	int Cnt = 0;
	while (Input != 0)
	{
		Input = Input / 10;
		Cnt++;
	}
	if (Cnt == NUMMAX) {
		return 0;
	}
	else if (Cnt < NUMMAX)
	{
		printf("%d자리 늘려 다시 입력해 주세요.", NUMMAX - Cnt);
		return 1;
	}
	else printf("%d자리 줄여 다시 입력해 주세요.", Cnt - NUMMAX); return 1;
}

void Input_arr(int Input, int arr[NUMMAX])
{
	int i;
	for (i = NUMMAX - 1; i >= 0; i--)
	{
		arr[i] = Input % 10;
		Input = Input / 10;
	}
}

int Print_arr(int Color, int arr[NUMMAX], int Check[NUMMAX])
{
	int i;
	for (i = 0; i < NUMMAX; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
		printf("%d ", arr[i]);
	}

	int Strike = 0, Ball = 0;
	int j;
	for (i = 0; i < NUMMAX; i++)
	{
		for (j = 0; j < NUMMAX; j++)
		{
			if (arr[i] == Check[j]) {
				if (i == j)	Strike++;
				else Ball++;
				break;
			}
		}
	}
	if (Strike == NUMMAX) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), YELLOW);
		printf("%dSTRIKE!!\n게임오버\n", NUMMAX);
		return 0;
	}
	else if (Strike + Ball > 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
		printf("%dS %dB", Strike, Ball);
		return 1;
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
		printf("OUT");
		return 1;
	}
}
