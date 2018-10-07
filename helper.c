#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


#define NUMMAX 3 // 7자리 수 까지 입력가능

int count_Candidate(int *save);  //처음 후보키의 개수 산출
void input_Arr(int *arr, int start, int num);  //후보키를 배열에 할당
int Check_Input(int strike, int ball);  //스트라이크,볼 카운트가 제대로 입력됬는지 확인 
int checking(int arr, int input[NUMMAX], int s_cnt, int b_cnt, int turn);  //후보키와 입력키 비교
void change_Arr(int arr, int output[NUMMAX]);  //숫자를 각각의 n자리의 배열방에 할당
int change_digit(int input[NUMMAX]);  //각각의 배열방의 숫자를 하나의 숫자로 변환


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
	input_Arr(NUM_candidate[0], start, len);

	//실행
	int input[NUMMAX];  //사용자의 숫자가 저장되는 배열
	int strike, ball;  //사용자의 카운트가 저장되는 변수
	int count[2] = { 0 }; //필터링을 거친 후보키들의 개수가 저장
	count[0] = len;  //초기설정
	int turn = 0;  //2차원 배열의 0행, 1행이 토글 될 수 있도록 선언

	while (count[(turn + 1) % 2] != 1) {

		//사용자의 입력
		printf("공격하실 숫자 %d 자리와 Strike, Ball 카운트를 차례대로 입력하세요\n", NUMMAX);
		for (int i = 0; i < NUMMAX; i++)
		{
			scanf_s("%01d", &input[i]);
		}
		do {
			scanf_s("%d %d", &strike, &ball);
		} while (Check_Input(strike, ball));
		system("cls");

		//비교
		count[(turn + 1) % 2] = 0;
		int j = 0;
		for (int i = 0; i < count[turn]; i++)
		{
			if (checking(NUM_candidate[turn][i], input, strike, ball, turn) == 0) {
				NUM_candidate[(turn + 1) % 2][j++] = NUM_candidate[turn][i];
				count[(turn + 1) % 2]++;
			}
		}

		for (int i = 0; i < count[(turn + 1) % 2]; i++) {
			printf("%03d\n", NUM_candidate[(turn + 1) % 2][i]);
		}

		turn = (turn + 1) % 2;
	}

	//메모리 동적할당 해제
	for (int i = 0; i < 2; i++) {
		free(NUM_candidate[i]);
	}
	free(NUM_candidate);
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

void input_Arr(int *arr, int start, int len)
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

int checking(int arr, int input[NUMMAX], int s_cnt, int b_cnt, int turn)
{
	int digit[NUMMAX];
	int i = 0;
	change_Arr(arr, digit);

	int s = 0, b = 0;
	for (int i = 0; i < NUMMAX; i++)
	{
		for (int j = 0; j < NUMMAX; j++)
		{
			if (input[i] == digit[j])
			{
				if (i == j) s++;
				else b++;
				break;
			}
		}
	}

	if (s_cnt == s && b_cnt == b)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void change_Arr(int arr, int output[NUMMAX])
{
	int num = arr;
	for (int i = NUMMAX - 1; i >= 0; i--) {
		output[i] = num % 10;
		num /= 10;
	}
}

int change_digit(int input[NUMMAX])
{
	int num = 0;
	int j = 1;
	for (int i = NUMMAX - 1; i >= 0; i--) {
		num += input[i] * j;
		j *= 10;
	}
	return num;
}

int Check_Input(int strike, int ball)
{
	if (strike + ball <= NUMMAX) {
		return 0;
	}
	else printf("다시 입력해 주세요.\n"); return 1;
}