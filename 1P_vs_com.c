#pragma warning (disable:4996)

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define BLACK 0
#define BLUE 9
#define RED 12
#define YELLOW 14
#define WHITE 15

#define NUMMAX 7

void setColor(unsigned short color);  //각 사용자의 UI를 위해 컬러 지정을 해주는 함수
int Check_Input(int Input);  //사용자가 입력한 숫자의 자리를 확인하는 함수
void Input_arr(int Input, int arr[NUMMAX]);  //입력한 숫자를 각각의 배열방에 넣는 함수
int set_com(int *arr, int len);  //컴퓨터의 숫자 지정
void input_candidate(int *arr, int start, int num);  //후보키를 배열에 할당
int count_Candidate(int *save);  //처음 후보키의 개수 산출
void end(int *arr);  	//메모리 동적할당 해제와 종료대기


int main() {
	//처음 후보키들이 나올수 있는 경우의 수 계산  -> len, start
	int len = 1;
	int start = count_Candidate(&len);

	//메모리 동적할당을 사용하여 후보키들을 넣을 2차원 배열 선언
	int **NUM_candidate;
	NUM_candidate = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i<2; i++) {
		NUM_candidate[i] = (int*)malloc(sizeof(int) * len);
	}

	//후보키들을 배열방에 할당
	input_candidate(NUM_candidate[0], start, len);

	//com의 숫자를 NUMMAX에 맞게 랜덤으로 지정
	unsigned int NUM_com = set_com(NUM_candidate[0], len);
	
	printf("%d", NUM_com);
	
	//end(NUM_candidate);
	system("PAUSE");
	return 0;
}

void setColor(unsigned short color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int set_com(int * arr, int len)
{
	srand(time(0));  //랜덤한 숫자를 만들기 위해 seed를 초기화
	int num;
	int random = rand() % len;
	num = arr[random];
	return num;
}

void end(int * arr)
{
	for (int i = 0; i < 2; i++) {
		free(arr[i]);
	}
	free(arr);
}

int Check_Input(int Input)
{
	int Cnt = 0;
	while (Input != 0)
	{
		Input /= 10;
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
		Input = Input / 10;
	
}

void input_candidate(int *arr, int start, int len)
{
	int cnt = 0;
	int digit = start;
	int i = 0;
	int temp;
	while (cnt != len) {
		int digit_Cnt[10] = { 0 };
		int flag = 0;
		temp = digit;
		for (int j = 0; j < NUMMAX; j++) {
			digit_Cnt[temp % 10]++;
			temp /= 10;
		}
		for (int c = 0; c < 10; c++)
		{
			if (digit_Cnt[c] > 1)
			{
				flag = 1;
				break;
			}
		}
		if (flag != 1)
		{
			arr[i++] = digit;
			cnt++;
		}
		digit++;
	}
}

int count_Candidate(int *save)
{
	int a = 10;
	for (int i = 0; i < NUMMAX; i++)
	{
		*save *= a--;
	}
	a = 10;
	int NUM_small = 1;
	for (int i = 0; i < NUMMAX - 1; i++)
	{
		NUM_small *= a--;
	}
	*save -= NUM_small;

	int start = 1;
	for (int i = 0; i < NUMMAX - 1; i++)
	{
		start *= 10;
	}
	return start;
}