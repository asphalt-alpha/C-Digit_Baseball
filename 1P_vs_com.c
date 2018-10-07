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

void setColor(unsigned short color);  //�� ������� UI�� ���� �÷� ������ ���ִ� �Լ�
int Check_Input(int Input);  //����ڰ� �Է��� ������ �ڸ��� Ȯ���ϴ� �Լ�
void Input_arr(int Input, int arr[NUMMAX]);  //�Է��� ���ڸ� ������ �迭�濡 �ִ� �Լ�
int set_com(int *arr, int len);  //��ǻ���� ���� ����
void input_candidate(int *arr, int start, int num);  //�ĺ�Ű�� �迭�� �Ҵ�
int count_Candidate(int *save);  //ó�� �ĺ�Ű�� ���� ����
void end(int *arr);  	//�޸� �����Ҵ� ������ ������


int main() {
	//ó�� �ĺ�Ű���� ���ü� �ִ� ����� �� ���  -> len, start
	int len = 1;
	int start = count_Candidate(&len);

	//�޸� �����Ҵ��� ����Ͽ� �ĺ�Ű���� ���� 2���� �迭 ����
	int **NUM_candidate;
	NUM_candidate = (int**)malloc(sizeof(int*) * 2);
	for (int i = 0; i<2; i++) {
		NUM_candidate[i] = (int*)malloc(sizeof(int) * len);
	}

	//�ĺ�Ű���� �迭�濡 �Ҵ�
	input_candidate(NUM_candidate[0], start, len);

	//com�� ���ڸ� NUMMAX�� �°� �������� ����
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
	srand(time(0));  //������ ���ڸ� ����� ���� seed�� �ʱ�ȭ
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
		printf("%d�ڸ� �÷� �ٽ� �Է��� �ּ���.", NUMMAX - Cnt);
		return 1;
	}
	else printf("%d�ڸ� �ٿ� �ٽ� �Է��� �ּ���.", Cnt - NUMMAX); return 1;
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